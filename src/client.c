/*
 *  ircd-hybrid: an advanced Internet Relay Chat Daemon(ircd).
 *  client.c: Controls clients.
 *
 *  Copyright (C) 2002 by the past and present ircd coders, and others.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 *  USA
 *
 *  $Id$
 */

#include "stdinc.h"
#include "client.h"
#include "channel_mode.h"
#include "common.h"
#include "hash.h"
#include "ircd.h"
#include "s_gline.h"
#include "numeric.h"
#include "packet.h"
#include "s_auth.h"
#include "s_conf.h"
#include "parse_aline.h"
#include "s_serv.h"
#include "send.h"
#include "whowas.h"
#include "s_user.h"
#include "hostmask.h"
#include "listener.h"
#include "userhost.h"
#include "s_stats.h"
#include "watch.h"

dlink_list listing_client_list = { NULL, NULL, 0 };
/* Pointer to beginning of Client list */
dlink_list global_client_list = {NULL, NULL, 0};
/* unknown/client pointer lists */
dlink_list unknown_list = {NULL, NULL, 0};
dlink_list local_client_list = {NULL, NULL, 0};
dlink_list serv_list = {NULL, NULL, 0};
dlink_list global_serv_list = {NULL, NULL, 0};
dlink_list oper_list = {NULL, NULL, 0};

static EVH check_pings;

static BlockHeap *client_heap  = NULL;
static BlockHeap *lclient_heap = NULL;

static dlink_list dead_list  = { NULL, NULL, 0};
static dlink_list abort_list = { NULL, NULL, 0};

static dlink_node *eac_next;  /* next aborted client to exit */

static void check_pings_list(dlink_list *);
static void check_unknowns_list(void);
static void close_connection(struct Client *);
static void ban_them(struct Client *client_p, struct ConfItem *conf);
static void del_all_accepts(struct Client *);

/* init_client()
 *
 * inputs	- NONE
 * output	- NONE
 * side effects	- initialize client free memory
 */
void
init_client(void)
{
  /* start off the check ping event ..  -- adrian
   * Every 30 seconds is plenty -- db
   */
  client_heap = BlockHeapCreate("client", sizeof(struct Client), CLIENT_HEAP_SIZE);
  lclient_heap = BlockHeapCreate("local client", sizeof(struct LocalUser), LCLIENT_HEAP_SIZE);
  eventAdd("check_pings", check_pings, NULL, 5);
}

/*
 * make_client - create a new Client struct and set it to initial state.
 *
 *      from == NULL,   create local client (a client connected
 *                      to a socket).
 *                      WARNING: This leaves the client in a dangerous
 *                      state where fd == -1, dead flag is not set and
 *                      the client is on the unknown_list; therefore,
 *                      the first thing to do after calling make_client(NULL)
 *                      is setting fd to something reasonable. -adx
 *
 *      from,   create remote client (behind a socket
 *                      associated with the client defined by
 *                      'from'). ('from' is a local client!!).
 */
struct Client *
make_client(struct Client *from)
{
  struct Client *client_p = BlockHeapAlloc(client_heap);

  if (from == NULL)
  {
    client_p->from  = client_p; /* 'from' of local client is self! */
    client_p->since = client_p->lasttime = client_p->firsttime = CurrentTime;

    client_p->localClient = BlockHeapAlloc(lclient_heap);
    /* as good a place as any... */
    dlinkAdd(client_p, make_dlink_node(), &unknown_list);
  }
  else
    client_p->from = from; /* 'from' of local client is self! */

  client_p->hnext  = client_p;
  client_p->status = STAT_UNKNOWN;
  strcpy(client_p->username, "unknown");

  return client_p;
}

/*
 * free_client
 *
 * inputs	- pointer to client
 * output	- NONE
 * side effects	- client pointed to has its memory freed
 */
static void
free_client(struct Client *client_p)
{
  assert(client_p != NULL);
  assert(client_p != &me);
  assert(client_p->hnext == client_p);
  assert(client_p->invited.head == NULL);
  assert(client_p->channel.head == NULL);
  assert(dlink_list_length(&client_p->invited) == 0);
  assert(dlink_list_length(&client_p->channel) == 0);

  MyFree(client_p->away);
  MyFree(client_p->serv);

  if (MyConnect(client_p))
  {
    assert(IsClosing(client_p) && IsDead(client_p));

    MyFree(client_p->localClient->response);
    MyFree(client_p->localClient->auth_oper);

    /*
     * clean up extra sockets from P-lines which have been discarded.
     */
    if (client_p->localClient->listener)
    {
      assert(0 < client_p->localClient->listener->ref_count);
      if (0 == --client_p->localClient->listener->ref_count &&
          !client_p->localClient->listener->active) 
        free_listener(client_p->localClient->listener);
    }

    dbuf_clear(&client_p->localClient->buf_recvq);
    dbuf_clear(&client_p->localClient->buf_sendq);

    BlockHeapFree(lclient_heap, client_p->localClient);
  }

  BlockHeapFree(client_heap, client_p);
}

/*
 * check_pings - go through the local client list and check activity
 * kill off stuff that should die
 *
 * inputs       - NOT USED (from event)
 * output       - next time_t when check_pings() should be called again
 * side effects - 
 *
 *
 * A PING can be sent to clients as necessary.
 *
 * Client/Server ping outs are handled.
 */

/*
 * Addon from adrian. We used to call this after nextping seconds,
 * however I've changed it to run once a second. This is only for
 * PING timeouts, not K/etc-line checks (thanks dianora!). Having it
 * run once a second makes life a lot easier - when a new client connects
 * and they need a ping in 4 seconds, if nextping was set to 20 seconds
 * we end up waiting 20 seconds. This is stupid. :-)
 * I will optimise (hah!) check_pings() once I've finished working on
 * tidying up other network IO evilnesses.
 *     -- adrian
 */

static void
check_pings(void *notused)
{               
  check_pings_list(&local_client_list);
  check_pings_list(&serv_list);
  check_unknowns_list();
}

/* check_pings_list()
 *
 * inputs	- pointer to list to check
 * output	- NONE
 * side effects	- 
 */
static void
check_pings_list(dlink_list *list)
{
  char scratch[32];        /* way too generous but... */
  struct Client *client_p; /* current local client_p being examined */
  int ping, pingwarn;      /* ping time value from client */
  dlink_node *ptr, *next_ptr;

  DLINK_FOREACH_SAFE(ptr, next_ptr, list->head)
  {
    client_p = ptr->data;

    /*
    ** Note: No need to notify opers here. It's
    ** already done when "FLAGS_DEADSOCKET" is set.
    */
    if (IsDead(client_p))
    {
      /* Ignore it, its been exited already */
      continue; 
    }

    if (client_p->localClient->reject_delay > 0)
    {
      if (client_p->localClient->reject_delay <= CurrentTime)
	exit_client(client_p, &me, "Rejected");
      continue;
    }

    if (GlobalSetOptions.idletime && IsClient(client_p))
    {
      if (!IsExemptKline(client_p) && !IsOper(client_p) &&
          !IsIdlelined(client_p) &&
	  ((CurrentTime - client_p->localClient->last) > GlobalSetOptions.idletime))
      {
        struct ConfItem *conf;
        struct AccessItem *aconf;

        conf = make_conf_item(KLINE_TYPE);
        aconf = &conf->conf.AccessItem;

        DupString(aconf->host, client_p->host);
        DupString(aconf->reason, "idle exceeder");
        DupString(aconf->user, client_p->username);
        aconf->hold = CurrentTime + 60;
        add_temp_line(conf);

        sendto_realops_flags(UMODE_ALL, L_ALL,
                             "Idle time limit exceeded for %s - temp k-lining",
                             get_client_name(client_p, HIDE_IP));
        exit_client(client_p, &me, aconf->reason);
        continue;
      }
    }

    if (!IsRegistered(client_p))
      ping = CONNECTTIMEOUT, pingwarn = 0;
    else
      ping = get_client_ping(client_p, &pingwarn);

    if (ping < CurrentTime - client_p->lasttime)
    {
      if (!IsPingSent(client_p))
      {
	/*
	 * if we havent PINGed the connection and we havent
	 * heard from it in a while, PING it to make sure
	 * it is still alive.
	 */
	SetPingSent(client_p);
	ClearPingWarning(client_p);
	client_p->lasttime = CurrentTime - ping;
	sendto_one(client_p, "PING :%s", ID_or_name(&me, client_p));
      }
      else
      {
        if (CurrentTime - client_p->lasttime >= 2 * ping)
        {
          /*
           * If the client/server hasn't talked to us in 2*ping seconds
           * and it has a ping time, then close its connection.
           */
          if (IsServer(client_p) || IsHandshake(client_p))
	  {
	    sendto_realops_flags(UMODE_ALL, L_ADMIN,
				 "No response from %s, closing link",
				 get_client_name(client_p, HIDE_IP));
	    sendto_realops_flags(UMODE_ALL, L_OPER,
				 "No response from %s, closing link",
				 get_client_name(client_p, MASK_IP));
	    ilog(L_NOTICE, "No response from %s, closing link",
		 get_client_name(client_p, HIDE_IP));
	  }
          ircsprintf(scratch, "Ping timeout: %d seconds",
                     (int)(CurrentTime - client_p->lasttime));

          exit_client(client_p, &me, scratch);
        }
        else if (!IsPingWarning(client_p) && pingwarn > 0 &&
	         (IsServer(client_p) || IsHandshake(client_p)) &&
	         CurrentTime - client_p->lasttime >= ping + pingwarn)
        {
          /*
           * If the server hasn't replied in pingwarn seconds after sending
           * the PING, notify the opers so that they are aware of the problem.
           */
	  SetPingWarning(client_p);
          sendto_realops_flags(UMODE_ALL, L_ADMIN,
	                       "Warning, no response from %s in %d seconds",
	                       get_client_name(client_p, HIDE_IP), pingwarn);
	  sendto_realops_flags(UMODE_ALL, L_OPER,
	                       "Warning, no response from %s in %d seconds",
	                       get_client_name(client_p, MASK_IP), pingwarn);
          ilog(L_NOTICE, "No response from %s in %d seconds",
	       get_client_name(client_p, HIDE_IP), pingwarn);
        }
      }
    }
  }
}

/* check_unknowns_list()
 *
 * inputs       - pointer to list of unknown clients
 * output       - NONE
 * side effects - unknown clients get marked for termination after n seconds
 */
static void
check_unknowns_list(void)
{
  dlink_node *ptr, *next_ptr;

  DLINK_FOREACH_SAFE(ptr, next_ptr, unknown_list.head)
  {
    struct Client *client_p = ptr->data;

    if (client_p->localClient->reject_delay > 0)
    {
      if (client_p->localClient->reject_delay <= CurrentTime)
        exit_client(client_p, &me, "Rejected");
      continue;
    }

    /* Check UNKNOWN connections - if they have been in this state
     * for > 30s, close them.
     */
    if (client_p->firsttime ? ((CurrentTime - client_p->firsttime) > 30) : 0)
      exit_client(client_p, &me, "Connection timed out");
  }
}

/* check_conf_klines()
 *
 * inputs       - NONE
 * output       - NONE
 * side effects - Check all connections for a pending kline against the
 * 		  client, exit the client if a kline matches.
 */
void 
check_conf_klines(void)
{               
  struct Client *client_p = NULL;       /* current local client_p being examined */
  struct AccessItem *aconf = NULL;
  struct ConfItem *conf = NULL;
  dlink_node *ptr, *next_ptr;

  DLINK_FOREACH_SAFE(ptr, next_ptr, local_client_list.head)
  {
    client_p = ptr->data;

    /* If a client is already being exited
     */
    if (IsDead(client_p) || !IsClient(client_p))
      continue;

    /* if there is a returned struct ConfItem then kill it */
    if ((aconf = find_dline_conf(&client_p->localClient->ip,
                                  client_p->localClient->aftype)) != NULL)
    {
      if (aconf->status & CONF_EXEMPTDLINE)
        continue;

      conf = aconf->conf_ptr;
      ban_them(client_p, conf);
      continue; /* and go examine next fd/client_p */
    }

    if (ConfigFileEntry.glines && (aconf = find_gline(client_p)) != NULL)
    {
      if (IsExemptKline(client_p) || IsExemptGline(client_p))
      {
        sendto_realops_flags(UMODE_ALL, L_ALL,
                             "GLINE over-ruled for %s, client is %cline_exempt",
                             get_client_name(client_p, HIDE_IP),
                             IsExemptKline(client_p) ? 'k' : 'g');
        continue;
      }

      conf = aconf->conf_ptr;
      ban_them(client_p, conf);
      /* and go examine next fd/client_p */    
      continue;
    } 

    if ((aconf = find_kill(client_p)) != NULL) 
    {

      /* if there is a returned struct AccessItem.. then kill it */
      if (IsExemptKline(client_p))
      {
        sendto_realops_flags(UMODE_ALL, L_ALL,
                             "KLINE over-ruled for %s, client is kline_exempt",
                             get_client_name(client_p, HIDE_IP));
        continue;
      }

      conf = aconf->conf_ptr;
      ban_them(client_p, conf);
      continue; 
    }

    /* if there is a returned struct MatchItem then kill it */
    if ((conf = find_matching_name_conf(XLINE_TYPE,  client_p->info,
                                        NULL, NULL, 0)) != NULL ||
        (conf = find_matching_name_conf(RXLINE_TYPE, client_p->info,
                                        NULL, NULL, 0)) != NULL)
    {
      ban_them(client_p, conf);
      continue;
    }
  }

  /* also check the unknowns list for new dlines */
  DLINK_FOREACH_SAFE(ptr, next_ptr, unknown_list.head)
  {
    client_p = ptr->data;

    if ((aconf = find_dline_conf(&client_p->localClient->ip,
                                  client_p->localClient->aftype)))
    {
      if (aconf->status & CONF_EXEMPTDLINE)
        continue;

      exit_client(client_p, &me, "D-lined");
    }
  }
}

/*
 * ban_them
 *
 * inputs	- pointer to client to ban
 * 		- pointer to ConfItem
 * output	- NONE
 * side effects	- given client_p is banned
 */
static void
ban_them(struct Client *client_p, struct ConfItem *conf)
{
  const char *user_reason = NULL;	/* What is sent to user */
  const char *channel_reason = NULL;	/* What is sent to channel */
  struct AccessItem *aconf = NULL;
  struct MatchItem *xconf = NULL;
  const char *type_string = NULL;
  const char dline_string[] = "D-line";
  const char kline_string[] = "K-line";
  const char gline_string[] = "G-line";
  const char xline_string[] = "X-line";

  switch (conf->type)
  {
    case RKLINE_TYPE:
    case KLINE_TYPE:
      type_string = kline_string;
      aconf = &conf->conf.AccessItem;
      break;
    case DLINE_TYPE:
      type_string = dline_string;
      aconf = &conf->conf.AccessItem;
      break;
    case GLINE_TYPE:
      type_string = gline_string;
      aconf = &conf->conf.AccessItem;
      break;
    case RXLINE_TYPE:
    case XLINE_TYPE:
      type_string = xline_string;
      xconf = &conf->conf.MatchItem;
      ++xconf->count;
      break;
    default:
      assert(0);
      break;
  }

  if (ConfigFileEntry.kline_with_reason)
  {
    if (aconf != NULL)
      user_reason = aconf->reason ? aconf->reason : type_string;
    if (xconf != NULL)
      user_reason = xconf->reason ? xconf->reason : type_string;
  }
  else
    user_reason = type_string;

  if (ConfigFileEntry.kline_reason != NULL)
    channel_reason = ConfigFileEntry.kline_reason;
  else
    channel_reason = user_reason;

  sendto_realops_flags(UMODE_ALL, L_ALL, "%s active for %s",
                       type_string, get_client_name(client_p, HIDE_IP));

  if (IsClient(client_p))
    sendto_one(client_p, form_str(ERR_YOUREBANNEDCREEP),
	       me.name, client_p->name, user_reason);

  exit_client(client_p, &me, channel_reason);
}

/* update_client_exit_stats()
 *
 * input	- pointer to client
 * output	- NONE
 * side effects	- 
 */
static void
update_client_exit_stats(struct Client *client_p)
{
  if (IsServer(client_p))
  {
    sendto_realops_flags(UMODE_EXTERNAL, L_ALL, 
			 "Server %s split from %s",
			 client_p->name, client_p->servptr->name);
  }
  else if (IsClient(client_p))
  {
    --Count.total;
    if (IsOper(client_p))
      --Count.oper;
    if (IsInvisible(client_p))
      --Count.invisi;
  }

  if (splitchecking && !splitmode)
    check_splitmode(NULL);
}

/* find_person()
 *
 * inputs	- pointer to name
 * output	- return client pointer
 * side effects - find person by (nick)name
 */
/* XXX - ugly wrapper */
struct Client *
find_person(const struct Client *client_p, const char *name)
{
  struct Client *c2ptr;

  if (IsDigit(*name))
  {
    if ((c2ptr = hash_find_id(name)) != NULL)
    {
      /* invisible users shall not be found by UID guessing */
      if (IsInvisible(c2ptr) && !IsServer(client_p))
        c2ptr = NULL;
    }
  }
  else
    c2ptr = find_client(name);

  return ((c2ptr != NULL && IsClient(c2ptr)) ? c2ptr : NULL);
}

/*
 * find_chasing - find the client structure for a nick name (user) 
 *      using history mechanism if necessary. If the client is not found, 
 *      an error message (NO SUCH NICK) is generated. If the client was found
 *      through the history, chasing will be 1 and otherwise 0.
 */
struct Client *
find_chasing(struct Client *client_p, struct Client *source_p, const char *user, int *chasing)
{
  struct Client *who = find_person(client_p, user);

  if (chasing)
    *chasing = 0;

  if (who)
    return(who);

  if (IsDigit(*user))
    return(NULL);

  if ((who = get_history(user,
			(time_t)ConfigFileEntry.kill_chase_time_limit))
			 == NULL)
  {
    sendto_one(source_p, form_str(ERR_NOSUCHNICK),
               me.name, source_p->name, user);
    return(NULL);
  }

  if (chasing)
    *chasing = 1;

  return(who);
}

/*
 * get_client_name -  Return the name of the client
 *    for various tracking and
 *      admin purposes. The main purpose of this function is to
 *      return the "socket host" name of the client, if that
 *        differs from the advertised name (other than case).
 *        But, this can be used to any client structure.
 *
 * NOTE 1:
 *        Watch out the allocation of "nbuf", if either source_p->name
 *        or source_p->sockhost gets changed into pointers instead of
 *        directly allocated within the structure...
 *
 * NOTE 2:
 *        Function return either a pointer to the structure (source_p) or
 *        to internal buffer (nbuf). *NEVER* use the returned pointer
 *        to modify what it points!!!
 */
const char *
get_client_name(struct Client *client, int showip)
{
  static char nbuf[HOSTLEN * 2 + USERLEN + 5];

  assert(client != NULL);

  if (irccmp(client->name, client->host) == 0)
    return(client->name);

  if (ConfigServerHide.hide_server_ips)
    if (IsServer(client) || IsConnecting(client) || IsHandshake(client))
      showip = MASK_IP;

  if (ConfigFileEntry.hide_spoof_ips)
    if (showip == SHOW_IP && IsIPSpoof(client))
      showip = MASK_IP;

  /* And finally, let's get the host information, ip or name */
  switch (showip)
  {
    case SHOW_IP:
      if (MyConnect(client))
      {
        ircsprintf(nbuf, "%s[%s@%s]", client->name, client->username,
                   client->sockhost);
        break;
      }
    case MASK_IP:
      ircsprintf(nbuf, "%s[%s@255.255.255.255]", client->name,
                 client->username);
      break;
    default:
      ircsprintf(nbuf, "%s[%s@%s]", client->name, client->username,
                 client->host);
  }

  return(nbuf);
}

void
free_exited_clients(void)
{
  dlink_node *ptr, *next;
  struct Client *target_p;
  
  DLINK_FOREACH_SAFE(ptr, next, dead_list.head)
  {
    target_p = ptr->data;

    if (ptr->data == NULL)
    {
      sendto_realops_flags(UMODE_ALL, L_ALL,
                           "Warning: null client on dead_list!");
      dlinkDelete(ptr, &dead_list);
      free_dlink_node(ptr);
      continue;
    }

    free_client(target_p);
    dlinkDelete(ptr, &dead_list);
    free_dlink_node(ptr);
  }
}

/*
 * Exit one client, local or remote. Assuming all dependents have
 * been already removed, and socket closed for local client.
 *
 * The only messages generated are QUITs on channels.
 */
static void
exit_one_client(struct Client *source_p, const char *quitmsg)
{
  dlink_node *lp = NULL, *next_lp = NULL;

  assert(!IsMe(source_p));

  if (IsServer(source_p))
  {
    dlinkDelete(&source_p->lnode, &source_p->servptr->serv->servers);

    if ((lp = dlinkFindDelete(&global_serv_list, source_p)) != NULL)
      free_dlink_node(lp);

    if (!MyConnect(source_p))
    {
      source_p->from->serv->dep_servers--;
      assert(source_p->from->serv->dep_servers > 0);
    }
  }
  else if (IsClient(source_p))
  {
    if (source_p->servptr->serv != NULL)
      dlinkDelete(&source_p->lnode, &source_p->servptr->serv->users);

    /* If a person is on a channel, send a QUIT notice
    ** to every client (person) on the same channel (so
    ** that the client can show the "**signoff" message).
    ** (Note: The notice is to the local clients *only*)
    */
    sendto_common_channels_local(source_p, 0, ":%s!%s@%s QUIT :%s",
                                 source_p->name, source_p->username,
                                 source_p->host, quitmsg);
    DLINK_FOREACH_SAFE(lp, next_lp, source_p->channel.head)
      remove_user_from_channel(lp->data);

    /* Clean up invitefield */
    DLINK_FOREACH_SAFE(lp, next_lp, source_p->invited.head)
      del_invite(lp->data, source_p);

    add_history(source_p, 0);
    off_history(source_p);

    assert(source_p->whowas.head == NULL);
    assert(source_p->whowas.tail == NULL);

    /* Do local vs. remote processing here */
    if (MyConnect(source_p))
    {
      /* Clean up allow lists */
      del_all_accepts(source_p);
    }
    else
    {
      source_p->from->serv->dep_users--;
      assert(source_p->from->serv->dep_users >= 0);
    }
  }

  /* Remove source_p from the client lists */
  if (HasID(source_p))
    hash_del_id(source_p);
  if (source_p->name[0])
    hash_del_client(source_p);

  hash_check_watch(source_p, RPL_LOGOFF);

  if (IsUserHostIp(source_p))
    delete_user_host(source_p->username, source_p->host, !MyConnect(source_p));

  /* remove from global client list
   * NOTE: source_p->node.next cannot be NULL if the client is added
   *       to global_client_list (there is always &me at its end)
   */
  if (source_p != NULL && source_p->node.next != NULL)
    dlinkDelete(&source_p->node, &global_client_list);

  update_client_exit_stats(source_p);

  /* Check to see if the client isn't already on the dead list */
  assert(dlinkFind(&dead_list, source_p) == NULL);

  /* add to dead client dlist */
  SetDead(source_p);
  dlinkAdd(source_p, make_dlink_node(), &dead_list);
}

/* Recursively send QUITs and SQUITs for source_p and all its dependent clients
 * and servers to those servers that need them.  A server needs the client
 * QUITs if it can't figure them out from the SQUIT (ie pre-TS4) or if it
 * isn't getting the SQUIT because of @#(*&@)# hostmasking.  With TS4, once
 * a link gets a SQUIT, it doesn't need any QUIT/SQUITs for clients depending
 * on that one -orabidoo
 *
 * This is now called on each local server -adx
 */
static void
recurse_send_quits(struct Client *original_source_p, struct Client *source_p,
                   struct Client *from, struct Client *to, const char *comment,
                   const char *splitstr, const char *myname)
{
  dlink_node *ptr, *next;
  struct Client *target_p;
  int hidden = match(myname, source_p->name);

  assert(to != source_p);  /* should be already removed from serv_list */

  /* If this server can handle quit storm (QS) removal
   * of dependents, just send the SQUIT
   *
   * Always check *all* dependent servers if some of them are
   * hidden behind fakename. If so, send out the QUITs -adx
   */
  if (hidden || !IsCapable(to, CAP_QS))
    DLINK_FOREACH_SAFE(ptr, next, source_p->serv->users.head)
    {
      target_p = ptr->data;
      sendto_one(to, ":%s QUIT :%s", target_p->name, splitstr);
    }

  DLINK_FOREACH_SAFE(ptr, next, source_p->serv->servers.head)
    recurse_send_quits(original_source_p, ptr->data, from, to,
                       comment, splitstr, myname);

  if (!hidden && ((source_p == original_source_p && to != from) ||
                  !IsCapable(to, CAP_QS)))
  {
    /* don't use a prefix here - we have to be 100% sure the message
     * will be accepted without Unknown prefix etc.. */
    sendto_one(to, "SQUIT %s :%s", ID_or_name(source_p, to), comment);
  }
}

/* 
 * Remove all clients that depend on source_p; assumes all (S)QUITs have
 * already been sent.  we make sure to exit a server's dependent clients 
 * and servers before the server itself; exit_one_client takes care of 
 * actually removing things off llists.   tweaked from +CSr31  -orabidoo
 */
static void
recurse_remove_clients(struct Client *source_p, const char *quitmsg)
{
  dlink_node *ptr, *next;

  DLINK_FOREACH_SAFE(ptr, next, source_p->serv->users.head)
    exit_one_client(ptr->data, quitmsg);

  DLINK_FOREACH_SAFE(ptr, next, source_p->serv->servers.head)
  {
    recurse_remove_clients(ptr->data, quitmsg);
    exit_one_client(ptr->data, quitmsg);
  }

  assert(source_p->serv->dep_servers == 1);
  assert(source_p->serv->dep_users == 0);
}

/*
** Remove *everything* that depends on source_p, from all lists, and sending
** all necessary QUITs and SQUITs.  source_p itself is still on the lists,
** and its SQUITs have been sent except for the upstream one  -orabidoo
*/
static void
remove_dependents(struct Client *source_p, struct Client *from,
                  const char *comment, const char *splitstr)
{
  struct Client *to;
  struct ConfItem *conf;
  struct AccessItem *aconf;
  static char myname[HOSTLEN+1];
  dlink_node *ptr;

  DLINK_FOREACH(ptr, serv_list.head)
  {
    to = ptr->data;

    if ((conf = to->serv->sconf) != NULL)
    {
      aconf = &conf->conf.AccessItem;
      strlcpy(myname, my_name_for_link(aconf), sizeof(myname));
    }
    else
      strlcpy(myname, me.name, sizeof(myname));
    recurse_send_quits(source_p, source_p, from, to,
                       comment, splitstr, myname);
  }

  recurse_remove_clients(source_p, splitstr);
}

/*
 * exit_client - exit a client of any type. Generally, you can use
 * this on any struct Client, regardless of its state.
 *
 * Note, you shouldn't exit remote _users_ without first doing
 * SetKilled and propagating a kill or similar message. However,
 * it is perfectly correct to call exit_client to force a _server_
 * quit (either local or remote one).
 *
 * inputs:       - a client pointer that is going to be exited
 *               - for servers, the second argument is a pointer to who
 *                 is firing the server. This side won't get any generated
 *                 messages. NEVER NULL!
 * output:       none
 * side effects: the client is delinked from all lists, disconnected,
 *               and the rest of IRC network is notified of the exit.
 *               Client memory is scheduled to be freed
 */
void
exit_client(struct Client *source_p, struct Client *from, const char *comment)
{
  dlink_node *m;

  if (MyConnect(source_p))
  {
    /* DO NOT REMOVE. exit_client can be called twice after a failed
     * read/write.
     */
    if (IsClosing(source_p))
      return;

    SetClosing(source_p);

    if (IsIpHash(source_p))
      remove_one_ip(&source_p->localClient->ip);

    delete_auth(source_p);

    /* This source_p could have status of one of STAT_UNKNOWN, STAT_CONNECTING
     * STAT_HANDSHAKE or STAT_UNKNOWN
     * all of which are lumped together into unknown_list
     *
     * In all above cases IsRegistered() will not be true.
     */
    if (!IsRegistered(source_p))
    {
      if ((m = dlinkFindDelete(&unknown_list, source_p)) != NULL)
        free_dlink_node(m);
    }
    else if (IsClient(source_p))
    {
      Count.local--;

      if (IsOper(source_p))
      {
        if ((m = dlinkFindDelete(&oper_list, source_p)) != NULL)
          free_dlink_node(m);
      }

      dlinkDelete(&source_p->localClient->lclient_node, &local_client_list);
      if (source_p->localClient->list_task != NULL)
        free_list_task(source_p->localClient->list_task, source_p);
      hash_del_watch_list(source_p);
      sendto_realops_flags(UMODE_CCONN, L_ALL, "Client exiting: %s (%s@%s) [%s] [%s]",
                           source_p->name, source_p->username, source_p->host, comment,
                           ConfigFileEntry.hide_spoof_ips && IsIPSpoof(source_p) ?
                           "255.255.255.255" : source_p->sockhost);
    }

    /* As soon as a client is known to be a server of some sort
     * it has to be put on the serv_list, or SJOIN's to this new server
     * from the connect burst will not be seen.
     */
    if (IsServer(source_p) || IsConnecting(source_p) ||
        IsHandshake(source_p))
    {
      if ((m = dlinkFindDelete(&serv_list, source_p)) != NULL)
      {
        free_dlink_node(m);
        unset_chcap_usage_counts(source_p);
      }

      if (IsServer(source_p))
      {
        Count.myserver--;
        if (ServerInfo.hub)
          remove_lazylink_flags(source_p->localClient->serverMask);
        else
          uplink = NULL;
      }
    }

    log_user_exit(source_p);

    if (!IsDead(source_p))
    {
      if (IsServer(source_p))
      {
        /* for them, we are exiting the network */
        sendto_one(source_p, ":%s SQUIT %s :%s",
	           ID_or_name(from, source_p), me.name, comment);
      }

      sendto_one(source_p, "ERROR :Closing Link: %s (%s)",
                 source_p->host, comment);
    }

    /*
    ** Currently only server connections can have
    ** depending remote clients here, but it does no
    ** harm to check for all local clients. In
    ** future some other clients than servers might
    ** have remotes too...
    **
    ** Close the Client connection first and mark it
    ** so that no messages are attempted to send to it.
    ** Remember it makes source_p->from == NULL.
    */
    close_connection(source_p);
  }

  if (IsServer(source_p))
  {
    char splitstr[HOSTLEN + HOSTLEN + 2];

    /* This shouldn't ever happen */
    assert(source_p->serv != NULL && source_p->servptr != NULL);

    if (ConfigServerHide.hide_servers)
      /* set netsplit message to "*.net *.split" to still show 
       * that its a split, but hide the servers splitting
       */
      strcpy(splitstr, "*.net *.split");
    else
      snprintf(splitstr, sizeof(splitstr), "%s %s",
               source_p->servptr->name, source_p->name);

    remove_dependents(source_p, from->from, comment, splitstr);

    if (source_p->servptr == &me)
    {
      sendto_realops_flags(UMODE_ALL, L_ALL,
                           "%s was connected for %d seconds.  %llu/%llu sendK/recvK.",
                           source_p->name, (int)(CurrentTime - source_p->firsttime),
                           source_p->localClient->send.bytes >> 10,
                           source_p->localClient->recv.bytes >> 10);
      ilog(L_NOTICE, "%s was connected for %d seconds.  %llu/%llu sendK/recvK.",
           source_p->name, (int)(CurrentTime - source_p->firsttime), 
           source_p->localClient->send.bytes >> 10,
           source_p->localClient->recv.bytes >> 10);
    }
  }
  else if (IsClient(source_p) && !IsKilled(source_p))
  {
    sendto_server(NULL, source_p, NULL, CAP_TS6, NOCAPS, NOFLAGS,
                  ":%s QUIT :%s", ID(source_p), comment);
    sendto_server(NULL, source_p, NULL, NOCAPS, CAP_TS6, NOFLAGS,
                  ":%s QUIT :%s", source_p->name, comment);
  }

  /* The client *better* be off all of the lists */
  assert(dlinkFind(&unknown_list, source_p) == NULL);
  assert(dlinkFind(&local_client_list, source_p) == NULL);
  assert(dlinkFind(&serv_list, source_p) == NULL);
  assert(dlinkFind(&oper_list, source_p) == NULL);

  exit_one_client(source_p, comment);
}

/*
 * close_connection
 *        Close the physical connection. This function must make
 *        MyConnect(client_p) == FALSE, and set client_p->from == NULL.
 */
static void
close_connection(struct Client *client_p)
{
  struct ConfItem *conf;
  struct AccessItem *aconf;
  struct ClassItem *aclass;

  assert(NULL != client_p);

  if (IsServer(client_p))
  {
    ServerStats->is_sv++;
    ServerStats->is_sbs += client_p->localClient->send.bytes;
    ServerStats->is_sbr += client_p->localClient->recv.bytes;
    ServerStats->is_sti += CurrentTime - client_p->firsttime;

    /* XXX Does this even make any sense at all anymore?
     * scheduling a 'quick' reconnect could cause a pile of
     * nick collides under TSora protocol... -db
     */
    /*
     * If the connection has been up for a long amount of time, schedule
     * a 'quick' reconnect, else reset the next-connect cycle.
     */
    if ((conf = find_exact_name_conf(SERVER_TYPE,
				     client_p->name, client_p->username,
				     client_p->host)))
    {
      /*
       * Reschedule a faster reconnect, if this was a automatically
       * connected configuration entry. (Note that if we have had
       * a rehash in between, the status has been changed to
       * CONF_ILLEGAL). But only do this if it was a "good" link.
       */
      aconf = &conf->conf.AccessItem;
      aclass = &((struct ConfItem *)aconf->class_ptr)->conf.ClassItem;
      aconf->hold = time(NULL);
      aconf->hold += (aconf->hold - client_p->since > HANGONGOODLINK) ?
        HANGONRETRYDELAY : ConFreq(aclass);
      if (nextconnect > aconf->hold)
        nextconnect = aconf->hold;
    }
  }
  else if (IsClient(client_p))
  {
    ServerStats->is_cl++;
    ServerStats->is_cbs += client_p->localClient->send.bytes;
    ServerStats->is_cbr += client_p->localClient->recv.bytes;
    ServerStats->is_cti += CurrentTime - client_p->firsttime;
  }
  else
    ServerStats->is_ni++;

  if (!IsDead(client_p))
  {
    /* attempt to flush any pending dbufs. Evil, but .. -- adrian */
    /* there is still a chance that we might send data to this socket
     * even if it is marked as blocked (COMM_SELECT_READ handler is called
     * before COMM_SELECT_WRITE). Let's try, nothing to lose.. -adx
     */
    ClearSendqBlocked(client_p);
    send_queued_write(client_p);
  }

#ifdef HAVE_LIBCRYPTO
  if (client_p->localClient->fd.ssl)
    SSL_shutdown(client_p->localClient->fd.ssl);
#endif
  if (client_p->localClient->fd.flags.open)
    fd_close(&client_p->localClient->fd);

  if (HasServlink(client_p))
  {
    if (client_p->localClient->ctrlfd.flags.open)
      fd_close(&client_p->localClient->ctrlfd);
  }

  dbuf_clear(&client_p->localClient->buf_sendq);
  dbuf_clear(&client_p->localClient->buf_recvq);

  MyFree(client_p->localClient->passwd);
  detach_conf(client_p, CONF_TYPE);
  client_p->from = NULL; /* ...this should catch them! >:) --msa */
}

/*
 * report_error - report an error from an errno.
 * Record error to log and also send a copy to all *LOCAL* opers online.
 *
 *        text        is a *format* string for outputing error. It must
 *                contain only two '%s', the first will be replaced
 *                by the sockhost from the client_p, and the latter will
 *                be taken from sys_errlist[errno].
 *
 *        client_p        if not NULL, is the *LOCAL* client associated with
 *                the error.
 *
 * Cannot use perror() within daemon. stderr is closed in
 * ircd and cannot be used. And, worse yet, it might have
 * been reassigned to a normal connection...
 *
 * Actually stderr is still there IFF ircd was run with -s --Rodder
 */
void
report_error(int level, const char *text, const char *who, int error)
{
  who = (who != NULL) ? who : "";

  sendto_realops_flags(UMODE_DEBUG, level, text, who, strerror(error));
  log_oper_action(LOG_IOERR_TYPE, NULL, "%s %s %s\n", who, text, strerror(error));
  ilog(L_ERROR, text, who, strerror(error));
}

/*
 * dead_link_on_write - report a write error if not already dead,
 *			mark it as dead then exit it
 */
void
dead_link_on_write(struct Client *client_p, int ierrno)
{
  dlink_node *ptr;

  if (IsDefunct(client_p))
    return;

  dbuf_clear(&client_p->localClient->buf_recvq);
  dbuf_clear(&client_p->localClient->buf_sendq);

  assert(dlinkFind(&abort_list, client_p) == NULL);
  ptr = make_dlink_node();
  /* don't let exit_aborted_clients() finish yet */
  dlinkAddTail(client_p, ptr, &abort_list);

  if (eac_next == NULL)
    eac_next = ptr;

  SetDead(client_p); /* You are dead my friend */
}

/*
 * dead_link_on_read -  report a read error if not already dead,
 *			mark it as dead then exit it
 */
void
dead_link_on_read(struct Client *client_p, int error)
{
  char errmsg[255];
  int current_error;

  if (IsDefunct(client_p))
    return;

  dbuf_clear(&client_p->localClient->buf_recvq);
  dbuf_clear(&client_p->localClient->buf_sendq);

  current_error = get_sockerr(client_p->localClient->fd.fd);

  if (IsServer(client_p) || IsHandshake(client_p))
  {
    int connected = CurrentTime - client_p->firsttime;
      
    if (error == 0)
    {
      /* Admins get the real IP */
      sendto_realops_flags(UMODE_ALL, L_ADMIN,
			   "Server %s closed the connection",
			   get_client_name(client_p, SHOW_IP));

      /* Opers get a masked IP */
      sendto_realops_flags(UMODE_ALL, L_OPER,
			   "Server %s closed the connection",
			   get_client_name(client_p, MASK_IP));

      ilog(L_NOTICE, "Server %s closed the connection",
	   get_client_name(client_p, SHOW_IP));
    }
    else
    {
      report_error(L_ADMIN, "Lost connection to %s: %d",
		   get_client_name(client_p, SHOW_IP), current_error);
      report_error(L_OPER, "Lost connection to %s: %d",
		   get_client_name(client_p, MASK_IP), current_error);
    }

    sendto_realops_flags(UMODE_ALL, L_ALL,
			 "%s had been connected for %d day%s, %2d:%02d:%02d",
			 client_p->name, connected/86400,
			 (connected/86400 == 1) ? "" : "s",
			 (connected % 86400) / 3600, (connected % 3600) / 60,
			 connected % 60);
  }

  if (error == 0)
    strlcpy(errmsg, "Remote host closed the connection",
            sizeof(errmsg));
  else
    ircsprintf(errmsg, "Read error: %s",
               strerror(current_error));

  exit_client(client_p, &me, errmsg);
}

void
exit_aborted_clients(void)
{
  dlink_node *ptr;
  struct Client *target_p;
  const char *notice;

  DLINK_FOREACH_SAFE(ptr, eac_next, abort_list.head)
  {
    target_p = ptr->data;
    eac_next = ptr->next;

    if (target_p == NULL)
    {
      sendto_realops_flags(UMODE_ALL, L_ALL,
                           "Warning: null client on abort_list!");
      dlinkDelete(ptr, &abort_list);
      free_dlink_node(ptr);
      continue;
    }

    dlinkDelete(ptr, &abort_list);

    if (IsSendQExceeded(target_p))
      notice = "Max SendQ exceeded";
    else
      notice = "Write error: connection closed";

    exit_client(target_p, &me, notice);  
    free_dlink_node(ptr);
  }
}

/*
 * accept processing, this adds a form of "caller ID" to ircd
 * 
 * If a client puts themselves into "caller ID only" mode,
 * only clients that match a client pointer they have put on 
 * the accept list will be allowed to message them.
 *
 * Diane Bruce, "Dianora" db@db.net
 */

void
del_accept(struct Accept *accept, struct Client *client_p)
{
  dlinkDelete(&accept->node, &client_p->localClient->acceptlist);

  MyFree(accept->nick);
  MyFree(accept->user);
  MyFree(accept->host);
  MyFree(accept);
}

struct Accept *
find_accept(const char *nick, const char *user,
            const char *host, struct Client *client_p, int do_match)
{
  dlink_node *ptr = NULL;
  /* XXX We wouldn't need that if match() would return 0 on match */
  int (*cmpfunc)(const char *, const char *) = do_match ? match : irccmp;

  DLINK_FOREACH(ptr, client_p->localClient->acceptlist.head)
  {
    struct Accept *accept = ptr->data;

    if (cmpfunc(accept->nick, nick) == do_match &&
        cmpfunc(accept->user, user) == do_match &&
        cmpfunc(accept->host, host) == do_match)
      return accept;
  }

  return NULL;
}

/* accept_message()
 *
 * inputs	- pointer to nick
 *		- pointer to username
 *		- pointer to hostname
 * 		- pointer to source client
 * 		- pointer to target client
 * output	- 1 if accept this message 0 if not
 * side effects - See if source is on target's allow list
 */
int
accept_message(struct Client *source,
               struct Client *target)
{
  dlink_node *ptr = NULL;

  if (source == target || find_accept(source->name, source->username,
                                      source->host, target, 1))
    return 1;

  if (IsSoftCallerId(target))
    DLINK_FOREACH(ptr, target->channel.head)
      if (IsMember(source, ptr->data))
        return 1;

  return 0;
}

/* del_all_accepts()
 *
 * inputs	- pointer to exiting client
 * output	- NONE
 * side effects - Walk through given clients acceptlist and remove all entries
 */
void
del_all_accepts(struct Client *client_p)
{
  dlink_node *ptr = NULL, *next_ptr = NULL;

  DLINK_FOREACH_SAFE(ptr, next_ptr, client_p->localClient->acceptlist.head)
    del_accept(ptr->data, client_p);
}

/* set_initial_nick()
 *
 * inputs
 * output
 * side effects	-
 *
 * This function is only called to set up an initially registering
 * client. 
 */
void
set_initial_nick(struct Client *client_p, struct Client *source_p,
                 const char *nick)
{
  char buf[USERLEN + 1];

  /* Client setting NICK the first time */
  
  /* This had to be copied here to avoid problems.. */
  source_p->tsinfo = CurrentTime;

  if (source_p->name[0])
    hash_del_client(source_p);

  strlcpy(source_p->name, nick, sizeof(source_p->name));
  hash_add_client(source_p);

  /* fd_desc is long enough */
  fd_note(&client_p->localClient->fd, "Nick: %s", nick);
  
  /* They have the nick they want now.. */
  client_p->localClient->llname[0] = '\0';

  if (source_p->flags & FLAGS_GOTUSER)
  {
    strlcpy(buf, source_p->username, sizeof(buf));

    /*
     * USER already received, now we have NICK.
     * *NOTE* For servers "NICK" *must* precede the
     * user message (giving USER before NICK is possible
     * only for local client connection!). register_user
     * may reject the client and call exit_client for it
     * --must test this and exit m_nick too!!!
     */
    register_local_user(client_p, source_p, nick, buf);
  }
}

/* change_local_nick()
 *
 * inputs	- pointer to server
 *		- pointer to client
 *              - nick
 * output	- 
 * side effects	- changes nick of a LOCAL user
 */
void
change_local_nick(struct Client *client_p, struct Client *source_p, const char *nick)
{
  int samenick = 0;

  /*
   * Client just changing his/her nick.  If he/she is
   * on a channel, send note of change to all clients
   * on that channel.  Propagate notice to other servers.
   */
  if ((source_p->localClient->last_nick_change +
       ConfigFileEntry.max_nick_time) < CurrentTime)
    source_p->localClient->number_of_nick_changes = 0;
  source_p->localClient->last_nick_change = CurrentTime;
  source_p->localClient->number_of_nick_changes++;

  if ((ConfigFileEntry.anti_nick_flood && 
      (source_p->localClient->number_of_nick_changes
       <= ConfigFileEntry.max_nick_changes)) ||
     !ConfigFileEntry.anti_nick_flood || 
     (IsOper(source_p) && ConfigFileEntry.no_oper_flood))
  {
    samenick = !irccmp(source_p->name, nick);
    if (!samenick)
      source_p->tsinfo = CurrentTime;

    /* XXX - the format of this notice should eventually be changed
     * to either %s[%s@%s], or even better would be get_client_name() -bill
     */
    sendto_realops_flags(UMODE_NCHANGE, L_ALL, "Nick change: From %s to %s [%s@%s]",
                         source_p->name, nick, source_p->username, source_p->host);
    sendto_common_channels_local(source_p, 1, ":%s!%s@%s NICK :%s",
                                 source_p->name, source_p->username,
                                 source_p->host, nick);

    add_history(source_p, 1);
	  
	 /* Only hubs care about lazy link nicks not being sent on yet
	   * lazylink leafs/leafs always send their nicks up to hub,
	   * hence must always propagate nick changes.
	   * hubs might not propagate a nick change, if the leaf
	   * does not know about that client yet.
	   */
    sendto_server(client_p, source_p, NULL, CAP_TS6, NOCAPS, NOFLAGS,
                  ":%s NICK %s :%lu",
                  ID(source_p), nick, (unsigned long)source_p->tsinfo);
    sendto_server(client_p, source_p, NULL, NOCAPS, CAP_TS6, NOFLAGS,
                  ":%s NICK %s :%lu",
                  source_p->name, nick, (unsigned long)source_p->tsinfo);
  }
  else
  {
    sendto_one(source_p, form_str(ERR_NICKTOOFAST),
               me.name, source_p->name, source_p->name,
               nick, ConfigFileEntry.max_nick_time);
    return;
  }

  /* Finally, add to hash */
  assert(source_p->name[0]);

  hash_del_client(source_p);
  if (!samenick)
    hash_check_watch(source_p, RPL_LOGOFF);
  strcpy(source_p->name, nick);
  hash_add_client(source_p);

  if (!samenick)
    hash_check_watch(source_p, RPL_LOGON);

  /* fd_desc is long enough */
  fd_note(&client_p->localClient->fd, "Nick: %s", nick);
}

/* log_user_exit()
 *
 * inputs       - pointer to connecting client
 * output       - NONE
 * side effects - Current exiting client is logged to
 *                either SYSLOG or to file.
 */
void
log_user_exit(struct Client *source_p)
{
  time_t on_for = CurrentTime - source_p->firsttime;
#ifdef SYSLOG_USERS
  if (IsClient(source_p))
  {
    ilog(L_INFO, "%s (%3ld:%02ld:%02ld): %s!%s@%s %llu/%llu\n",
         myctime(source_p->firsttime),
          (signed long) on_for / 3600,
          (signed long) (on_for % 3600)/60,
          (signed long) on_for % 60,
          source_p->name, source_p->username, source_p->host,
          source_p->localClient->send.bytes>>10,
          source_p->localClient->recv.bytes>>10);
    }
#else
  {
    char linebuf[BUFSIZ];

    /*
     * This conditional makes the logfile active only after
     * it's been created - thus logging can be turned off by
     * removing the file.
     * -Taner
     */
    if (IsClient(source_p))
    {
      if (user_log_fb == NULL)
      {
        if ((ConfigLoggingEntry.userlog[0] != '\0') &&
           (user_log_fb = fbopen(ConfigLoggingEntry.userlog, "r")) != NULL)
        {
          fbclose(user_log_fb);
          user_log_fb = fbopen(ConfigLoggingEntry.userlog, "a");
        }
      }

      if (user_log_fb != NULL)
      {
        size_t nbytes = ircsprintf(linebuf,
                   "%s (%3ld:%02ld:%02ld): %s!%s@%s %llu/%llu\n",
                   myctime(source_p->firsttime),
                   (signed long) on_for / 3600,
                   (signed long) (on_for % 3600)/60,
                   (signed long) on_for % 60,
                   source_p->name, source_p->username, source_p->host,
                   source_p->localClient->send.bytes>>10,
                   source_p->localClient->recv.bytes>>10);
        fbputs(linebuf, user_log_fb, nbytes);
      }
    }
  }
#endif
}


/* log_oper_action()
 *
 * inputs       - type of oper log entry
 *              - pointer to oper
 *              - const char *pattern == format string
 *              - var args for format string
 * output       - none
 * side effects - corresponding log is written to, if its present.
 *
 * rewritten sept 5 2005 - Dianora
 */
void
log_oper_action(int log_type, const struct Client *source_p,
                const char *pattern, ...)
{
  va_list args;
  char linebuf[IRCD_BUFSIZE];
  FBFILE *log_fb;
  char *logfile;
  const char *log_message;
  size_t nbytes;
  size_t n_preamble;
  char *p;

  switch(log_type)
  {
  case LOG_OPER_TYPE:
    logfile = ConfigLoggingEntry.operlog;
    log_message = "OPER";
    break;
  case LOG_FAILED_OPER_TYPE:
    logfile = ConfigLoggingEntry.failed_operlog;
    log_message = "FAILED OPER";
    break;
  case LOG_KLINE_TYPE:
    logfile = ConfigLoggingEntry.klinelog;
    log_message = "KLINE";
    break;
  case LOG_RKLINE_TYPE:
    logfile = ConfigLoggingEntry.klinelog;
    log_message = "RKLINE";
    break;
  case LOG_DLINE_TYPE:
    logfile = ConfigLoggingEntry.klinelog;
    log_message = "DLINE";
    break;
  case LOG_TEMP_DLINE_TYPE:
    logfile = ConfigLoggingEntry.klinelog;
    log_message = "TEMP DLINE";
    break;
  case LOG_TEMP_KLINE_TYPE:
    logfile = ConfigLoggingEntry.klinelog;
    log_message = "TEMP KLINE";
    break;
  case LOG_GLINE_TYPE:
    logfile = ConfigLoggingEntry.glinelog;
    log_message = "GLINE";
    break;
  case LOG_KILL_TYPE:
    logfile = ConfigLoggingEntry.killlog;
    log_message = "KILL";
    break;
  case LOG_IOERR_TYPE:
    logfile = ConfigLoggingEntry.ioerrlog;
    log_message = "IO ERR";
    break;
  default:
    return;
  }

  if (*logfile == '\0')
    return;

  p = linebuf;
  if (source_p != NULL)
  {
    n_preamble = ircsprintf(linebuf, "%s %s by (%s!%s@%s) :",
                            myctime(CurrentTime), log_message,
                            source_p->name, source_p->username, source_p->host);

  }
  else
  {
    n_preamble = ircsprintf(linebuf, "%s %s :",
                            myctime(CurrentTime), log_message);
  }

  p += n_preamble;

  if ((log_fb = fbopen(logfile, "r")) != NULL)
  {
    fbclose(log_fb);
    log_fb = fbopen(logfile, "a");
    if (log_fb == NULL)
      return;
    va_start(args, pattern);
    /* XXX add check for IRCD_BUFSIZE-(n_preamble+1) < 0 ? -db */
    nbytes = vsnprintf(p, IRCD_BUFSIZE-(n_preamble+1), pattern, args);
    nbytes += n_preamble;
    va_end(args);
    fbputs(linebuf, log_fb, nbytes);
    fbclose(log_fb);
  }
}

/*
 *  ircd-hybrid: an advanced, lightweight Internet Relay Chat Daemon (ircd)
 *
 *  Copyright (c) 1997-2014 ircd-hybrid development team
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
 */

/*! \file m_server.c
 * \brief Includes required functions for processing the SERVER/SID command.
 * \version $Id$
 */

#include "stdinc.h"
#include "list.h"
#include "client.h"
#include "event.h"
#include "hash.h"
#include "irc_string.h"
#include "ircd.h"
#include "numeric.h"
#include "conf.h"
#include "log.h"
#include "s_serv.h"
#include "s_user.h"
#include "send.h"
#include "parse.h"
#include "modules.h"


/* set_server_gecos()
 *
 * input        - pointer to client
 * output       - NONE
 * side effects - servers gecos field is set
 */
static void
set_server_gecos(struct Client *client_p, const char *info)
{
  const char *s = info;

  /* check for (H) which is a hidden server */
  if (!strncmp(s, "(H) ", 4))
  {
    SetHidden(client_p);
    s = s + 4;
  }

  if (!EmptyString(s))
    strlcpy(client_p->info, s, sizeof(client_p->info));
  else
    strlcpy(client_p->info, "(Unknown Location)", sizeof(client_p->info));
}

/* mr_server()
 *  parv[0] = command
 *  parv[1] = servername
 *  parv[2] = hopcount
 *  parv[3] = serverinfo
 */
static int
mr_server(struct Client *source_p, int parc, char *parv[])
{
  char *name;
  struct Client *target_p;
  int hop;
  const char *error = NULL;
  int warn = 1;

  if (EmptyString(parv[3]))
  {
    sendto_one(source_p, "ERROR :No servername");
    exit_client(source_p, "Wrong number of args");
    return 0;
  }

  name = parv[1];
  hop  = atoi(parv[2]);

  /*
   * Reject a direct nonTS server connection if we're TS_ONLY -orabidoo
   */
  if (!DoesTS(source_p))
  {
    sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
          "Unauthorized server connection attempt from %s: Non-TS server "
          "for server %s", get_client_name(source_p, HIDE_IP), name);
    sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
          "Unauthorized server connection attempt from %s: Non-TS server "
          "for server %s", get_client_name(source_p, MASK_IP), name);
    exit_client(source_p, "Non-TS server");
    return 0;
  }

  if (!valid_servname(name))
  {
    sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
          "Unauthorized server connection attempt from %s: Bogus server name "
          "for server %s", get_client_name(source_p, HIDE_IP), name);
    sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
          "Unauthorized server connection attempt from %s: Bogus server name "
          "for server %s", get_client_name(source_p, MASK_IP), name);
    exit_client(source_p, "Bogus server name");
    return 0;
  }

  if (!valid_sid(source_p->id))
  {
    sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
                         "Link %s introduced server with bogus server ID %s",
                         get_client_name(source_p, SHOW_IP), source_p->id);
    sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
                         "Link %s introduced server with bogus server ID %s",
                         get_client_name(source_p, MASK_IP), source_p->id);
    sendto_one(source_p, "ERROR :Bogus server ID introduced");
    exit_client(source_p, "Bogus server ID intoduced");
    return 0;
  }

  /* Now we just have to call check_server and everything should
   * be checked for us... -A1kmm.
   */
  switch (check_server(name, source_p))
  {
    case CHECK_SERVER_NOCONNECT:
      error = "No connect{} block";
      warn = ConfigFileEntry.warn_no_nline;
      break;
    case CHECK_SERVER_INVALID_PASSWORD:
      error = "Bad password";
      break;
    case CHECK_SERVER_INVALID_HOST:
      error = "Invalid host";
      break;
    case CHECK_SERVER_INVALID_CERTIFICATE:
      error = "Invalid certificate fingerprint";
      break;
  }
  if (error != NULL)
  {
    if (warn)
    {
      sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
         "Unauthorized server connection attempt from %s: %s for server %s",
         get_client_name(source_p, HIDE_IP), error, name);

      sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
         "Unauthorized server connection attempt from %s: %s for server %s",
         get_client_name(source_p, MASK_IP), error, name);
    }

    exit_client(source_p, error);
    return 0;
  }

  if ((target_p = find_server(name)))
  {
    /* This link is trying feed me a server that I already have
     * access through another path -- multiple paths not accepted
     * currently, kill this link immediately!!
     *
     * Rather than KILL the link which introduced it, KILL the
     * youngest of the two links. -avalon
     *
     * Definitely don't do that here. This is from an unregistered
     * connect - A1kmm.
     */
    sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
                         "Attempt to re-introduce server %s from %s",
                         name, get_client_name(source_p, HIDE_IP));
    sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
                         "Attempt to re-introduce server %s from %s",
                         name, get_client_name(source_p, MASK_IP));
    sendto_one(source_p, "ERROR :Server already exists.");
    exit_client(source_p, "Server already exists");
    return 0;
  }

  if ((target_p = find_server(source_p->id)))
  {
    sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
                         "Attempt to re-introduce server %s SID %s from %s",
                         name, source_p->id,
                         get_client_name(source_p, HIDE_IP));
    sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
                         "Attempt to re-introduce server %s SID %s from %s",
                         name, source_p->id,
                         get_client_name(source_p, MASK_IP));
    sendto_one(source_p, "ERROR :Server ID already exists.");
    exit_client(source_p, "Server ID already exists");
    return 0;
  }

  if (!IsCapable(source_p, CAP_QS))
  {
    sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
                        "Dropping link %s from %s, we require QS",
                         source_p->name, get_client_name(source_p, HIDE_IP));
    sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
                        "Dropping link %s from %s, we require QS",
                         source_p->name, get_client_name(source_p, MASK_IP));

    sendto_one(source_p, "ERROR :QS is required to link");
    exit_client(source_p, "ERROR :QS is required to link");
    return 0;
  }

  /* XXX If somehow there is a connect in progress and
   * a connect comes in with same name toss the pending one,
   * but only if it's not the same client! - Dianora
   */
  if ((target_p = find_servconn_in_progress(name)))
    if (target_p != source_p)
      exit_client(target_p, "Overridden");

  /* if we are connecting (Handshake), we already have the name from the
   * connect{} block in source_p->name
   */
  strlcpy(source_p->name, name, sizeof(source_p->name));
  set_server_gecos(source_p, parv[3]);
  source_p->hopcount = hop;
  server_estab(source_p);
  return 0;
}

/* ms_sid()
 *  parv[0] = command
 *  parv[1] = servername
 *  parv[2] = hopcount
 *  parv[3] = sid of new server
 *  parv[4] = serverinfo
 */
static int
ms_sid(struct Client *source_p, int parc, char *parv[])
{
  dlink_node *ptr = NULL;
  struct Client *target_p = NULL;
  struct Client *client_p = source_p->from; /* XXX */
  const struct MaskItem *conf = NULL;
  int hlined = 0;
  int llined = 0;
  int hop = 0;

  if (EmptyString(parv[4]))
  {
    sendto_one(client_p, "ERROR :No servername");
    return 0;
  }

  hop = atoi(parv[2]);

  if (!valid_servname(parv[1]))
  {
    sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
                         "Link %s introduced server with bogus server name %s",
                         get_client_name(client_p, SHOW_IP), parv[1]);
    sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
                         "Link %s introduced server with bogus server name %s",
                         get_client_name(client_p, MASK_IP), parv[1]);
    sendto_one(client_p, "ERROR :Bogus server name introduced");
    exit_client(client_p, "Bogus server name intoduced");
    return 0;
  }

  if (!valid_sid(parv[3]))
  {
    sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
                         "Link %s introduced server with bogus server ID %s",
                         get_client_name(client_p, SHOW_IP), parv[3]);
    sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
                         "Link %s introduced server with bogus server ID %s",
                         get_client_name(client_p, MASK_IP), parv[3]);
    sendto_one(client_p, "ERROR :Bogus server ID introduced");
    exit_client(client_p, "Bogus server ID intoduced");
    return 0;
  }

  /* collision on SID? */
  if ((target_p = find_server(parv[3])))
  {
    sendto_one(client_p, "ERROR :SID %s already exists", parv[3]);
    sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
                         "Link %s cancelled, SID %s already exists",
                         get_client_name(client_p, SHOW_IP), parv[3]);
    sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
                         "Link %s cancelled, SID %s already exists",
                         client_p->name, parv[3]);
    exit_client(client_p, "SID Exists");
    return 0;
  }

  /* collision on name? */
  if ((target_p = find_server(parv[1])))
  {
    sendto_one(client_p, "ERROR :Server %s already exists", parv[1]);
    sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
                         "Link %s cancelled, server %s already exists",
                         get_client_name(client_p, SHOW_IP), parv[1]);
    sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
                         "Link %s cancelled, server %s already exists",
                         client_p->name, parv[1]);
    exit_client(client_p, "Server Exists");
    return 0;
  }

  /* XXX If somehow there is a connect in progress and
   * a connect comes in with same name toss the pending one,
   * but only if it's not the same client! - Dianora
   */
  if ((target_p = find_servconn_in_progress(parv[1])))
    if (target_p != client_p)
      exit_client(target_p, "Overridden");

  conf = client_p->localClient->confs.head->data;

  /* See if the newly found server is behind a guaranteed
   * leaf. If so, close the link.
   */
  DLINK_FOREACH(ptr, conf->leaf_list.head)
  {
    if (!match(ptr->data, parv[1]))
    {
      llined = 1;
      break;
    }
  }

  DLINK_FOREACH(ptr, conf->hub_list.head)
  {
    if (!match(ptr->data, parv[1]))
    {
      hlined = 1;
      break;
    }
  }

  /* Ok, this way this works is
   *
   * A server can have a CONF_HUB allowing it to introduce servers
   * behind it.
   *
   * connect {
   *            name = "irc.bighub.net";
   *            hub_mask="*";
   *            ...
   *
   * That would allow "irc.bighub.net" to introduce anything it wanted..
   *
   * However
   *
   * connect {
   *            name = "irc.somehub.fi";
   *		hub_mask="*";
   *		leaf_mask="*.edu";
   *...
   * Would allow this server in finland to hub anything but
   * .edu's
   */

  /* Ok, check client_p can hub the new server, and make sure it's not a LL */
  if (!hlined)
  {
    /* OOOPs nope can't HUB */
    sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
                         "Non-Hub link %s introduced %s.",
                         get_client_name(client_p, SHOW_IP), parv[1]);
    sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
                         "Non-Hub link %s introduced %s.",
                         get_client_name(client_p, MASK_IP), parv[1]);
    exit_client(source_p, "No matching hub_mask.");
    return 0;
  }

  /* Check for the new server being leafed behind this HUB */
  if (llined)
  {
    /* OOOPs nope can't HUB this leaf */
    sendto_realops_flags(UMODE_ALL, L_ADMIN, SEND_NOTICE,
                         "Link %s introduced leafed server %s.",
                         get_client_name(client_p, SHOW_IP), parv[1]);
    sendto_realops_flags(UMODE_ALL, L_OPER, SEND_NOTICE,
                         "Link %s introduced leafed server %s.",
                         get_client_name(client_p, MASK_IP), parv[1]);
    exit_client(client_p, "Leafed Server.");
    return 0;
  }

  target_p = make_client(client_p);
  make_server(target_p);
  target_p->hopcount = hop;
  target_p->servptr = source_p;

  strlcpy(target_p->name, parv[1], sizeof(target_p->name));
  strlcpy(target_p->id, parv[3], sizeof(target_p->id));

  set_server_gecos(target_p, parv[4]);
  SetServer(target_p);

  if (HasFlag(source_p, FLAGS_SERVICE) || find_matching_name_conf(CONF_SERVICE, target_p->name, NULL, NULL, 0))
    AddFlag(target_p, FLAGS_SERVICE);

  dlinkAdd(target_p, &target_p->node, &global_client_list);
  dlinkAdd(target_p, make_dlink_node(), &global_serv_list);
  dlinkAdd(target_p, &target_p->lnode, &target_p->servptr->serv->server_list);

  hash_add(&clientTable, &target_p->hnode, target_p->name, target_p);
  hash_add(&idTable, &target_p->idhnode, target_p->id, target_p);

  sendto_server(client_p, NOCAPS, NOCAPS, ":%s SID %s %d %s :%s%s",
                ID_or_name(source_p, client_p), target_p->name, hop + 1,
                target_p->id, IsHidden(target_p) ? "(H) " : "", target_p->info);
  sendto_realops_flags(UMODE_EXTERNAL, L_ALL, SEND_NOTICE,
                       "Server %s being introduced by %s",
                       target_p->name, source_p->name);
  return 0;
}

static struct Message server_msgtab =
{
  "SERVER", 0, 0, 4, MAXPARA, MFLG_SLOW, 0,
  { mr_server, m_registered, m_ignore, m_ignore, m_registered, m_ignore }
};

static struct Message sid_msgtab =
{
  "SID", 0, 0, 5, MAXPARA, MFLG_SLOW, 0,
  { m_ignore, m_ignore, m_ignore, ms_sid, m_ignore, m_ignore }
};

static void
module_init(void)
{
  mod_add_cmd(&sid_msgtab);
  mod_add_cmd(&server_msgtab);
}

static void
module_exit(void)
{
  mod_del_cmd(&sid_msgtab);
  mod_del_cmd(&server_msgtab);
}

struct module module_entry =
{
  .node    = { NULL, NULL, NULL },
  .name    = NULL,
  .version = "$Revision$",
  .handle  = NULL,
  .modinit = module_init,
  .modexit = module_exit,
  .flags   = MODULE_FLAG_CORE
};

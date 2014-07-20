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

/*! \file m_whois.c
 * \brief Includes required functions for processing the WHOIS command.
 * \version $Id$
 */

#include "stdinc.h"
#include "list.h"
#include "client.h"
#include "hash.h"
#include "channel.h"
#include "channel_mode.h"
#include "ircd.h"
#include "numeric.h"
#include "conf.h"
#include "misc.h"
#include "server.h"
#include "user.h"
#include "send.h"
#include "irc_string.h"
#include "parse.h"
#include "modules.h"


static int
whois_can_see_channels(struct Channel *chptr,
                       struct Client *source_p,
                       struct Client *target_p)
{
  if (PubChannel(chptr) && !HasUMode(target_p, UMODE_HIDECHANS))
    return 1;

  if (source_p == target_p || IsMember(source_p, chptr))
    return 1;

  if (HasUMode(source_p, UMODE_ADMIN))
    return 2;
  return 0;
}

/* whois_person()
 *
 * inputs	- source_p client to report to
 *		- target_p client to report on
 * output	- NONE
 * side effects	- 
 */
static void
whois_person(struct Client *source_p, struct Client *target_p)
{
  char buf[IRCD_BUFSIZE] = "";
  const dlink_node *lp = NULL;
  char *t = NULL;
  int cur_len = 0;
  int show_ip = 0;
  int mlen = 0;
  int tlen = 0;
  int reply_to_send = 0;

  sendto_one_numeric(source_p, &me, RPL_WHOISUSER, target_p->name,
                     target_p->username, target_p->host,
                     target_p->info);

  cur_len = mlen = snprintf(buf, sizeof(buf), numeric_form(RPL_WHOISCHANNELS),
                            me.name, source_p->name, target_p->name, "");
  t = buf + mlen;

  DLINK_FOREACH(lp, target_p->channel.head)
  {
    const struct Membership *ms = lp->data;
    int show = whois_can_see_channels(ms->chptr, source_p, target_p);

    if (show)
    {
      if ((cur_len + 4 + strlen(ms->chptr->chname) + 1) > (IRCD_BUFSIZE - 2))
      {
        *(t - 1) = '\0';
        sendto_one(source_p, "%s", buf);
        cur_len = mlen;
        t = buf + mlen;
      }

      tlen = sprintf(t, "%s%s%s ", show == 2 ? "~" : "", get_member_status(ms, 1),
                     ms->chptr->chname);
      t += tlen;
      cur_len += tlen;
      reply_to_send = 1;
    }
  }

  if (reply_to_send)
  {
    *(t - 1) = '\0';
    sendto_one(source_p, "%s", buf);
  }

  if ((ConfigServerHide.hide_servers || IsHidden(target_p->servptr)) &&
      !(HasUMode(source_p, UMODE_OPER) || target_p == source_p))
    sendto_one_numeric(source_p, &me, RPL_WHOISSERVER, target_p->name,
                       ConfigServerHide.hidden_name,
                       ServerInfo.network_desc);
  else
    sendto_one_numeric(source_p, &me, RPL_WHOISSERVER, target_p->name,
                       target_p->servptr->name, target_p->servptr->info);

  if (HasUMode(target_p, UMODE_REGISTERED))
    sendto_one_numeric(source_p, &me, RPL_WHOISREGNICK, target_p->name);

  if (!IsDigit(target_p->svid[0]))
    sendto_one_numeric(source_p, &me, RPL_WHOISACCOUNT, target_p->name,
                       target_p->svid);

  if (target_p->away[0])
    sendto_one_numeric(source_p, &me, RPL_AWAY, target_p->name,
                       target_p->away);

  if (HasUMode(target_p, UMODE_CALLERID|UMODE_SOFTCALLERID))
  {
    int callerid = !!HasUMode(target_p, UMODE_CALLERID);

    sendto_one_numeric(source_p, &me, RPL_TARGUMODEG, target_p->name,
                       callerid ? "+g" : "+G",
                       callerid ? "server side ignore" :
                                  "server side ignore with the exception of common channels");
  }

  if (HasUMode(target_p, UMODE_OPER))
    if (!HasUMode(target_p, UMODE_HIDDEN) || HasUMode(source_p, UMODE_OPER))
      sendto_one_numeric(source_p, &me, RPL_WHOISOPERATOR, target_p->name,
                 HasUMode(target_p, UMODE_ADMIN) ? "is a Server Administrator" :
                                                   "is an IRC Operator");

  if (HasUMode(target_p, UMODE_WEBIRC))
    sendto_one_numeric(source_p, &me, RPL_WHOISTEXT, target_p->name,
                       "User connected using a webirc gateway");

  if (HasUMode(source_p, UMODE_ADMIN) || source_p == target_p)
  {
    char *m = buf;
    *m++ = '+';

    for (unsigned int i = 0; i < 128; ++i)
      if (HasUMode(target_p, user_modes[i]))
        *m++ = (char)i;
    *m = '\0';

    sendto_one_numeric(source_p, &me, RPL_WHOISMODES, target_p->name, buf);
  }

  if (target_p->sockhost[0] && strcmp(target_p->sockhost, "0"))
  {
    if (HasUMode(source_p, UMODE_ADMIN) || source_p == target_p)
      show_ip = 1;
    else if (IsIPSpoof(target_p))
      show_ip = (HasUMode(source_p, UMODE_OPER) && !ConfigFileEntry.hide_spoof_ips);
    else
      show_ip = 1;


    sendto_one_numeric(source_p, &me, RPL_WHOISACTUALLY, target_p->name,
                       show_ip ? target_p->sockhost : "255.255.255.255");
  }

  if (HasUMode(target_p, UMODE_SSL))
    sendto_one_numeric(source_p, &me, RPL_WHOISSECURE, target_p->name);

  if (!EmptyString(target_p->certfp))
    if (target_p == source_p || HasUMode(source_p, UMODE_ADMIN))
      sendto_one_numeric(source_p, &me, RPL_WHOISCERTFP, target_p->name, target_p->certfp);

  if (MyConnect(target_p))
    if (!HasUMode(target_p, UMODE_HIDEIDLE) || HasUMode(source_p, UMODE_OPER) ||
        source_p == target_p)
      sendto_one_numeric(source_p, &me, RPL_WHOISIDLE, target_p->name,
                         idle_time_get(source_p, target_p),
                         target_p->localClient->firsttime);
}

/* do_whois()
 *
 * inputs       - pointer to /whois source
 *              - number of parameters
 *              - pointer to parameters array
 * output       - pointer to void
 * side effects - Does whois
 */
static void
do_whois(struct Client *source_p, const char *name)
{
  struct Client *target_p = NULL;

  if ((target_p = find_person(source_p, name)))
    whois_person(source_p, target_p);
  else if (!IsDigit(*name))
    sendto_one_numeric(source_p, &me, ERR_NOSUCHNICK, name);

  sendto_one_numeric(source_p, &me, RPL_ENDOFWHOIS, name);
}

/*! \brief WHOIS command handler
 *
 * \param source_p Pointer to allocated Client struct from which the message
 *                 originally comes from.  This can be a local or remote client.
 * \param parc     Integer holding the number of supplied arguments.
 * \param parv     Argument vector where parv[0] .. parv[parc-1] are non-NULL
 *                 pointers.
 * \note Valid arguments for this command are:
 *      - parv[0] = command
 *      - parv[1] = nickname/servername
 *      - parv[2] = nickname
 */
static int
m_whois(struct Client *source_p, int parc, char *parv[])
{
  static time_t last_used = 0;

  if (parc < 2 || EmptyString(parv[1]))
  {
    sendto_one_numeric(source_p, &me, ERR_NONICKNAMEGIVEN);
    return 0;
  }

  if (parc > 2 && !EmptyString(parv[2]))
  {
    /* seeing as this is going across servers, we should limit it */
    if ((last_used + ConfigFileEntry.pace_wait_simple) > CurrentTime)
    {
      sendto_one_numeric(source_p, &me, RPL_LOAD2HI);
      return 0;
    }

    last_used = CurrentTime;

    /*
     * if we have serverhide enabled, they can either ask the clients
     * server, or our server.. I don't see why they would need to ask
     * anything else for info about the client.. --fl_
     */
    if (ConfigServerHide.disable_remote_commands)
      parv[1] = parv[2];

    if (hunt_server(source_p, ":%s WHOIS %s :%s", 1,
                    parc, parv) != HUNTED_ISME)
      return 0;

    parv[1] = parv[2];
  }

  do_whois(source_p, parv[1]);
  return 0;
}

/*! \brief WHOIS command handler
 *
 * \param source_p Pointer to allocated Client struct from which the message
 *                 originally comes from.  This can be a local or remote client.
 * \param parc     Integer holding the number of supplied arguments.
 * \param parv     Argument vector where parv[0] .. parv[parc-1] are non-NULL
 *                 pointers.
 * \note Valid arguments for this command are:
 *      - parv[0] = command
 *      - parv[1] = nickname/servername
 *      - parv[2] = nickname
 */
static int
mo_whois(struct Client *source_p, int parc, char *parv[])
{
  if (parc < 2 || EmptyString(parv[1]))
  {
    sendto_one_numeric(source_p, &me, ERR_NONICKNAMEGIVEN);
    return 0;
  }

  if (parc > 2 && !EmptyString(parv[2]))
  {
    if (hunt_server(source_p, ":%s WHOIS %s :%s", 1,
                    parc, parv) != HUNTED_ISME)
      return 0;

    parv[1] = parv[2];
  }

  do_whois(source_p, parv[1]);
  return 0;
}

static struct Message whois_msgtab =
{
  "WHOIS", 0, 0, 0, MAXPARA, MFLG_SLOW, 0,
  { m_unregistered, m_whois, mo_whois, m_ignore, mo_whois, m_ignore }
};

static void
module_init(void)
{
  mod_add_cmd(&whois_msgtab);
}

static void
module_exit(void)
{
  mod_del_cmd(&whois_msgtab);
}

struct module module_entry =
{
  .node    = { NULL, NULL, NULL },
  .name    = NULL,
  .version = "$Revision$",
  .handle  = NULL,
  .modinit = module_init,
  .modexit = module_exit,
  .flags   = 0
};

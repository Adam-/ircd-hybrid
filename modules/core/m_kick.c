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

/*! \file m_kick.c
 * \brief Includes required functions for processing the KICK command.
 * \version $Id$
 */

#include "stdinc.h"
#include "list.h"
#include "channel.h"
#include "channel_mode.h"
#include "client.h"
#include "irc_string.h"
#include "ircd.h"
#include "numeric.h"
#include "send.h"
#include "modules.h"
#include "parse.h"
#include "hash.h"
#include "packet.h"
#include "s_serv.h"


/* m_kick()
 *  parv[0] = command
 *  parv[1] = channel
 *  parv[2] = client to kick
 *  parv[3] = kick comment
 */
static int
m_kick(struct Client *source_p, int parc, char *parv[])
{
  struct Client *who;
  struct Channel *chptr;
  int chasing = 0;
  char *comment;
  char *name;
  char *p = NULL;
  char *user;
  struct Membership *ms = NULL;
  struct Membership *ms_target;

  if (EmptyString(parv[2]))
  {
    sendto_one_numeric(source_p, &me, ERR_NEEDMOREPARAMS, "KICK");
    return 0;
  }

  if (!IsFloodDone(source_p))
    flood_endgrace(source_p);

  comment = (EmptyString(parv[3])) ? source_p->name : parv[3];
  if (strlen(comment) > (size_t)KICKLEN)
    comment[KICKLEN] = '\0';

  name = parv[1];
  if ((p = strchr(name,',')) != NULL)
    *p = '\0';
  if (*name == '\0')
    return 0;

  if ((chptr = hash_find(&channelTable, name)) == NULL)
  {
    sendto_one_numeric(source_p, &me, ERR_NOSUCHCHANNEL, name);
    return 0;
  }

  if ((ms = find_channel_link(source_p, chptr)) == NULL)
  {
    sendto_one_numeric(source_p, &me, ERR_NOTONCHANNEL, name);
    return 0;
  }

  if (!has_member_flags(ms, CHFL_CHANOP|CHFL_HALFOP))
  {
      sendto_one_numeric(source_p, &me, ERR_CHANOPRIVSNEEDED, name);
      return 0;
  }

  user = parv[2];
  if ((p = strchr(user, ',')) != NULL)
    *p = '\0';

  if (*user == '\0')
    return 0;

  if ((who = find_chasing(source_p, user, &chasing)) == NULL)
    return 0;

  if ((ms_target = find_channel_link(who, chptr)) == NULL)
  {
    sendto_one_numeric(source_p, &me, ERR_USERNOTINCHANNEL, user, name);
    return 0;
  }

#ifdef HALFOPS
  /* half ops cannot kick other halfops on private channels */
  if (has_member_flags(ms, CHFL_HALFOP) && !has_member_flags(ms, CHFL_CHANOP))
  {
    if (((chptr->mode.mode & MODE_PRIVATE) && has_member_flags(ms_target,
      CHFL_CHANOP|CHFL_HALFOP)) || has_member_flags(ms_target, CHFL_CHANOP))
    {
      sendto_one_numeric(source_p, &me, ERR_CHANOPRIVSNEEDED, name);
      return 0;
    }
  }
#endif

  sendto_channel_local(ALL_MEMBERS, 0, chptr, ":%s!%s@%s KICK %s %s :%s",
                       source_p->name, source_p->username,
                       source_p->host, name, who->name, comment);

  sendto_server(source_p, NOCAPS, NOCAPS,
                ":%s KICK %s %s :%s",
                ID(source_p), chptr->chname, ID(who), comment);

  remove_user_from_channel(ms_target);

  return 0;
}

static int
ms_kick(struct Client *source_p, int parc, char **parv)
{
  const char *name = parv[1];
  const char *target = parv[2];
  char *comment;
  struct Channel *chptr;
  struct Client *who;
  struct Membership *ms_target;

  chptr = hash_find(&channelTable, name);
  if (chptr == NULL)
    return 0;

  who = find_person(source_p, target);
  if (who == NULL)
    return 0;

  ms_target = find_channel_link(who, chptr);
  if (ms_target == NULL)
    return 0;

  comment = (EmptyString(parv[3])) ? source_p->name : parv[3];

  if (IsServer(source_p))
    sendto_channel_local(ALL_MEMBERS, 0, chptr, ":%s KICK %s %s :%s",
                         source_p->name, name, who->name, comment);
  else
    sendto_channel_local(ALL_MEMBERS, 0, chptr, ":%s!%s@%s KICK %s %s :%s",
                         source_p->name, source_p->username,
                         source_p->host, name, who->name, comment);

  sendto_server(source_p, NOCAPS, NOCAPS,
                ":%s KICK %s %s :%s",
                ID(source_p), chptr->chname, ID(who), comment);

  remove_user_from_channel(ms_target);
  return 0;
}

static struct Message kick_msgtab =
{
  "KICK", 0, 0, 3, MAXPARA, MFLG_SLOW, 0,
  { m_unregistered, m_kick, ms_kick, ms_kick, m_ignore, m_kick }
};

static void
module_init(void)
{
  mod_add_cmd(&kick_msgtab);
}

static void
module_exit(void)
{
  mod_del_cmd(&kick_msgtab);
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

/*
 *  ircd-hybrid: an advanced Internet Relay Chat Daemon(ircd).
 *  m_challenge.c: Allows an IRC Operator to securely authenticate.
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
#include "handlers.h"
#include "client.h"
#include "ircd.h"
#include "modules.h"
#include "numeric.h"
#include "send.h"
#include "s_conf.h"
/* -lcrypto is implicit for building this module! */
#include "rsa.h"
#include "msg.h"
#include "parse.h"
#include "s_user.h"

static void failed_challenge_notice(struct Client *, const char *,
                                    const char *);
static void m_challenge(struct Client *, struct Client *, int, char *[]);

/* We have openssl support, so include /CHALLENGE */
struct Message challenge_msgtab = {
  "CHALLENGE", 0, 0, 2, 0, MFLG_SLOW, 0,
  { m_unregistered, m_challenge, m_ignore, m_ignore, m_challenge, m_ignore }
};

INIT_MODULE(m_challenge, "$Revision$")
{
  mod_add_cmd(&challenge_msgtab);
}

CLEANUP_MODULE
{
  mod_del_cmd(&challenge_msgtab);
}

/*! \brief CHALLENGE command handler (called for local clients only)
 *
 * Generate RSA challenge for wouldbe oper
 *
 * \param client_p Pointer to allocated Client struct with physical connection
 *                 to this server, i.e. with an open socket connected.
 * \param source_p Pointer to allocated Client struct from which the message
 *                 originally comes from.  This can be a local or remote client.
 * \param parc     Integer holding the number of supplied arguments.
 * \param parv     Argument vector where parv[0] .. parv[parc-1] are non-NULL
 *                 pointers.
 * \note Valid arguments for this command are:
 *      - parv[0] = sender prefix
 *      - parv[1] = operator to challenge for, or +response
 */
static void
m_challenge(struct Client *client_p, struct Client *source_p,
            int parc, char *parv[])
{
  char *challenge = NULL;
  struct ConfItem *conf = NULL;
  struct AccessItem *aconf = NULL;

  assert(source_p->localClient);

  /* if theyre an oper, reprint oper motd and ignore */
  if (IsOper(source_p))
  {
    sendto_one(source_p, form_str(RPL_YOUREOPER), me.name, source_p->name);
    send_message_file(source_p, &ConfigFileEntry.opermotd);
    return;
  }

  if (*parv[1] == '+')
  {
    /* Ignore it if we aren't expecting this... -A1kmm */
    if (source_p->localClient->response == NULL)
      return;

    if (irccmp(source_p->localClient->response, ++parv[1]))
    {
      sendto_one(source_p, form_str(ERR_PASSWDMISMATCH), me.name,
		 source_p->name);
      failed_challenge_notice(source_p, source_p->localClient->auth_oper,
			      "challenge failed");
      return;
    }
     
    if ((conf = find_exact_name_conf(OPER_TYPE,
				     source_p->localClient->auth_oper,
				     source_p->username, source_p->host
				   )) == NULL)
    {
      sendto_one (source_p, form_str(ERR_NOOPERHOST), me.name, source_p->name);
      log_oper_action(LOG_FAILED_OPER_TYPE, source_p, "%s\n",
		      source_p->localClient->auth_oper);
      return;
    }

    oper_up(source_p, conf);

    ilog(L_TRACE, "OPER %s by %s!%s@%s",
	 source_p->localClient->auth_oper, source_p->name, source_p->username,
	 source_p->host);
    log_oper_action(LOG_OPER_TYPE, source_p,
		    "%s\n", source_p->localClient->auth_oper);

    MyFree(source_p->localClient->response);
/*
 *  Do NOT free auth_oper here as it is already done and
 *  a new string is copied to it in oper_up()
 */
/*  MyFree(source_p->localClient->auth_oper);*/
    source_p->localClient->response  = NULL;
/*  source_p->localClient->auth_oper = NULL; */
    return;
  }

  MyFree(source_p->localClient->response);
  MyFree(source_p->localClient->auth_oper);
  source_p->localClient->response  = NULL;
  source_p->localClient->auth_oper = NULL;

  if ((conf = find_exact_name_conf(OPER_TYPE,
				   parv[1], source_p->username, source_p->host
				   )) != NULL)
  {
    aconf = &conf->conf.AccessItem;
  }
  else if ((conf = find_exact_name_conf(OPER_TYPE,
					parv[1], source_p->username,
					source_p->sockhost)) != NULL)
  {
    aconf = &conf->conf.AccessItem;
  }

  if (aconf == NULL)
  {
    sendto_one (source_p, form_str(ERR_NOOPERHOST), me.name, source_p->name);
    conf = find_exact_name_conf(OPER_TYPE, parv[1], NULL, NULL);
    failed_challenge_notice(source_p, parv[1], (conf != NULL)
                            ? "host mismatch" : "no oper {} block");
    log_oper_action(LOG_FAILED_OPER_TYPE, source_p, "%s\n", parv[1]);
    return;
  }

  if (aconf->rsa_public_key == NULL)
  {
    sendto_one (source_p, ":%s NOTICE %s :I'm sorry, PK authentication "
		"is not enabled for your oper{} block.", me.name,
		source_p->name);
    return;
  }

  if (!generate_challenge(&challenge, &(source_p->localClient->response),
                          aconf->rsa_public_key))
    sendto_one(source_p, form_str(RPL_RSACHALLENGE),
               me.name, source_p->name, challenge);

  DupString(source_p->localClient->auth_oper, conf->name);
  MyFree(challenge);
}

/* failed_challenge_notice()
 *
 * inputs       - pointer to client doing /oper ...
 *              - pointer to nick they tried to oper as
 *              - pointer to reason they have failed
 * output       - nothing
 * side effects - notices all opers of the failed oper attempt if enabled
 */
static void
failed_challenge_notice(struct Client *source_p, const char *name,
			const char *reason)
{
  if (ConfigFileEntry.failed_oper_notice)
    sendto_realops_flags(UMODE_ALL, L_ALL, "Failed CHALLENGE attempt as %s "
                         "by %s (%s@%s) - %s", name, source_p->name,
                         source_p->username, source_p->host, reason);
}

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

/*! \file m_hash.c
 * \brief Includes required functions for processing the HASH command.
 * \version $Id$
 */

#include "stdinc.h"
#include "list.h"
#include "client.h"
#include "hash.h"
#include "ircd.h"
#include "numeric.h"
#include "send.h"
#include "parse.h"
#include "modules.h"
#include "userhost.h"


/*! \brief HASH command handler
 *
 * \param source_p Pointer to allocated Client struct from which the message
 *                 originally comes from.  This can be a local or remote client.
 * \param parc     Integer holding the number of supplied arguments.
 * \param parv     Argument vector where parv[0] .. parv[parc-1] are non-NULL
 *                 pointers.
 * \note Valid arguments for this command are:
 *      - parv[0] = command
 */
static int
mo_hash(struct Client *source_p, int parc, char *parv[])
{
  unsigned int count, buckets, max_chain;

  hash_get_stats(&clientTable, &count, &buckets, &max_chain);
  sendto_one_notice(source_p, &me, ":Client: entries: %u buckets: %u "
                    "max chain: %u", count, buckets, max_chain);

  hash_get_stats(&channel_table, &count, &buckets, &max_chain);
  sendto_one_notice(source_p, &me, ":Channel: entries: %u buckets: %u "
                    "max chain: %u", count, buckets, max_chain);

  hash_get_stats(&idTable, &count, &buckets, &max_chain);
  sendto_one_notice(source_p, &me, ":Id: entries: %u buckets: %u "
                    "max chain: %u", count, buckets, max_chain);


  hash_get_stats(&userhostTable, &count, &buckets, &max_chain);
  sendto_one_notice(source_p, &me, ":UserHost: entries: %u buckets: %u "
                    "max chain: %u", count, buckets, max_chain);
  return 0;
}

static struct Message hash_msgtab =
{
  "HASH", 0, 0, 0, MAXPARA, MFLG_SLOW, 0,
  { m_unregistered, m_not_oper, m_ignore, m_ignore, mo_hash, m_ignore }
};

static void
module_init(void)
{
  mod_add_cmd(&hash_msgtab);
}

static void
module_exit(void)
{
  mod_del_cmd(&hash_msgtab);
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

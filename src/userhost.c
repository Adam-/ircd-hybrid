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

/*! \file userhost.c
 * \version $Id$
 */

#include "stdinc.h"
#include "ircd_defs.h"
#include "irc_string.h"
#include "hash.h"
#include "userhost.h"
#include "mempool.h"

static mp_pool_t *userhost_pool;
static mp_pool_t *namehost_pool;

struct hash_table userhostTable = {
  .buckets = NULL,
  .power = FNV1_32_BITS,
  .size = FNV1_32_SIZE,
  .hash = fnv_hash_ircstring_lower,
  .compare = (hash_compare) irccmp
};

/* count_user_host()
 *
 * inputs	- user name
 *		- hostname
 *		- int flag 1 if global, 0 if local
 * 		- pointer to where global count should go
 *		- pointer to where local count should go
 *		- pointer to where identd count should go (local clients only)
 * output	- none
 * side effects	-
 */
void
count_user_host(const char *user, const char *host, unsigned int *global_p,
                unsigned int *local_p, unsigned int *icount_p)
{
  dlink_node *ptr;
  struct UserHost *found_userhost;
  struct NameHost *nameh;

  if ((found_userhost = hash_find(&userhostTable, host)) == NULL)
    return;

  DLINK_FOREACH(ptr, found_userhost->list.head)
  {
    nameh = ptr->data;

    if (!irccmp(user, nameh->name))
    {
      if (global_p != NULL)
        *global_p = nameh->gcount;
      if (local_p != NULL)
        *local_p  = nameh->lcount;
      if (icount_p != NULL)
        *icount_p = nameh->icount;
      return;
    }
  }
}

/* find_or_add_userhost()
 *
 * inputs       - host name
 * output       - none
 * side effects - find UserHost * for given host name
 */
static struct UserHost *
find_or_add_userhost(const char *host)
{
  struct UserHost *userhost;

  if ((userhost = hash_find(&userhostTable, host)) != NULL)
    return userhost;

  if (userhost_pool == NULL)
    userhost_pool = mp_pool_new(sizeof(struct UserHost), MP_CHUNK_SIZE_USERHOST);
  userhost = mp_pool_get(userhost_pool);

  strlcpy(userhost->host, host, sizeof(userhost->host));
  hash_add(&userhostTable, &userhost->hnode, userhost->host, userhost);

  return userhost;
}

/* add_user_host()
 *
 * inputs	- user name
 *		- hostname
 *		- int flag 1 if global, 0 if local
 * output	- none
 * side effects	- add given user@host to hash tables
 */
void
add_user_host(const char *user, const char *host, int global)
{
  dlink_node *ptr;
  struct UserHost *found_userhost;
  struct NameHost *nameh;
  int hasident = 1;

  if (*user == '~')
  {
    hasident = 0;
    ++user;
  }

  if ((found_userhost = find_or_add_userhost(host)) == NULL)
    return;

  DLINK_FOREACH(ptr, found_userhost->list.head)
  {
    nameh = ptr->data;

    if (!irccmp(user, nameh->name))
    {
      nameh->gcount++;

      if (!global)
      {
        if (hasident)
          nameh->icount++;
        nameh->lcount++;
      }

      return;
    }
  }

  if (namehost_pool == NULL)
    namehost_pool = mp_pool_new(sizeof(struct NameHost), MP_CHUNK_SIZE_NAMEHOST);
  nameh = mp_pool_get(namehost_pool);
  strlcpy(nameh->name, user, sizeof(nameh->name));

  nameh->gcount = 1;

  if (!global)
  {
    if (hasident)
      nameh->icount = 1;
    nameh->lcount = 1;
  }

  dlinkAdd(nameh, &nameh->node, &found_userhost->list);
}

/* delete_user_host()
 *
 * inputs	- user name
 *		- hostname
 *		- int flag 1 if global, 0 if local
 * output	- none
 * side effects	- delete given user@host to hash tables
 */
void
delete_user_host(const char *user, const char *host, int global)
{
  dlink_node *ptr = NULL, *next_ptr = NULL;
  struct UserHost *found_userhost;
  struct NameHost *nameh;
  int hasident = 1;

  if (*user == '~')
  {
    hasident = 0;
    ++user;
  }

  if ((found_userhost = hash_find(&userhostTable, host)) == NULL)
    return;

  DLINK_FOREACH_SAFE(ptr, next_ptr, found_userhost->list.head)
  {
    nameh = ptr->data;

    if (!irccmp(user, nameh->name))
    {
      if (nameh->gcount > 0)
        nameh->gcount--;
      if (!global)
      {
        if (nameh->lcount > 0)
          nameh->lcount--;
        if (hasident && nameh->icount > 0)
          nameh->icount--;
      }

      if (nameh->gcount == 0 && nameh->lcount == 0)
      {
        dlinkDelete(&nameh->node, &found_userhost->list);
        mp_pool_release(nameh);
      }

      if (dlink_list_length(&found_userhost->list) == 0)
      {
        hash_del_node(&userhostTable, &found_userhost->hnode);
        mp_pool_release(found_userhost);
      }

      return;
    }
  }
}

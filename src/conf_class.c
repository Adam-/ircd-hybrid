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

/*! \file conf_class.c
 * \brief Configuration managment for class{} blocks
 * \version $Id$
 */

#include "stdinc.h"
#include "list.h"
#include "ircd.h"
#include "conf.h"
#include "hostmask.h"
#include "irc_string.h"
#include "memory.h"
#include "mempool.h"
 
#define CIDR_HASH_SIZE (1 << 16)

struct CidrItem
{
  dlink_node node;
  struct ClassItem *class;
  struct irc_ssaddr mask;
  unsigned int number_on_this_cidr;
};


struct ClassItem *class_default;

static dlink_list class_list;

static dlink_list cidrs[CIDR_HASH_SIZE];
static mp_pool_t *cidr_pool;

const dlink_list *
class_get_list(void)
{
  return &class_list;
}

struct ClassItem *
class_make(void)
{
  struct ClassItem *class = MyMalloc(sizeof(*class));

  class->active    = 1;
  class->con_freq  = DEFAULT_CONNECTFREQUENCY;
  class->ping_freq = DEFAULT_PINGFREQUENCY;
  class->max_total = MAXIMUM_LINKS_DEFAULT;
  class->max_sendq = DEFAULT_SENDQ;
  class->max_recvq = DEFAULT_RECVQ;

  dlinkAdd(class, &class->node, &class_list);

  return class;
}

void
class_free(struct ClassItem *class)
{
  assert(class);
  assert(class->active    == 0);
  assert(class->ref_count == 0);

  dlinkDelete(&class->node, &class_list);
  MyFree(class->name);
  MyFree(class);
}

void
class_init(void)
{
  (class_default = class_make())->name = xstrdup("default");
  cidr_pool = mp_pool_new(sizeof(struct CidrItem), sizeof(struct CidrItem) * 1024);
}

struct ClassItem *
get_class_ptr(const dlink_list *const list)
{
  const dlink_node *ptr = NULL;

  if ((ptr = list->head))
  {
    const struct MaskItem *conf = ptr->data;

    assert(conf->class);
    assert(conf->type & (CONF_OPER | CONF_CLIENT | CONF_SERVER));

    return conf->class;
  }

  return class_default;
}

const char *
get_client_class(const dlink_list *const list)
{
  const dlink_node *ptr = NULL;

  if ((ptr = list->head))
  {
    const struct MaskItem *conf = ptr->data;

    assert(conf->class);
    assert(conf->type & (CONF_OPER | CONF_CLIENT | CONF_SERVER));

    return conf->class->name;
  }

  return class_default->name;
}

unsigned int
get_client_ping(const dlink_list *const list)
{
  const dlink_node *ptr = NULL;

  if ((ptr = list->head))
  {
    const struct MaskItem *conf = ptr->data;

    assert(conf->class);
    assert(conf->type & (CONF_OPER | CONF_CLIENT | CONF_SERVER));

    return conf->class->ping_freq;
  }

  return class_default->ping_freq;
}

unsigned int
get_sendq(const dlink_list *const list)
{
  const dlink_node *ptr = NULL;

  if ((ptr = list->head))
  {
    const struct MaskItem *conf = ptr->data;

    assert(conf->class);
    assert(conf->type & (CONF_OPER | CONF_CLIENT | CONF_SERVER));

    return conf->class->max_sendq;
  }

  return class_default->max_sendq;
}

unsigned int
get_recvq(const dlink_list *const list)
{
  const dlink_node *ptr = NULL;

  if ((ptr = list->head))
  {
    const struct MaskItem *conf = ptr->data;

    assert(conf->class);
    assert(conf->type & (CONF_OPER | CONF_CLIENT | CONF_SERVER));

    return conf->class->max_recvq;
  }

  return class_default->max_recvq;
}

/*
 * inputs       - Integer (Number of class)
 * output       - Pointer to ClassItem struct. Non-NULL expected
 * side effects - NONE
 */
struct ClassItem *
class_find(const char *name, int active)
{
  dlink_node *ptr = NULL;

  DLINK_FOREACH(ptr, class_list.head)
  {
    struct ClassItem *class = ptr->data;

    if (!irccmp(class->name, name))
      return active && !class->active ? NULL : class;
  }

  return NULL;
}

/*
 * We don't delete the class table, rather mark all entries for deletion.
 * The table is cleaned up by delete_marked_classes. - avalon
 */
void
class_mark_for_deletion(void)
{
  dlink_node *ptr = NULL;

  DLINK_FOREACH_PREV(ptr, class_list.tail->prev)
    ((struct ClassItem *)ptr->data)->active = 0;
}

void
class_delete_marked(void)
{
  dlink_node *ptr = NULL, *ptr_next = NULL;

  DLINK_FOREACH_SAFE(ptr, ptr_next, class_list.head)
  {
    struct ClassItem *class = ptr->data;

    if (!class->active && !class->ref_count)
    {
      destroy_cidr_class(class);
      class_free(class);
    }
  }
}

/*
 * cidr_limit_reached
 *
 * inputs	- int flag allowing over_rule of limits
 *		- pointer to the ip to be added
 *		- pointer to the class
 * output	- non zero if limit reached
 *		  0 if limit not reached
 * side effects	-
 */
int
cidr_limit_reached(int over_rule, struct irc_ssaddr *ip, struct ClassItem *class)
{
  dlink_node *ptr = NULL;
  struct CidrItem *cidr = NULL;
  unsigned int bitlen;
  unsigned int hashv = 0;
  int match = 0;

  if (class->number_per_cidr == 0)
    return 0;

#ifndef IPV6
  if (ip->ss.ss_family != AF_INET)
    return 0;
#endif

  if (ip->ss.ss_family == AF_INET)
    bitlen = class->cidr_bitlen_ipv4;
  else
    bitlen = class->cidr_bitlen_ipv6;

  if (!bitlen)
    return 0;

  if (ip->ss.ss_family == AF_INET)
    hashv = hash_ipv4(ip, class->cidr_bitlen_ipv4) & (CIDR_HASH_SIZE - 1);
#ifdef IPV6
  else
    hashv = hash_ipv6(ip, class->cidr_bitlen_ipv6) & (CIDR_HASH_SIZE - 1);
#endif

  DLINK_FOREACH(ptr, cidrs[hashv].head)
  {
    cidr = ptr->data;

    if (ip->ss.ss_family != cidr->mask.ss.ss_family)
      continue;

    if (class != cidr->class)
      continue;

    if (ip->ss.ss_family == AF_INET)
      match = match_ipv4(ip, &cidr->mask, class->cidr_bitlen_ipv4);
#ifdef IPV6
    else
      match = match_ipv6(ip, &cidr->mask, class->cidr_bitlen_ipv6);
#endif

    if (match)
    {
        if (!over_rule && (cidr->number_on_this_cidr >= class->number_per_cidr))
          return -1;

        cidr->number_on_this_cidr++;
        return 0;
    }
  }

  cidr = mp_pool_get(cidr_pool);
  memset(cidr, 0, sizeof(*cidr));
  cidr->class = class;
  cidr->number_on_this_cidr = 1;
  cidr->mask = *ip;
  mask_addr(&cidr->mask, bitlen);
  dlinkAdd(cidr, &cidr->node, &cidrs[hashv]);

  return 0;
}

/*
 * remove_from_cidr_check
 *
 * inputs	- pointer to the ip to be removed
 *		- pointer to the class
 * output	- NONE
 * side effects	-
 */
void
remove_from_cidr_check(struct irc_ssaddr *ip, struct ClassItem *aclass)
{
  dlink_node *ptr = NULL;
  struct CidrItem *cidr;
  unsigned int bitlen;
  unsigned int hashv = 0;
  int match = 0;

  if (aclass->number_per_cidr == 0)
    return;

#ifndef IPV6
  if (ip->ss.ss_family != AF_INET)
    return 0;
#endif

  if (ip->ss.ss_family == AF_INET)
    bitlen = aclass->cidr_bitlen_ipv4;
  else
    bitlen = aclass->cidr_bitlen_ipv6;

  if (!bitlen)
    return;

  if (ip->ss.ss_family == AF_INET)
    hashv = hash_ipv4(ip, aclass->cidr_bitlen_ipv4) & (CIDR_HASH_SIZE - 1);
#ifdef IPV6
  else
    hashv = hash_ipv6(ip, aclass->cidr_bitlen_ipv6) & (CIDR_HASH_SIZE - 1);
#endif

  DLINK_FOREACH(ptr, cidrs[hashv].head)
  {
    cidr = ptr->data;

    if (ip->ss.ss_family != cidr->mask.ss.ss_family)
      continue;

    if (aclass != cidr->class)
      continue;

    if (ip->ss.ss_family != AF_INET)
      match = match_ipv4(ip, &cidr->mask, aclass->cidr_bitlen_ipv4);
#ifdef IPV6
    else
      match = match_ipv6(ip, &cidr->mask, aclass->cidr_bitlen_ipv6);
#endif

    if (match)
    {
      cidr->number_on_this_cidr--;

      if (cidr->number_on_this_cidr == 0)
      {
        dlinkDelete(ptr, &cidrs[hashv]);
        mp_pool_release(cidr);
        break;
      }
    }
  }
}

void
rebuild_cidr_list(struct ClassItem *class)
{
  dlink_node *ptr = NULL;

  destroy_cidr_class(class);

  DLINK_FOREACH(ptr, local_client_list.head)
  {
    struct Client *client_p = ptr->data;
    struct MaskItem *conf = client_p->localClient->confs.tail->data;

    if (conf && (conf->type == CONF_CLIENT))
      if (conf->class == class)
        cidr_limit_reached(1, &client_p->localClient->ip, class);
  }
}

/*
 * destroy_cidr_class
 *
 * inputs	- pointer to class
 * output	- none
 * side effects	- completely destroys the class link list of cidr blocks
 */
void
destroy_cidr_class(struct ClassItem *class)
{
  int i;
  dlink_node *ptr, *next_ptr;

  for (i = 0; i < CIDR_HASH_SIZE; ++i)
    DLINK_FOREACH_SAFE(ptr, next_ptr, cidrs[i].head)
    {
      struct CidrItem *cidr = ptr->data;

      if (cidr->class == class)
      {
        dlinkDelete(ptr, &cidrs[i]);
        mp_pool_release(cidr);
      }
    }
}

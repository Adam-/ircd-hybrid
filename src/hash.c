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

/*! \file hash.c
 * \brief Hash table management.
 * \version $Id$
 */

#include "stdinc.h"
#include "list.h"
#include "conf.h"
#include "channel.h"
#include "channel_mode.h"
#include "client.h"
#include "modules.h"
#include "hash.h"
#include "resv.h"
#include "rng_mt.h"
#include "userhost.h"
#include "irc_string.h"
#include "ircd.h"
#include "numeric.h"
#include "send.h"
#include "memory.h"
#include "mempool.h"
#include "dbuf.h"
#include "s_user.h"

static unsigned int hashf_xor_key = 0;

/*
 * New hash function based on the Fowler/Noll/Vo (FNV) algorithm from
 * http://www.isthe.com/chongo/tech/comp/fnv/
 *
 * Here, we use the FNV-1 method, which gives slightly better results
 * than FNV-1a.   -Michael
 */
unsigned int
fnv_hash_ircstring_lower(const unsigned char *name)
{
  const unsigned char *p = name;
  unsigned int hval = FNV1_32_INIT;

  if (EmptyString(p))
    return 0;
  for (; *p != '\0'; ++p)
  {
    hval += (hval << 1) + (hval <<  4) + (hval << 7) +
            (hval << 8) + (hval << 24);
    hval ^= (ToLower(*p) ^ hashf_xor_key);
  }

  return hval;
}

inline unsigned int
hash_fold(struct hash_table *table, unsigned int hashv)
{
  return (hashv >> table->power) ^ (hashv & (1 << table->power) - 1);
}

void
hash_init(void)
{
  hashf_xor_key = genrand_int32() % 256;  /* better than nothing --adx */
}

void
hash_add(struct hash_table *table, hash_node *node, const unsigned char *key, void *what)
{
  unsigned int hashv, bucketv;
  hash_bucket *bucket;

  hashv = table->hash(key);
  bucketv = hash_fold(table, hashv);
  bucket = &table->buckets[bucketv];

  assert(bucketv < table->size);
  assert(node->bucket == NULL);

  dlinkAdd(what, &node->dnode, bucket);
  node->key = key;
  node->hashv = hashv;
  node->bucket = bucket;
}

void
hash_del_node(struct hash_table *table, hash_node *node)
{
  assert(node->bucket != NULL);

  dlinkDelete(&node->dnode, node->bucket);
  node->bucket = NULL;
}

static hash_node *
hash_find_node(struct hash_table *table, const unsigned char *key, void *what)
{
  unsigned int hashv, bucketv;
  hash_bucket *bucket;
  dlink_node *ptr;

  hashv = table->hash(key);
  bucketv = hash_fold(table, hashv);
  bucket = &table->buckets[bucketv];

  assert(bucketv < table->size);

  DLINK_FOREACH(ptr, bucket->head)
  {
    hash_node *node = (hash_node *) ptr;

    if (what)
    {
      if (node->dnode.data == what)
        return node;
    }
    else
    {
      if (hashv == node->hashv && !table->compare(node->key, key))
        return node;
    }
  }

  return NULL;
}

void
hash_del(struct hash_table *table, const unsigned char *key, void *what)
{
  hash_node *node = hash_find_node(table, key, what);
  if (node != NULL)
    hash_del_node(table, node);
}

void *
hash_find(struct hash_table *table, const unsigned char *key)
{
  hash_node *node = hash_find_node(table, key, NULL);
  hash_bucket *bucket;

  if (node == NULL)
    return NULL;

  bucket = node->bucket;

  /* move node to the beginning of the bucket */
  hash_del_node(table, node);

  node->bucket = bucket;
  dlinkAdd(node->dnode.data, &node->dnode, node->bucket);

  return node->dnode.data;
}

void
hash_get_stats(struct hash_table *table, unsigned int *restrict entries, unsigned int *restrict buckets, unsigned int *restrict maxchain)
{
  int i;

  *entries = 0;
  *buckets = table->size;
  *maxchain = 0;

  for (i = 0; i < table->size; ++i)
  {
    hash_bucket *bucket = &table->buckets[i];
    size_t len = dlink_list_length(bucket);

    *entries += len;

    if (len > *maxchain)
      *maxchain = len;
  }
}


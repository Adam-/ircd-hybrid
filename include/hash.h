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

/*! \file hash.h
 * \brief A header for the ircd hashtable code.
 * \version $Id$
 */

#ifndef INCLUDED_hash_h
#define INCLUDED_hash_h

#include "list.h"

#define FNV1_32_INIT 0x811c9dc5
#define FNV1_32_BITS 16
#define HASHSIZE FNV1_32_BITS /* 2^16 = 65536 */

typedef unsigned int (*hash_function)(const unsigned char *);
typedef int (*hash_compare)(const unsigned char *, const unsigned char *);

#define HASH(name, sz) \
  static hash_bucket name ## _buckets[(1 << sz)]; \
  struct hash_table name = \
  { \
    .power = sz, \
    .size = (1 << sz), \
    .hash = fnv_hash_ircstring_lower, \
    .compare = (hash_compare) irccmp, \
    .buckets = name ## _buckets \
  }

typedef dlink_list hash_bucket;
typedef struct hash_node hash_node;

struct hash_table
{
  size_t power;
  size_t size;
  hash_function hash;
  hash_compare compare;
  hash_bucket *buckets;
};

struct hash_node
{
  dlink_node dnode;
  const unsigned char *key;
  unsigned int hashv;
  hash_bucket *bucket;
};

extern void hash_init(void);
extern void hash_add(struct hash_table *table, hash_node *node, const unsigned char *key, void *what);
extern void hash_del_node(struct hash_table *table, hash_node *node);
extern void hash_del(struct hash_table *table, const unsigned char *key, void *what);
extern void *hash_find(struct hash_table *table, const unsigned char *key);
extern void hash_get_stats(struct hash_table *table, unsigned int *restrict entries, unsigned int *restrict buckets, unsigned int *restrict maxchain);

extern unsigned int hash_fold(struct hash_table *table, unsigned int hashv);
extern unsigned int fnv_hash_ircstring_lower(const unsigned char *name);
#endif  /* INCLUDED_hash_h */

/*
 *  ircd-hybrid: an advanced Internet Relay Chat Daemon(ircd).
 *  hash.h: A header for the ircd hashtable code.
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

#ifndef INCLUDED_hash_h
#define INCLUDED_hash_h

#define FNV1_32_INIT 0x811c9dc5
#define FNV1_32_BITS 16
#define FNV1_32_SIZE (1 << FNV1_32_BITS)  /* 2^16 = 65536 */
#define HASHSIZE FNV1_32_SIZE

struct Client;
struct Channel;
struct ResvChannel;
struct UserHost;
struct ListTask;

enum {
  HASH_TYPE_ID,
  HASH_TYPE_CLIENT,
  HASH_TYPE_CHANNEL,
  HASH_TYPE_USERHOST,
  HASH_TYPE_RESERVED
};

void init_hash(void);

EXTERN void hash_add_client(struct Client *);
EXTERN void hash_del_client(struct Client *);
EXTERN void hash_add_channel(struct Channel *);
EXTERN void hash_del_channel(struct Channel *);
EXTERN void hash_add_resv(struct ResvChannel *);
EXTERN void hash_del_resv(struct ResvChannel *);
EXTERN void hash_add_id(struct Client *);
EXTERN void hash_del_id(struct Client *);
EXTERN void hash_add_userhost(struct UserHost *);
EXTERN void hash_del_userhost(struct UserHost *);

EXTERN struct UserHost *hash_find_userhost(const char *);
EXTERN struct Client *hash_find_id(const char *);
EXTERN struct Client *find_client(const char *);
EXTERN struct Client *find_server(const char *);
EXTERN struct Channel *hash_find_channel(const char *);
EXTERN void *hash_get_bucket(int, unsigned int);
EXTERN struct ResvChannel *hash_find_resv(const char *);

EXTERN void free_list_task(struct ListTask *, struct Client *);
EXTERN void safe_list_channels(struct Client *, struct ListTask *, int);

EXTERN unsigned int strhash(const char *);
#endif  /* INCLUDED_hash_h */

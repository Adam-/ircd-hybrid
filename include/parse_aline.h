/*
 *  ircd-hybrid: an advanced Internet Relay Chat Daemon(ircd).
 *  s_conf.h: A header for the configuration functions.
 *
 *  Copyright (C) 2005 by the past and present ircd coders, and others.
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

#ifndef INCLUDED_parse_aline_h
#define INCLUDED_parse_aline_h
#include "setup.h"

EXTERN dlink_list rxconf_items;
EXTERN dlink_list rkconf_items;
EXTERN dlink_list temporary_klines;
EXTERN dlink_list temporary_dlines;
EXTERN dlink_list temporary_glines;
EXTERN dlink_list temporary_xlines;
EXTERN dlink_list temporary_rxlines;
EXTERN dlink_list temporary_rklines;

EXTERN void cluster_a_line(struct Client *,
			   const char *, int, int, const char *,...);
EXTERN int valid_wild_card(struct Client *, int, int, ...);

#define CLEANUP_TKLINES_TIME 60
#define TK_SECONDS 0
#define TK_MINUTES 1
EXTERN time_t valid_tkline(char *, int);

#define AWILD 0x1		/* check wild cards */
#define NOUSERLOOKUP 0x2 /* Don't lookup the user@host on /rkline nick */
EXTERN int parse_aline(const char *, struct Client *, int, char **,
		       int, char **, char **, time_t *, char **, char **);
EXTERN int valid_comment(struct Client *, char *, int);
EXTERN struct AccessItem *find_kill(struct Client *);
EXTERN struct AccessItem *find_gline(struct Client *);
EXTERN struct AccessItem *find_regexp_kline(const char *[]);

EXTERN void cleanup_tklines(void *);
EXTERN void add_temp_line(struct ConfItem *);
#endif /* INCLUDED_parse_aline_h */

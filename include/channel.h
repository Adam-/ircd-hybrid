/*
 *  ircd-hybrid: an advanced Internet Relay Chat Daemon(ircd).
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
 */

/*! \file channel.h
 * \brief Responsible for managing channels, members, bans and topics
 * \version $Id$
 */

#ifndef INCLUDED_channel_h
#define INCLUDED_channel_h

#include "ircd_defs.h"        /* KEYLEN, CHANNELLEN */

struct Client;

/*! \brief Mode structure for channels */
struct Mode
{
  unsigned int mode;   /*!< simple modes */
  unsigned int limit;  /*!< +l userlimit */
  char key[KEYLEN];    /*!< +k key */
};

/*! \brief Channel structure */
struct Channel
{
  dlink_node node;

  struct Channel *hnextch;

  struct Mode mode;
  char *topic;
  char *topic_info;
  time_t topic_time;
  time_t last_knock; /*!< don't allow knock to flood */

  dlink_list members;
  dlink_list invites;
  dlink_list banlist;
  dlink_list exceptlist;
  dlink_list invexlist;

  time_t first_received_message_time; /*!< channel flood control */
  int received_number_of_privmsgs;
  int flags;
  float number_joined;
  time_t last_join_time;

  time_t channelts;
  char chname[CHANNELLEN + 1];
};

/*! \brief Membership structure */
struct Membership
{
  dlink_node channode;     /*!< link to chptr->members    */
  dlink_node usernode;     /*!< link to source_p->channel */
  struct Channel *chptr;   /*!< Channel pointer */
  struct Client *client_p; /*!< Client pointer */
  unsigned int flags;      /*!< user/channel flags, e.g. CHFL_CHANOP */
};

/*! \brief Ban structure.  Used for b/e/I n!u\@h masks */
struct Ban
{
  dlink_node node;
  size_t len;
  char *name;
  char *username;
  char *host;
  char *who;
  struct irc_ssaddr addr;
  int bits;
  char type;
  time_t when;
};

EXTERN dlink_list global_channel_list;

EXTERN void init_channels(void);

EXTERN int check_channel_name(const char *, int);
EXTERN int can_send(struct Channel *, struct Client *, struct Membership *);
EXTERN int is_banned(const struct Channel *, const struct Client *);
EXTERN int can_join(struct Client *, struct Channel *, const char *);
EXTERN int has_member_flags(struct Membership *, unsigned int);

EXTERN void remove_ban(struct Ban *, dlink_list *);
EXTERN void add_user_to_channel(struct Channel *, struct Client *,
                                unsigned int, int);
EXTERN void remove_user_from_channel(struct Membership *);
EXTERN void channel_member_names(struct Client *, struct Channel *, int);
EXTERN void add_invite(struct Channel *, struct Client *);
EXTERN void del_invite(struct Channel *, struct Client *);
EXTERN void send_channel_modes(struct Client *, struct Channel *);
EXTERN void channel_modes(struct Channel *, struct Client *, char *, char *);
EXTERN void check_spambot_warning(struct Client *, const char *);
EXTERN void check_splitmode(void *);
EXTERN void free_channel_list(dlink_list *);
EXTERN void free_topic(struct Channel *);
EXTERN void destroy_channel(struct Channel *);
EXTERN void set_channel_topic(struct Channel *, const char *, const char *, time_t);

EXTERN const char *get_member_status(const struct Membership *, int);

EXTERN struct Channel *make_channel(const char *);
EXTERN struct Membership *find_channel_link(struct Client *, struct Channel *);

/* channel visible */
#define ShowChannel(v,c)        (PubChannel(c) || IsMember((v),(c)))

#define IsMember(who, chan) ((find_channel_link(who, chan)) ? 1 : 0)
#define AddMemberFlag(x, y) ((x)->flags |=  (y))
#define DelMemberFlag(x, y) ((x)->flags &= ~(y))

#define FLOOD_NOTICED		1
#define JOIN_FLOOD_NOTICED	2

#define SetMsgFloodNoticed(x)   ((x)->flags |= FLOOD_NOTICED)
#define IsMsgFloodNoticed(x) ((x)->flags & FLOOD_NOTICED)
#define ClearMsgFloodNoticed(x) ((x)->flags &= ~FLOOD_NOTICED)

#define SetJoinFloodNoticed(x)   ((x)->flags |= JOIN_FLOOD_NOTICED)
#define IsSetJoinFloodNoticed(x) ((x)->flags & JOIN_FLOOD_NOTICED)
#define ClearJoinFloodNoticed(x) ((x)->flags &= ~JOIN_FLOOD_NOTICED)

#endif  /* INCLUDED_channel_h */

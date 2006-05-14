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

#ifndef INCLUDED_s_conf_h
#define INCLUDED_s_conf_h
#include "setup.h"
#ifdef HAVE_LIBCRYPTO
#include <openssl/rsa.h>
#endif
#include "ircd_defs.h"
#include "motd.h"               /* MessageFile */
#include "client.h"
#include "resv.h"

struct Client;
struct DNSReply;
struct hostent;

extern FBFILE *conf_fbfile_in;
extern struct Callback *client_check_cb;

struct CidrItem
{
  struct irc_ssaddr mask;
  int number_on_this_cidr;
  dlink_node node;
};

struct split_nuh_item
{
  dlink_node node;

  char *nuhmask;
  char *nickptr;
  char *userptr;
  char *hostptr;

  size_t nicksize;
  size_t usersize;
  size_t hostsize;
};

struct gline_pending
{
  dlink_node node;

  struct {
    char nick[NICKLEN + 1];
    char user[USERLEN + 1];
    char host[HOSTLEN + 1];
    char server[HOSTLEN + 1];
    char reason[REASONLEN + 1];
    time_t time_request;
  } request1, request2;

  time_t last_gline_time;    /* for expiring entry */
  char user[USERLEN * 2 + 2];
  char host[HOSTLEN * 2 + 2];
};

/*
 * how long a pending G line can be around
 * 10 minutes should be plenty
 */
#define GLINE_PENDING_EXPIRE 600
#define CLEANUP_GLINES_TIME  300

EXTERN dlink_list pending_glines;

#define ConFreq(x)	((x)->con_freq)
#define PingFreq(x)	((x)->ping_freq)
#define PingWarning(x)  ((x)->ping_warning)
#define MaxTotal(x)	((x)->max_total)
#define MaxGlobal(x)	((x)->max_global)
#define MaxLocal(x)	((x)->max_local)
#define MaxIdent(x)	((x)->max_ident)
#define MaxPerIp(x)	((x)->max_perip)
#define MaxSendq(x)	((x)->max_sendq)
#define CurrUserCount(x) ((x)->curr_user_count)
#define CidrBitlenIPV4(x)	((x)->cidr_bitlen_ipv4)
#define CidrBitlenIPV6(x)	((x)->cidr_bitlen_ipv6)
#define NumberPerCidr(x) ((x)->number_per_cidr)

#define ClassPtr(x)      ((x)->class_ptr)


#define CONF_ILLEGAL            0x80000000
#define CONF_RESERVED           0x00000001
#define CONF_CLIENT             0x00000002
#define CONF_SERVER             0x00000004
#define CONF_OPERATOR           0x00000008
#define CONF_KILL               0x00000010
#define CONF_KLINE              CONF_KILL
#define CONF_CLASS              0x00000020
#define CONF_LEAF               0x00000040
#define CONF_LISTEN_PORT        0x00000080
#define CONF_HUB                0x00000100
#define CONF_EXEMPTKLINE        0x00000200
#define CONF_NOLIMIT            0x00000400
#define CONF_DLINE              0x00000800
#define CONF_XLINE              0x00001000
#define CONF_ULINE              0x00002000
#define CONF_EXEMPTDLINE        0x00004000
#define CONF_GLINE              0x00008000

#define CONF_SERVER_MASK       CONF_SERVER
#define CONF_CLIENT_MASK       (CONF_CLIENT | CONF_OPERATOR | CONF_SERVER_MASK)

/* XXX temporary hack */
#define CONF_CRESV	        0x80000001
#define CONF_NRESV	        0x80000002

#define IsConfIllegal(x)	((x)->status & CONF_ILLEGAL)
#define SetConfIllegal(x)	((x)->status |= CONF_ILLEGAL)
#define IsConfServer(x)		((x)->status == CONF_SERVER)
#define SetConfServer(x)	((x)->status = CONF_SERVER)
#define IsConfOperator(x)	((x)->status & CONF_OPERATOR)
#define IsConfHub(x)		((x)->status == CONF_HUB)
#define SetConfHub(x)		((x)->status = CONF_HUB)
#define IsConfLeaf(x)		((x)->status == CONF_LEAF)
#define SetConfLeaf(x)		((x)->status = CONF_LEAF)
#define IsConfHubOrLeaf(x)	((x)->status & (CONF_HUB|CONF_LEAF))
#define IsConfKill(x)		((x)->status == CONF_KILL)
#define IsConfClient(x)		((x)->status & CONF_CLIENT)
#define IsConfTypeOfClient(x)	((x)->status & CONF_CLIENT_MASK)
#define IsConfUline(x)		((x)->status & CONF_ULINE)
#define IsConfXline(x)		((x)->status & CONF_XLINE)
#define IsConfGline(x)          ((x)->status == CONF_GLINE)

/* AccessItem->flags */

/* Generic flags... */
/* access flags... */
#define CONF_FLAGS_DO_IDENTD            0x00000001
#define CONF_FLAGS_LIMIT_IP             0x00000002
#define CONF_FLAGS_NO_TILDE             0x00000004
#define CONF_FLAGS_NEED_IDENTD          0x00000008
/*                                      0x00000010 */
#define CONF_FLAGS_NOMATCH_IP           0x00000020
#define CONF_FLAGS_EXEMPTKLINE          0x00000040
#define CONF_FLAGS_NOLIMIT              0x00000080
#define CONF_FLAGS_IDLE_LINED           0x00000100
#define CONF_FLAGS_SPOOF_IP             0x00000200
#define CONF_FLAGS_SPOOF_NOTICE         0x00000400
#define CONF_FLAGS_REDIR                0x00000800
#define CONF_FLAGS_EXEMPTGLINE          0x00001000
#define CONF_FLAGS_RESTRICTED           0x00002000
#define CONF_FLAGS_CAN_FLOOD            0x00100000
#define CONF_FLAGS_NEED_PASSWORD        0x00200000
/* server flags */
#define CONF_FLAGS_ALLOW_AUTO_CONN      0x00004000
#define CONF_FLAGS_ENCRYPTED            0x00010000
#define CONF_FLAGS_COMPRESSED           0x00020000
#define CONF_FLAGS_TEMPORARY            0x00040000
#define CONF_FLAGS_CRYPTLINK            0x00080000
#define CONF_FLAGS_BURST_AWAY           0x00400000
#define CONF_FLAGS_EXEMPTRESV           0x00800000
#define CONF_FLAGS_TOPICBURST           0x01000000

/* Macros for struct AccessItem */
#define IsLimitIp(x)            ((x)->flags & CONF_FLAGS_LIMIT_IP)
#define IsNoTilde(x)            ((x)->flags & CONF_FLAGS_NO_TILDE)
#define IsConfCanFlood(x)       ((x)->flags & CONF_FLAGS_CAN_FLOOD)
#define IsNeedPassword(x)       ((x)->flags & CONF_FLAGS_NEED_PASSWORD)
#define IsNeedIdentd(x)         ((x)->flags & CONF_FLAGS_NEED_IDENTD)
#define IsNoMatchIp(x)          ((x)->flags & CONF_FLAGS_NOMATCH_IP)
#define IsConfExemptKline(x)    ((x)->flags & CONF_FLAGS_EXEMPTKLINE)
#define IsConfExemptLimits(x)   ((x)->flags & CONF_FLAGS_NOLIMIT)
#define IsConfExemptGline(x)    ((x)->flags & CONF_FLAGS_EXEMPTGLINE)
#define IsConfExemptResv(x)     ((x)->flags & CONF_FLAGS_EXEMPTRESV)
#define IsConfIdlelined(x)      ((x)->flags & CONF_FLAGS_IDLE_LINED)
#define IsConfDoIdentd(x)       ((x)->flags & CONF_FLAGS_DO_IDENTD)
#define IsConfDoSpoofIp(x)      ((x)->flags & CONF_FLAGS_SPOOF_IP)
#define IsConfSpoofNotice(x)    ((x)->flags & CONF_FLAGS_SPOOF_NOTICE)
#define IsConfRestricted(x)     ((x)->flags & CONF_FLAGS_RESTRICTED)
#define IsConfEncrypted(x)      ((x)->flags & CONF_FLAGS_ENCRYPTED)
#define SetConfEncrypted(x)	((x)->flags |= CONF_FLAGS_ENCRYPTED)
#define ClearConfEncrypted(x)	((x)->flags &= ~CONF_FLAGS_ENCRYPTED)
#define IsConfCompressed(x)     ((x)->flags & CONF_FLAGS_COMPRESSED)
#define SetConfCompressed(x)    ((x)->flags |= CONF_FLAGS_COMPRESSED)
#define ClearConfCompressed(x)  ((x)->flags &= ~CONF_FLAGS_COMPRESSED)
#define IsConfCryptLink(x)      ((x)->flags & CONF_FLAGS_CRYPTLINK)
#define SetConfCryptLink(x)     ((x)->flags |= CONF_FLAGS_CRYPTLINK)
#define ClearConfCryptLink(x)   ((x)->flags &= ~CONF_FLAGS_CRYPTLINK)
#define IsConfAllowAutoConn(x)  ((x)->flags & CONF_FLAGS_ALLOW_AUTO_CONN)
#define SetConfAllowAutoConn(x)	((x)->flags |= CONF_FLAGS_ALLOW_AUTO_CONN)
#define ClearConfAllowAutoConn(x) ((x)->flags &= ~CONF_FLAGS_ALLOW_AUTO_CONN)
#define IsConfTemporary(x)      ((x)->flags & CONF_FLAGS_TEMPORARY)
#define SetConfTemporary(x)     ((x)->flags |= CONF_FLAGS_TEMPORARY)
#define IsConfRedir(x)          ((x)->flags & CONF_FLAGS_REDIR)
#define IsConfAwayBurst(x)      ((x)->flags & CONF_FLAGS_BURST_AWAY)
#define SetConfAwayBurst(x)     ((x)->flags |= CONF_FLAGS_BURST_AWAY)
#define ClearConfAwayBurst(x)   ((x)->flags &= ~CONF_FLAGS_BURST_AWAY)
#define IsConfTopicBurst(x)     ((x)->flags & CONF_FLAGS_TOPICBURST)
#define SetConfTopicBurst(x)    ((x)->flags |= CONF_FLAGS_TOPICBURST)
#define ClearConfTopicBurst(x)  ((x)->flags &= ~CONF_FLAGS_TOPICBURST)

/* shared/cluster server entry types 
 * These defines are used for both shared and cluster.
 */
#define SHARED_KLINE		0x0001
#define SHARED_TKLINE		0x0002
#define SHARED_UNKLINE		0x0004
#define SHARED_XLINE		0x0008
#define SHARED_TXLINE		0x0010
#define SHARED_UNXLINE		0x0020
#define SHARED_RESV		0x0040
#define SHARED_TRESV		0x0080
#define SHARED_UNRESV		0x0100
#define SHARED_LOCOPS           0x0200
#define SHARED_ALL		(SHARED_KLINE | SHARED_TKLINE | SHARED_UNKLINE | \
				 SHARED_XLINE | SHARED_TXLINE | SHARED_UNXLINE | \
				 SHARED_RESV | SHARED_TRESV | SHARED_UNRESV |\
                                 SHARED_LOCOPS)

/* gline acl entry actions */
#define GDENY_BLOCK		0x1
#define GDENY_REJECT		0x2

typedef enum
{  
  CONF_TYPE, 
  CLASS_TYPE,
  OPER_TYPE,
  CLIENT_TYPE,
  SERVER_TYPE,
  HUB_TYPE,
  LEAF_TYPE,
  KLINE_TYPE,
  DLINE_TYPE,
  EXEMPTDLINE_TYPE,
  CLUSTER_TYPE,
  RKLINE_TYPE,
  RXLINE_TYPE,
  XLINE_TYPE,    
  ULINE_TYPE,
  GLINE_TYPE,
  CRESV_TYPE,     
  NRESV_TYPE,
  GDENY_TYPE
} ConfType;


/*
 * MatchItem - used for XLINE and ULINE types
 */
struct MatchItem
{
  void *conf_ptr;       /* pointer back to conf */
  char *user;           /* Used for ULINE only */
  char *host;           /* Used for ULINE only */
  char *reason;
  char *oper_reason;
  int action;           /* used for uline */
  int count;            /* How many times this matchitem has been matched */
  int ref_count;        /* How many times is this matchitem in use */
  int illegal;          /* Should it be deleted when possible? */
  time_t hold;     /* Hold action until this time (calendar time) */
};

struct AccessItem
{
  void *conf_ptr;            /* pointer back to conf */
  dlink_node node;
  unsigned int     status;   /* If CONF_ILLEGAL, delete when no clients */
  unsigned int     flags;
  unsigned int     modes;
  struct irc_ssaddr my_ipnum; /* ip to bind to for outgoing connect */
  struct irc_ssaddr ipnum;	/* ip to connect to */
  char *           host;     /* host part of user@host */
  char *           passwd;
  char *           spasswd;  /* Password to send. */
  char *	   reason;
  char *	   oper_reason;
  char *           user;     /* user part of user@host */
  int              port;
  char *           fakename;   /* Mask name */
  time_t           hold;     /* Hold action until this time (calendar time) */
  struct ConfItem *class_ptr;  /* Class of connection */
  struct DNSQuery* dns_query;
  int              aftype;
#ifdef HAVE_LIBCRYPTO
  char *           rsa_public_key_file;
  RSA *            rsa_public_key;
  struct EncCapability *cipher_preference;
#endif
  pcre *regexuser;
  pcre *regexhost;
};

struct ClassItem
{
  void *conf_ptr;          /* pointer back to conf */
  long max_sendq;
  int con_freq;
  int ping_freq;
  int ping_warning;
  int max_total;
  int max_local;
  int max_global;
  int max_ident;
  int max_perip;
  int curr_user_count;
  int cidr_bitlen_ipv4;
  int cidr_bitlen_ipv6;
  int number_per_cidr;
  dlink_list list_ipv4;         /* base of per cidr ipv4 client link list */
  dlink_list list_ipv6;         /* base of per cidr ipv6 client link list */
};

struct ConfItem
{
  char *name;		/* Primary key */
  pcre *regexpname;
  dlink_node node;	/* link into known ConfItems of this type */
  unsigned int flags;
  ConfType type;
  dlink_list mask_list;

  union
  {
    struct MatchItem MatchItem;
    struct AccessItem AccessItem;
    struct ClassItem ClassItem;
    struct ResvChannel ResvChannel;
  } conf;
};

struct conf_item_table_type
{
  size_t size;
  int status;
  dlink_list *list;
  void (*freer)(struct ConfItem *, dlink_list *);
};

struct config_file_entry
{
  const char *dpath;          /* DPATH if set from command line */
  const char *configfile;
  const char *klinefile;
  const char *xlinefile;
  const char *rxlinefile;
  const char *rklinefile;
  const char *dlinefile;
  const char *glinefile;
  const char *cresvfile;
  const char *nresvfile;

  char *logpath;
  char *operlog;

  char *servlink_path;
  char *egdpool_path;

  MessageFile motd;
  MessageFile opermotd;
  MessageFile linksfile;

  unsigned char compression_level;
  int max_watch;
  int gline_min_cidr;
  int gline_min_cidr6;
  int dot_in_ip6_addr;
  int dots_in_ident;
  int failed_oper_notice;
  int anti_spam_exit_message_time;
  int max_accept;
  int max_nick_time;
  int max_nick_changes;
  int ts_max_delta;
  int ts_warn_delta;
  int anti_nick_flood;
  int kline_with_reason;
  int warn_no_nline;
  int invisible_on_connect;
  int stats_o_oper_only;
  int stats_k_oper_only;
  int stats_i_oper_only;
  int stats_P_oper_only;
  int short_motd;
  int no_oper_flood;
  int true_no_oper_flood;
  int oper_pass_resv;
  int glines;
  int hide_spoof_ips;
  int burst_away;
  int use_whois_actually;
  int tkline_expire_notices;
  int opers_bypass_callerid;
  int ignore_bogus_ts;
  char *kline_reason;
  int pace_wait;
  int pace_wait_simple;
  int gline_time;
  int gline_logging;
  int idletime;
  int oper_only_umodes;
  int oper_umodes;
  int max_targets;
  int caller_id_wait;
  int min_nonwildcard;
  int min_nonwildcard_simple;
  int kill_chase_time_limit;
  int default_floodcount;
  int client_flood;
  /* 0 == don't use throttle... */
  int throttle_time;
  int use_egd;
  int ping_cookie;
  int disable_auth;
  int disable_remote;
#ifdef HAVE_LIBCRYPTO
  struct EncCapability *default_cipher_preference;
#endif
};

struct config_channel_entry
{
  int restrict_channels;
  int disable_local_channels;
  int use_except;
  int use_invex;
  int use_knock;
  int knock_delay;
  int knock_delay_channel;
  unsigned int max_bans;
  unsigned int max_chans_per_user;
  int no_create_on_split;
  int no_join_on_split;
  int quiet_on_ban;
  int burst_topicwho;
  int default_split_server_count;
  int default_split_user_count;
};

struct config_server_hide
{
  int flatten_links;
  int hide_servers;
  char *hidden_name;
  int links_delay;
  int links_disabled;
  int hidden;
  int disable_hidden;
  int hide_server_ips;
};

struct server_info
{
  char *name;
  char *description;
  char *network_name;
  char *network_desc;
#ifdef HAVE_LIBCRYPTO
  char *rsa_private_key_file;
  RSA *rsa_private_key;
  SSL_CTX *ctx;
#endif
  char *sid;
  int hub;
  struct irc_ssaddr ip;
  struct irc_ssaddr ip6;
  int max_clients;
  int specific_ipv4_vhost;
  int specific_ipv6_vhost;
  struct sockaddr_in dns_host;
  int can_use_v6;
};

struct admin_info
{
  char *name;
  char *description;
  char *email;
};

struct logging_entry
{
  unsigned int use_logging;
  char operlog[PATH_MAX + 1];
  char userlog[PATH_MAX + 1];
  char glinelog[PATH_MAX + 1];
  char ioerrlog[PATH_MAX + 1];
  char klinelog[PATH_MAX + 1];
  char killlog[PATH_MAX + 1];
  char operspylog[PATH_MAX + 1];
  char failed_operlog[PATH_MAX + 1];
};

void init_class(void);
void check_class(void);
void init_ip_hash_table(void);
void yyerror(const char *);
int conf_yy_fatal_error(const char *);
void read_conf_files(int);
int yylex(void);
void rebuild_cidr_class(struct ClassItem *, struct ClassItem *);

EXTERN int ypass;
EXTERN dlink_list class_items;
EXTERN dlink_list server_items;
EXTERN dlink_list cluster_items;
EXTERN dlink_list hub_items;
EXTERN dlink_list leaf_items;
EXTERN struct logging_entry ConfigLoggingEntry;
EXTERN struct config_file_entry ConfigFileEntry;/* defined in ircd.c*/
EXTERN struct config_channel_entry ConfigChannel;/* defined in channel.c*/
EXTERN struct config_server_hide ConfigServerHide; /* defined in s_conf.c */
EXTERN struct server_info ServerInfo;       /* defined in ircd.c */
EXTERN struct admin_info AdminInfo;        /* defined in ircd.c */

/* End GLOBAL section */

EXTERN unsigned long get_sendq(struct Client *);
EXTERN const char *get_client_className(struct Client *);
EXTERN int get_client_ping(struct Client *, int *);
EXTERN struct ConfItem *find_class(const char *);
EXTERN void count_ip_hash(int *, unsigned long *);
EXTERN void remove_one_ip(struct irc_ssaddr *);
EXTERN struct ConfItem *make_conf_item(ConfType);
EXTERN int attach_class(struct Client *, struct ConfItem *);
EXTERN int attach_connect_block(struct Client *, const char *, const char *);
EXTERN int attach_server_conf(struct Client *, struct ConfItem *);
EXTERN int attach_leaf_hub(struct Client *, struct ConfItem *);
EXTERN int detach_confs(struct Client *);

EXTERN int conf_connect_allowed(const struct irc_ssaddr *);
EXTERN char *oper_privs_as_string(const unsigned int);
EXTERN void split_nuh(struct split_nuh_item *);
EXTERN struct ConfItem *find_matching_name_conf(ConfType, const char *,
                                                const char *, const char *, int);
EXTERN struct ConfItem *find_exact_name_conf(ConfType, const char *,
                                             const char *, const char *);
EXTERN void delete_conf_item(struct ConfItem *);
EXTERN void report_confitem_types(struct Client *, ConfType, int);
EXTERN int conf_fbgets(char *, unsigned int, FBFILE *);
EXTERN void write_conf_line(struct Client *, struct ConfItem *,
                            const char *, time_t);
EXTERN int remove_conf_line(ConfType, struct Client *, const char *,
                            const char *);

EXTERN const char *get_conf_name(ConfType);
EXTERN int rehash(int);
EXTERN int conf_add_server(struct ConfItem *, const char *);
EXTERN void conf_add_class_to_conf(struct ConfItem *, const char *);
EXTERN void conf_add_d_conf(struct AccessItem *);

/* XXX consider moving these into csvlib.h */
EXTERN void parse_csv_file(FBFILE *, ConfType);

EXTERN char *get_oper_name(const struct Client *);

EXTERN int match_conf_password(const char *, const struct AccessItem *);

#define NOT_AUTHORIZED    (-1)
#define I_LINE_FULL       (-2)
#define TOO_MANY          (-3)
#define BANNED_CLIENT     (-4)
#define TOO_FAST          (-5)

#endif /* INCLUDED_s_conf_h */

/* A Bison parser, made by GNU Bison 2.5.1.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 25 "conf_parser.y"


#define YY_NO_UNPUT
#include <sys/types.h>
#include <string.h>

#include "config.h"
#include "stdinc.h"
#include "ircd.h"
#include "list.h"
#include "conf.h"
#include "event.h"
#include "log.h"
#include "client.h"	/* for UMODE_ALL only */
#include "irc_string.h"
#include "sprintf_irc.h"
#include "memory.h"
#include "modules.h"
#include "s_serv.h"
#include "hostmask.h"
#include "send.h"
#include "listener.h"
#include "resv.h"
#include "numeric.h"
#include "s_user.h"

#ifdef HAVE_LIBCRYPTO
#include <openssl/rsa.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/dh.h>
#endif

int yylex(void);

static char *class_name = NULL;
static struct ConfItem *yy_conf = NULL;
static struct AccessItem *yy_aconf = NULL;
static struct MatchItem *yy_match_item = NULL;
static struct ClassItem *yy_class = NULL;
static char *yy_class_name = NULL;

static dlink_list col_conf_list  = { NULL, NULL, 0 };
static unsigned int listener_flags = 0;
static unsigned int regex_ban = 0;
static char userbuf[IRCD_BUFSIZE];
static char hostbuf[IRCD_BUFSIZE];
static char reasonbuf[REASONLEN + 1];
static char gecos_name[REALLEN * 4];
static char lfile[IRCD_BUFSIZE];
static unsigned int ltype = 0;
static unsigned int lsize = 0;
static char *resv_reason = NULL;
static char *listener_address = NULL;

struct CollectItem
{
  dlink_node node;
  char *name;
  char *user;
  char *host;
  char *passwd;
  int  port;
  int  flags;
#ifdef HAVE_LIBCRYPTO
  char *rsa_public_key_file;
  RSA *rsa_public_key;
#endif
};

static void
free_collect_item(struct CollectItem *item)
{
  MyFree(item->name);
  MyFree(item->user);
  MyFree(item->host);
  MyFree(item->passwd);
#ifdef HAVE_LIBCRYPTO
  MyFree(item->rsa_public_key_file);
#endif
  MyFree(item);
}



/* Line 268 of yacc.c  */
#line 157 "conf_parser.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ACCEPT_PASSWORD = 258,
     ACTION = 259,
     ADMIN = 260,
     AFTYPE = 261,
     T_ALLOW = 262,
     ANTI_NICK_FLOOD = 263,
     ANTI_SPAM_EXIT_MESSAGE_TIME = 264,
     AUTOCONN = 265,
     T_BLOCK = 266,
     BURST_AWAY = 267,
     BYTES = 268,
     KBYTES = 269,
     MBYTES = 270,
     GBYTES = 271,
     TBYTES = 272,
     CALLER_ID_WAIT = 273,
     CAN_FLOOD = 274,
     CHANNEL = 275,
     CIDR_BITLEN_IPV4 = 276,
     CIDR_BITLEN_IPV6 = 277,
     CLASS = 278,
     CONNECT = 279,
     CONNECTFREQ = 280,
     DEFAULT_FLOODCOUNT = 281,
     DEFAULT_SPLIT_SERVER_COUNT = 282,
     DEFAULT_SPLIT_USER_COUNT = 283,
     DENY = 284,
     DESCRIPTION = 285,
     DIE = 286,
     DISABLE_AUTH = 287,
     DISABLE_FAKE_CHANNELS = 288,
     DISABLE_HIDDEN = 289,
     DISABLE_LOCAL_CHANNELS = 290,
     DISABLE_REMOTE_COMMANDS = 291,
     DOTS_IN_IDENT = 292,
     DURATION = 293,
     EGDPOOL_PATH = 294,
     EMAIL = 295,
     ENABLE = 296,
     ENCRYPTED = 297,
     EXCEED_LIMIT = 298,
     EXEMPT = 299,
     FAILED_OPER_NOTICE = 300,
     IRCD_FLAGS = 301,
     FLATTEN_LINKS = 302,
     GECOS = 303,
     GENERAL = 304,
     GLINE = 305,
     GLINES = 306,
     GLINE_EXEMPT = 307,
     GLINE_TIME = 308,
     GLINE_MIN_CIDR = 309,
     GLINE_MIN_CIDR6 = 310,
     GLOBAL_KILL = 311,
     IRCD_AUTH = 312,
     NEED_IDENT = 313,
     HAVENT_READ_CONF = 314,
     HIDDEN = 315,
     HIDDEN_NAME = 316,
     HIDE_SERVER_IPS = 317,
     HIDE_SERVERS = 318,
     HIDE_SPOOF_IPS = 319,
     HOST = 320,
     HUB = 321,
     HUB_MASK = 322,
     IGNORE_BOGUS_TS = 323,
     INVISIBLE_ON_CONNECT = 324,
     IP = 325,
     KILL = 326,
     KILL_CHASE_TIME_LIMIT = 327,
     KLINE = 328,
     KLINE_EXEMPT = 329,
     KLINE_REASON = 330,
     KLINE_WITH_REASON = 331,
     KNOCK_DELAY = 332,
     KNOCK_DELAY_CHANNEL = 333,
     LEAF_MASK = 334,
     LINKS_DELAY = 335,
     LISTEN = 336,
     T_LOG = 337,
     MAX_ACCEPT = 338,
     MAX_BANS = 339,
     MAX_CHANS_PER_OPER = 340,
     MAX_CHANS_PER_USER = 341,
     MAX_GLOBAL = 342,
     MAX_IDENT = 343,
     MAX_LOCAL = 344,
     MAX_NICK_CHANGES = 345,
     MAX_NICK_TIME = 346,
     MAX_NUMBER = 347,
     MAX_TARGETS = 348,
     MAX_WATCH = 349,
     MESSAGE_LOCALE = 350,
     MIN_NONWILDCARD = 351,
     MIN_NONWILDCARD_SIMPLE = 352,
     MODULE = 353,
     MODULES = 354,
     NAME = 355,
     NEED_PASSWORD = 356,
     NETWORK_DESC = 357,
     NETWORK_NAME = 358,
     NICK = 359,
     NICK_CHANGES = 360,
     NO_CREATE_ON_SPLIT = 361,
     NO_JOIN_ON_SPLIT = 362,
     NO_OPER_FLOOD = 363,
     NO_TILDE = 364,
     NUMBER = 365,
     NUMBER_PER_IDENT = 366,
     NUMBER_PER_CIDR = 367,
     NUMBER_PER_IP = 368,
     NUMBER_PER_IP_GLOBAL = 369,
     OPERATOR = 370,
     OPERS_BYPASS_CALLERID = 371,
     OPER_ONLY_UMODES = 372,
     OPER_PASS_RESV = 373,
     OPER_SPY_T = 374,
     OPER_UMODES = 375,
     JOIN_FLOOD_COUNT = 376,
     JOIN_FLOOD_TIME = 377,
     PACE_WAIT = 378,
     PACE_WAIT_SIMPLE = 379,
     PASSWORD = 380,
     PATH = 381,
     PING_COOKIE = 382,
     PING_TIME = 383,
     PING_WARNING = 384,
     PORT = 385,
     QSTRING = 386,
     QUIET_ON_BAN = 387,
     REASON = 388,
     REDIRPORT = 389,
     REDIRSERV = 390,
     REGEX_T = 391,
     REHASH = 392,
     TREJECT_HOLD_TIME = 393,
     REMOTE = 394,
     REMOTEBAN = 395,
     RESTRICT_CHANNELS = 396,
     RESTRICTED = 397,
     RSA_PRIVATE_KEY_FILE = 398,
     RSA_PUBLIC_KEY_FILE = 399,
     SSL_CERTIFICATE_FILE = 400,
     SSL_DH_PARAM_FILE = 401,
     T_SSL_CLIENT_METHOD = 402,
     T_SSL_SERVER_METHOD = 403,
     T_SSLV3 = 404,
     T_TLSV1 = 405,
     RESV = 406,
     RESV_EXEMPT = 407,
     SECONDS = 408,
     MINUTES = 409,
     HOURS = 410,
     DAYS = 411,
     WEEKS = 412,
     SENDQ = 413,
     SEND_PASSWORD = 414,
     SERVERHIDE = 415,
     SERVERINFO = 416,
     IRCD_SID = 417,
     TKLINE_EXPIRE_NOTICES = 418,
     T_SHARED = 419,
     T_CLUSTER = 420,
     TYPE = 421,
     SHORT_MOTD = 422,
     SILENT = 423,
     SPOOF = 424,
     SPOOF_NOTICE = 425,
     STATS_E_DISABLED = 426,
     STATS_I_OPER_ONLY = 427,
     STATS_K_OPER_ONLY = 428,
     STATS_O_OPER_ONLY = 429,
     STATS_P_OPER_ONLY = 430,
     TBOOL = 431,
     TMASKED = 432,
     T_REJECT = 433,
     TS_MAX_DELTA = 434,
     TS_WARN_DELTA = 435,
     TWODOTS = 436,
     T_ALL = 437,
     T_BOTS = 438,
     T_SOFTCALLERID = 439,
     T_CALLERID = 440,
     T_CCONN = 441,
     T_CCONN_FULL = 442,
     T_SSL_CIPHER_LIST = 443,
     T_CLIENT_FLOOD = 444,
     T_DEAF = 445,
     T_DEBUG = 446,
     T_DLINE = 447,
     T_DRONE = 448,
     T_EXTERNAL = 449,
     T_FULL = 450,
     T_INVISIBLE = 451,
     T_IPV4 = 452,
     T_IPV6 = 453,
     T_LOCOPS = 454,
     T_MAX_CLIENTS = 455,
     T_NCHANGE = 456,
     T_OPERWALL = 457,
     T_REJ = 458,
     T_SERVER = 459,
     T_SERVNOTICE = 460,
     T_SKILL = 461,
     T_SPY = 462,
     T_SSL = 463,
     T_UMODES = 464,
     T_UNAUTH = 465,
     T_UNDLINE = 466,
     T_UNLIMITED = 467,
     T_UNRESV = 468,
     T_UNXLINE = 469,
     T_GLOBOPS = 470,
     T_WALLOP = 471,
     T_RESTART = 472,
     T_SERVICE = 473,
     T_SERVICES_NAME = 474,
     THROTTLE_TIME = 475,
     TOPICBURST = 476,
     TRUE_NO_OPER_FLOOD = 477,
     TKLINE = 478,
     TXLINE = 479,
     TRESV = 480,
     UNKLINE = 481,
     USER = 482,
     USE_EGD = 483,
     USE_EXCEPT = 484,
     USE_INVEX = 485,
     USE_KNOCK = 486,
     USE_LOGGING = 487,
     USE_WHOIS_ACTUALLY = 488,
     VHOST = 489,
     VHOST6 = 490,
     XLINE = 491,
     WARN = 492,
     WARN_NO_NLINE = 493,
     T_SIZE = 494,
     T_FILE = 495
   };
#endif
/* Tokens.  */
#define ACCEPT_PASSWORD 258
#define ACTION 259
#define ADMIN 260
#define AFTYPE 261
#define T_ALLOW 262
#define ANTI_NICK_FLOOD 263
#define ANTI_SPAM_EXIT_MESSAGE_TIME 264
#define AUTOCONN 265
#define T_BLOCK 266
#define BURST_AWAY 267
#define BYTES 268
#define KBYTES 269
#define MBYTES 270
#define GBYTES 271
#define TBYTES 272
#define CALLER_ID_WAIT 273
#define CAN_FLOOD 274
#define CHANNEL 275
#define CIDR_BITLEN_IPV4 276
#define CIDR_BITLEN_IPV6 277
#define CLASS 278
#define CONNECT 279
#define CONNECTFREQ 280
#define DEFAULT_FLOODCOUNT 281
#define DEFAULT_SPLIT_SERVER_COUNT 282
#define DEFAULT_SPLIT_USER_COUNT 283
#define DENY 284
#define DESCRIPTION 285
#define DIE 286
#define DISABLE_AUTH 287
#define DISABLE_FAKE_CHANNELS 288
#define DISABLE_HIDDEN 289
#define DISABLE_LOCAL_CHANNELS 290
#define DISABLE_REMOTE_COMMANDS 291
#define DOTS_IN_IDENT 292
#define DURATION 293
#define EGDPOOL_PATH 294
#define EMAIL 295
#define ENABLE 296
#define ENCRYPTED 297
#define EXCEED_LIMIT 298
#define EXEMPT 299
#define FAILED_OPER_NOTICE 300
#define IRCD_FLAGS 301
#define FLATTEN_LINKS 302
#define GECOS 303
#define GENERAL 304
#define GLINE 305
#define GLINES 306
#define GLINE_EXEMPT 307
#define GLINE_TIME 308
#define GLINE_MIN_CIDR 309
#define GLINE_MIN_CIDR6 310
#define GLOBAL_KILL 311
#define IRCD_AUTH 312
#define NEED_IDENT 313
#define HAVENT_READ_CONF 314
#define HIDDEN 315
#define HIDDEN_NAME 316
#define HIDE_SERVER_IPS 317
#define HIDE_SERVERS 318
#define HIDE_SPOOF_IPS 319
#define HOST 320
#define HUB 321
#define HUB_MASK 322
#define IGNORE_BOGUS_TS 323
#define INVISIBLE_ON_CONNECT 324
#define IP 325
#define KILL 326
#define KILL_CHASE_TIME_LIMIT 327
#define KLINE 328
#define KLINE_EXEMPT 329
#define KLINE_REASON 330
#define KLINE_WITH_REASON 331
#define KNOCK_DELAY 332
#define KNOCK_DELAY_CHANNEL 333
#define LEAF_MASK 334
#define LINKS_DELAY 335
#define LISTEN 336
#define T_LOG 337
#define MAX_ACCEPT 338
#define MAX_BANS 339
#define MAX_CHANS_PER_OPER 340
#define MAX_CHANS_PER_USER 341
#define MAX_GLOBAL 342
#define MAX_IDENT 343
#define MAX_LOCAL 344
#define MAX_NICK_CHANGES 345
#define MAX_NICK_TIME 346
#define MAX_NUMBER 347
#define MAX_TARGETS 348
#define MAX_WATCH 349
#define MESSAGE_LOCALE 350
#define MIN_NONWILDCARD 351
#define MIN_NONWILDCARD_SIMPLE 352
#define MODULE 353
#define MODULES 354
#define NAME 355
#define NEED_PASSWORD 356
#define NETWORK_DESC 357
#define NETWORK_NAME 358
#define NICK 359
#define NICK_CHANGES 360
#define NO_CREATE_ON_SPLIT 361
#define NO_JOIN_ON_SPLIT 362
#define NO_OPER_FLOOD 363
#define NO_TILDE 364
#define NUMBER 365
#define NUMBER_PER_IDENT 366
#define NUMBER_PER_CIDR 367
#define NUMBER_PER_IP 368
#define NUMBER_PER_IP_GLOBAL 369
#define OPERATOR 370
#define OPERS_BYPASS_CALLERID 371
#define OPER_ONLY_UMODES 372
#define OPER_PASS_RESV 373
#define OPER_SPY_T 374
#define OPER_UMODES 375
#define JOIN_FLOOD_COUNT 376
#define JOIN_FLOOD_TIME 377
#define PACE_WAIT 378
#define PACE_WAIT_SIMPLE 379
#define PASSWORD 380
#define PATH 381
#define PING_COOKIE 382
#define PING_TIME 383
#define PING_WARNING 384
#define PORT 385
#define QSTRING 386
#define QUIET_ON_BAN 387
#define REASON 388
#define REDIRPORT 389
#define REDIRSERV 390
#define REGEX_T 391
#define REHASH 392
#define TREJECT_HOLD_TIME 393
#define REMOTE 394
#define REMOTEBAN 395
#define RESTRICT_CHANNELS 396
#define RESTRICTED 397
#define RSA_PRIVATE_KEY_FILE 398
#define RSA_PUBLIC_KEY_FILE 399
#define SSL_CERTIFICATE_FILE 400
#define SSL_DH_PARAM_FILE 401
#define T_SSL_CLIENT_METHOD 402
#define T_SSL_SERVER_METHOD 403
#define T_SSLV3 404
#define T_TLSV1 405
#define RESV 406
#define RESV_EXEMPT 407
#define SECONDS 408
#define MINUTES 409
#define HOURS 410
#define DAYS 411
#define WEEKS 412
#define SENDQ 413
#define SEND_PASSWORD 414
#define SERVERHIDE 415
#define SERVERINFO 416
#define IRCD_SID 417
#define TKLINE_EXPIRE_NOTICES 418
#define T_SHARED 419
#define T_CLUSTER 420
#define TYPE 421
#define SHORT_MOTD 422
#define SILENT 423
#define SPOOF 424
#define SPOOF_NOTICE 425
#define STATS_E_DISABLED 426
#define STATS_I_OPER_ONLY 427
#define STATS_K_OPER_ONLY 428
#define STATS_O_OPER_ONLY 429
#define STATS_P_OPER_ONLY 430
#define TBOOL 431
#define TMASKED 432
#define T_REJECT 433
#define TS_MAX_DELTA 434
#define TS_WARN_DELTA 435
#define TWODOTS 436
#define T_ALL 437
#define T_BOTS 438
#define T_SOFTCALLERID 439
#define T_CALLERID 440
#define T_CCONN 441
#define T_CCONN_FULL 442
#define T_SSL_CIPHER_LIST 443
#define T_CLIENT_FLOOD 444
#define T_DEAF 445
#define T_DEBUG 446
#define T_DLINE 447
#define T_DRONE 448
#define T_EXTERNAL 449
#define T_FULL 450
#define T_INVISIBLE 451
#define T_IPV4 452
#define T_IPV6 453
#define T_LOCOPS 454
#define T_MAX_CLIENTS 455
#define T_NCHANGE 456
#define T_OPERWALL 457
#define T_REJ 458
#define T_SERVER 459
#define T_SERVNOTICE 460
#define T_SKILL 461
#define T_SPY 462
#define T_SSL 463
#define T_UMODES 464
#define T_UNAUTH 465
#define T_UNDLINE 466
#define T_UNLIMITED 467
#define T_UNRESV 468
#define T_UNXLINE 469
#define T_GLOBOPS 470
#define T_WALLOP 471
#define T_RESTART 472
#define T_SERVICE 473
#define T_SERVICES_NAME 474
#define THROTTLE_TIME 475
#define TOPICBURST 476
#define TRUE_NO_OPER_FLOOD 477
#define TKLINE 478
#define TXLINE 479
#define TRESV 480
#define UNKLINE 481
#define USER 482
#define USE_EGD 483
#define USE_EXCEPT 484
#define USE_INVEX 485
#define USE_KNOCK 486
#define USE_LOGGING 487
#define USE_WHOIS_ACTUALLY 488
#define VHOST 489
#define VHOST6 490
#define XLINE 491
#define WARN 492
#define WARN_NO_NLINE 493
#define T_SIZE 494
#define T_FILE 495




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 295 of yacc.c  */
#line 110 "conf_parser.y"

  int number;
  char *string;



/* Line 295 of yacc.c  */
#line 688 "conf_parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 345 of yacc.c  */
#line 700 "conf_parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1248

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  246
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  305
/* YYNRULES -- Number of rules.  */
#define YYNRULES  668
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1311

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   495

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   245,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   241,
       2,   244,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   243,     2,   242,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    33,    35,    37,
      39,    41,    43,    45,    47,    49,    52,    55,    56,    58,
      61,    65,    69,    73,    77,    81,    82,    84,    87,    91,
      95,    99,   105,   108,   110,   112,   114,   117,   122,   127,
     133,   136,   138,   140,   142,   144,   146,   148,   150,   152,
     154,   156,   158,   160,   162,   164,   166,   168,   171,   176,
     181,   185,   187,   189,   191,   195,   197,   199,   201,   206,
     211,   216,   221,   226,   231,   236,   241,   246,   251,   256,
     261,   266,   272,   275,   277,   279,   281,   283,   286,   291,
     296,   301,   307,   310,   312,   314,   316,   319,   324,   325,
     332,   335,   337,   339,   341,   343,   346,   351,   356,   361,
     362,   368,   372,   374,   376,   378,   380,   382,   384,   386,
     388,   389,   396,   399,   401,   403,   405,   407,   409,   411,
     413,   415,   417,   420,   425,   430,   435,   440,   445,   450,
     451,   457,   461,   463,   465,   467,   469,   471,   473,   475,
     477,   479,   481,   483,   485,   487,   489,   491,   493,   495,
     497,   499,   501,   503,   504,   510,   514,   516,   518,   520,
     522,   524,   526,   528,   530,   532,   534,   536,   538,   540,
     542,   544,   546,   548,   550,   552,   553,   560,   563,   565,
     567,   569,   571,   573,   575,   577,   579,   581,   583,   585,
     587,   589,   591,   594,   599,   604,   609,   614,   619,   624,
     629,   634,   639,   644,   649,   654,   659,   660,   667,   668,
     674,   678,   680,   682,   684,   686,   689,   691,   693,   695,
     697,   699,   702,   703,   709,   713,   715,   717,   721,   726,
     731,   732,   739,   742,   744,   746,   748,   750,   752,   754,
     756,   758,   760,   763,   768,   773,   778,   783,   784,   790,
     794,   796,   798,   800,   802,   804,   806,   808,   810,   812,
     814,   819,   824,   829,   830,   837,   840,   842,   844,   846,
     848,   851,   856,   861,   866,   872,   875,   877,   879,   881,
     886,   887,   894,   897,   899,   901,   903,   905,   908,   913,
     918,   919,   925,   929,   931,   933,   935,   937,   939,   941,
     943,   945,   947,   949,   951,   952,   959,   962,   964,   966,
     968,   971,   976,   977,   983,   987,   989,   991,   993,   995,
     997,   999,  1001,  1003,  1005,  1007,  1009,  1010,  1017,  1020,
    1022,  1024,  1026,  1028,  1030,  1032,  1034,  1036,  1038,  1040,
    1042,  1044,  1046,  1048,  1051,  1056,  1061,  1066,  1071,  1076,
    1081,  1086,  1091,  1092,  1098,  1102,  1104,  1106,  1108,  1110,
    1112,  1117,  1122,  1127,  1132,  1137,  1138,  1145,  1146,  1152,
    1156,  1158,  1160,  1163,  1165,  1167,  1169,  1171,  1173,  1178,
    1183,  1184,  1191,  1194,  1196,  1198,  1200,  1202,  1207,  1212,
    1218,  1221,  1223,  1225,  1227,  1232,  1233,  1240,  1241,  1247,
    1251,  1253,  1255,  1258,  1260,  1262,  1264,  1266,  1268,  1273,
    1278,  1284,  1287,  1289,  1291,  1293,  1295,  1297,  1299,  1301,
    1303,  1305,  1307,  1309,  1311,  1313,  1315,  1317,  1319,  1321,
    1323,  1325,  1327,  1329,  1331,  1333,  1335,  1337,  1339,  1341,
    1343,  1345,  1347,  1349,  1351,  1353,  1355,  1357,  1359,  1361,
    1363,  1365,  1367,  1369,  1371,  1373,  1375,  1377,  1379,  1381,
    1383,  1385,  1387,  1389,  1391,  1393,  1398,  1403,  1408,  1413,
    1418,  1423,  1428,  1433,  1438,  1443,  1448,  1453,  1458,  1463,
    1468,  1473,  1478,  1483,  1488,  1493,  1498,  1503,  1508,  1513,
    1518,  1523,  1528,  1533,  1538,  1543,  1548,  1553,  1558,  1563,
    1568,  1573,  1578,  1583,  1588,  1593,  1598,  1603,  1608,  1613,
    1618,  1623,  1628,  1629,  1635,  1639,  1641,  1643,  1645,  1647,
    1649,  1651,  1653,  1655,  1657,  1659,  1661,  1663,  1665,  1667,
    1669,  1671,  1673,  1675,  1677,  1679,  1681,  1682,  1688,  1692,
    1694,  1696,  1698,  1700,  1702,  1704,  1706,  1708,  1710,  1712,
    1714,  1716,  1718,  1720,  1722,  1724,  1726,  1728,  1730,  1732,
    1734,  1739,  1744,  1749,  1754,  1755,  1762,  1765,  1767,  1769,
    1771,  1773,  1775,  1777,  1779,  1781,  1786,  1791,  1792,  1798,
    1802,  1804,  1806,  1808,  1813,  1818,  1819,  1825,  1829,  1831,
    1833,  1835,  1841,  1844,  1846,  1848,  1850,  1852,  1854,  1856,
    1858,  1860,  1862,  1864,  1866,  1868,  1870,  1872,  1874,  1876,
    1878,  1880,  1882,  1884,  1889,  1894,  1899,  1904,  1909,  1914,
    1919,  1924,  1929,  1934,  1939,  1944,  1949,  1954,  1959,  1964,
    1969,  1974,  1980,  1983,  1985,  1987,  1989,  1991,  1993,  1995,
    1997,  1999,  2001,  2006,  2011,  2016,  2021,  2026,  2031
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     247,     0,    -1,    -1,   247,   248,    -1,   280,    -1,   286,
      -1,   300,    -1,   520,    -1,   318,    -1,   335,    -1,   349,
      -1,   258,    -1,   541,    -1,   364,    -1,   371,    -1,   375,
      -1,   385,    -1,   394,    -1,   414,    -1,   424,    -1,   430,
      -1,   444,    -1,   504,    -1,   434,    -1,   253,    -1,     1,
     241,    -1,     1,   242,    -1,    -1,   250,    -1,   110,   249,
      -1,   110,   153,   249,    -1,   110,   154,   249,    -1,   110,
     155,   249,    -1,   110,   156,   249,    -1,   110,   157,   249,
      -1,    -1,   252,    -1,   110,   251,    -1,   110,    13,   251,
      -1,   110,    14,   251,    -1,   110,    15,   251,    -1,    99,
     243,   254,   242,   241,    -1,   254,   255,    -1,   255,    -1,
     256,    -1,   257,    -1,     1,   241,    -1,    98,   244,   131,
     241,    -1,   126,   244,   131,   241,    -1,   161,   243,   259,
     242,   241,    -1,   259,   260,    -1,   260,    -1,   271,    -1,
     276,    -1,   279,    -1,   273,    -1,   274,    -1,   275,    -1,
     278,    -1,   269,    -1,   268,    -1,   277,    -1,   272,    -1,
     267,    -1,   261,    -1,   262,    -1,   270,    -1,     1,   241,
      -1,   147,   244,   263,   241,    -1,   148,   244,   265,   241,
      -1,   263,   245,   264,    -1,   264,    -1,   149,    -1,   150,
      -1,   265,   245,   266,    -1,   266,    -1,   149,    -1,   150,
      -1,   145,   244,   131,   241,    -1,   143,   244,   131,   241,
      -1,   146,   244,   131,   241,    -1,   188,   244,   131,   241,
      -1,   100,   244,   131,   241,    -1,   162,   244,   131,   241,
      -1,    30,   244,   131,   241,    -1,   103,   244,   131,   241,
      -1,   102,   244,   131,   241,    -1,   234,   244,   131,   241,
      -1,   235,   244,   131,   241,    -1,   200,   244,   110,   241,
      -1,    66,   244,   176,   241,    -1,     5,   243,   281,   242,
     241,    -1,   281,   282,    -1,   282,    -1,   283,    -1,   285,
      -1,   284,    -1,     1,   241,    -1,   100,   244,   131,   241,
      -1,    40,   244,   131,   241,    -1,    30,   244,   131,   241,
      -1,    82,   243,   287,   242,   241,    -1,   287,   288,    -1,
     288,    -1,   289,    -1,   290,    -1,     1,   241,    -1,   232,
     244,   176,   241,    -1,    -1,   291,   240,   243,   292,   242,
     241,    -1,   292,   293,    -1,   293,    -1,   294,    -1,   296,
      -1,   295,    -1,     1,   241,    -1,   100,   244,   131,   241,
      -1,   239,   244,   252,   241,    -1,   239,   244,   212,   241,
      -1,    -1,   166,   297,   244,   298,   241,    -1,   298,   245,
     299,    -1,   299,    -1,   227,    -1,   115,    -1,    50,    -1,
     192,    -1,    73,    -1,    71,    -1,   191,    -1,    -1,   115,
     301,   243,   302,   242,   241,    -1,   302,   303,    -1,   303,
      -1,   304,    -1,   305,    -1,   306,    -1,   310,    -1,   309,
      -1,   307,    -1,   308,    -1,   314,    -1,     1,   241,    -1,
     100,   244,   131,   241,    -1,   227,   244,   131,   241,    -1,
     125,   244,   131,   241,    -1,    42,   244,   176,   241,    -1,
     144,   244,   131,   241,    -1,    23,   244,   131,   241,    -1,
      -1,   209,   311,   244,   312,   241,    -1,   312,   245,   313,
      -1,   313,    -1,   183,    -1,   186,    -1,   187,    -1,   190,
      -1,   191,    -1,   195,    -1,    60,    -1,   206,    -1,   201,
      -1,   203,    -1,   210,    -1,   207,    -1,   194,    -1,   202,
      -1,   205,    -1,   196,    -1,   216,    -1,   184,    -1,   185,
      -1,   199,    -1,    -1,    46,   315,   244,   316,   241,    -1,
     316,   245,   317,    -1,   317,    -1,    56,    -1,   139,    -1,
      73,    -1,   226,    -1,   192,    -1,   211,    -1,   236,    -1,
      50,    -1,    31,    -1,   217,    -1,   137,    -1,     5,    -1,
     105,    -1,   202,    -1,   215,    -1,   119,    -1,   140,    -1,
      98,    -1,    -1,    23,   319,   243,   320,   242,   241,    -1,
     320,   321,    -1,   321,    -1,   322,    -1,   332,    -1,   333,
      -1,   323,    -1,   324,    -1,   334,    -1,   325,    -1,   326,
      -1,   327,    -1,   328,    -1,   329,    -1,   330,    -1,   331,
      -1,     1,   241,    -1,   100,   244,   131,   241,    -1,   128,
     244,   250,   241,    -1,   129,   244,   250,   241,    -1,   113,
     244,   110,   241,    -1,    25,   244,   250,   241,    -1,    92,
     244,   110,   241,    -1,    87,   244,   110,   241,    -1,    89,
     244,   110,   241,    -1,    88,   244,   110,   241,    -1,   158,
     244,   252,   241,    -1,    21,   244,   110,   241,    -1,    22,
     244,   110,   241,    -1,   112,   244,   110,   241,    -1,    -1,
      81,   336,   243,   341,   242,   241,    -1,    -1,    46,   338,
     244,   339,   241,    -1,   339,   245,   340,    -1,   340,    -1,
     208,    -1,    60,    -1,   204,    -1,   341,   342,    -1,   342,
      -1,   343,    -1,   337,    -1,   347,    -1,   348,    -1,     1,
     241,    -1,    -1,   130,   244,   345,   344,   241,    -1,   345,
     245,   346,    -1,   346,    -1,   110,    -1,   110,   181,   110,
      -1,    70,   244,   131,   241,    -1,    65,   244,   131,   241,
      -1,    -1,    57,   350,   243,   351,   242,   241,    -1,   351,
     352,    -1,   352,    -1,   353,    -1,   354,    -1,   355,    -1,
     357,    -1,   361,    -1,   362,    -1,   363,    -1,   356,    -1,
       1,   241,    -1,   227,   244,   131,   241,    -1,   125,   244,
     131,   241,    -1,    23,   244,   131,   241,    -1,    42,   244,
     176,   241,    -1,    -1,    46,   358,   244,   359,   241,    -1,
     359,   245,   360,    -1,   360,    -1,   170,    -1,    43,    -1,
      74,    -1,    58,    -1,    19,    -1,   109,    -1,    52,    -1,
     152,    -1,   101,    -1,   169,   244,   131,   241,    -1,   135,
     244,   131,   241,    -1,   134,   244,   110,   241,    -1,    -1,
     151,   365,   243,   366,   242,   241,    -1,   366,   367,    -1,
     367,    -1,   368,    -1,   369,    -1,   370,    -1,     1,   241,
      -1,   133,   244,   131,   241,    -1,    20,   244,   131,   241,
      -1,   104,   244,   131,   241,    -1,   218,   243,   372,   242,
     241,    -1,   372,   373,    -1,   373,    -1,   374,    -1,     1,
      -1,   100,   244,   131,   241,    -1,    -1,   164,   376,   243,
     377,   242,   241,    -1,   377,   378,    -1,   378,    -1,   379,
      -1,   380,    -1,   381,    -1,     1,   241,    -1,   100,   244,
     131,   241,    -1,   227,   244,   131,   241,    -1,    -1,   166,
     382,   244,   383,   241,    -1,   383,   245,   384,    -1,   384,
      -1,    73,    -1,   226,    -1,   192,    -1,   211,    -1,   236,
      -1,   214,    -1,   151,    -1,   213,    -1,   199,    -1,   182,
      -1,    -1,   165,   386,   243,   387,   242,   241,    -1,   387,
     388,    -1,   388,    -1,   389,    -1,   390,    -1,     1,   241,
      -1,   100,   244,   131,   241,    -1,    -1,   166,   391,   244,
     392,   241,    -1,   392,   245,   393,    -1,   393,    -1,    73,
      -1,   226,    -1,   192,    -1,   211,    -1,   236,    -1,   214,
      -1,   151,    -1,   213,    -1,   199,    -1,   182,    -1,    -1,
      24,   395,   243,   396,   242,   241,    -1,   396,   397,    -1,
     397,    -1,   398,    -1,   399,    -1,   400,    -1,   401,    -1,
     402,    -1,   404,    -1,   403,    -1,   413,    -1,   405,    -1,
     410,    -1,   411,    -1,   412,    -1,   409,    -1,     1,   241,
      -1,   100,   244,   131,   241,    -1,    65,   244,   131,   241,
      -1,   234,   244,   131,   241,    -1,   159,   244,   131,   241,
      -1,     3,   244,   131,   241,    -1,   130,   244,   110,   241,
      -1,     6,   244,   197,   241,    -1,     6,   244,   198,   241,
      -1,    -1,    46,   406,   244,   407,   241,    -1,   407,   245,
     408,    -1,   408,    -1,    10,    -1,    12,    -1,   221,    -1,
     208,    -1,    42,   244,   176,   241,    -1,    67,   244,   131,
     241,    -1,    79,   244,   131,   241,    -1,    23,   244,   131,
     241,    -1,   188,   244,   131,   241,    -1,    -1,    71,   415,
     243,   420,   242,   241,    -1,    -1,   166,   417,   244,   418,
     241,    -1,   418,   245,   419,    -1,   419,    -1,   136,    -1,
     420,   421,    -1,   421,    -1,   422,    -1,   423,    -1,   416,
      -1,     1,    -1,   227,   244,   131,   241,    -1,   133,   244,
     131,   241,    -1,    -1,    29,   425,   243,   426,   242,   241,
      -1,   426,   427,    -1,   427,    -1,   428,    -1,   429,    -1,
       1,    -1,    70,   244,   131,   241,    -1,   133,   244,   131,
     241,    -1,    44,   243,   431,   242,   241,    -1,   431,   432,
      -1,   432,    -1,   433,    -1,     1,    -1,    70,   244,   131,
     241,    -1,    -1,    48,   435,   243,   440,   242,   241,    -1,
      -1,   166,   437,   244,   438,   241,    -1,   438,   245,   439,
      -1,   439,    -1,   136,    -1,   440,   441,    -1,   441,    -1,
     442,    -1,   443,    -1,   436,    -1,     1,    -1,   100,   244,
     131,   241,    -1,   133,   244,   131,   241,    -1,    49,   243,
     445,   242,   241,    -1,   445,   446,    -1,   446,    -1,   454,
      -1,   455,    -1,   457,    -1,   458,    -1,   459,    -1,   460,
      -1,   461,    -1,   462,    -1,   463,    -1,   464,    -1,   453,
      -1,   466,    -1,   467,    -1,   468,    -1,   469,    -1,   484,
      -1,   471,    -1,   473,    -1,   475,    -1,   474,    -1,   478,
      -1,   472,    -1,   479,    -1,   480,    -1,   481,    -1,   482,
      -1,   483,    -1,   496,    -1,   485,    -1,   486,    -1,   487,
      -1,   492,    -1,   476,    -1,   477,    -1,   502,    -1,   500,
      -1,   501,    -1,   456,    -1,   503,    -1,   491,    -1,   465,
      -1,   489,    -1,   490,    -1,   452,    -1,   448,    -1,   449,
      -1,   450,    -1,   451,    -1,   470,    -1,   447,    -1,   488,
      -1,     1,    -1,    94,   244,   110,   241,    -1,    54,   244,
     110,   241,    -1,    55,   244,   110,   241,    -1,   233,   244,
     176,   241,    -1,   138,   244,   250,   241,    -1,   163,   244,
     176,   241,    -1,    72,   244,   250,   241,    -1,    64,   244,
     176,   241,    -1,    68,   244,   176,   241,    -1,    36,   244,
     176,   241,    -1,    45,   244,   176,   241,    -1,     8,   244,
     176,   241,    -1,    91,   244,   250,   241,    -1,    90,   244,
     110,   241,    -1,    83,   244,   110,   241,    -1,     9,   244,
     250,   241,    -1,   180,   244,   250,   241,    -1,   179,   244,
     250,   241,    -1,    59,   244,   110,   241,    -1,    76,   244,
     176,   241,    -1,    75,   244,   131,   241,    -1,    69,   244,
     176,   241,    -1,   238,   244,   176,   241,    -1,   171,   244,
     176,   241,    -1,   174,   244,   176,   241,    -1,   175,   244,
     176,   241,    -1,   173,   244,   176,   241,    -1,   173,   244,
     177,   241,    -1,   172,   244,   176,   241,    -1,   172,   244,
     177,   241,    -1,   123,   244,   250,   241,    -1,    18,   244,
     250,   241,    -1,   116,   244,   176,   241,    -1,   124,   244,
     250,   241,    -1,   167,   244,   176,   241,    -1,   108,   244,
     176,   241,    -1,   222,   244,   176,   241,    -1,   118,   244,
     176,   241,    -1,    95,   244,   131,   241,    -1,    37,   244,
     110,   241,    -1,    93,   244,   110,   241,    -1,   228,   244,
     176,   241,    -1,    39,   244,   131,   241,    -1,   219,   244,
     131,   241,    -1,   127,   244,   176,   241,    -1,    32,   244,
     176,   241,    -1,   220,   244,   250,   241,    -1,    -1,   120,
     493,   244,   494,   241,    -1,   494,   245,   495,    -1,   495,
      -1,   183,    -1,   186,    -1,   187,    -1,   190,    -1,   191,
      -1,   195,    -1,    60,    -1,   206,    -1,   201,    -1,   203,
      -1,   210,    -1,   207,    -1,   194,    -1,   202,    -1,   205,
      -1,   196,    -1,   216,    -1,   184,    -1,   185,    -1,   199,
      -1,    -1,   117,   497,   244,   498,   241,    -1,   498,   245,
     499,    -1,   499,    -1,   183,    -1,   186,    -1,   187,    -1,
     190,    -1,   191,    -1,   195,    -1,   206,    -1,    60,    -1,
     201,    -1,   203,    -1,   210,    -1,   207,    -1,   194,    -1,
     202,    -1,   205,    -1,   196,    -1,   216,    -1,   184,    -1,
     185,    -1,   199,    -1,    96,   244,   110,   241,    -1,    97,
     244,   110,   241,    -1,    26,   244,   110,   241,    -1,   189,
     244,   252,   241,    -1,    -1,    51,   505,   243,   506,   242,
     241,    -1,   506,   507,    -1,   507,    -1,   508,    -1,   509,
      -1,   510,    -1,   514,    -1,   515,    -1,   516,    -1,     1,
      -1,    41,   244,   176,   241,    -1,    38,   244,   250,   241,
      -1,    -1,    82,   511,   244,   512,   241,    -1,   512,   245,
     513,    -1,   513,    -1,   178,    -1,    11,    -1,   227,   244,
     131,   241,    -1,   100,   244,   131,   241,    -1,    -1,     4,
     517,   244,   518,   241,    -1,   518,   245,   519,    -1,   519,
      -1,   178,    -1,    11,    -1,    20,   243,   521,   242,   241,
      -1,   521,   522,    -1,   522,    -1,   525,    -1,   526,    -1,
     527,    -1,   528,    -1,   534,    -1,   529,    -1,   530,    -1,
     531,    -1,   532,    -1,   533,    -1,   535,    -1,   536,    -1,
     537,    -1,   524,    -1,   538,    -1,   539,    -1,   540,    -1,
     523,    -1,     1,    -1,    33,   244,   176,   241,    -1,   141,
     244,   176,   241,    -1,    35,   244,   176,   241,    -1,   229,
     244,   176,   241,    -1,   230,   244,   176,   241,    -1,   231,
     244,   176,   241,    -1,    77,   244,   250,   241,    -1,    78,
     244,   250,   241,    -1,    86,   244,   110,   241,    -1,    85,
     244,   110,   241,    -1,   132,   244,   176,   241,    -1,    84,
     244,   110,   241,    -1,    28,   244,   110,   241,    -1,    27,
     244,   110,   241,    -1,   106,   244,   176,   241,    -1,   107,
     244,   176,   241,    -1,   121,   244,   110,   241,    -1,   122,
     244,   250,   241,    -1,   160,   243,   542,   242,   241,    -1,
     542,   543,    -1,   543,    -1,   544,    -1,   545,    -1,   547,
      -1,   549,    -1,   548,    -1,   546,    -1,   550,    -1,     1,
      -1,    47,   244,   176,   241,    -1,    63,   244,   176,   241,
      -1,    61,   244,   131,   241,    -1,    80,   244,   250,   241,
      -1,    60,   244,   176,   241,    -1,    34,   244,   176,   241,
      -1,    62,   244,   176,   241,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   354,   354,   355,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   367,   368,   369,   370,   371,   372,   373,
     374,   375,   376,   377,   378,   379,   380,   384,   384,   385,
     389,   393,   397,   401,   405,   411,   411,   412,   413,   414,
     415,   422,   425,   425,   426,   426,   426,   428,   434,   441,
     443,   443,   444,   444,   445,   445,   446,   446,   447,   447,
     448,   448,   449,   449,   450,   450,   451,   452,   455,   456,
     458,   458,   459,   465,   473,   473,   474,   480,   488,   527,
     586,   614,   622,   637,   652,   661,   675,   684,   712,   742,
     765,   774,   776,   776,   777,   777,   778,   778,   780,   789,
     798,   810,   811,   811,   813,   813,   814,   816,   823,   823,
     833,   834,   836,   836,   837,   837,   839,   844,   847,   853,
     852,   858,   858,   859,   863,   867,   871,   875,   879,   883,
     894,   893,   991,   991,   992,   992,   992,   993,   993,   993,
     994,   994,   994,   996,  1005,  1042,  1054,  1065,  1107,  1117,
    1116,  1122,  1122,  1123,  1127,  1131,  1135,  1139,  1143,  1147,
    1151,  1155,  1159,  1163,  1167,  1171,  1175,  1179,  1183,  1187,
    1191,  1195,  1199,  1206,  1205,  1211,  1211,  1212,  1216,  1220,
    1224,  1228,  1232,  1236,  1240,  1244,  1248,  1252,  1256,  1260,
    1264,  1268,  1272,  1276,  1280,  1291,  1290,  1340,  1340,  1341,
    1342,  1342,  1343,  1344,  1345,  1346,  1347,  1348,  1349,  1350,
    1351,  1352,  1353,  1355,  1364,  1370,  1376,  1382,  1388,  1394,
    1400,  1406,  1412,  1418,  1424,  1430,  1440,  1439,  1456,  1455,
    1460,  1460,  1461,  1465,  1469,  1477,  1477,  1478,  1478,  1478,
    1478,  1478,  1480,  1480,  1482,  1482,  1484,  1498,  1518,  1527,
    1540,  1539,  1608,  1608,  1609,  1609,  1609,  1609,  1610,  1610,
    1610,  1611,  1611,  1613,  1648,  1661,  1670,  1682,  1681,  1685,
    1685,  1686,  1690,  1694,  1698,  1702,  1706,  1710,  1714,  1718,
    1725,  1744,  1754,  1768,  1767,  1783,  1783,  1784,  1784,  1784,
    1784,  1786,  1795,  1810,  1823,  1825,  1825,  1826,  1826,  1828,
    1844,  1843,  1859,  1859,  1860,  1860,  1860,  1860,  1862,  1871,
    1894,  1893,  1899,  1899,  1900,  1904,  1908,  1912,  1916,  1920,
    1924,  1928,  1932,  1936,  1946,  1945,  1962,  1962,  1963,  1963,
    1963,  1965,  1972,  1971,  1977,  1977,  1978,  1982,  1986,  1990,
    1994,  1998,  2002,  2006,  2010,  2014,  2024,  2023,  2074,  2074,
    2075,  2075,  2075,  2076,  2076,  2077,  2077,  2077,  2078,  2078,
    2078,  2079,  2079,  2080,  2082,  2091,  2100,  2126,  2144,  2162,
    2168,  2172,  2181,  2180,  2184,  2184,  2185,  2189,  2193,  2197,
    2203,  2214,  2225,  2236,  2245,  2264,  2263,  2329,  2328,  2332,
    2332,  2333,  2339,  2339,  2340,  2340,  2340,  2340,  2342,  2361,
    2371,  2370,  2395,  2395,  2396,  2396,  2396,  2398,  2404,  2413,
    2415,  2415,  2416,  2416,  2418,  2437,  2436,  2484,  2483,  2487,
    2487,  2488,  2494,  2494,  2495,  2495,  2495,  2495,  2497,  2503,
    2512,  2515,  2515,  2516,  2516,  2517,  2517,  2518,  2518,  2519,
    2519,  2520,  2520,  2521,  2521,  2522,  2522,  2523,  2523,  2524,
    2524,  2525,  2525,  2526,  2526,  2527,  2527,  2528,  2528,  2529,
    2530,  2530,  2531,  2531,  2532,  2532,  2533,  2533,  2534,  2534,
    2535,  2536,  2537,  2537,  2538,  2539,  2540,  2540,  2541,  2541,
    2542,  2542,  2543,  2543,  2544,  2547,  2552,  2557,  2562,  2567,
    2572,  2577,  2582,  2587,  2592,  2597,  2602,  2607,  2612,  2617,
    2622,  2627,  2632,  2638,  2649,  2654,  2663,  2668,  2673,  2678,
    2683,  2688,  2691,  2696,  2699,  2704,  2709,  2714,  2719,  2724,
    2729,  2734,  2739,  2744,  2755,  2760,  2765,  2770,  2779,  2788,
    2793,  2798,  2804,  2803,  2808,  2808,  2809,  2812,  2815,  2818,
    2821,  2824,  2827,  2830,  2833,  2836,  2839,  2842,  2845,  2848,
    2851,  2854,  2857,  2860,  2863,  2866,  2872,  2871,  2876,  2876,
    2877,  2880,  2883,  2886,  2889,  2892,  2895,  2898,  2901,  2904,
    2907,  2910,  2913,  2916,  2919,  2922,  2925,  2928,  2931,  2934,
    2939,  2944,  2949,  2954,  2964,  2963,  2987,  2987,  2988,  2989,
    2990,  2991,  2992,  2993,  2994,  2996,  3002,  3009,  3008,  3013,
    3013,  3014,  3018,  3024,  3058,  3068,  3067,  3117,  3117,  3118,
    3122,  3131,  3134,  3134,  3135,  3135,  3136,  3136,  3136,  3137,
    3137,  3138,  3138,  3139,  3139,  3140,  3141,  3141,  3142,  3143,
    3143,  3144,  3144,  3146,  3151,  3156,  3161,  3166,  3171,  3176,
    3181,  3186,  3191,  3196,  3201,  3206,  3211,  3216,  3221,  3226,
    3231,  3239,  3242,  3242,  3243,  3243,  3244,  3245,  3246,  3246,
    3247,  3248,  3250,  3256,  3262,  3271,  3285,  3291,  3297
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ACCEPT_PASSWORD", "ACTION", "ADMIN",
  "AFTYPE", "T_ALLOW", "ANTI_NICK_FLOOD", "ANTI_SPAM_EXIT_MESSAGE_TIME",
  "AUTOCONN", "T_BLOCK", "BURST_AWAY", "BYTES", "KBYTES", "MBYTES",
  "GBYTES", "TBYTES", "CALLER_ID_WAIT", "CAN_FLOOD", "CHANNEL",
  "CIDR_BITLEN_IPV4", "CIDR_BITLEN_IPV6", "CLASS", "CONNECT",
  "CONNECTFREQ", "DEFAULT_FLOODCOUNT", "DEFAULT_SPLIT_SERVER_COUNT",
  "DEFAULT_SPLIT_USER_COUNT", "DENY", "DESCRIPTION", "DIE", "DISABLE_AUTH",
  "DISABLE_FAKE_CHANNELS", "DISABLE_HIDDEN", "DISABLE_LOCAL_CHANNELS",
  "DISABLE_REMOTE_COMMANDS", "DOTS_IN_IDENT", "DURATION", "EGDPOOL_PATH",
  "EMAIL", "ENABLE", "ENCRYPTED", "EXCEED_LIMIT", "EXEMPT",
  "FAILED_OPER_NOTICE", "IRCD_FLAGS", "FLATTEN_LINKS", "GECOS", "GENERAL",
  "GLINE", "GLINES", "GLINE_EXEMPT", "GLINE_TIME", "GLINE_MIN_CIDR",
  "GLINE_MIN_CIDR6", "GLOBAL_KILL", "IRCD_AUTH", "NEED_IDENT",
  "HAVENT_READ_CONF", "HIDDEN", "HIDDEN_NAME", "HIDE_SERVER_IPS",
  "HIDE_SERVERS", "HIDE_SPOOF_IPS", "HOST", "HUB", "HUB_MASK",
  "IGNORE_BOGUS_TS", "INVISIBLE_ON_CONNECT", "IP", "KILL",
  "KILL_CHASE_TIME_LIMIT", "KLINE", "KLINE_EXEMPT", "KLINE_REASON",
  "KLINE_WITH_REASON", "KNOCK_DELAY", "KNOCK_DELAY_CHANNEL", "LEAF_MASK",
  "LINKS_DELAY", "LISTEN", "T_LOG", "MAX_ACCEPT", "MAX_BANS",
  "MAX_CHANS_PER_OPER", "MAX_CHANS_PER_USER", "MAX_GLOBAL", "MAX_IDENT",
  "MAX_LOCAL", "MAX_NICK_CHANGES", "MAX_NICK_TIME", "MAX_NUMBER",
  "MAX_TARGETS", "MAX_WATCH", "MESSAGE_LOCALE", "MIN_NONWILDCARD",
  "MIN_NONWILDCARD_SIMPLE", "MODULE", "MODULES", "NAME", "NEED_PASSWORD",
  "NETWORK_DESC", "NETWORK_NAME", "NICK", "NICK_CHANGES",
  "NO_CREATE_ON_SPLIT", "NO_JOIN_ON_SPLIT", "NO_OPER_FLOOD", "NO_TILDE",
  "NUMBER", "NUMBER_PER_IDENT", "NUMBER_PER_CIDR", "NUMBER_PER_IP",
  "NUMBER_PER_IP_GLOBAL", "OPERATOR", "OPERS_BYPASS_CALLERID",
  "OPER_ONLY_UMODES", "OPER_PASS_RESV", "OPER_SPY_T", "OPER_UMODES",
  "JOIN_FLOOD_COUNT", "JOIN_FLOOD_TIME", "PACE_WAIT", "PACE_WAIT_SIMPLE",
  "PASSWORD", "PATH", "PING_COOKIE", "PING_TIME", "PING_WARNING", "PORT",
  "QSTRING", "QUIET_ON_BAN", "REASON", "REDIRPORT", "REDIRSERV", "REGEX_T",
  "REHASH", "TREJECT_HOLD_TIME", "REMOTE", "REMOTEBAN",
  "RESTRICT_CHANNELS", "RESTRICTED", "RSA_PRIVATE_KEY_FILE",
  "RSA_PUBLIC_KEY_FILE", "SSL_CERTIFICATE_FILE", "SSL_DH_PARAM_FILE",
  "T_SSL_CLIENT_METHOD", "T_SSL_SERVER_METHOD", "T_SSLV3", "T_TLSV1",
  "RESV", "RESV_EXEMPT", "SECONDS", "MINUTES", "HOURS", "DAYS", "WEEKS",
  "SENDQ", "SEND_PASSWORD", "SERVERHIDE", "SERVERINFO", "IRCD_SID",
  "TKLINE_EXPIRE_NOTICES", "T_SHARED", "T_CLUSTER", "TYPE", "SHORT_MOTD",
  "SILENT", "SPOOF", "SPOOF_NOTICE", "STATS_E_DISABLED",
  "STATS_I_OPER_ONLY", "STATS_K_OPER_ONLY", "STATS_O_OPER_ONLY",
  "STATS_P_OPER_ONLY", "TBOOL", "TMASKED", "T_REJECT", "TS_MAX_DELTA",
  "TS_WARN_DELTA", "TWODOTS", "T_ALL", "T_BOTS", "T_SOFTCALLERID",
  "T_CALLERID", "T_CCONN", "T_CCONN_FULL", "T_SSL_CIPHER_LIST",
  "T_CLIENT_FLOOD", "T_DEAF", "T_DEBUG", "T_DLINE", "T_DRONE",
  "T_EXTERNAL", "T_FULL", "T_INVISIBLE", "T_IPV4", "T_IPV6", "T_LOCOPS",
  "T_MAX_CLIENTS", "T_NCHANGE", "T_OPERWALL", "T_REJ", "T_SERVER",
  "T_SERVNOTICE", "T_SKILL", "T_SPY", "T_SSL", "T_UMODES", "T_UNAUTH",
  "T_UNDLINE", "T_UNLIMITED", "T_UNRESV", "T_UNXLINE", "T_GLOBOPS",
  "T_WALLOP", "T_RESTART", "T_SERVICE", "T_SERVICES_NAME", "THROTTLE_TIME",
  "TOPICBURST", "TRUE_NO_OPER_FLOOD", "TKLINE", "TXLINE", "TRESV",
  "UNKLINE", "USER", "USE_EGD", "USE_EXCEPT", "USE_INVEX", "USE_KNOCK",
  "USE_LOGGING", "USE_WHOIS_ACTUALLY", "VHOST", "VHOST6", "XLINE", "WARN",
  "WARN_NO_NLINE", "T_SIZE", "T_FILE", "';'", "'}'", "'{'", "'='", "','",
  "$accept", "conf", "conf_item", "timespec_", "timespec", "sizespec_",
  "sizespec", "modules_entry", "modules_items", "modules_item",
  "modules_module", "modules_path", "serverinfo_entry", "serverinfo_items",
  "serverinfo_item", "serverinfo_ssl_client_method",
  "serverinfo_ssl_server_method", "client_method_types",
  "client_method_type_item", "server_method_types",
  "server_method_type_item", "serverinfo_ssl_certificate_file",
  "serverinfo_rsa_private_key_file", "serverinfo_ssl_dh_param_file",
  "serverinfo_ssl_cipher_list", "serverinfo_name", "serverinfo_sid",
  "serverinfo_description", "serverinfo_network_name",
  "serverinfo_network_desc", "serverinfo_vhost", "serverinfo_vhost6",
  "serverinfo_max_clients", "serverinfo_hub", "admin_entry", "admin_items",
  "admin_item", "admin_name", "admin_email", "admin_description",
  "logging_entry", "logging_items", "logging_item", "logging_use_logging",
  "logging_file_entry", "$@1", "logging_file_items", "logging_file_item",
  "logging_file_name", "logging_file_size", "logging_file_type", "$@2",
  "logging_file_type_items", "logging_file_type_item", "oper_entry", "$@3",
  "oper_items", "oper_item", "oper_name", "oper_user", "oper_password",
  "oper_encrypted", "oper_rsa_public_key_file", "oper_class",
  "oper_umodes", "$@4", "oper_umodes_items", "oper_umodes_item",
  "oper_flags", "$@5", "oper_flags_items", "oper_flags_item",
  "class_entry", "$@6", "class_items", "class_item", "class_name",
  "class_ping_time", "class_ping_warning", "class_number_per_ip",
  "class_connectfreq", "class_max_number", "class_max_global",
  "class_max_local", "class_max_ident", "class_sendq",
  "class_cidr_bitlen_ipv4", "class_cidr_bitlen_ipv6",
  "class_number_per_cidr", "listen_entry", "$@7", "listen_flags", "$@8",
  "listen_flags_items", "listen_flags_item", "listen_items", "listen_item",
  "listen_port", "$@9", "port_items", "port_item", "listen_address",
  "listen_host", "auth_entry", "$@10", "auth_items", "auth_item",
  "auth_user", "auth_passwd", "auth_class", "auth_encrypted", "auth_flags",
  "$@11", "auth_flags_items", "auth_flags_item", "auth_spoof",
  "auth_redir_serv", "auth_redir_port", "resv_entry", "$@12", "resv_items",
  "resv_item", "resv_creason", "resv_channel", "resv_nick",
  "service_entry", "service_items", "service_item", "service_name",
  "shared_entry", "$@13", "shared_items", "shared_item", "shared_name",
  "shared_user", "shared_type", "$@14", "shared_types", "shared_type_item",
  "cluster_entry", "$@15", "cluster_items", "cluster_item", "cluster_name",
  "cluster_type", "$@16", "cluster_types", "cluster_type_item",
  "connect_entry", "$@17", "connect_items", "connect_item", "connect_name",
  "connect_host", "connect_vhost", "connect_send_password",
  "connect_accept_password", "connect_port", "connect_aftype",
  "connect_flags", "$@18", "connect_flags_items", "connect_flags_item",
  "connect_encrypted", "connect_hub_mask", "connect_leaf_mask",
  "connect_class", "connect_ssl_cipher_list", "kill_entry", "$@19",
  "kill_type", "$@20", "kill_type_items", "kill_type_item", "kill_items",
  "kill_item", "kill_user", "kill_reason", "deny_entry", "$@21",
  "deny_items", "deny_item", "deny_ip", "deny_reason", "exempt_entry",
  "exempt_items", "exempt_item", "exempt_ip", "gecos_entry", "$@22",
  "gecos_flags", "$@23", "gecos_flags_items", "gecos_flags_item",
  "gecos_items", "gecos_item", "gecos_name", "gecos_reason",
  "general_entry", "general_items", "general_item", "general_max_watch",
  "general_gline_min_cidr", "general_gline_min_cidr6",
  "general_use_whois_actually", "general_reject_hold_time",
  "general_tkline_expire_notices", "general_kill_chase_time_limit",
  "general_hide_spoof_ips", "general_ignore_bogus_ts",
  "general_disable_remote_commands", "general_failed_oper_notice",
  "general_anti_nick_flood", "general_max_nick_time",
  "general_max_nick_changes", "general_max_accept",
  "general_anti_spam_exit_message_time", "general_ts_warn_delta",
  "general_ts_max_delta", "general_havent_read_conf",
  "general_kline_with_reason", "general_kline_reason",
  "general_invisible_on_connect", "general_warn_no_nline",
  "general_stats_e_disabled", "general_stats_o_oper_only",
  "general_stats_P_oper_only", "general_stats_k_oper_only",
  "general_stats_i_oper_only", "general_pace_wait",
  "general_caller_id_wait", "general_opers_bypass_callerid",
  "general_pace_wait_simple", "general_short_motd",
  "general_no_oper_flood", "general_true_no_oper_flood",
  "general_oper_pass_resv", "general_message_locale",
  "general_dots_in_ident", "general_max_targets", "general_use_egd",
  "general_egdpool_path", "general_services_name", "general_ping_cookie",
  "general_disable_auth", "general_throttle_time", "general_oper_umodes",
  "$@24", "umode_oitems", "umode_oitem", "general_oper_only_umodes",
  "$@25", "umode_items", "umode_item", "general_min_nonwildcard",
  "general_min_nonwildcard_simple", "general_default_floodcount",
  "general_client_flood", "gline_entry", "$@26", "gline_items",
  "gline_item", "gline_enable", "gline_duration", "gline_logging", "$@27",
  "gline_logging_types", "gline_logging_type_item", "gline_user",
  "gline_server", "gline_action", "$@28", "gdeny_types", "gdeny_type_item",
  "channel_entry", "channel_items", "channel_item",
  "channel_disable_fake_channels", "channel_restrict_channels",
  "channel_disable_local_channels", "channel_use_except",
  "channel_use_invex", "channel_use_knock", "channel_knock_delay",
  "channel_knock_delay_channel", "channel_max_chans_per_user",
  "channel_max_chans_per_oper", "channel_quiet_on_ban", "channel_max_bans",
  "channel_default_split_user_count", "channel_default_split_server_count",
  "channel_no_create_on_split", "channel_no_join_on_split",
  "channel_jflood_count", "channel_jflood_time", "serverhide_entry",
  "serverhide_items", "serverhide_item", "serverhide_flatten_links",
  "serverhide_hide_servers", "serverhide_hidden_name",
  "serverhide_links_delay", "serverhide_hidden",
  "serverhide_disable_hidden", "serverhide_hide_server_ips", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,    59,   125,   123,    61,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   246,   247,   247,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   249,   249,   250,
     250,   250,   250,   250,   250,   251,   251,   252,   252,   252,
     252,   253,   254,   254,   255,   255,   255,   256,   257,   258,
     259,   259,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   261,   262,
     263,   263,   264,   264,   265,   265,   266,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   281,   282,   282,   282,   282,   283,   284,
     285,   286,   287,   287,   288,   288,   288,   289,   291,   290,
     292,   292,   293,   293,   293,   293,   294,   295,   295,   297,
     296,   298,   298,   299,   299,   299,   299,   299,   299,   299,
     301,   300,   302,   302,   303,   303,   303,   303,   303,   303,
     303,   303,   303,   304,   305,   306,   307,   308,   309,   311,
     310,   312,   312,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   313,   315,   314,   316,   316,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   319,   318,   320,   320,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   321,   321,
     321,   321,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   336,   335,   338,   337,
     339,   339,   340,   340,   340,   341,   341,   342,   342,   342,
     342,   342,   344,   343,   345,   345,   346,   346,   347,   348,
     350,   349,   351,   351,   352,   352,   352,   352,   352,   352,
     352,   352,   352,   353,   354,   355,   356,   358,   357,   359,
     359,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     361,   362,   363,   365,   364,   366,   366,   367,   367,   367,
     367,   368,   369,   370,   371,   372,   372,   373,   373,   374,
     376,   375,   377,   377,   378,   378,   378,   378,   379,   380,
     382,   381,   383,   383,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   386,   385,   387,   387,   388,   388,
     388,   389,   391,   390,   392,   392,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   395,   394,   396,   396,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   398,   399,   400,   401,   402,   403,
     404,   404,   406,   405,   407,   407,   408,   408,   408,   408,
     409,   410,   411,   412,   413,   415,   414,   417,   416,   418,
     418,   419,   420,   420,   421,   421,   421,   421,   422,   423,
     425,   424,   426,   426,   427,   427,   427,   428,   429,   430,
     431,   431,   432,   432,   433,   435,   434,   437,   436,   438,
     438,   439,   440,   440,   441,   441,   441,   441,   442,   443,
     444,   445,   445,   446,   446,   446,   446,   446,   446,   446,
     446,   446,   446,   446,   446,   446,   446,   446,   446,   446,
     446,   446,   446,   446,   446,   446,   446,   446,   446,   446,
     446,   446,   446,   446,   446,   446,   446,   446,   446,   446,
     446,   446,   446,   446,   446,   446,   446,   446,   446,   446,
     446,   446,   446,   446,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   473,   474,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   493,   492,   494,   494,   495,   495,   495,   495,
     495,   495,   495,   495,   495,   495,   495,   495,   495,   495,
     495,   495,   495,   495,   495,   495,   497,   496,   498,   498,
     499,   499,   499,   499,   499,   499,   499,   499,   499,   499,
     499,   499,   499,   499,   499,   499,   499,   499,   499,   499,
     500,   501,   502,   503,   505,   504,   506,   506,   507,   507,
     507,   507,   507,   507,   507,   508,   509,   511,   510,   512,
     512,   513,   513,   514,   515,   517,   516,   518,   518,   519,
     519,   520,   521,   521,   522,   522,   522,   522,   522,   522,
     522,   522,   522,   522,   522,   522,   522,   522,   522,   522,
     522,   522,   522,   523,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   542,   543,   543,   543,   543,   543,   543,
     543,   543,   544,   545,   546,   547,   548,   549,   550
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     0,     1,     2,
       3,     3,     3,     3,     3,     0,     1,     2,     3,     3,
       3,     5,     2,     1,     1,     1,     2,     4,     4,     5,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     4,
       3,     1,     1,     1,     3,     1,     1,     1,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     5,     2,     1,     1,     1,     1,     2,     4,     4,
       4,     5,     2,     1,     1,     1,     2,     4,     0,     6,
       2,     1,     1,     1,     1,     2,     4,     4,     4,     0,
       5,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     4,     4,     4,     4,     4,     4,     0,
       5,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     5,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     0,     6,     0,     5,
       3,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     2,     0,     5,     3,     1,     1,     3,     4,     4,
       0,     6,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     4,     4,     4,     4,     0,     5,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     4,     4,     0,     6,     2,     1,     1,     1,     1,
       2,     4,     4,     4,     5,     2,     1,     1,     1,     4,
       0,     6,     2,     1,     1,     1,     1,     2,     4,     4,
       0,     5,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     2,     1,     1,     1,
       2,     4,     0,     5,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     4,     4,     4,     4,     4,     4,
       4,     4,     0,     5,     3,     1,     1,     1,     1,     1,
       4,     4,     4,     4,     4,     0,     6,     0,     5,     3,
       1,     1,     2,     1,     1,     1,     1,     1,     4,     4,
       0,     6,     2,     1,     1,     1,     1,     4,     4,     5,
       2,     1,     1,     1,     4,     0,     6,     0,     5,     3,
       1,     1,     2,     1,     1,     1,     1,     1,     4,     4,
       5,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     0,     5,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     5,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     4,     4,     4,     0,     6,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     0,     5,     3,
       1,     1,     1,     4,     4,     0,     5,     3,     1,     1,
       1,     5,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     5,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     4,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     0,     0,   195,   346,   400,     0,
     415,     0,   584,   250,   385,   226,     0,     0,   130,   283,
       0,     0,   300,   324,     0,     3,    24,    11,     4,     5,
       6,     8,     9,    10,    13,    14,    15,    16,    17,    18,
      19,    20,    23,    21,    22,     7,    12,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    93,    94,    96,    95,   632,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   613,
     631,   627,   614,   615,   616,   617,   619,   620,   621,   622,
     623,   618,   624,   625,   626,   628,   629,   630,     0,     0,
       0,   413,     0,     0,   411,   412,     0,   484,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   556,     0,   532,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     432,   482,   477,   478,   479,   480,   476,   443,   433,   434,
     470,   435,   436,   437,   438,   439,   440,   441,   442,   473,
     444,   445,   446,   447,   481,   449,   454,   450,   452,   451,
     465,   466,   453,   455,   456,   457,   458,   459,   448,   461,
     462,   463,   483,   474,   475,   472,   464,   460,   468,   469,
     467,   471,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,     0,     0,     0,     0,     0,    43,    44,    45,
       0,     0,   661,     0,     0,     0,     0,     0,     0,     0,
       0,   653,   654,   655,   659,   656,   658,   657,   660,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,    64,    65,    63,
      60,    59,    66,    52,    62,    55,    56,    57,    53,    61,
      58,    54,     0,     0,   298,     0,     0,   296,   297,    97,
       0,     0,     0,     0,    92,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   612,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     198,   199,   202,   203,   205,   206,   207,   208,   209,   210,
     211,   200,   201,   204,     0,     0,     0,     0,     0,   372,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   349,
     350,   351,   352,   353,   354,   356,   355,   358,   362,   359,
     360,   361,   357,   406,     0,     0,     0,   403,   404,   405,
       0,     0,   410,   427,     0,     0,   417,   426,     0,   423,
     424,   425,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   431,   594,   605,     0,     0,   597,
       0,     0,     0,   587,   588,   589,   590,   591,   592,   593,
       0,     0,     0,   267,     0,     0,     0,     0,     0,     0,
     253,   254,   255,   256,   261,   257,   258,   259,   260,   397,
       0,   387,     0,   396,     0,   393,   394,   395,     0,   228,
       0,     0,     0,   238,     0,   236,   237,   239,   240,   106,
       0,     0,   102,     0,    46,     0,     0,     0,    42,     0,
       0,     0,   173,     0,     0,     0,   149,     0,     0,   133,
     134,   135,   136,   139,   140,   138,   137,   141,     0,     0,
       0,     0,     0,   286,   287,   288,   289,     0,     0,     0,
       0,     0,     0,     0,     0,   652,    67,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,     0,     0,   310,     0,     0,   303,
     304,   305,   306,     0,     0,   332,     0,   327,   328,   329,
       0,     0,   295,     0,     0,     0,    91,     0,     0,     0,
       0,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   611,   212,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   197,   363,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   348,     0,
       0,     0,   402,     0,   409,     0,     0,     0,     0,   422,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,     0,     0,     0,
       0,     0,     0,     0,   430,     0,     0,     0,     0,     0,
       0,     0,   586,   262,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   252,     0,     0,     0,     0,   392,   241,
       0,     0,     0,     0,     0,   235,     0,   101,     0,     0,
       0,    41,   142,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   132,   290,     0,     0,     0,     0,   285,     0,
       0,     0,     0,     0,     0,     0,   651,     0,     0,     0,
       0,     0,     0,     0,     0,    72,    73,     0,    71,    76,
      77,     0,    75,     0,     0,     0,     0,     0,    49,   307,
       0,     0,     0,     0,   302,   330,     0,     0,     0,   326,
       0,   294,   100,    99,    98,   646,   645,   633,   635,    27,
      27,    27,    27,    27,    29,    28,   639,   640,   644,   642,
     641,   647,   648,   649,   650,   643,   634,   636,   637,   638,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   196,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   347,     0,
       0,   401,   414,     0,     0,     0,   416,   496,   500,   516,
     582,   530,   494,   524,   527,   495,   486,   487,   503,   492,
     493,   506,   491,   505,   504,   499,   498,   497,   525,   485,
     523,   580,   581,   520,   517,   567,   560,   577,   578,   561,
     562,   563,   564,   572,   565,   575,   579,   568,   573,   569,
     574,   566,   571,   570,   576,     0,   559,   522,   542,   536,
     553,   554,   537,   538,   539,   540,   548,   541,   551,   555,
     544,   549,   545,   550,   543,   547,   546,   552,     0,   535,
     515,   518,   529,   489,   490,   519,   508,   513,   514,   511,
     512,   509,   510,   502,   501,    35,    35,    35,    37,    36,
     583,   528,   531,   521,   526,   488,   507,     0,     0,     0,
       0,     0,     0,   585,     0,     0,     0,     0,     0,     0,
       0,     0,   251,     0,     0,     0,   386,     0,     0,     0,
     246,   242,   245,   227,   107,     0,     0,   119,     0,     0,
     111,   112,   114,   113,    47,    48,     0,     0,     0,     0,
       0,     0,     0,     0,   131,     0,     0,     0,   284,   667,
     662,   666,   664,   668,   663,   665,    84,    90,    82,    86,
      85,    79,    78,    80,    68,     0,    69,     0,    83,    81,
      89,    87,    88,     0,     0,     0,   301,     0,     0,   325,
     299,    30,    31,    32,    33,    34,   223,   224,   217,   219,
     221,   220,   218,   213,   225,   216,   214,   215,   222,   368,
     370,   371,   383,   380,   376,   377,   379,   378,     0,   375,
     365,   381,   382,   364,   369,   367,   384,   366,   407,   408,
     428,   429,   421,     0,   420,   557,     0,   533,     0,    38,
      39,    40,   610,   609,     0,   608,   596,   595,   602,   601,
       0,   600,   604,   603,   265,   266,   275,   272,   277,   274,
     273,   279,   276,   278,   271,     0,   270,   264,   282,   281,
     280,   263,   399,   391,     0,   390,   398,   233,   234,   232,
       0,   231,   249,   248,     0,     0,     0,   115,     0,     0,
       0,     0,   110,   148,   146,   188,   185,   184,   177,   179,
     194,   189,   192,   187,   178,   193,   181,   190,   182,   191,
     186,   180,   183,     0,   176,   143,   145,   147,   159,   153,
     170,   171,   154,   155,   156,   157,   165,   158,   168,   172,
     161,   166,   162,   167,   160,   164,   163,   169,     0,   152,
     144,   292,   293,   291,    70,    74,   308,   314,   320,   323,
     316,   322,   317,   321,   319,   315,   318,     0,   313,   309,
     331,   336,   342,   345,   338,   344,   339,   343,   341,   337,
     340,     0,   335,   373,     0,   418,     0,   558,   534,   606,
       0,   598,     0,   268,     0,   388,     0,   229,     0,   247,
     244,   243,     0,     0,     0,     0,   109,   174,     0,   150,
       0,   311,     0,   333,     0,   374,   419,   607,   599,   269,
     389,   230,   116,   125,   128,   127,   124,   129,   126,   123,
       0,   122,   118,   117,   175,   151,   312,   334,   120,     0,
     121
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    25,   834,   835,   978,   979,    26,   246,   247,
     248,   249,    27,   285,   286,   287,   288,   797,   798,   801,
     802,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,    28,    74,    75,    76,    77,    78,
      29,   238,   239,   240,   241,   242,  1019,  1020,  1021,  1022,
    1023,  1169,  1300,  1301,    30,    63,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   769,  1218,  1219,   547,   765,
    1193,  1194,    31,    51,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,    32,
      60,   513,   750,  1160,  1161,   514,   515,   516,  1166,  1011,
    1012,   517,   518,    33,    58,   489,   490,   491,   492,   493,
     494,   495,   736,  1145,  1146,   496,   497,   498,    34,    64,
     552,   553,   554,   555,   556,    35,   306,   307,   308,    36,
      67,   588,   589,   590,   591,   592,   811,  1237,  1238,    37,
      68,   596,   597,   598,   599,   817,  1251,  1252,    38,    52,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     648,  1098,  1099,   388,   389,   390,   391,   392,    39,    59,
     503,   745,  1154,  1155,   504,   505,   506,   507,    40,    53,
     396,   397,   398,   399,    41,   123,   124,   125,    42,    55,
     407,   667,  1113,  1114,   408,   409,   410,   411,    43,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   442,   958,   959,
     227,   440,   935,   936,   228,   229,   230,   231,    44,    57,
     472,   473,   474,   475,   476,   728,  1130,  1131,   477,   478,
     479,   725,  1124,  1125,    45,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,    46,   260,   261,   262,   263,
     264,   265,   266,   267,   268
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -733
static const yytype_int16 yypact[] =
{
    -733,   707,  -733,  -152,  -235,  -230,  -733,  -733,  -733,  -228,
    -733,  -225,  -733,  -733,  -733,  -733,  -222,  -219,  -733,  -733,
    -217,  -211,  -733,  -733,  -206,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,    13,
     612,  -201,  -198,  -188,    16,  -183,   373,  -173,  -170,  -167,
    -164,    40,    90,  -151,  -135,   359,   422,  -132,   -97,    15,
     -82,   -64,   -61,   -55,    22,  -733,  -733,  -733,  -733,  -733,
     -49,   -43,   -41,   -13,   -10,    -8,    -3,     7,    30,    66,
      80,    85,    95,   134,   135,   139,   146,   154,   172,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,   637,   472,
      18,  -733,   169,    24,  -733,  -733,   189,  -733,   171,   180,
     182,   186,   192,   196,   199,   200,   202,   203,   206,   207,
     210,   211,   214,   216,   218,   227,   228,   230,   233,   239,
     241,   242,   248,   255,   260,   261,  -733,   263,  -733,   265,
     268,   273,   275,   276,   277,   282,   285,   286,   287,   288,
     291,   297,   298,   299,   305,   310,   311,   312,   313,    48,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,   307,   456,    64,   346,   -32,   314,    33,  -733,
    -733,  -733,    44,    28,   315,   316,    29,  -733,  -733,  -733,
     464,   109,  -733,   317,   319,   322,   327,   329,   330,   332,
     281,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,   116,
     333,   334,   339,   341,   342,   343,   344,   350,   353,   354,
     355,   356,   360,   361,   363,   152,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,    21,    58,  -733,   365,    81,  -733,  -733,  -733,
     254,   266,   300,   176,  -733,   493,   502,   442,   443,   510,
     510,   511,   513,   514,   450,   451,   518,   510,   453,   454,
     458,   459,   460,   391,  -733,   396,   397,   398,   399,   400,
     402,   404,   405,   406,   407,   408,   409,   410,   411,   238,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,   420,   419,   421,   423,   424,  -733,
     426,   427,   428,   431,   432,   433,   434,   436,     4,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,   437,   438,    63,  -733,  -733,  -733,
     533,   425,  -733,  -733,   440,   441,  -733,  -733,    19,  -733,
    -733,  -733,   517,   510,   510,   576,   519,   523,   577,   569,
     525,   592,   594,   595,   534,   539,   540,   510,   578,   541,
     610,   611,   510,   613,   618,   591,   622,   625,   562,   564,
     497,   567,   501,   510,   510,   570,   510,   571,   572,   581,
     -15,   141,   584,   585,   510,   510,   644,   631,   510,   587,
     593,   596,   599,   526,  -733,  -733,  -733,   524,   535,  -733,
     536,   537,   153,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
     529,   538,   543,  -733,   546,   547,   548,   549,   550,    35,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
     558,  -733,   559,  -733,    60,  -733,  -733,  -733,   542,  -733,
     563,   568,   574,  -733,     2,  -733,  -733,  -733,  -733,  -733,
     601,   544,  -733,   580,  -733,   653,   680,   573,  -733,   586,
     582,   588,  -733,   589,   590,   600,  -733,   602,     5,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,   597,   603,
     604,   605,    43,  -733,  -733,  -733,  -733,   649,   652,   655,
     698,   659,   660,   510,   598,  -733,  -733,   706,   664,   714,
     719,   720,   721,   722,   723,   187,   213,   724,   725,   747,
     729,   730,   635,  -733,   636,   643,  -733,   646,    74,  -733,
    -733,  -733,  -733,   638,   647,  -733,    77,  -733,  -733,  -733,
     757,   656,  -733,   663,   667,   668,  -733,   672,   675,   683,
     686,   178,   687,   688,   689,   690,   692,   693,   694,   695,
     696,   697,   699,   701,   702,   703,  -733,  -733,   783,   784,
     510,   786,   795,   810,   829,   814,   836,   837,   510,   510,
     644,   709,  -733,  -733,   817,   173,   820,   776,   710,   822,
     824,   825,   826,   848,   828,   830,   831,   726,  -733,   832,
     833,   727,  -733,   728,  -733,   834,   835,   731,   732,  -733,
     733,   735,   736,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   748,   749,   750,   752,   753,   754,   755,
     756,   758,   759,   760,   761,   762,   763,   764,   614,   765,
     679,   766,   767,   768,   770,   771,   772,   773,   774,   775,
     777,   778,   779,   780,   781,   782,    25,   785,   787,   788,
     789,   790,   791,   792,  -733,   793,   510,   794,   796,   841,
     857,   797,  -733,  -733,   867,   849,   798,   886,   850,   893,
     896,   903,   800,  -733,   904,   799,   905,   803,  -733,  -733,
     801,   908,   915,   861,   806,  -733,   807,  -733,   117,   808,
     809,  -733,  -733,   920,   876,   811,   922,   923,   925,   813,
     927,   818,  -733,  -733,   929,   930,   931,   823,  -733,   827,
     838,   839,   842,   843,   844,   845,  -733,   846,   847,   851,
     852,   853,   854,   855,   856,  -733,  -733,  -212,  -733,  -733,
    -733,  -210,  -733,   858,   859,   860,   862,   863,  -733,  -733,
     932,   821,   935,   864,  -733,  -733,   936,   865,   866,  -733,
     869,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,   510,
     510,   510,   510,   510,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
     870,   871,   872,   873,   874,   875,   877,   878,   879,   880,
     881,   882,   883,  -733,   884,   885,   887,   888,   889,   138,
     890,   891,   892,   894,   895,   897,   898,   899,  -733,   900,
     901,  -733,  -733,   902,   906,   933,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,   -35,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,   -33,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,   644,   644,   644,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,     0,   907,   909,
       1,   910,   911,  -733,   912,   913,   840,   914,   916,   917,
     918,   919,  -733,   921,   934,   924,  -733,    -6,   926,   928,
     946,   937,  -733,  -733,  -733,   938,   939,  -733,   940,    67,
    -733,  -733,  -733,  -733,  -733,  -733,   944,   945,   477,   947,
     948,   949,   716,   950,  -733,   951,   952,   953,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,   187,  -733,   213,  -733,  -733,
    -733,  -733,  -733,   954,   302,   955,  -733,   956,   560,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,   -16,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,    51,  -733,  -733,   614,  -733,   679,  -733,
    -733,  -733,  -733,  -733,    62,  -733,  -733,  -733,  -733,  -733,
     108,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,   113,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,   123,  -733,  -733,  -733,  -733,  -733,
     124,  -733,  -733,  -733,   961,   861,   957,  -733,   941,   943,
    -106,   958,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,   131,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,   132,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,   143,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,   159,  -733,  -733,   138,  -733,   933,  -733,  -733,  -733,
       0,  -733,     1,  -733,   840,  -733,   934,  -733,    -6,  -733,
    -733,  -733,   959,   388,   960,   962,  -733,  -733,   477,  -733,
     716,  -733,   302,  -733,   560,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
     184,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,   388,
    -733
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -733,  -733,  -733,  -732,  -318,  -542,  -456,  -733,  -733,   963,
    -733,  -733,  -733,  -733,   804,  -733,  -733,  -733,    20,  -733,
      17,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,   999,  -733,  -733,  -733,
    -733,  -733,   868,  -733,  -733,  -733,  -733,    57,  -733,  -733,
    -733,  -733,  -733,  -232,  -733,  -733,  -733,   552,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -202,  -733,  -733,
    -733,  -197,  -733,  -733,  -733,   812,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -186,  -733,   620,  -733,  -733,  -733,
     -74,  -733,  -733,  -733,  -733,  -733,   609,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -162,  -733,  -733,  -733,  -733,  -733,
    -733,   556,  -733,  -733,  -733,  -733,  -733,   942,  -733,  -733,
    -733,  -733,   557,  -733,  -733,  -733,  -733,  -733,  -165,  -733,
    -733,  -733,   553,  -733,  -733,  -733,  -733,  -147,  -733,  -733,
    -733,   802,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -110,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -120,  -733,   662,  -733,  -733,  -733,  -733,
    -733,   815,  -733,  -733,  -733,  -733,  1033,  -733,  -733,  -733,
    -733,  -733,  -733,   -93,  -733,   769,  -733,  -733,  -733,  -733,
     985,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,    50,
    -733,  -733,  -733,    54,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,   700,  -733,  -733,  -733,  -733,  -733,   -91,  -733,  -733,
    -733,  -733,  -733,   -87,  -733,  -733,  1076,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,  -733,
    -733,  -733,  -733,  -733,  -733,  -733,  -733,   964,  -733,  -733,
    -733,  -733,  -733,  -733,  -733
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -109
static const yytype_int16 yytable[] =
{
     717,   612,   613,   508,   716,   364,   529,   365,    49,   620,
     366,  1122,  1128,    50,    70,    54,   304,   121,    56,   393,
     403,    61,   584,    70,    62,   121,    65,   367,   530,  1054,
     243,  1056,    66,  1055,   236,  1057,   480,    69,   975,   976,
     977,   236,   118,    71,   548,   119,   368,   531,   509,   127,
     369,   532,    71,    72,  1157,   120,   128,   129,   481,   593,
     126,   499,    72,   549,   393,   499,   130,   510,  1015,   370,
     232,   371,   511,   233,   131,   584,   234,   482,   593,   235,
     132,   483,   304,   372,   133,   134,   122,   135,   394,    47,
      48,   243,   250,   136,   122,   671,   672,  1071,  1072,  1073,
    1074,  1075,   137,   138,   373,   533,  1274,   139,   251,   685,
     548,   302,   140,    73,   690,   305,   141,   142,  1015,   404,
     143,   585,    73,   144,   145,   701,   702,   244,   704,   549,
     534,   146,   512,   394,   374,   716,   714,   715,   147,   148,
     719,   149,   150,   151,   152,   153,   303,   550,  1094,   535,
    1095,   395,   405,   269,   465,   245,   154,   466,   594,   309,
     484,   708,   709,   375,   155,   156,   157,  1016,   158,   485,
     486,   159,   160,    79,   585,   161,   551,   594,  1123,  1129,
     310,   305,   270,   311,   862,   406,   162,   586,   244,   312,
     403,   467,   376,   500,   468,   315,   395,   500,  1158,    80,
      81,   316,  1159,   317,   487,    82,  1115,    83,  1117,   519,
    1116,   163,  1118,   550,   536,   164,   245,  1016,   271,   165,
     166,   167,   168,   169,   595,  1253,   501,   170,   171,  1254,
     501,   318,   537,  1017,   319,   469,   320,   172,   377,   335,
     586,   321,   551,   595,   754,   785,   657,   771,   587,    84,
      85,   322,   272,   470,   273,   274,    86,    87,    88,   336,
     337,   668,   488,   338,   313,   237,   401,   173,   174,   524,
     175,   527,   237,  -108,   323,   521,   176,   742,    89,    90,
    -108,   177,   252,  1017,   523,   777,   178,   502,   611,   404,
     463,   502,  1255,    91,    92,   275,  1256,   276,   277,   278,
     279,   587,   747,  1259,    93,   661,  1018,  1260,   465,  1171,
     324,   466,   852,    94,   280,   253,   813,   710,   711,   818,
     860,   861,   405,   601,   325,   339,   340,   341,   254,   326,
     342,   829,   830,   831,   832,   833,   795,   796,   343,   327,
     281,   255,   256,   257,   258,   467,  1096,   508,   468,  1261,
     344,   345,   282,  1262,  1263,   406,  1018,   566,  1264,  1097,
     252,   259,   799,   800,  1265,  1267,   346,   347,  1266,  1268,
     865,   866,  1277,  1279,   127,  1227,  1278,  1280,   328,   329,
     471,   128,   129,   330,  1281,   603,   283,   284,  1282,   469,
     331,   130,   509,   253,   582,   731,   348,   604,   332,   131,
    1283,    95,    96,    97,  1284,   132,   254,   470,   988,   133,
     134,   510,   135,   400,   333,   412,   511,   606,   136,   255,
     256,   257,   258,   269,   413,  1308,   414,   137,   138,  1309,
     415,   605,   139,  1119,  1120,  1121,   416,   140,  1293,   259,
     417,   141,   142,   418,   419,   143,   420,   421,   144,   145,
     422,   423,   270,  1228,   424,   425,   146,   480,   426,  1294,
     427,  1295,   428,   147,   148,   529,   149,   150,   151,   152,
     153,   429,   430,   364,   431,   365,   512,   432,   366,   481,
     641,   154,  1175,   433,  1229,   434,   435,   530,   271,   155,
     156,   157,   436,   158,  1230,   367,   159,   160,   482,   437,
     161,  1231,   483,  1296,   438,   439,   531,   441,  1176,   443,
     532,   162,   444,  1232,   368,  1233,  1234,   445,   369,   446,
     447,   448,   272,   564,   273,   274,   449,  1177,  1235,   450,
     451,   452,   453,  1178,   471,   454,   163,   370,  1236,   371,
     164,   455,   456,   457,   165,   166,   167,   168,   169,   458,
    1179,   372,   170,   171,   459,   460,   461,   462,   520,   525,
     526,   557,   172,   558,   533,   275,   559,   276,   277,   278,
     279,   560,   373,   561,   562,  1180,   563,   567,   568,  1297,
    1298,   484,  1181,   569,   280,   570,   571,   572,   573,   534,
     485,   486,   173,   174,   574,   175,  1182,   575,   576,   577,
     578,   176,   374,   607,   579,   580,   177,   581,   535,   600,
     281,   178,   608,    79,  1183,  1299,  1184,  1185,   609,   610,
     611,   614,   282,   615,   616,   487,   617,   618,   619,   621,
     622,   375,   626,  1241,   623,   624,   625,   627,   335,    80,
      81,   628,   629,   630,   631,    82,   632,    83,   633,   634,
     635,   636,   637,   638,   639,   640,   283,   284,   336,   337,
     376,   643,   338,   644,   663,   645,   664,   646,   647,  1186,
     649,   650,   651,   536,   915,   652,   653,   654,   655,  1187,
     656,   659,   660,   488,   665,   666,   673,   676,  1188,    84,
      85,   537,  1189,   670,  1190,   674,    86,    87,    88,   675,
     677,   678,   679,  1191,   680,   681,   377,     2,     3,   686,
     682,  1242,     4,  1192,  1275,   683,   684,   687,    89,    90,
     688,   689,   693,   691,   339,   340,   341,     5,   692,   342,
       6,     7,   694,    91,    92,   695,     8,   343,   696,   938,
     697,   698,  1243,   699,    93,   700,   703,   705,   706,   344,
     345,     9,  1244,    94,   716,    10,    11,   707,    12,  1245,
     712,   713,   718,   720,    13,   346,   347,   724,   726,   721,
     733,  1246,   722,  1247,  1248,   723,  1198,   756,    14,   727,
     729,   730,   734,   749,   759,   757,  1249,   735,    15,    16,
     737,   738,   739,   740,   741,   348,  1250,   916,   917,   918,
     919,   920,   744,   746,   921,   922,    17,   751,   923,   924,
     925,   760,   752,   926,   761,   927,   928,   929,   753,   930,
     931,   932,    18,   758,   933,   779,   763,   762,   780,   782,
     934,   781,   764,   766,   767,   783,   784,   787,   773,   786,
     788,    95,    96,    97,   768,   789,   770,   774,   775,   776,
     790,   791,   792,   793,   794,   803,   804,   805,    19,  1136,
     806,   807,   939,   940,   941,   942,   943,    20,    21,   944,
     945,    22,    23,   946,   947,   948,   808,   809,   949,   815,
     950,   951,   952,  1137,   953,   954,   955,   810,   820,   956,
     812,   816,  1138,   850,   851,   957,   853,   821,  1139,  1199,
    1200,  1201,  1202,  1203,   822,   854,  1204,  1205,   823,   824,
    1206,  1207,  1208,   825,  1140,  1209,   826,  1210,  1211,  1212,
     855,  1213,  1214,  1215,   827,    24,  1216,   828,   836,   837,
     838,   839,  1217,   840,   841,   842,   843,   844,   845,   856,
     846,  1141,   847,   848,   849,   857,   858,   859,   864,  1142,
     863,   867,   868,   870,   869,   871,   872,   873,   874,   875,
     998,   876,   877,   879,   880,   883,   884,   878,   881,   882,
     989,  1010,   991,   886,   887,   885,   888,   889,   890,   891,
     892,   893,   894,   895,   896,   897,   898,   899,   992,   900,
     901,   902,  1143,   903,   904,   905,   906,   907,   994,   908,
     909,   910,   911,   912,   913,   914,   937,   960,   961,   962,
    1144,   963,   964,   965,   966,   967,   968,   997,   969,   970,
     971,   972,   973,   974,   999,   995,   980,  1000,   981,   982,
     983,   984,   985,   986,  1001,  1003,  1005,   987,   993,  1008,
     990,  1002,   996,  1004,  1006,  1007,  1009,  1013,  1014,  1024,
    1025,  1026,  1027,  1029,  1030,  1028,  1031,  1032,  1033,  1034,
    1035,  1036,  1037,  1063,  1038,  1064,  1065,  1067,  1039,  1112,
    1153,  1269,  1272,   314,  1225,  1224,  1172,  1310,  1305,  1040,
    1041,  1304,  1291,  1042,  1043,  1044,  1045,  1046,  1047,   583,
     772,  1270,  1048,  1049,  1050,  1051,  1052,  1053,   743,  1058,
    1059,  1060,  1289,  1061,  1062,  1066,   522,  1069,   778,  1068,
    1070,  1076,  1077,  1078,  1079,  1080,  1081,  1306,  1082,  1083,
    1084,  1085,  1086,  1087,  1088,  1089,  1090,  1164,  1091,  1092,
    1093,  1100,  1101,  1102,   755,  1103,  1104,  1307,  1105,  1106,
    1107,  1108,  1109,  1110,  1285,   814,  1290,  1111,  1126,   819,
    1127,  1132,  1133,  1134,  1135,  1147,   402,  1148,  1149,  1150,
    1151,   642,  1152,  1286,   464,  1156,   748,  1162,  1258,  1163,
    1257,  1288,   732,  1287,   334,     0,     0,   669,     0,  1167,
     658,     0,  1165,  1168,  1170,  1173,  1174,  1273,  1195,  1196,
    1197,  1220,  1221,  1222,  1223,  1226,  1239,  1240,  1271,  1276,
    1292,  1302,     0,  1303,     0,     0,     0,     0,     0,   528,
       0,   662,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   565,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   602
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-733))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     456,   319,   320,     1,   110,     1,     1,     3,   243,   327,
       6,    11,    11,   243,     1,   243,     1,     1,   243,     1,
       1,   243,     1,     1,   243,     1,   243,    23,    23,   241,
       1,   241,   243,   245,     1,   245,     1,   243,    13,    14,
      15,     1,   243,    30,     1,   243,    42,    42,    46,     1,
      46,    46,    30,    40,    60,   243,     8,     9,    23,     1,
     243,     1,    40,    20,     1,     1,    18,    65,     1,    65,
     243,    67,    70,   243,    26,     1,   243,    42,     1,   243,
      32,    46,     1,    79,    36,    37,    70,    39,    70,   241,
     242,     1,   243,    45,    70,   413,   414,   829,   830,   831,
     832,   833,    54,    55,   100,   100,   212,    59,   243,   427,
       1,   243,    64,   100,   432,   100,    68,    69,     1,   100,
      72,   100,   100,    75,    76,   443,   444,    98,   446,    20,
     125,    83,   130,    70,   130,   110,   454,   455,    90,    91,
     458,    93,    94,    95,    96,    97,   243,   104,    10,   144,
      12,   133,   133,     1,     1,   126,   108,     4,   100,   241,
     125,   176,   177,   159,   116,   117,   118,   100,   120,   134,
     135,   123,   124,     1,   100,   127,   133,   100,   178,   178,
     244,   100,    30,   244,   640,   166,   138,   166,    98,   244,
       1,    38,   188,   133,    41,   244,   133,   133,   204,    27,
      28,   244,   208,   244,   169,    33,   241,    35,   241,   241,
     245,   163,   245,   104,   209,   167,   126,   100,    66,   171,
     172,   173,   174,   175,   166,   241,   166,   179,   180,   245,
     166,   244,   227,   166,   244,    82,   244,   189,   234,     1,
     166,   244,   133,   166,   242,   563,   242,   242,   227,    77,
      78,   244,   100,   100,   102,   103,    84,    85,    86,    21,
      22,   242,   227,    25,   242,   232,   242,   219,   220,   241,
     222,   242,   232,   240,   244,   242,   228,   242,   106,   107,
     240,   233,     1,   166,   240,   242,   238,   227,   110,   100,
     242,   227,   241,   121,   122,   143,   245,   145,   146,   147,
     148,   227,   242,   241,   132,   242,   239,   245,     1,   242,
     244,     4,   630,   141,   162,    34,   242,   176,   177,   242,
     638,   639,   133,   242,   244,    87,    88,    89,    47,   244,
      92,   153,   154,   155,   156,   157,   149,   150,   100,   244,
     188,    60,    61,    62,    63,    38,   208,     1,    41,   241,
     112,   113,   200,   245,   241,   166,   239,   241,   245,   221,
       1,    80,   149,   150,   241,   241,   128,   129,   245,   245,
     197,   198,   241,   241,     1,    73,   245,   245,   244,   244,
     227,     8,     9,   244,   241,   131,   234,   235,   245,    82,
     244,    18,    46,    34,   242,   242,   158,   131,   244,    26,
     241,   229,   230,   231,   245,    32,    47,   100,   726,    36,
      37,    65,    39,   244,   242,   244,    70,   241,    45,    60,
      61,    62,    63,     1,   244,   241,   244,    54,    55,   245,
     244,   131,    59,   975,   976,   977,   244,    64,    50,    80,
     244,    68,    69,   244,   244,    72,   244,   244,    75,    76,
     244,   244,    30,   151,   244,   244,    83,     1,   244,    71,
     244,    73,   244,    90,    91,     1,    93,    94,    95,    96,
      97,   244,   244,     1,   244,     3,   130,   244,     6,    23,
     242,   108,     5,   244,   182,   244,   244,    23,    66,   116,
     117,   118,   244,   120,   192,    23,   123,   124,    42,   244,
     127,   199,    46,   115,   244,   244,    42,   244,    31,   244,
      46,   138,   244,   211,    42,   213,   214,   244,    46,   244,
     244,   244,   100,   242,   102,   103,   244,    50,   226,   244,
     244,   244,   244,    56,   227,   244,   163,    65,   236,    67,
     167,   244,   244,   244,   171,   172,   173,   174,   175,   244,
      73,    79,   179,   180,   244,   244,   244,   244,   244,   244,
     244,   244,   189,   244,   100,   143,   244,   145,   146,   147,
     148,   244,   100,   244,   244,    98,   244,   244,   244,   191,
     192,   125,   105,   244,   162,   244,   244,   244,   244,   125,
     134,   135,   219,   220,   244,   222,   119,   244,   244,   244,
     244,   228,   130,   110,   244,   244,   233,   244,   144,   244,
     188,   238,   110,     1,   137,   227,   139,   140,   176,   176,
     110,   110,   200,   110,   110,   169,   176,   176,   110,   176,
     176,   159,   241,    73,   176,   176,   176,   241,     1,    27,
      28,   244,   244,   244,   244,    33,   244,    35,   244,   244,
     244,   244,   244,   244,   244,   244,   234,   235,    21,    22,
     188,   241,    25,   244,   131,   244,   241,   244,   244,   192,
     244,   244,   244,   209,    60,   244,   244,   244,   244,   202,
     244,   244,   244,   227,   244,   244,   110,   110,   211,    77,
      78,   227,   215,   176,   217,   176,    84,    85,    86,   176,
     131,   176,   110,   226,   110,   110,   234,     0,     1,   131,
     176,   151,     5,   236,  1170,   176,   176,   176,   106,   107,
     110,   110,   131,   110,    87,    88,    89,    20,   110,    92,
      23,    24,   110,   121,   122,   110,    29,   100,   176,    60,
     176,   244,   182,   176,   132,   244,   176,   176,   176,   112,
     113,    44,   192,   141,   110,    48,    49,   176,    51,   199,
     176,   176,   131,   176,    57,   128,   129,   241,   244,   176,
     241,   211,   176,   213,   214,   176,    60,   176,    71,   244,
     244,   244,   244,   241,   131,   241,   226,   244,    81,    82,
     244,   244,   244,   244,   244,   158,   236,   183,   184,   185,
     186,   187,   244,   244,   190,   191,    99,   244,   194,   195,
     196,   131,   244,   199,   241,   201,   202,   203,   244,   205,
     206,   207,   115,   243,   210,   176,   244,   241,   176,   131,
     216,   176,   244,   244,   244,   176,   176,   131,   241,   241,
     176,   229,   230,   231,   244,   131,   244,   244,   244,   244,
     131,   131,   131,   131,   131,   131,   131,   110,   151,    19,
     131,   131,   183,   184,   185,   186,   187,   160,   161,   190,
     191,   164,   165,   194,   195,   196,   241,   241,   199,   241,
     201,   202,   203,    43,   205,   206,   207,   244,   131,   210,
     244,   244,    52,   110,   110,   216,   110,   241,    58,   183,
     184,   185,   186,   187,   241,   110,   190,   191,   241,   241,
     194,   195,   196,   241,    74,   199,   241,   201,   202,   203,
     110,   205,   206,   207,   241,   218,   210,   241,   241,   241,
     241,   241,   216,   241,   241,   241,   241,   241,   241,   110,
     241,   101,   241,   241,   241,   131,   110,   110,   131,   109,
     241,   131,   176,   131,   244,   131,   131,   131,   110,   131,
     110,   131,   131,   131,   131,   131,   131,   241,   241,   241,
     176,   110,   131,   241,   241,   244,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   131,   241,
     241,   241,   152,   241,   241,   241,   241,   241,   131,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     170,   241,   241,   241,   241,   241,   241,   131,   241,   241,
     241,   241,   241,   241,   131,   176,   241,   131,   241,   241,
     241,   241,   241,   241,   131,   131,   131,   244,   241,   131,
     244,   241,   244,   244,   241,   244,   131,   241,   241,   241,
     241,   131,   176,   131,   131,   244,   131,   244,   131,   241,
     131,   131,   131,   131,   241,   244,   131,   131,   241,   136,
     136,   110,   131,    74,  1057,  1055,  1019,  1309,  1280,   241,
     241,  1278,  1268,   241,   241,   241,   241,   241,   241,   285,
     538,  1165,   241,   241,   241,   241,   241,   241,   489,   241,
     241,   241,  1264,   241,   241,   241,   238,   241,   552,   244,
     241,   241,   241,   241,   241,   241,   241,  1282,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   181,   241,   241,
     241,   241,   241,   241,   514,   241,   241,  1284,   241,   241,
     241,   241,   241,   241,  1254,   588,  1266,   241,   241,   596,
     241,   241,   241,   241,   241,   241,   123,   241,   241,   241,
     241,   349,   241,  1256,   179,   241,   504,   241,  1118,   241,
    1116,  1262,   472,  1260,    98,    -1,    -1,   408,    -1,   241,
     378,    -1,   245,   244,   244,   241,   241,   244,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,    -1,   241,    -1,    -1,    -1,    -1,    -1,   246,
      -1,   396,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   260,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   306
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   247,     0,     1,     5,    20,    23,    24,    29,    44,
      48,    49,    51,    57,    71,    81,    82,    99,   115,   151,
     160,   161,   164,   165,   218,   248,   253,   258,   280,   286,
     300,   318,   335,   349,   364,   371,   375,   385,   394,   414,
     424,   430,   434,   444,   504,   520,   541,   241,   242,   243,
     243,   319,   395,   425,   243,   435,   243,   505,   350,   415,
     336,   243,   243,   301,   365,   243,   243,   376,   386,   243,
       1,    30,    40,   100,   281,   282,   283,   284,   285,     1,
      27,    28,    33,    35,    77,    78,    84,    85,    86,   106,
     107,   121,   122,   132,   141,   229,   230,   231,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   243,   243,
     243,     1,    70,   431,   432,   433,   243,     1,     8,     9,
      18,    26,    32,    36,    37,    39,    45,    54,    55,    59,
      64,    68,    69,    72,    75,    76,    83,    90,    91,    93,
      94,    95,    96,    97,   108,   116,   117,   118,   120,   123,
     124,   127,   138,   163,   167,   171,   172,   173,   174,   175,
     179,   180,   189,   219,   220,   222,   228,   233,   238,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   496,   500,   501,
     502,   503,   243,   243,   243,   243,     1,   232,   287,   288,
     289,   290,   291,     1,    98,   126,   254,   255,   256,   257,
     243,   243,     1,    34,    47,    60,    61,    62,    63,    80,
     542,   543,   544,   545,   546,   547,   548,   549,   550,     1,
      30,    66,   100,   102,   103,   143,   145,   146,   147,   148,
     162,   188,   200,   234,   235,   259,   260,   261,   262,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   243,   243,     1,   100,   372,   373,   374,   241,
     244,   244,   244,   242,   282,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   242,   522,     1,    21,    22,    25,    87,
      88,    89,    92,   100,   112,   113,   128,   129,   158,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,     1,     3,     6,    23,    42,    46,
      65,    67,    79,   100,   130,   159,   188,   234,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   409,   410,
     411,   412,   413,     1,    70,   133,   426,   427,   428,   429,
     244,   242,   432,     1,   100,   133,   166,   436,   440,   441,
     442,   443,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     497,   244,   493,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   242,   446,     1,     4,    38,    41,    82,
     100,   227,   506,   507,   508,   509,   510,   514,   515,   516,
       1,    23,    42,    46,   125,   134,   135,   169,   227,   351,
     352,   353,   354,   355,   356,   357,   361,   362,   363,     1,
     133,   166,   227,   416,   420,   421,   422,   423,     1,    46,
      65,    70,   130,   337,   341,   342,   343,   347,   348,   241,
     244,   242,   288,   240,   241,   244,   244,   242,   255,     1,
      23,    42,    46,   100,   125,   144,   209,   227,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   314,     1,    20,
     104,   133,   366,   367,   368,   369,   370,   244,   244,   244,
     244,   244,   244,   244,   242,   543,   241,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   242,   260,     1,   100,   166,   227,   377,   378,
     379,   380,   381,     1,   100,   166,   387,   388,   389,   390,
     244,   242,   373,   131,   131,   131,   241,   110,   110,   176,
     176,   110,   250,   250,   110,   110,   110,   176,   176,   110,
     250,   176,   176,   176,   176,   176,   241,   241,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   242,   321,   241,   244,   244,   244,   244,   406,   244,
     244,   244,   244,   244,   244,   244,   244,   242,   397,   244,
     244,   242,   427,   131,   241,   244,   244,   437,   242,   441,
     176,   250,   250,   110,   176,   176,   110,   131,   176,   110,
     110,   110,   176,   176,   176,   250,   131,   176,   110,   110,
     250,   110,   110,   131,   110,   110,   176,   176,   244,   176,
     244,   250,   250,   176,   250,   176,   176,   176,   176,   177,
     176,   177,   176,   176,   250,   250,   110,   252,   131,   250,
     176,   176,   176,   176,   241,   517,   244,   244,   511,   244,
     244,   242,   507,   241,   244,   244,   358,   244,   244,   244,
     244,   244,   242,   352,   244,   417,   244,   242,   421,   241,
     338,   244,   244,   244,   242,   342,   176,   241,   243,   131,
     131,   241,   241,   244,   244,   315,   244,   244,   244,   311,
     244,   242,   303,   241,   244,   244,   244,   242,   367,   176,
     176,   176,   131,   176,   176,   250,   241,   131,   176,   131,
     131,   131,   131,   131,   131,   149,   150,   263,   264,   149,
     150,   265,   266,   131,   131,   110,   131,   131,   241,   241,
     244,   382,   244,   242,   378,   241,   244,   391,   242,   388,
     131,   241,   241,   241,   241,   241,   241,   241,   241,   153,
     154,   155,   156,   157,   249,   250,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     110,   110,   250,   110,   110,   110,   110,   131,   110,   110,
     250,   250,   252,   241,   131,   197,   198,   131,   176,   244,
     131,   131,   131,   131,   110,   131,   131,   131,   241,   131,
     131,   241,   241,   131,   131,   244,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,    60,   183,   184,   185,   186,
     187,   190,   191,   194,   195,   196,   199,   201,   202,   203,
     205,   206,   207,   210,   216,   498,   499,   241,    60,   183,
     184,   185,   186,   187,   190,   191,   194,   195,   196,   199,
     201,   202,   203,   205,   206,   207,   210,   216,   494,   495,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,    13,    14,    15,   251,   252,
     241,   241,   241,   241,   241,   241,   241,   244,   250,   176,
     244,   131,   131,   241,   131,   176,   244,   131,   110,   131,
     131,   131,   241,   131,   244,   131,   241,   244,   131,   131,
     110,   345,   346,   241,   241,     1,   100,   166,   239,   292,
     293,   294,   295,   296,   241,   241,   131,   176,   244,   131,
     131,   131,   244,   131,   241,   131,   131,   131,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   245,   241,   245,   241,   241,
     241,   241,   241,   131,   244,   131,   241,   131,   244,   241,
     241,   249,   249,   249,   249,   249,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,    10,    12,   208,   221,   407,   408,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   136,   438,   439,   241,   245,   241,   245,   251,
     251,   251,    11,   178,   518,   519,   241,   241,    11,   178,
     512,   513,   241,   241,   241,   241,    19,    43,    52,    58,
      74,   101,   109,   152,   170,   359,   360,   241,   241,   241,
     241,   241,   241,   136,   418,   419,   241,    60,   204,   208,
     339,   340,   241,   241,   181,   245,   344,   241,   244,   297,
     244,   242,   293,   241,   241,     5,    31,    50,    56,    73,
      98,   105,   119,   137,   139,   140,   192,   202,   211,   215,
     217,   226,   236,   316,   317,   241,   241,   241,    60,   183,
     184,   185,   186,   187,   190,   191,   194,   195,   196,   199,
     201,   202,   203,   205,   206,   207,   210,   216,   312,   313,
     241,   241,   241,   241,   264,   266,   241,    73,   151,   182,
     192,   199,   211,   213,   214,   226,   236,   383,   384,   241,
     241,    73,   151,   182,   192,   199,   211,   213,   214,   226,
     236,   392,   393,   241,   245,   241,   245,   499,   495,   241,
     245,   241,   245,   241,   245,   241,   245,   241,   245,   110,
     346,   241,   131,   244,   212,   252,   241,   241,   245,   241,
     245,   241,   245,   241,   245,   408,   439,   519,   513,   360,
     419,   340,   241,    50,    71,    73,   115,   191,   192,   227,
     298,   299,   241,   241,   317,   313,   384,   393,   241,   245,
     299
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 27:

/* Line 1810 of yacc.c  */
#line 384 "conf_parser.y"
    { (yyval.number) = 0; }
    break;

  case 29:

/* Line 1810 of yacc.c  */
#line 386 "conf_parser.y"
    {
			(yyval.number) = (yyvsp[(1) - (2)].number) + (yyvsp[(2) - (2)].number);
		}
    break;

  case 30:

/* Line 1810 of yacc.c  */
#line 390 "conf_parser.y"
    {
			(yyval.number) = (yyvsp[(1) - (3)].number) + (yyvsp[(3) - (3)].number);
		}
    break;

  case 31:

/* Line 1810 of yacc.c  */
#line 394 "conf_parser.y"
    {
			(yyval.number) = (yyvsp[(1) - (3)].number) * 60 + (yyvsp[(3) - (3)].number);
		}
    break;

  case 32:

/* Line 1810 of yacc.c  */
#line 398 "conf_parser.y"
    {
			(yyval.number) = (yyvsp[(1) - (3)].number) * 60 * 60 + (yyvsp[(3) - (3)].number);
		}
    break;

  case 33:

/* Line 1810 of yacc.c  */
#line 402 "conf_parser.y"
    {
			(yyval.number) = (yyvsp[(1) - (3)].number) * 60 * 60 * 24 + (yyvsp[(3) - (3)].number);
		}
    break;

  case 34:

/* Line 1810 of yacc.c  */
#line 406 "conf_parser.y"
    {
			(yyval.number) = (yyvsp[(1) - (3)].number) * 60 * 60 * 24 * 7 + (yyvsp[(3) - (3)].number);
		}
    break;

  case 35:

/* Line 1810 of yacc.c  */
#line 411 "conf_parser.y"
    { (yyval.number) = 0; }
    break;

  case 37:

/* Line 1810 of yacc.c  */
#line 412 "conf_parser.y"
    { (yyval.number) = (yyvsp[(1) - (2)].number) + (yyvsp[(2) - (2)].number); }
    break;

  case 38:

/* Line 1810 of yacc.c  */
#line 413 "conf_parser.y"
    { (yyval.number) = (yyvsp[(1) - (3)].number) + (yyvsp[(3) - (3)].number); }
    break;

  case 39:

/* Line 1810 of yacc.c  */
#line 414 "conf_parser.y"
    { (yyval.number) = (yyvsp[(1) - (3)].number) * 1024 + (yyvsp[(3) - (3)].number); }
    break;

  case 40:

/* Line 1810 of yacc.c  */
#line 415 "conf_parser.y"
    { (yyval.number) = (yyvsp[(1) - (3)].number) * 1024 * 1024 + (yyvsp[(3) - (3)].number); }
    break;

  case 47:

/* Line 1810 of yacc.c  */
#line 429 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    add_conf_module(libio_basename(yylval.string));
}
    break;

  case 48:

/* Line 1810 of yacc.c  */
#line 435 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    mod_add_path(yylval.string);
}
    break;

  case 72:

/* Line 1810 of yacc.c  */
#line 460 "conf_parser.y"
    {
#ifdef HAVE_LIBCRYPTO
  if (conf_parser_ctx.pass == 2 && ServerInfo.client_ctx)
    SSL_CTX_clear_options(ServerInfo.client_ctx, SSL_OP_NO_SSLv3);
#endif
}
    break;

  case 73:

/* Line 1810 of yacc.c  */
#line 466 "conf_parser.y"
    {
#ifdef HAVE_LIBCRYPTO
  if (conf_parser_ctx.pass == 2 && ServerInfo.client_ctx)
    SSL_CTX_clear_options(ServerInfo.client_ctx, SSL_OP_NO_TLSv1);
#endif
}
    break;

  case 76:

/* Line 1810 of yacc.c  */
#line 475 "conf_parser.y"
    {
#ifdef HAVE_LIBCRYPTO
  if (conf_parser_ctx.pass == 2 && ServerInfo.server_ctx)
    SSL_CTX_clear_options(ServerInfo.server_ctx, SSL_OP_NO_SSLv3);
#endif
}
    break;

  case 77:

/* Line 1810 of yacc.c  */
#line 481 "conf_parser.y"
    {
#ifdef HAVE_LIBCRYPTO
  if (conf_parser_ctx.pass == 2 && ServerInfo.server_ctx)
    SSL_CTX_clear_options(ServerInfo.server_ctx, SSL_OP_NO_TLSv1);
#endif
}
    break;

  case 78:

/* Line 1810 of yacc.c  */
#line 489 "conf_parser.y"
    {
#ifdef HAVE_LIBCRYPTO
  if (conf_parser_ctx.pass == 2 && ServerInfo.server_ctx) 
  {
    if (!ServerInfo.rsa_private_key_file)
    {
      yyerror("No rsa_private_key_file specified, SSL disabled");
      break;
    }

    if (SSL_CTX_use_certificate_file(ServerInfo.server_ctx, yylval.string,
                                     SSL_FILETYPE_PEM) <= 0 ||
        SSL_CTX_use_certificate_file(ServerInfo.client_ctx, yylval.string,
                                     SSL_FILETYPE_PEM) <= 0)
    {
      yyerror(ERR_lib_error_string(ERR_get_error()));
      break;
    }

    if (SSL_CTX_use_PrivateKey_file(ServerInfo.server_ctx, ServerInfo.rsa_private_key_file,
                                    SSL_FILETYPE_PEM) <= 0 ||
        SSL_CTX_use_PrivateKey_file(ServerInfo.client_ctx, ServerInfo.rsa_private_key_file,
                                    SSL_FILETYPE_PEM) <= 0)
    {
      yyerror(ERR_lib_error_string(ERR_get_error()));
      break;
    }

    if (!SSL_CTX_check_private_key(ServerInfo.server_ctx) ||
        !SSL_CTX_check_private_key(ServerInfo.client_ctx))
    {
      yyerror(ERR_lib_error_string(ERR_get_error()));
      break;
    }
  }
#endif
}
    break;

  case 79:

/* Line 1810 of yacc.c  */
#line 528 "conf_parser.y"
    {
#ifdef HAVE_LIBCRYPTO
  if (conf_parser_ctx.pass == 1)
  {
    BIO *file;

    if (ServerInfo.rsa_private_key)
    {
      RSA_free(ServerInfo.rsa_private_key);
      ServerInfo.rsa_private_key = NULL;
    }

    if (ServerInfo.rsa_private_key_file)
    {
      MyFree(ServerInfo.rsa_private_key_file);
      ServerInfo.rsa_private_key_file = NULL;
    }

    DupString(ServerInfo.rsa_private_key_file, yylval.string);

    if ((file = BIO_new_file(yylval.string, "r")) == NULL)
    {
      yyerror("File open failed, ignoring");
      break;
    }

    ServerInfo.rsa_private_key = PEM_read_bio_RSAPrivateKey(file, NULL, 0, NULL);

    BIO_set_close(file, BIO_CLOSE);
    BIO_free(file);

    if (ServerInfo.rsa_private_key == NULL)
    {
      yyerror("Couldn't extract key, ignoring");
      break;
    }

    if (!RSA_check_key(ServerInfo.rsa_private_key))
    {
      RSA_free(ServerInfo.rsa_private_key);
      ServerInfo.rsa_private_key = NULL;

      yyerror("Invalid key, ignoring");
      break;
    }

    /* require 2048 bit (256 byte) key */
    if (RSA_size(ServerInfo.rsa_private_key) != 256)
    {
      RSA_free(ServerInfo.rsa_private_key);
      ServerInfo.rsa_private_key = NULL;

      yyerror("Not a 2048 bit key, ignoring");
    }
  }
#endif
}
    break;

  case 80:

/* Line 1810 of yacc.c  */
#line 587 "conf_parser.y"
    {
/* TBD - XXX: error reporting */
#ifdef HAVE_LIBCRYPTO
  if (conf_parser_ctx.pass == 2 && ServerInfo.server_ctx)
  {
    BIO *file = BIO_new_file(yylval.string, "r");

    if (file)
    {
      DH *dh = PEM_read_bio_DHparams(file, NULL, NULL, NULL);

      BIO_free(file);

      if (dh)
      {
        if (DH_size(dh) < 128)
          ilog(LOG_TYPE_IRCD, "Ignoring serverinfo::ssl_dh_param_file -- need at least a 1024 bit DH prime size");
        else
          SSL_CTX_set_tmp_dh(ServerInfo.server_ctx, dh);

        DH_free(dh);
      }
    }
  }
#endif
}
    break;

  case 81:

/* Line 1810 of yacc.c  */
#line 615 "conf_parser.y"
    {
#ifdef HAVE_LIBCRYPTO
  if (conf_parser_ctx.pass == 2 && ServerInfo.server_ctx)
    SSL_CTX_set_cipher_list(ServerInfo.server_ctx, yylval.string);
#endif
}
    break;

  case 82:

/* Line 1810 of yacc.c  */
#line 623 "conf_parser.y"
    {
  /* this isn't rehashable */
  if (conf_parser_ctx.pass == 2 && !ServerInfo.name)
  {
    if (valid_servname(yylval.string))
      DupString(ServerInfo.name, yylval.string);
    else
    {
      ilog(LOG_TYPE_IRCD, "Ignoring serverinfo::name -- invalid name. Aborting.");
      exit(0);
    }
  }
}
    break;

  case 83:

/* Line 1810 of yacc.c  */
#line 638 "conf_parser.y"
    {
  /* this isn't rehashable */
  if (conf_parser_ctx.pass == 2 && !ServerInfo.sid)
  {
    if (valid_sid(yylval.string))
      DupString(ServerInfo.sid, yylval.string);
    else
    {
      ilog(LOG_TYPE_IRCD, "Ignoring serverinfo::sid -- invalid SID. Aborting.");
      exit(0);
    }
  }
}
    break;

  case 84:

/* Line 1810 of yacc.c  */
#line 653 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(ServerInfo.description);
    DupString(ServerInfo.description,yylval.string);
  }
}
    break;

  case 85:

/* Line 1810 of yacc.c  */
#line 662 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    char *p;

    if ((p = strchr(yylval.string, ' ')) != NULL)
      p = '\0';

    MyFree(ServerInfo.network_name);
    DupString(ServerInfo.network_name, yylval.string);
  }
}
    break;

  case 86:

/* Line 1810 of yacc.c  */
#line 676 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(ServerInfo.network_desc);
    DupString(ServerInfo.network_desc, yylval.string);
  }
}
    break;

  case 87:

/* Line 1810 of yacc.c  */
#line 685 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2 && *yylval.string != '*')
  {
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE | AI_NUMERICHOST;

    if (getaddrinfo(yylval.string, NULL, &hints, &res))
      ilog(LOG_TYPE_IRCD, "Invalid netmask for server vhost(%s)", yylval.string);
    else
    {
      assert(res != NULL);

      memcpy(&ServerInfo.ip, res->ai_addr, res->ai_addrlen);
      ServerInfo.ip.ss.ss_family = res->ai_family;
      ServerInfo.ip.ss_len = res->ai_addrlen;
      freeaddrinfo(res);

      ServerInfo.specific_ipv4_vhost = 1;
    }
  }
}
    break;

  case 88:

/* Line 1810 of yacc.c  */
#line 713 "conf_parser.y"
    {
#ifdef IPV6
  if (conf_parser_ctx.pass == 2 && *yylval.string != '*')
  {
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE | AI_NUMERICHOST;

    if (getaddrinfo(yylval.string, NULL, &hints, &res))
      ilog(LOG_TYPE_IRCD, "Invalid netmask for server vhost6(%s)", yylval.string);
    else
    {
      assert(res != NULL);

      memcpy(&ServerInfo.ip6, res->ai_addr, res->ai_addrlen);
      ServerInfo.ip6.ss.ss_family = res->ai_family;
      ServerInfo.ip6.ss_len = res->ai_addrlen;
      freeaddrinfo(res);

      ServerInfo.specific_ipv6_vhost = 1;
    }
  }
#endif
}
    break;

  case 89:

/* Line 1810 of yacc.c  */
#line 743 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    recalc_fdlimit(NULL);

    if ((yyvsp[(3) - (4)].number) < MAXCLIENTS_MIN)
    {
      char buf[IRCD_BUFSIZE];
      ircsprintf(buf, "MAXCLIENTS too low, setting to %d", MAXCLIENTS_MIN);
      yyerror(buf);
    }
    else if ((yyvsp[(3) - (4)].number) > MAXCLIENTS_MAX)
    {
      char buf[IRCD_BUFSIZE];
      ircsprintf(buf, "MAXCLIENTS too high, setting to %d", MAXCLIENTS_MAX);
      yyerror(buf);
    }
    else
      ServerInfo.max_clients = (yyvsp[(3) - (4)].number);
  }
}
    break;

  case 90:

/* Line 1810 of yacc.c  */
#line 766 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ServerInfo.hub = yylval.number;
}
    break;

  case 98:

/* Line 1810 of yacc.c  */
#line 781 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(AdminInfo.name);
    DupString(AdminInfo.name, yylval.string);
  }
}
    break;

  case 99:

/* Line 1810 of yacc.c  */
#line 790 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(AdminInfo.email);
    DupString(AdminInfo.email, yylval.string);
  }
}
    break;

  case 100:

/* Line 1810 of yacc.c  */
#line 799 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(AdminInfo.description);
    DupString(AdminInfo.description, yylval.string);
  }
}
    break;

  case 107:

/* Line 1810 of yacc.c  */
#line 817 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ConfigLoggingEntry.use_logging = yylval.number;
}
    break;

  case 108:

/* Line 1810 of yacc.c  */
#line 823 "conf_parser.y"
    {
  lfile[0] = '\0';
  ltype = 0;
  lsize = 0;
}
    break;

  case 109:

/* Line 1810 of yacc.c  */
#line 828 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2 && ltype > 0)
    log_add_file(ltype, lsize, lfile);
}
    break;

  case 116:

/* Line 1810 of yacc.c  */
#line 840 "conf_parser.y"
    {
  strlcpy(lfile, yylval.string, sizeof(lfile));
}
    break;

  case 117:

/* Line 1810 of yacc.c  */
#line 845 "conf_parser.y"
    {
  lsize = (yyvsp[(3) - (4)].number);
}
    break;

  case 118:

/* Line 1810 of yacc.c  */
#line 848 "conf_parser.y"
    {
  lsize = 0;
}
    break;

  case 119:

/* Line 1810 of yacc.c  */
#line 853 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ltype = 0;
}
    break;

  case 123:

/* Line 1810 of yacc.c  */
#line 860 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ltype = LOG_TYPE_USER;
}
    break;

  case 124:

/* Line 1810 of yacc.c  */
#line 864 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ltype = LOG_TYPE_OPER;
}
    break;

  case 125:

/* Line 1810 of yacc.c  */
#line 868 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ltype = LOG_TYPE_GLINE;
}
    break;

  case 126:

/* Line 1810 of yacc.c  */
#line 872 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ltype = LOG_TYPE_DLINE;
}
    break;

  case 127:

/* Line 1810 of yacc.c  */
#line 876 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ltype = LOG_TYPE_KLINE;
}
    break;

  case 128:

/* Line 1810 of yacc.c  */
#line 880 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ltype = LOG_TYPE_KILL;
}
    break;

  case 129:

/* Line 1810 of yacc.c  */
#line 884 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ltype = LOG_TYPE_DEBUG;
}
    break;

  case 130:

/* Line 1810 of yacc.c  */
#line 894 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    yy_conf = make_conf_item(OPER_TYPE);
    yy_aconf = map_to_conf(yy_conf);
    SetConfEncrypted(yy_aconf); /* Yes, the default is encrypted */
  }
  else
  {
    MyFree(class_name);
    class_name = NULL;
  }
}
    break;

  case 131:

/* Line 1810 of yacc.c  */
#line 907 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    struct CollectItem *yy_tmp;
    dlink_node *ptr;
    dlink_node *next_ptr;

    conf_add_class_to_conf(yy_conf, class_name);

    /* Now, make sure there is a copy of the "base" given oper
     * block in each of the collected copies
     */

    DLINK_FOREACH_SAFE(ptr, next_ptr, col_conf_list.head)
    {
      struct AccessItem *new_aconf;
      struct ConfItem *new_conf;
      yy_tmp = ptr->data;

      new_conf = make_conf_item(OPER_TYPE);
      new_aconf = (struct AccessItem *)map_to_conf(new_conf);

      new_aconf->flags = yy_aconf->flags;

      if (yy_conf->name != NULL)
        DupString(new_conf->name, yy_conf->name);
      if (yy_tmp->user != NULL)
	DupString(new_aconf->user, yy_tmp->user);
      else
	DupString(new_aconf->user, "*");
      if (yy_tmp->host != NULL)
	DupString(new_aconf->host, yy_tmp->host);
      else
	DupString(new_aconf->host, "*");

      new_aconf->type = parse_netmask(new_aconf->host, &new_aconf->addr,
                                     &new_aconf->bits);

      conf_add_class_to_conf(new_conf, class_name);
      if (yy_aconf->passwd != NULL)
        DupString(new_aconf->passwd, yy_aconf->passwd);

      new_aconf->port = yy_aconf->port;
#ifdef HAVE_LIBCRYPTO
      if (yy_aconf->rsa_public_key_file != NULL)
      {
        BIO *file;

        DupString(new_aconf->rsa_public_key_file,
		  yy_aconf->rsa_public_key_file);

        file = BIO_new_file(yy_aconf->rsa_public_key_file, "r");
        new_aconf->rsa_public_key = (RSA *)PEM_read_bio_RSA_PUBKEY(file, 
							   NULL, 0, NULL);
        BIO_set_close(file, BIO_CLOSE);
        BIO_free(file);
      }
#endif

#ifdef HAVE_LIBCRYPTO
      if (yy_tmp->name && (yy_tmp->passwd || yy_aconf->rsa_public_key)
	  && yy_tmp->host)
#else
      if (yy_tmp->name && yy_tmp->passwd && yy_tmp->host)
#endif
      {
        conf_add_class_to_conf(new_conf, class_name);
	if (yy_tmp->name != NULL)
	  DupString(new_conf->name, yy_tmp->name);
      }

      dlinkDelete(&yy_tmp->node, &col_conf_list);
      free_collect_item(yy_tmp);
    }

    yy_conf = NULL;
    yy_aconf = NULL;


    MyFree(class_name);
    class_name = NULL;
  }
}
    break;

  case 143:

/* Line 1810 of yacc.c  */
#line 997 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(yy_conf->name);
    DupString(yy_conf->name, yylval.string);
  }
}
    break;

  case 144:

/* Line 1810 of yacc.c  */
#line 1006 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    struct split_nuh_item nuh;

    nuh.nuhmask  = yylval.string;
    nuh.nickptr  = NULL;
    nuh.userptr  = userbuf;
    nuh.hostptr  = hostbuf;

    nuh.nicksize = 0;
    nuh.usersize = sizeof(userbuf);
    nuh.hostsize = sizeof(hostbuf);

    split_nuh(&nuh);

    if (yy_aconf->user == NULL)
    {
      DupString(yy_aconf->user, userbuf);
      DupString(yy_aconf->host, hostbuf);

      yy_aconf->type = parse_netmask(yy_aconf->host, &yy_aconf->addr,
                                    &yy_aconf->bits);
    }
    else
    {
      struct CollectItem *yy_tmp = MyMalloc(sizeof(struct CollectItem));

      DupString(yy_tmp->user, userbuf);
      DupString(yy_tmp->host, hostbuf);

      dlinkAdd(yy_tmp, &yy_tmp->node, &col_conf_list);
    }
  }
}
    break;

  case 145:

/* Line 1810 of yacc.c  */
#line 1043 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (yy_aconf->passwd != NULL)
      memset(yy_aconf->passwd, 0, strlen(yy_aconf->passwd));

    MyFree(yy_aconf->passwd);
    DupString(yy_aconf->passwd, yylval.string);
  }
}
    break;

  case 146:

/* Line 1810 of yacc.c  */
#line 1055 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (yylval.number)
      SetConfEncrypted(yy_aconf);
    else
      ClearConfEncrypted(yy_aconf);
  }
}
    break;

  case 147:

/* Line 1810 of yacc.c  */
#line 1066 "conf_parser.y"
    {
#ifdef HAVE_LIBCRYPTO
  if (conf_parser_ctx.pass == 2)
  {
    BIO *file;

    if (yy_aconf->rsa_public_key != NULL)
    {
      RSA_free(yy_aconf->rsa_public_key);
      yy_aconf->rsa_public_key = NULL;
    }

    if (yy_aconf->rsa_public_key_file != NULL)
    {
      MyFree(yy_aconf->rsa_public_key_file);
      yy_aconf->rsa_public_key_file = NULL;
    }

    DupString(yy_aconf->rsa_public_key_file, yylval.string);
    file = BIO_new_file(yylval.string, "r");

    if (file == NULL)
    {
      yyerror("Ignoring rsa_public_key_file -- file doesn't exist");
      break;
    }

    yy_aconf->rsa_public_key = (RSA *)PEM_read_bio_RSA_PUBKEY(file, NULL, 0, NULL);

    if (yy_aconf->rsa_public_key == NULL)
    {
      yyerror("Ignoring rsa_public_key_file -- Key invalid; check key syntax.");
      break;
    }

    BIO_set_close(file, BIO_CLOSE);
    BIO_free(file);
  }
#endif /* HAVE_LIBCRYPTO */
}
    break;

  case 148:

/* Line 1810 of yacc.c  */
#line 1108 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(class_name);
    DupString(class_name, yylval.string);
  }
}
    break;

  case 149:

/* Line 1810 of yacc.c  */
#line 1117 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes = 0;
}
    break;

  case 153:

/* Line 1810 of yacc.c  */
#line 1124 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_BOTS;
}
    break;

  case 154:

/* Line 1810 of yacc.c  */
#line 1128 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_CCONN;
}
    break;

  case 155:

/* Line 1810 of yacc.c  */
#line 1132 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_CCONN_FULL;
}
    break;

  case 156:

/* Line 1810 of yacc.c  */
#line 1136 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_DEAF;
}
    break;

  case 157:

/* Line 1810 of yacc.c  */
#line 1140 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_DEBUG;
}
    break;

  case 158:

/* Line 1810 of yacc.c  */
#line 1144 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_FULL;
}
    break;

  case 159:

/* Line 1810 of yacc.c  */
#line 1148 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_HIDDEN;
}
    break;

  case 160:

/* Line 1810 of yacc.c  */
#line 1152 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_SKILL;
}
    break;

  case 161:

/* Line 1810 of yacc.c  */
#line 1156 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_NCHANGE;
}
    break;

  case 162:

/* Line 1810 of yacc.c  */
#line 1160 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_REJ;
}
    break;

  case 163:

/* Line 1810 of yacc.c  */
#line 1164 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_UNAUTH;
}
    break;

  case 164:

/* Line 1810 of yacc.c  */
#line 1168 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_SPY;
}
    break;

  case 165:

/* Line 1810 of yacc.c  */
#line 1172 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_EXTERNAL;
}
    break;

  case 166:

/* Line 1810 of yacc.c  */
#line 1176 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_OPERWALL;
}
    break;

  case 167:

/* Line 1810 of yacc.c  */
#line 1180 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_SERVNOTICE;
}
    break;

  case 168:

/* Line 1810 of yacc.c  */
#line 1184 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_INVISIBLE;
}
    break;

  case 169:

/* Line 1810 of yacc.c  */
#line 1188 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_WALLOP;
}
    break;

  case 170:

/* Line 1810 of yacc.c  */
#line 1192 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_SOFTCALLERID;
}
    break;

  case 171:

/* Line 1810 of yacc.c  */
#line 1196 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_CALLERID;
}
    break;

  case 172:

/* Line 1810 of yacc.c  */
#line 1200 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->modes |= UMODE_LOCOPS;
}
    break;

  case 173:

/* Line 1810 of yacc.c  */
#line 1206 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port = 0;
}
    break;

  case 177:

/* Line 1810 of yacc.c  */
#line 1213 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_GLOBAL_KILL;
}
    break;

  case 178:

/* Line 1810 of yacc.c  */
#line 1217 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_REMOTE;
}
    break;

  case 179:

/* Line 1810 of yacc.c  */
#line 1221 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_K;
}
    break;

  case 180:

/* Line 1810 of yacc.c  */
#line 1225 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_UNKLINE;
}
    break;

  case 181:

/* Line 1810 of yacc.c  */
#line 1229 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_DLINE;
}
    break;

  case 182:

/* Line 1810 of yacc.c  */
#line 1233 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_UNDLINE;
}
    break;

  case 183:

/* Line 1810 of yacc.c  */
#line 1237 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_X;
}
    break;

  case 184:

/* Line 1810 of yacc.c  */
#line 1241 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_GLINE;
}
    break;

  case 185:

/* Line 1810 of yacc.c  */
#line 1245 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_DIE;
}
    break;

  case 186:

/* Line 1810 of yacc.c  */
#line 1249 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_RESTART;
}
    break;

  case 187:

/* Line 1810 of yacc.c  */
#line 1253 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_REHASH;
}
    break;

  case 188:

/* Line 1810 of yacc.c  */
#line 1257 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_ADMIN;
}
    break;

  case 189:

/* Line 1810 of yacc.c  */
#line 1261 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_N;
}
    break;

  case 190:

/* Line 1810 of yacc.c  */
#line 1265 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_OPERWALL;
}
    break;

  case 191:

/* Line 1810 of yacc.c  */
#line 1269 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_GLOBOPS;
}
    break;

  case 192:

/* Line 1810 of yacc.c  */
#line 1273 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_OPER_SPY;
}
    break;

  case 193:

/* Line 1810 of yacc.c  */
#line 1277 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_REMOTEBAN;
}
    break;

  case 194:

/* Line 1810 of yacc.c  */
#line 1281 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port |= OPER_FLAG_MODULE;
}
    break;

  case 195:

/* Line 1810 of yacc.c  */
#line 1291 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
  {
    yy_conf = make_conf_item(CLASS_TYPE);
    yy_class = map_to_conf(yy_conf);
  }
}
    break;

  case 196:

/* Line 1810 of yacc.c  */
#line 1298 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
  {
    struct ConfItem *cconf = NULL;
    struct ClassItem *class = NULL;

    if (yy_class_name == NULL)
      delete_conf_item(yy_conf);
    else
    {
      cconf = find_exact_name_conf(CLASS_TYPE, NULL, yy_class_name, NULL, NULL);

      if (cconf != NULL)		/* The class existed already */
      {
        int user_count = 0;

        rebuild_cidr_class(cconf, yy_class);

        class = map_to_conf(cconf);

        user_count = class->curr_user_count;
        memcpy(class, yy_class, sizeof(*class));
        class->curr_user_count = user_count;
        class->active = 1;

        delete_conf_item(yy_conf);

        MyFree(cconf->name);            /* Allows case change of class name */
        cconf->name = yy_class_name;
      }
      else	/* Brand new class */
      {
        MyFree(yy_conf->name);          /* just in case it was allocated */
        yy_conf->name = yy_class_name;
        yy_class->active = 1;
      }
    }

    yy_class_name = NULL;
  }
}
    break;

  case 213:

/* Line 1810 of yacc.c  */
#line 1356 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
  {
    MyFree(yy_class_name);
    DupString(yy_class_name, yylval.string);
  }
}
    break;

  case 214:

/* Line 1810 of yacc.c  */
#line 1365 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
    yy_class->ping_freq = (yyvsp[(3) - (4)].number);
}
    break;

  case 215:

/* Line 1810 of yacc.c  */
#line 1371 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
    yy_class->ping_warning = (yyvsp[(3) - (4)].number);
}
    break;

  case 216:

/* Line 1810 of yacc.c  */
#line 1377 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
    yy_class->max_perip = (yyvsp[(3) - (4)].number);
}
    break;

  case 217:

/* Line 1810 of yacc.c  */
#line 1383 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
    yy_class->con_freq = (yyvsp[(3) - (4)].number);
}
    break;

  case 218:

/* Line 1810 of yacc.c  */
#line 1389 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
    yy_class->max_total = (yyvsp[(3) - (4)].number);
}
    break;

  case 219:

/* Line 1810 of yacc.c  */
#line 1395 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
    yy_class->max_global = (yyvsp[(3) - (4)].number);
}
    break;

  case 220:

/* Line 1810 of yacc.c  */
#line 1401 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
    yy_class->max_local = (yyvsp[(3) - (4)].number);
}
    break;

  case 221:

/* Line 1810 of yacc.c  */
#line 1407 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
    yy_class->max_ident = (yyvsp[(3) - (4)].number);
}
    break;

  case 222:

/* Line 1810 of yacc.c  */
#line 1413 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
    yy_class->max_sendq = (yyvsp[(3) - (4)].number);
}
    break;

  case 223:

/* Line 1810 of yacc.c  */
#line 1419 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
    yy_class->cidr_bitlen_ipv4 = (yyvsp[(3) - (4)].number) > 32 ? 32 : (yyvsp[(3) - (4)].number);
}
    break;

  case 224:

/* Line 1810 of yacc.c  */
#line 1425 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
    yy_class->cidr_bitlen_ipv6 = (yyvsp[(3) - (4)].number) > 128 ? 128 : (yyvsp[(3) - (4)].number);
}
    break;

  case 225:

/* Line 1810 of yacc.c  */
#line 1431 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 1)
    yy_class->number_per_cidr = (yyvsp[(3) - (4)].number);
}
    break;

  case 226:

/* Line 1810 of yacc.c  */
#line 1440 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    listener_address = NULL;
    listener_flags = 0;
  }
}
    break;

  case 227:

/* Line 1810 of yacc.c  */
#line 1447 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(listener_address);
    listener_address = NULL;
  }
}
    break;

  case 228:

/* Line 1810 of yacc.c  */
#line 1456 "conf_parser.y"
    {
  listener_flags = 0;
}
    break;

  case 232:

/* Line 1810 of yacc.c  */
#line 1462 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    listener_flags |= LISTENER_SSL;
}
    break;

  case 233:

/* Line 1810 of yacc.c  */
#line 1466 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    listener_flags |= LISTENER_HIDDEN;
}
    break;

  case 234:

/* Line 1810 of yacc.c  */
#line 1470 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    listener_flags |= LISTENER_SERVER;
}
    break;

  case 242:

/* Line 1810 of yacc.c  */
#line 1480 "conf_parser.y"
    { listener_flags = 0; }
    break;

  case 246:

/* Line 1810 of yacc.c  */
#line 1485 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if ((listener_flags & LISTENER_SSL))
#ifdef HAVE_LIBCRYPTO
      if (!ServerInfo.server_ctx)
#endif
      {
        yyerror("SSL not available - port closed");
	break;
      }
    add_listener((yyvsp[(1) - (1)].number), listener_address, listener_flags);
  }
}
    break;

  case 247:

/* Line 1810 of yacc.c  */
#line 1499 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    int i;

    if ((listener_flags & LISTENER_SSL))
#ifdef HAVE_LIBCRYPTO
      if (!ServerInfo.server_ctx)
#endif
      {
        yyerror("SSL not available - port closed");
	break;
      }

    for (i = (yyvsp[(1) - (3)].number); i <= (yyvsp[(3) - (3)].number); ++i)
      add_listener(i, listener_address, listener_flags);
  }
}
    break;

  case 248:

/* Line 1810 of yacc.c  */
#line 1519 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(listener_address);
    DupString(listener_address, yylval.string);
  }
}
    break;

  case 249:

/* Line 1810 of yacc.c  */
#line 1528 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(listener_address);
    DupString(listener_address, yylval.string);
  }
}
    break;

  case 250:

/* Line 1810 of yacc.c  */
#line 1540 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    yy_conf = make_conf_item(CLIENT_TYPE);
    yy_aconf = map_to_conf(yy_conf);
  }
  else
  {
    MyFree(class_name);
    class_name = NULL;
  }
}
    break;

  case 251:

/* Line 1810 of yacc.c  */
#line 1552 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    struct CollectItem *yy_tmp = NULL;
    dlink_node *ptr = NULL, *next_ptr = NULL;

    if (yy_aconf->user && yy_aconf->host)
    {
      conf_add_class_to_conf(yy_conf, class_name);
      add_conf_by_address(CONF_CLIENT, yy_aconf);
    }
    else
      delete_conf_item(yy_conf);

    /* copy over settings from first struct */
    DLINK_FOREACH_SAFE(ptr, next_ptr, col_conf_list.head)
    {
      struct AccessItem *new_aconf;
      struct ConfItem *new_conf;

      new_conf = make_conf_item(CLIENT_TYPE);
      new_aconf = map_to_conf(new_conf);

      yy_tmp = ptr->data;

      assert(yy_tmp->user && yy_tmp->host);

      if (yy_aconf->passwd != NULL)
        DupString(new_aconf->passwd, yy_aconf->passwd);
      if (yy_conf->name != NULL)
        DupString(new_conf->name, yy_conf->name);
      if (yy_aconf->passwd != NULL)
        DupString(new_aconf->passwd, yy_aconf->passwd);

      new_aconf->flags = yy_aconf->flags;
      new_aconf->port  = yy_aconf->port;

      DupString(new_aconf->user, yy_tmp->user);
      collapse(new_aconf->user);

      DupString(new_aconf->host, yy_tmp->host);
      collapse(new_aconf->host);

      conf_add_class_to_conf(new_conf, class_name);
      add_conf_by_address(CONF_CLIENT, new_aconf);
      dlinkDelete(&yy_tmp->node, &col_conf_list);
      free_collect_item(yy_tmp);
    }

    MyFree(class_name);
    class_name = NULL;
    yy_conf = NULL;
    yy_aconf = NULL;
  }
}
    break;

  case 263:

/* Line 1810 of yacc.c  */
#line 1614 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    struct CollectItem *yy_tmp = NULL;
    struct split_nuh_item nuh;

    nuh.nuhmask  = yylval.string;
    nuh.nickptr  = NULL;
    nuh.userptr  = userbuf;
    nuh.hostptr  = hostbuf;

    nuh.nicksize = 0;
    nuh.usersize = sizeof(userbuf);
    nuh.hostsize = sizeof(hostbuf);

    split_nuh(&nuh);

    if (yy_aconf->user == NULL)
    {
      DupString(yy_aconf->user, userbuf);
      DupString(yy_aconf->host, hostbuf);
    }
    else
    {
      yy_tmp = MyMalloc(sizeof(struct CollectItem));

      DupString(yy_tmp->user, userbuf);
      DupString(yy_tmp->host, hostbuf);

      dlinkAdd(yy_tmp, &yy_tmp->node, &col_conf_list);
    }
  }
}
    break;

  case 264:

/* Line 1810 of yacc.c  */
#line 1649 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    /* be paranoid */
    if (yy_aconf->passwd != NULL)
      memset(yy_aconf->passwd, 0, strlen(yy_aconf->passwd));

    MyFree(yy_aconf->passwd);
    DupString(yy_aconf->passwd, yylval.string);
  }
}
    break;

  case 265:

/* Line 1810 of yacc.c  */
#line 1662 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(class_name);
    DupString(class_name, yylval.string);
  }
}
    break;

  case 266:

/* Line 1810 of yacc.c  */
#line 1671 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (yylval.number)
      SetConfEncrypted(yy_aconf);
    else
      ClearConfEncrypted(yy_aconf);
  }
}
    break;

  case 267:

/* Line 1810 of yacc.c  */
#line 1682 "conf_parser.y"
    {
}
    break;

  case 271:

/* Line 1810 of yacc.c  */
#line 1687 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->flags |= CONF_FLAGS_SPOOF_NOTICE;
}
    break;

  case 272:

/* Line 1810 of yacc.c  */
#line 1691 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->flags |= CONF_FLAGS_NOLIMIT;
}
    break;

  case 273:

/* Line 1810 of yacc.c  */
#line 1695 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->flags |= CONF_FLAGS_EXEMPTKLINE;
}
    break;

  case 274:

/* Line 1810 of yacc.c  */
#line 1699 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->flags |= CONF_FLAGS_NEED_IDENTD;
}
    break;

  case 275:

/* Line 1810 of yacc.c  */
#line 1703 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->flags |= CONF_FLAGS_CAN_FLOOD;
}
    break;

  case 276:

/* Line 1810 of yacc.c  */
#line 1707 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->flags |= CONF_FLAGS_NO_TILDE;
}
    break;

  case 277:

/* Line 1810 of yacc.c  */
#line 1711 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->flags |= CONF_FLAGS_EXEMPTGLINE;
}
    break;

  case 278:

/* Line 1810 of yacc.c  */
#line 1715 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->flags |= CONF_FLAGS_EXEMPTRESV;
}
    break;

  case 279:

/* Line 1810 of yacc.c  */
#line 1719 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->flags |= CONF_FLAGS_NEED_PASSWORD;
}
    break;

  case 280:

/* Line 1810 of yacc.c  */
#line 1726 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(yy_conf->name);

    if (strlen(yylval.string) < HOSTLEN)
    {    
      DupString(yy_conf->name, yylval.string);
      yy_aconf->flags |= CONF_FLAGS_SPOOF_IP;
    }
    else
    {
      ilog(LOG_TYPE_IRCD, "Spoofs must be less than %d..ignoring it", HOSTLEN);
      yy_conf->name = NULL;
    }
  }
}
    break;

  case 281:

/* Line 1810 of yacc.c  */
#line 1745 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    yy_aconf->flags |= CONF_FLAGS_REDIR;
    MyFree(yy_conf->name);
    DupString(yy_conf->name, yylval.string);
  }
}
    break;

  case 282:

/* Line 1810 of yacc.c  */
#line 1755 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    yy_aconf->flags |= CONF_FLAGS_REDIR;
    yy_aconf->port = (yyvsp[(3) - (4)].number);
  }
}
    break;

  case 283:

/* Line 1810 of yacc.c  */
#line 1768 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(resv_reason);
    resv_reason = NULL;
  }
}
    break;

  case 284:

/* Line 1810 of yacc.c  */
#line 1775 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(resv_reason);
    resv_reason = NULL;
  }
}
    break;

  case 291:

/* Line 1810 of yacc.c  */
#line 1787 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(resv_reason);
    DupString(resv_reason, yylval.string);
  }
}
    break;

  case 292:

/* Line 1810 of yacc.c  */
#line 1796 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (IsChanPrefix(*yylval.string))
    {
      char def_reason[] = "No reason";

      create_channel_resv(yylval.string, resv_reason != NULL ? resv_reason : def_reason, 1);
    }
  }
  /* ignore it for now.. but we really should make a warning if
   * its an erroneous name --fl_ */
}
    break;

  case 293:

/* Line 1810 of yacc.c  */
#line 1811 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    char def_reason[] = "No reason";

    create_nick_resv(yylval.string, resv_reason != NULL ? resv_reason : def_reason, 1);
  }
}
    break;

  case 299:

/* Line 1810 of yacc.c  */
#line 1829 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (valid_servname(yylval.string))
    {
      yy_conf = make_conf_item(SERVICE_TYPE);
      DupString(yy_conf->name, yylval.string);
    }
  }
}
    break;

  case 300:

/* Line 1810 of yacc.c  */
#line 1844 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    yy_conf = make_conf_item(ULINE_TYPE);
    yy_match_item = map_to_conf(yy_conf);
    yy_match_item->action = SHARED_ALL;
  }
}
    break;

  case 301:

/* Line 1810 of yacc.c  */
#line 1852 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    yy_conf = NULL;
  }
}
    break;

  case 308:

/* Line 1810 of yacc.c  */
#line 1863 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(yy_conf->name);
    DupString(yy_conf->name, yylval.string);
  }
}
    break;

  case 309:

/* Line 1810 of yacc.c  */
#line 1872 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    struct split_nuh_item nuh;

    nuh.nuhmask  = yylval.string;
    nuh.nickptr  = NULL;
    nuh.userptr  = userbuf;
    nuh.hostptr  = hostbuf;

    nuh.nicksize = 0;
    nuh.usersize = sizeof(userbuf);
    nuh.hostsize = sizeof(hostbuf);

    split_nuh(&nuh);

    DupString(yy_match_item->user, userbuf);
    DupString(yy_match_item->host, hostbuf);
  }
}
    break;

  case 310:

/* Line 1810 of yacc.c  */
#line 1894 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_match_item->action = 0;
}
    break;

  case 314:

/* Line 1810 of yacc.c  */
#line 1901 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_match_item->action |= SHARED_KLINE;
}
    break;

  case 315:

/* Line 1810 of yacc.c  */
#line 1905 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_match_item->action |= SHARED_UNKLINE;
}
    break;

  case 316:

/* Line 1810 of yacc.c  */
#line 1909 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_match_item->action |= SHARED_DLINE;
}
    break;

  case 317:

/* Line 1810 of yacc.c  */
#line 1913 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_match_item->action |= SHARED_UNDLINE;
}
    break;

  case 318:

/* Line 1810 of yacc.c  */
#line 1917 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_match_item->action |= SHARED_XLINE;
}
    break;

  case 319:

/* Line 1810 of yacc.c  */
#line 1921 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_match_item->action |= SHARED_UNXLINE;
}
    break;

  case 320:

/* Line 1810 of yacc.c  */
#line 1925 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_match_item->action |= SHARED_RESV;
}
    break;

  case 321:

/* Line 1810 of yacc.c  */
#line 1929 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_match_item->action |= SHARED_UNRESV;
}
    break;

  case 322:

/* Line 1810 of yacc.c  */
#line 1933 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_match_item->action |= SHARED_LOCOPS;
}
    break;

  case 323:

/* Line 1810 of yacc.c  */
#line 1937 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_match_item->action = SHARED_ALL;
}
    break;

  case 324:

/* Line 1810 of yacc.c  */
#line 1946 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    yy_conf = make_conf_item(CLUSTER_TYPE);
    yy_conf->flags = SHARED_ALL;
  }
}
    break;

  case 325:

/* Line 1810 of yacc.c  */
#line 1953 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (yy_conf->name == NULL)
      DupString(yy_conf->name, "*");
    yy_conf = NULL;
  }
}
    break;

  case 331:

/* Line 1810 of yacc.c  */
#line 1966 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    DupString(yy_conf->name, yylval.string);
}
    break;

  case 332:

/* Line 1810 of yacc.c  */
#line 1972 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_conf->flags = 0;
}
    break;

  case 336:

/* Line 1810 of yacc.c  */
#line 1979 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_conf->flags |= SHARED_KLINE;
}
    break;

  case 337:

/* Line 1810 of yacc.c  */
#line 1983 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_conf->flags |= SHARED_UNKLINE;
}
    break;

  case 338:

/* Line 1810 of yacc.c  */
#line 1987 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_conf->flags |= SHARED_DLINE;
}
    break;

  case 339:

/* Line 1810 of yacc.c  */
#line 1991 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_conf->flags |= SHARED_UNDLINE;
}
    break;

  case 340:

/* Line 1810 of yacc.c  */
#line 1995 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_conf->flags |= SHARED_XLINE;
}
    break;

  case 341:

/* Line 1810 of yacc.c  */
#line 1999 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_conf->flags |= SHARED_UNXLINE;
}
    break;

  case 342:

/* Line 1810 of yacc.c  */
#line 2003 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_conf->flags |= SHARED_RESV;
}
    break;

  case 343:

/* Line 1810 of yacc.c  */
#line 2007 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_conf->flags |= SHARED_UNRESV;
}
    break;

  case 344:

/* Line 1810 of yacc.c  */
#line 2011 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_conf->flags |= SHARED_LOCOPS;
}
    break;

  case 345:

/* Line 1810 of yacc.c  */
#line 2015 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_conf->flags = SHARED_ALL;
}
    break;

  case 346:

/* Line 1810 of yacc.c  */
#line 2024 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    yy_conf = make_conf_item(SERVER_TYPE);
    yy_aconf = map_to_conf(yy_conf);

    /* defaults */
    yy_aconf->port = PORTNUM;
  }
  else
  {
    MyFree(class_name);
    class_name = NULL;
  }
}
    break;

  case 347:

/* Line 1810 of yacc.c  */
#line 2039 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (yy_aconf->host && yy_aconf->passwd && yy_aconf->spasswd)
    {
      if (conf_add_server(yy_conf, class_name) == -1)
        delete_conf_item(yy_conf);
    }
    else
    {
      if (yy_conf->name != NULL)
      {
        if (yy_aconf->host == NULL)
          yyerror("Ignoring connect block -- missing host");
        else if (!yy_aconf->passwd || !yy_aconf->spasswd)
          yyerror("Ignoring connect block -- missing password");
      }

      /* XXX
       * This fixes a try_connections() core (caused by invalid class_ptr
       * pointers) reported by metalrock. That's an ugly fix, but there
       * is currently no better way. The entire config subsystem needs an
       * rewrite ASAP. make_conf_item() shouldn't really add things onto
       * a doubly linked list immediately without any sanity checks!  -Michael
       */
      delete_conf_item(yy_conf);
    }

    MyFree(class_name);
    class_name = NULL;
    yy_conf = NULL;
    yy_aconf = NULL;
  }
}
    break;

  case 364:

/* Line 1810 of yacc.c  */
#line 2083 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(yy_conf->name);
    DupString(yy_conf->name, yylval.string);
  }
}
    break;

  case 365:

/* Line 1810 of yacc.c  */
#line 2092 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(yy_aconf->host);
    DupString(yy_aconf->host, yylval.string);
  }
}
    break;

  case 366:

/* Line 1810 of yacc.c  */
#line 2101 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE | AI_NUMERICHOST;

    if (getaddrinfo(yylval.string, NULL, &hints, &res))
      ilog(LOG_TYPE_IRCD, "Invalid netmask for server vhost(%s)", yylval.string);
    else
    {
      assert(res != NULL);

      memcpy(&yy_aconf->bind, res->ai_addr, res->ai_addrlen);
      yy_aconf->bind.ss.ss_family = res->ai_family;
      yy_aconf->bind.ss_len = res->ai_addrlen;
      freeaddrinfo(res);
    }
  }
}
    break;

  case 367:

/* Line 1810 of yacc.c  */
#line 2127 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if ((yyvsp[(3) - (4)].string)[0] == ':')
      yyerror("Server passwords cannot begin with a colon");
    else if (strchr((yyvsp[(3) - (4)].string), ' ') != NULL)
      yyerror("Server passwords cannot contain spaces");
    else {
      if (yy_aconf->spasswd != NULL)
        memset(yy_aconf->spasswd, 0, strlen(yy_aconf->spasswd));

      MyFree(yy_aconf->spasswd);
      DupString(yy_aconf->spasswd, yylval.string);
    }
  }
}
    break;

  case 368:

/* Line 1810 of yacc.c  */
#line 2145 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if ((yyvsp[(3) - (4)].string)[0] == ':')
      yyerror("Server passwords cannot begin with a colon");
    else if (strchr((yyvsp[(3) - (4)].string), ' ') != NULL)
      yyerror("Server passwords cannot contain spaces");
    else {
      if (yy_aconf->passwd != NULL)
        memset(yy_aconf->passwd, 0, strlen(yy_aconf->passwd));

      MyFree(yy_aconf->passwd);
      DupString(yy_aconf->passwd, yylval.string);
    }
  }
}
    break;

  case 369:

/* Line 1810 of yacc.c  */
#line 2163 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->port = (yyvsp[(3) - (4)].number);
}
    break;

  case 370:

/* Line 1810 of yacc.c  */
#line 2169 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->aftype = AF_INET;
}
    break;

  case 371:

/* Line 1810 of yacc.c  */
#line 2173 "conf_parser.y"
    {
#ifdef IPV6
  if (conf_parser_ctx.pass == 2)
    yy_aconf->aftype = AF_INET6;
#endif
}
    break;

  case 372:

/* Line 1810 of yacc.c  */
#line 2181 "conf_parser.y"
    {
}
    break;

  case 376:

/* Line 1810 of yacc.c  */
#line 2186 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    SetConfAllowAutoConn(yy_aconf);
}
    break;

  case 377:

/* Line 1810 of yacc.c  */
#line 2190 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    SetConfAwayBurst(yy_aconf);
}
    break;

  case 378:

/* Line 1810 of yacc.c  */
#line 2194 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    SetConfTopicBurst(yy_aconf);
}
    break;

  case 379:

/* Line 1810 of yacc.c  */
#line 2198 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    SetConfSSL(yy_aconf);
}
    break;

  case 380:

/* Line 1810 of yacc.c  */
#line 2204 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (yylval.number)
      yy_aconf->flags |= CONF_FLAGS_ENCRYPTED;
    else
      yy_aconf->flags &= ~CONF_FLAGS_ENCRYPTED;
  }
}
    break;

  case 381:

/* Line 1810 of yacc.c  */
#line 2215 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    char *mask;

    DupString(mask, yylval.string);
    dlinkAdd(mask, make_dlink_node(), &yy_aconf->hub_list);
  }
}
    break;

  case 382:

/* Line 1810 of yacc.c  */
#line 2226 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    char *mask;

    DupString(mask, yylval.string);
    dlinkAdd(mask, make_dlink_node(), &yy_aconf->leaf_list);
  }
}
    break;

  case 383:

/* Line 1810 of yacc.c  */
#line 2237 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(class_name);
    DupString(class_name, yylval.string);
  }
}
    break;

  case 384:

/* Line 1810 of yacc.c  */
#line 2246 "conf_parser.y"
    {
#ifdef HAVE_LIBCRYPTO
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(yy_aconf->cipher_list);
    DupString(yy_aconf->cipher_list, yylval.string);
  }
#else
  if (conf_parser_ctx.pass == 2)
    yyerror("Ignoring connect::ciphers -- no OpenSSL support");
#endif
}
    break;

  case 385:

/* Line 1810 of yacc.c  */
#line 2264 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    userbuf[0] = hostbuf[0] = reasonbuf[0] = '\0';
    regex_ban = 0;
  }
}
    break;

  case 386:

/* Line 1810 of yacc.c  */
#line 2271 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (userbuf[0] && hostbuf[0])
    {
      if (regex_ban)
      {
#ifdef HAVE_LIBPCRE
        void *exp_user = NULL;
        void *exp_host = NULL;
        const char *errptr = NULL;

        if (!(exp_user = ircd_pcre_compile(userbuf, &errptr)) ||
            !(exp_host = ircd_pcre_compile(hostbuf, &errptr)))
        {
          ilog(LOG_TYPE_IRCD, "Failed to add regular expression based K-Line: %s",
               errptr);
          break;
        }

        yy_aconf = map_to_conf(make_conf_item(RKLINE_TYPE));
        yy_aconf->regexuser = exp_user;
        yy_aconf->regexhost = exp_host;

        DupString(yy_aconf->user, userbuf);
        DupString(yy_aconf->host, hostbuf);

        if (reasonbuf[0])
          DupString(yy_aconf->reason, reasonbuf);
        else
          DupString(yy_aconf->reason, "No reason");
#else
        ilog(LOG_TYPE_IRCD, "Failed to add regular expression based K-Line: no PCRE support");
        break;
#endif
      }
      else
      {
        find_and_delete_temporary(userbuf, hostbuf, CONF_KLINE);

        yy_aconf = map_to_conf(make_conf_item(KLINE_TYPE));

        DupString(yy_aconf->user, userbuf);
        DupString(yy_aconf->host, hostbuf);

        if (reasonbuf[0])
          DupString(yy_aconf->reason, reasonbuf);
        else
          DupString(yy_aconf->reason, "No reason");
        add_conf_by_address(CONF_KLINE, yy_aconf);
      }
    }

    yy_aconf = NULL;
  }
}
    break;

  case 387:

/* Line 1810 of yacc.c  */
#line 2329 "conf_parser.y"
    {
}
    break;

  case 391:

/* Line 1810 of yacc.c  */
#line 2334 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    regex_ban = 1;
}
    break;

  case 398:

/* Line 1810 of yacc.c  */
#line 2343 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    struct split_nuh_item nuh;

    nuh.nuhmask  = yylval.string;
    nuh.nickptr  = NULL;
    nuh.userptr  = userbuf;
    nuh.hostptr  = hostbuf;

    nuh.nicksize = 0;
    nuh.usersize = sizeof(userbuf);
    nuh.hostsize = sizeof(hostbuf);

    split_nuh(&nuh);
  }
}
    break;

  case 399:

/* Line 1810 of yacc.c  */
#line 2362 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    strlcpy(reasonbuf, yylval.string, sizeof(reasonbuf));
}
    break;

  case 400:

/* Line 1810 of yacc.c  */
#line 2371 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    hostbuf[0] = reasonbuf[0] = '\0';
}
    break;

  case 401:

/* Line 1810 of yacc.c  */
#line 2375 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (hostbuf[0] && parse_netmask(hostbuf, NULL, NULL) != HM_HOST)
    {
      find_and_delete_temporary(NULL, hostbuf, CONF_DLINE);

      yy_aconf = map_to_conf(make_conf_item(DLINE_TYPE));
      DupString(yy_aconf->host, hostbuf);

      if (reasonbuf[0])
        DupString(yy_aconf->reason, reasonbuf);
      else
        DupString(yy_aconf->reason, "No reason");
      add_conf_by_address(CONF_DLINE, yy_aconf);
      yy_aconf = NULL;
    }
  }
}
    break;

  case 407:

/* Line 1810 of yacc.c  */
#line 2399 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    strlcpy(hostbuf, yylval.string, sizeof(hostbuf));
}
    break;

  case 408:

/* Line 1810 of yacc.c  */
#line 2405 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    strlcpy(reasonbuf, yylval.string, sizeof(reasonbuf));
}
    break;

  case 414:

/* Line 1810 of yacc.c  */
#line 2419 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (yylval.string[0] && parse_netmask(yylval.string, NULL, NULL) != HM_HOST)
    {
      yy_aconf = map_to_conf(make_conf_item(EXEMPTDLINE_TYPE));
      DupString(yy_aconf->host, yylval.string);

      add_conf_by_address(CONF_EXEMPTDLINE, yy_aconf);
      yy_aconf = NULL;
    }
  }
}
    break;

  case 415:

/* Line 1810 of yacc.c  */
#line 2437 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    regex_ban = 0;
    reasonbuf[0] = gecos_name[0] = '\0';
  }
}
    break;

  case 416:

/* Line 1810 of yacc.c  */
#line 2444 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (gecos_name[0])
    {
      if (regex_ban)
      {
#ifdef HAVE_LIBPCRE
        void *exp_p = NULL;
        const char *errptr = NULL;

        if (!(exp_p = ircd_pcre_compile(gecos_name, &errptr)))
        {
          ilog(LOG_TYPE_IRCD, "Failed to add regular expression based X-Line: %s",
               errptr);
          break;
        }

        yy_conf = make_conf_item(RXLINE_TYPE);
        yy_conf->regexpname = exp_p;
#else
        ilog(LOG_TYPE_IRCD, "Failed to add regular expression based X-Line: no PCRE support");
        break;
#endif
      }
      else
        yy_conf = make_conf_item(XLINE_TYPE);

      yy_match_item = map_to_conf(yy_conf);
      DupString(yy_conf->name, gecos_name);

      if (reasonbuf[0])
        DupString(yy_match_item->reason, reasonbuf);
      else
        DupString(yy_match_item->reason, "No reason");
    }
  }
}
    break;

  case 417:

/* Line 1810 of yacc.c  */
#line 2484 "conf_parser.y"
    {
}
    break;

  case 421:

/* Line 1810 of yacc.c  */
#line 2489 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    regex_ban = 1;
}
    break;

  case 428:

/* Line 1810 of yacc.c  */
#line 2498 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    strlcpy(gecos_name, yylval.string, sizeof(gecos_name));
}
    break;

  case 429:

/* Line 1810 of yacc.c  */
#line 2504 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    strlcpy(reasonbuf, yylval.string, sizeof(reasonbuf));
}
    break;

  case 485:

/* Line 1810 of yacc.c  */
#line 2548 "conf_parser.y"
    {
  ConfigFileEntry.max_watch = (yyvsp[(3) - (4)].number);
}
    break;

  case 486:

/* Line 1810 of yacc.c  */
#line 2553 "conf_parser.y"
    {
  ConfigFileEntry.gline_min_cidr = (yyvsp[(3) - (4)].number);
}
    break;

  case 487:

/* Line 1810 of yacc.c  */
#line 2558 "conf_parser.y"
    {
  ConfigFileEntry.gline_min_cidr6 = (yyvsp[(3) - (4)].number);
}
    break;

  case 488:

/* Line 1810 of yacc.c  */
#line 2563 "conf_parser.y"
    {
  ConfigFileEntry.use_whois_actually = yylval.number;
}
    break;

  case 489:

/* Line 1810 of yacc.c  */
#line 2568 "conf_parser.y"
    {
  GlobalSetOptions.rejecttime = yylval.number;
}
    break;

  case 490:

/* Line 1810 of yacc.c  */
#line 2573 "conf_parser.y"
    {
  ConfigFileEntry.tkline_expire_notices = yylval.number;
}
    break;

  case 491:

/* Line 1810 of yacc.c  */
#line 2578 "conf_parser.y"
    {
  ConfigFileEntry.kill_chase_time_limit = (yyvsp[(3) - (4)].number);
}
    break;

  case 492:

/* Line 1810 of yacc.c  */
#line 2583 "conf_parser.y"
    {
  ConfigFileEntry.hide_spoof_ips = yylval.number;
}
    break;

  case 493:

/* Line 1810 of yacc.c  */
#line 2588 "conf_parser.y"
    {
  ConfigFileEntry.ignore_bogus_ts = yylval.number;
}
    break;

  case 494:

/* Line 1810 of yacc.c  */
#line 2593 "conf_parser.y"
    {
  ConfigFileEntry.disable_remote = yylval.number;
}
    break;

  case 495:

/* Line 1810 of yacc.c  */
#line 2598 "conf_parser.y"
    {
  ConfigFileEntry.failed_oper_notice = yylval.number;
}
    break;

  case 496:

/* Line 1810 of yacc.c  */
#line 2603 "conf_parser.y"
    {
  ConfigFileEntry.anti_nick_flood = yylval.number;
}
    break;

  case 497:

/* Line 1810 of yacc.c  */
#line 2608 "conf_parser.y"
    {
  ConfigFileEntry.max_nick_time = (yyvsp[(3) - (4)].number); 
}
    break;

  case 498:

/* Line 1810 of yacc.c  */
#line 2613 "conf_parser.y"
    {
  ConfigFileEntry.max_nick_changes = (yyvsp[(3) - (4)].number);
}
    break;

  case 499:

/* Line 1810 of yacc.c  */
#line 2618 "conf_parser.y"
    {
  ConfigFileEntry.max_accept = (yyvsp[(3) - (4)].number);
}
    break;

  case 500:

/* Line 1810 of yacc.c  */
#line 2623 "conf_parser.y"
    {
  ConfigFileEntry.anti_spam_exit_message_time = (yyvsp[(3) - (4)].number);
}
    break;

  case 501:

/* Line 1810 of yacc.c  */
#line 2628 "conf_parser.y"
    {
  ConfigFileEntry.ts_warn_delta = (yyvsp[(3) - (4)].number);
}
    break;

  case 502:

/* Line 1810 of yacc.c  */
#line 2633 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ConfigFileEntry.ts_max_delta = (yyvsp[(3) - (4)].number);
}
    break;

  case 503:

/* Line 1810 of yacc.c  */
#line 2639 "conf_parser.y"
    {
  if (((yyvsp[(3) - (4)].number) > 0) && conf_parser_ctx.pass == 1)
  {
    ilog(LOG_TYPE_IRCD, "You haven't read your config file properly.");
    ilog(LOG_TYPE_IRCD, "There is a line in the example conf that will kill your server if not removed.");
    ilog(LOG_TYPE_IRCD, "Consider actually reading/editing the conf file, and removing this line.");
    exit(0);
  }
}
    break;

  case 504:

/* Line 1810 of yacc.c  */
#line 2650 "conf_parser.y"
    {
  ConfigFileEntry.kline_with_reason = yylval.number;
}
    break;

  case 505:

/* Line 1810 of yacc.c  */
#line 2655 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(ConfigFileEntry.kline_reason);
    DupString(ConfigFileEntry.kline_reason, yylval.string);
  }
}
    break;

  case 506:

/* Line 1810 of yacc.c  */
#line 2664 "conf_parser.y"
    {
  ConfigFileEntry.invisible_on_connect = yylval.number;
}
    break;

  case 507:

/* Line 1810 of yacc.c  */
#line 2669 "conf_parser.y"
    {
  ConfigFileEntry.warn_no_nline = yylval.number;
}
    break;

  case 508:

/* Line 1810 of yacc.c  */
#line 2674 "conf_parser.y"
    {
  ConfigFileEntry.stats_e_disabled = yylval.number;
}
    break;

  case 509:

/* Line 1810 of yacc.c  */
#line 2679 "conf_parser.y"
    {
  ConfigFileEntry.stats_o_oper_only = yylval.number;
}
    break;

  case 510:

/* Line 1810 of yacc.c  */
#line 2684 "conf_parser.y"
    {
  ConfigFileEntry.stats_P_oper_only = yylval.number;
}
    break;

  case 511:

/* Line 1810 of yacc.c  */
#line 2689 "conf_parser.y"
    {
  ConfigFileEntry.stats_k_oper_only = 2 * yylval.number;
}
    break;

  case 512:

/* Line 1810 of yacc.c  */
#line 2692 "conf_parser.y"
    {
  ConfigFileEntry.stats_k_oper_only = 1;
}
    break;

  case 513:

/* Line 1810 of yacc.c  */
#line 2697 "conf_parser.y"
    {
  ConfigFileEntry.stats_i_oper_only = 2 * yylval.number;
}
    break;

  case 514:

/* Line 1810 of yacc.c  */
#line 2700 "conf_parser.y"
    {
  ConfigFileEntry.stats_i_oper_only = 1;
}
    break;

  case 515:

/* Line 1810 of yacc.c  */
#line 2705 "conf_parser.y"
    {
  ConfigFileEntry.pace_wait = (yyvsp[(3) - (4)].number);
}
    break;

  case 516:

/* Line 1810 of yacc.c  */
#line 2710 "conf_parser.y"
    {
  ConfigFileEntry.caller_id_wait = (yyvsp[(3) - (4)].number);
}
    break;

  case 517:

/* Line 1810 of yacc.c  */
#line 2715 "conf_parser.y"
    {
  ConfigFileEntry.opers_bypass_callerid = yylval.number;
}
    break;

  case 518:

/* Line 1810 of yacc.c  */
#line 2720 "conf_parser.y"
    {
  ConfigFileEntry.pace_wait_simple = (yyvsp[(3) - (4)].number);
}
    break;

  case 519:

/* Line 1810 of yacc.c  */
#line 2725 "conf_parser.y"
    {
  ConfigFileEntry.short_motd = yylval.number;
}
    break;

  case 520:

/* Line 1810 of yacc.c  */
#line 2730 "conf_parser.y"
    {
  ConfigFileEntry.no_oper_flood = yylval.number;
}
    break;

  case 521:

/* Line 1810 of yacc.c  */
#line 2735 "conf_parser.y"
    {
  ConfigFileEntry.true_no_oper_flood = yylval.number;
}
    break;

  case 522:

/* Line 1810 of yacc.c  */
#line 2740 "conf_parser.y"
    {
  ConfigFileEntry.oper_pass_resv = yylval.number;
}
    break;

  case 523:

/* Line 1810 of yacc.c  */
#line 2745 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (strlen(yylval.string) > LOCALE_LENGTH-2)
      yylval.string[LOCALE_LENGTH-1] = '\0';

    set_locale(yylval.string);
  }
}
    break;

  case 524:

/* Line 1810 of yacc.c  */
#line 2756 "conf_parser.y"
    {
  ConfigFileEntry.dots_in_ident = (yyvsp[(3) - (4)].number);
}
    break;

  case 525:

/* Line 1810 of yacc.c  */
#line 2761 "conf_parser.y"
    {
  ConfigFileEntry.max_targets = (yyvsp[(3) - (4)].number);
}
    break;

  case 526:

/* Line 1810 of yacc.c  */
#line 2766 "conf_parser.y"
    {
  ConfigFileEntry.use_egd = yylval.number;
}
    break;

  case 527:

/* Line 1810 of yacc.c  */
#line 2771 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(ConfigFileEntry.egdpool_path);
    DupString(ConfigFileEntry.egdpool_path, yylval.string);
  }
}
    break;

  case 528:

/* Line 1810 of yacc.c  */
#line 2780 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2 && valid_servname(yylval.string))
  {
    MyFree(ConfigFileEntry.service_name);
    DupString(ConfigFileEntry.service_name, yylval.string);
  }
}
    break;

  case 529:

/* Line 1810 of yacc.c  */
#line 2789 "conf_parser.y"
    {
  ConfigFileEntry.ping_cookie = yylval.number;
}
    break;

  case 530:

/* Line 1810 of yacc.c  */
#line 2794 "conf_parser.y"
    {
  ConfigFileEntry.disable_auth = yylval.number;
}
    break;

  case 531:

/* Line 1810 of yacc.c  */
#line 2799 "conf_parser.y"
    {
  ConfigFileEntry.throttle_time = yylval.number;
}
    break;

  case 532:

/* Line 1810 of yacc.c  */
#line 2804 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes = 0;
}
    break;

  case 536:

/* Line 1810 of yacc.c  */
#line 2810 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_BOTS;
}
    break;

  case 537:

/* Line 1810 of yacc.c  */
#line 2813 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_CCONN;
}
    break;

  case 538:

/* Line 1810 of yacc.c  */
#line 2816 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_CCONN_FULL;
}
    break;

  case 539:

/* Line 1810 of yacc.c  */
#line 2819 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_DEAF;
}
    break;

  case 540:

/* Line 1810 of yacc.c  */
#line 2822 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_DEBUG;
}
    break;

  case 541:

/* Line 1810 of yacc.c  */
#line 2825 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_FULL;
}
    break;

  case 542:

/* Line 1810 of yacc.c  */
#line 2828 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_HIDDEN;
}
    break;

  case 543:

/* Line 1810 of yacc.c  */
#line 2831 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_SKILL;
}
    break;

  case 544:

/* Line 1810 of yacc.c  */
#line 2834 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_NCHANGE;
}
    break;

  case 545:

/* Line 1810 of yacc.c  */
#line 2837 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_REJ;
}
    break;

  case 546:

/* Line 1810 of yacc.c  */
#line 2840 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_UNAUTH;
}
    break;

  case 547:

/* Line 1810 of yacc.c  */
#line 2843 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_SPY;
}
    break;

  case 548:

/* Line 1810 of yacc.c  */
#line 2846 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_EXTERNAL;
}
    break;

  case 549:

/* Line 1810 of yacc.c  */
#line 2849 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_OPERWALL;
}
    break;

  case 550:

/* Line 1810 of yacc.c  */
#line 2852 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_SERVNOTICE;
}
    break;

  case 551:

/* Line 1810 of yacc.c  */
#line 2855 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_INVISIBLE;
}
    break;

  case 552:

/* Line 1810 of yacc.c  */
#line 2858 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_WALLOP;
}
    break;

  case 553:

/* Line 1810 of yacc.c  */
#line 2861 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_SOFTCALLERID;
}
    break;

  case 554:

/* Line 1810 of yacc.c  */
#line 2864 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_CALLERID;
}
    break;

  case 555:

/* Line 1810 of yacc.c  */
#line 2867 "conf_parser.y"
    {
  ConfigFileEntry.oper_umodes |= UMODE_LOCOPS;
}
    break;

  case 556:

/* Line 1810 of yacc.c  */
#line 2872 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes = 0;
}
    break;

  case 560:

/* Line 1810 of yacc.c  */
#line 2878 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_BOTS;
}
    break;

  case 561:

/* Line 1810 of yacc.c  */
#line 2881 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_CCONN;
}
    break;

  case 562:

/* Line 1810 of yacc.c  */
#line 2884 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_CCONN_FULL;
}
    break;

  case 563:

/* Line 1810 of yacc.c  */
#line 2887 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_DEAF;
}
    break;

  case 564:

/* Line 1810 of yacc.c  */
#line 2890 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_DEBUG;
}
    break;

  case 565:

/* Line 1810 of yacc.c  */
#line 2893 "conf_parser.y"
    { 
  ConfigFileEntry.oper_only_umodes |= UMODE_FULL;
}
    break;

  case 566:

/* Line 1810 of yacc.c  */
#line 2896 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_SKILL;
}
    break;

  case 567:

/* Line 1810 of yacc.c  */
#line 2899 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_HIDDEN;
}
    break;

  case 568:

/* Line 1810 of yacc.c  */
#line 2902 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_NCHANGE;
}
    break;

  case 569:

/* Line 1810 of yacc.c  */
#line 2905 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_REJ;
}
    break;

  case 570:

/* Line 1810 of yacc.c  */
#line 2908 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_UNAUTH;
}
    break;

  case 571:

/* Line 1810 of yacc.c  */
#line 2911 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_SPY;
}
    break;

  case 572:

/* Line 1810 of yacc.c  */
#line 2914 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_EXTERNAL;
}
    break;

  case 573:

/* Line 1810 of yacc.c  */
#line 2917 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_OPERWALL;
}
    break;

  case 574:

/* Line 1810 of yacc.c  */
#line 2920 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_SERVNOTICE;
}
    break;

  case 575:

/* Line 1810 of yacc.c  */
#line 2923 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_INVISIBLE;
}
    break;

  case 576:

/* Line 1810 of yacc.c  */
#line 2926 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_WALLOP;
}
    break;

  case 577:

/* Line 1810 of yacc.c  */
#line 2929 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_SOFTCALLERID;
}
    break;

  case 578:

/* Line 1810 of yacc.c  */
#line 2932 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_CALLERID;
}
    break;

  case 579:

/* Line 1810 of yacc.c  */
#line 2935 "conf_parser.y"
    {
  ConfigFileEntry.oper_only_umodes |= UMODE_LOCOPS;
}
    break;

  case 580:

/* Line 1810 of yacc.c  */
#line 2940 "conf_parser.y"
    {
  ConfigFileEntry.min_nonwildcard = (yyvsp[(3) - (4)].number);
}
    break;

  case 581:

/* Line 1810 of yacc.c  */
#line 2945 "conf_parser.y"
    {
  ConfigFileEntry.min_nonwildcard_simple = (yyvsp[(3) - (4)].number);
}
    break;

  case 582:

/* Line 1810 of yacc.c  */
#line 2950 "conf_parser.y"
    {
  ConfigFileEntry.default_floodcount = (yyvsp[(3) - (4)].number);
}
    break;

  case 583:

/* Line 1810 of yacc.c  */
#line 2955 "conf_parser.y"
    {
  ConfigFileEntry.client_flood = (yyvsp[(3) - (4)].number);
}
    break;

  case 584:

/* Line 1810 of yacc.c  */
#line 2964 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    yy_conf = make_conf_item(GDENY_TYPE);
    yy_aconf = map_to_conf(yy_conf);
  }
}
    break;

  case 585:

/* Line 1810 of yacc.c  */
#line 2971 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    /*
     * since we re-allocate yy_conf/yy_aconf after the end of action=, at the
     * end we will have one extra, so we should free it.
     */
    if (yy_conf->name == NULL || yy_aconf->user == NULL)
    {
      delete_conf_item(yy_conf);
      yy_conf = NULL;
      yy_aconf = NULL;
    }
  }
}
    break;

  case 595:

/* Line 1810 of yacc.c  */
#line 2997 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ConfigFileEntry.glines = yylval.number;
}
    break;

  case 596:

/* Line 1810 of yacc.c  */
#line 3003 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ConfigFileEntry.gline_time = (yyvsp[(3) - (4)].number);
}
    break;

  case 597:

/* Line 1810 of yacc.c  */
#line 3009 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ConfigFileEntry.gline_logging = 0;
}
    break;

  case 601:

/* Line 1810 of yacc.c  */
#line 3015 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ConfigFileEntry.gline_logging |= GDENY_REJECT;
}
    break;

  case 602:

/* Line 1810 of yacc.c  */
#line 3019 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ConfigFileEntry.gline_logging |= GDENY_BLOCK;
}
    break;

  case 603:

/* Line 1810 of yacc.c  */
#line 3025 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    struct split_nuh_item nuh;

    nuh.nuhmask  = yylval.string;
    nuh.nickptr  = NULL;
    nuh.userptr  = userbuf;
    nuh.hostptr  = hostbuf;

    nuh.nicksize = 0;
    nuh.usersize = sizeof(userbuf);
    nuh.hostsize = sizeof(hostbuf);

    split_nuh(&nuh);

    if (yy_aconf->user == NULL)
    {
      DupString(yy_aconf->user, userbuf);
      DupString(yy_aconf->host, hostbuf);
    }
    else
    {
      struct CollectItem *yy_tmp = MyMalloc(sizeof(struct CollectItem));

      DupString(yy_tmp->user, userbuf);
      DupString(yy_tmp->host, hostbuf);

      dlinkAdd(yy_tmp, &yy_tmp->node, &col_conf_list);
    }
  }
}
    break;

  case 604:

/* Line 1810 of yacc.c  */
#line 3059 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)  
  {
    MyFree(yy_conf->name);
    DupString(yy_conf->name, yylval.string);
  }
}
    break;

  case 605:

/* Line 1810 of yacc.c  */
#line 3068 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->flags = 0;
}
    break;

  case 606:

/* Line 1810 of yacc.c  */
#line 3072 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    struct CollectItem *yy_tmp = NULL;
    dlink_node *ptr, *next_ptr;

    DLINK_FOREACH_SAFE(ptr, next_ptr, col_conf_list.head)
    {
      struct AccessItem *new_aconf;
      struct ConfItem *new_conf;

      yy_tmp = ptr->data;
      new_conf = make_conf_item(GDENY_TYPE);
      new_aconf = map_to_conf(new_conf);

      new_aconf->flags = yy_aconf->flags;

      if (yy_conf->name != NULL)
        DupString(new_conf->name, yy_conf->name);
      else
        DupString(new_conf->name, "*");
      if (yy_aconf->user != NULL)
         DupString(new_aconf->user, yy_tmp->user);
      else   
        DupString(new_aconf->user, "*");
      if (yy_aconf->host != NULL)
        DupString(new_aconf->host, yy_tmp->host);
      else
        DupString(new_aconf->host, "*");

      dlinkDelete(&yy_tmp->node, &col_conf_list);
    }

    /*
     * In case someone has fed us with more than one action= after user/name
     * which would leak memory  -Michael
     */
    if (yy_conf->name == NULL || yy_aconf->user == NULL)
      delete_conf_item(yy_conf);

    yy_conf = make_conf_item(GDENY_TYPE);
    yy_aconf = map_to_conf(yy_conf);
  }
}
    break;

  case 609:

/* Line 1810 of yacc.c  */
#line 3119 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->flags |= GDENY_REJECT;
}
    break;

  case 610:

/* Line 1810 of yacc.c  */
#line 3123 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    yy_aconf->flags |= GDENY_BLOCK;
}
    break;

  case 633:

/* Line 1810 of yacc.c  */
#line 3147 "conf_parser.y"
    {
  ConfigChannel.disable_fake_channels = yylval.number;
}
    break;

  case 634:

/* Line 1810 of yacc.c  */
#line 3152 "conf_parser.y"
    {
  ConfigChannel.restrict_channels = yylval.number;
}
    break;

  case 635:

/* Line 1810 of yacc.c  */
#line 3157 "conf_parser.y"
    {
  ConfigChannel.disable_local_channels = yylval.number;
}
    break;

  case 636:

/* Line 1810 of yacc.c  */
#line 3162 "conf_parser.y"
    {
  ConfigChannel.use_except = yylval.number;
}
    break;

  case 637:

/* Line 1810 of yacc.c  */
#line 3167 "conf_parser.y"
    {
  ConfigChannel.use_invex = yylval.number;
}
    break;

  case 638:

/* Line 1810 of yacc.c  */
#line 3172 "conf_parser.y"
    {
  ConfigChannel.use_knock = yylval.number;
}
    break;

  case 639:

/* Line 1810 of yacc.c  */
#line 3177 "conf_parser.y"
    {
  ConfigChannel.knock_delay = (yyvsp[(3) - (4)].number);
}
    break;

  case 640:

/* Line 1810 of yacc.c  */
#line 3182 "conf_parser.y"
    {
  ConfigChannel.knock_delay_channel = (yyvsp[(3) - (4)].number);
}
    break;

  case 641:

/* Line 1810 of yacc.c  */
#line 3187 "conf_parser.y"
    {
  ConfigChannel.max_chans_per_user = (yyvsp[(3) - (4)].number);
}
    break;

  case 642:

/* Line 1810 of yacc.c  */
#line 3192 "conf_parser.y"
    {
  ConfigChannel.max_chans_per_oper = (yyvsp[(3) - (4)].number);
}
    break;

  case 643:

/* Line 1810 of yacc.c  */
#line 3197 "conf_parser.y"
    {
  ConfigChannel.quiet_on_ban = yylval.number;
}
    break;

  case 644:

/* Line 1810 of yacc.c  */
#line 3202 "conf_parser.y"
    {
  ConfigChannel.max_bans = (yyvsp[(3) - (4)].number);
}
    break;

  case 645:

/* Line 1810 of yacc.c  */
#line 3207 "conf_parser.y"
    {
  ConfigChannel.default_split_user_count = (yyvsp[(3) - (4)].number);
}
    break;

  case 646:

/* Line 1810 of yacc.c  */
#line 3212 "conf_parser.y"
    {
  ConfigChannel.default_split_server_count = (yyvsp[(3) - (4)].number);
}
    break;

  case 647:

/* Line 1810 of yacc.c  */
#line 3217 "conf_parser.y"
    {
  ConfigChannel.no_create_on_split = yylval.number;
}
    break;

  case 648:

/* Line 1810 of yacc.c  */
#line 3222 "conf_parser.y"
    {
  ConfigChannel.no_join_on_split = yylval.number;
}
    break;

  case 649:

/* Line 1810 of yacc.c  */
#line 3227 "conf_parser.y"
    {
  GlobalSetOptions.joinfloodcount = yylval.number;
}
    break;

  case 650:

/* Line 1810 of yacc.c  */
#line 3232 "conf_parser.y"
    {
  GlobalSetOptions.joinfloodtime = yylval.number;
}
    break;

  case 662:

/* Line 1810 of yacc.c  */
#line 3251 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ConfigServerHide.flatten_links = yylval.number;
}
    break;

  case 663:

/* Line 1810 of yacc.c  */
#line 3257 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ConfigServerHide.hide_servers = yylval.number;
}
    break;

  case 664:

/* Line 1810 of yacc.c  */
#line 3263 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    MyFree(ConfigServerHide.hidden_name);
    DupString(ConfigServerHide.hidden_name, yylval.string);
  }
}
    break;

  case 665:

/* Line 1810 of yacc.c  */
#line 3272 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
  {
    if (((yyvsp[(3) - (4)].number) > 0) && ConfigServerHide.links_disabled == 1)
    {
      eventAddIsh("write_links_file", write_links_file, NULL, (yyvsp[(3) - (4)].number));
      ConfigServerHide.links_disabled = 0;
    }

    ConfigServerHide.links_delay = (yyvsp[(3) - (4)].number);
  }
}
    break;

  case 666:

/* Line 1810 of yacc.c  */
#line 3286 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ConfigServerHide.hidden = yylval.number;
}
    break;

  case 667:

/* Line 1810 of yacc.c  */
#line 3292 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ConfigServerHide.disable_hidden = yylval.number;
}
    break;

  case 668:

/* Line 1810 of yacc.c  */
#line 3298 "conf_parser.y"
    {
  if (conf_parser_ctx.pass == 2)
    ConfigServerHide.hide_server_ips = yylval.number;
}
    break;



/* Line 1810 of yacc.c  */
#line 7589 "conf_parser.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}




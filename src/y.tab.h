/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

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
     BURST_TOPICWHO = 268,
     BYTES = 269,
     KBYTES = 270,
     MBYTES = 271,
     GBYTES = 272,
     TBYTES = 273,
     CALLER_ID_WAIT = 274,
     CAN_FLOOD = 275,
     CAN_IDLE = 276,
     CHANNEL = 277,
     CIDR_BITLEN_IPV4 = 278,
     CIDR_BITLEN_IPV6 = 279,
     CIPHER_PREFERENCE = 280,
     CLASS = 281,
     COMPRESSED = 282,
     COMPRESSION_LEVEL = 283,
     CONNECT = 284,
     CONNECTFREQ = 285,
     CRYPTLINK = 286,
     DEFAULT_CIPHER_PREFERENCE = 287,
     DEFAULT_FLOODCOUNT = 288,
     DEFAULT_SPLIT_SERVER_COUNT = 289,
     DEFAULT_SPLIT_USER_COUNT = 290,
     DENY = 291,
     DESCRIPTION = 292,
     DIE = 293,
     DISABLE_AUTH = 294,
     DISABLE_HIDDEN = 295,
     DISABLE_LOCAL_CHANNELS = 296,
     DISABLE_REMOTE_COMMANDS = 297,
     DOT_IN_IP6_ADDR = 298,
     DOTS_IN_IDENT = 299,
     DURATION = 300,
     EGDPOOL_PATH = 301,
     EMAIL = 302,
     ENABLE = 303,
     ENCRYPTED = 304,
     EXCEED_LIMIT = 305,
     EXEMPT = 306,
     FAILED_OPER_NOTICE = 307,
     FAKENAME = 308,
     IRCD_FLAGS = 309,
     FLATTEN_LINKS = 310,
     FFAILED_OPERLOG = 311,
     FKILLLOG = 312,
     FKLINELOG = 313,
     FGLINELOG = 314,
     FIOERRLOG = 315,
     FOPERLOG = 316,
     FOPERSPYLOG = 317,
     FUSERLOG = 318,
     GECOS = 319,
     GENERAL = 320,
     GLINE = 321,
     GLINES = 322,
     GLINE_EXEMPT = 323,
     GLINE_LOG = 324,
     GLINE_TIME = 325,
     GLINE_MIN_CIDR = 326,
     GLINE_MIN_CIDR6 = 327,
     GLOBAL_KILL = 328,
     IRCD_AUTH = 329,
     NEED_IDENT = 330,
     HAVENT_READ_CONF = 331,
     HIDDEN = 332,
     HIDDEN_ADMIN = 333,
     HIDDEN_NAME = 334,
     HIDDEN_OPER = 335,
     HIDE_SERVER_IPS = 336,
     HIDE_SERVERS = 337,
     HIDE_SPOOF_IPS = 338,
     HOST = 339,
     HUB = 340,
     HUB_MASK = 341,
     IDLETIME = 342,
     IGNORE_BOGUS_TS = 343,
     INVISIBLE_ON_CONNECT = 344,
     IP = 345,
     KILL = 346,
     KILL_CHASE_TIME_LIMIT = 347,
     KLINE = 348,
     KLINE_EXEMPT = 349,
     KLINE_REASON = 350,
     KLINE_WITH_REASON = 351,
     KNOCK_DELAY = 352,
     KNOCK_DELAY_CHANNEL = 353,
     LAZYLINK = 354,
     LEAF_MASK = 355,
     LINKS_DELAY = 356,
     LISTEN = 357,
     T_LOG = 358,
     LOGGING = 359,
     LOG_LEVEL = 360,
     MAX_ACCEPT = 361,
     MAX_BANS = 362,
     MAX_CHANS_PER_USER = 363,
     MAX_GLOBAL = 364,
     MAX_IDENT = 365,
     MAX_LOCAL = 366,
     MAX_NICK_CHANGES = 367,
     MAX_NICK_TIME = 368,
     MAX_NUMBER = 369,
     MAX_TARGETS = 370,
     MESSAGE_LOCALE = 371,
     MIN_NONWILDCARD = 372,
     MIN_NONWILDCARD_SIMPLE = 373,
     MODULE = 374,
     MODULES = 375,
     NAME = 376,
     NEED_PASSWORD = 377,
     NETWORK_DESC = 378,
     NETWORK_NAME = 379,
     NICK = 380,
     NICK_CHANGES = 381,
     NO_CREATE_ON_SPLIT = 382,
     NO_JOIN_ON_SPLIT = 383,
     NO_OPER_FLOOD = 384,
     NO_TILDE = 385,
     NOT = 386,
     NUMBER = 387,
     NUMBER_PER_IDENT = 388,
     NUMBER_PER_CIDR = 389,
     NUMBER_PER_IP = 390,
     NUMBER_PER_IP_GLOBAL = 391,
     OPERATOR = 392,
     OPERS_BYPASS_CALLERID = 393,
     OPER_LOG = 394,
     OPER_ONLY_UMODES = 395,
     OPER_PASS_RESV = 396,
     OPER_SPY_T = 397,
     OPER_UMODES = 398,
     INVITE_OPS_ONLY = 399,
     JOIN_FLOOD_COUNT = 400,
     JOIN_FLOOD_TIME = 401,
     PACE_WAIT = 402,
     PACE_WAIT_SIMPLE = 403,
     PASSWORD = 404,
     PATH = 405,
     PING_COOKIE = 406,
     PING_TIME = 407,
     PING_WARNING = 408,
     PORT = 409,
     QSTRING = 410,
     QUIET_ON_BAN = 411,
     REASON = 412,
     REDIRPORT = 413,
     REDIRSERV = 414,
     REGEX_T = 415,
     REHASH = 416,
     TREJECT_HOLD_TIME = 417,
     REMOTE = 418,
     REMOTEBAN = 419,
     RESTRICT_CHANNELS = 420,
     RESTRICTED = 421,
     RSA_PRIVATE_KEY_FILE = 422,
     RSA_PUBLIC_KEY_FILE = 423,
     SSL_CERTIFICATE_FILE = 424,
     RESV = 425,
     RESV_EXEMPT = 426,
     SECONDS = 427,
     MINUTES = 428,
     HOURS = 429,
     DAYS = 430,
     WEEKS = 431,
     SENDQ = 432,
     SEND_PASSWORD = 433,
     SERVERHIDE = 434,
     SERVERINFO = 435,
     SERVLINK_PATH = 436,
     IRCD_SID = 437,
     TKLINE_EXPIRE_NOTICES = 438,
     T_SHARED = 439,
     T_CLUSTER = 440,
     TYPE = 441,
     SHORT_MOTD = 442,
     SILENT = 443,
     SPOOF = 444,
     SPOOF_NOTICE = 445,
     STATS_I_OPER_ONLY = 446,
     STATS_K_OPER_ONLY = 447,
     STATS_O_OPER_ONLY = 448,
     STATS_P_OPER_ONLY = 449,
     TBOOL = 450,
     TMASKED = 451,
     T_REJECT = 452,
     TS_MAX_DELTA = 453,
     TS_WARN_DELTA = 454,
     TWODOTS = 455,
     T_ALL = 456,
     T_BOTS = 457,
     T_SOFTCALLERID = 458,
     T_CALLERID = 459,
     T_CCONN = 460,
     T_CLIENT_FLOOD = 461,
     T_DEAF = 462,
     T_DEBUG = 463,
     T_DRONE = 464,
     T_EXTERNAL = 465,
     T_FULL = 466,
     T_INVISIBLE = 467,
     T_IPV4 = 468,
     T_IPV6 = 469,
     T_LOCOPS = 470,
     T_LOGPATH = 471,
     T_L_CRIT = 472,
     T_L_DEBUG = 473,
     T_L_ERROR = 474,
     T_L_INFO = 475,
     T_L_NOTICE = 476,
     T_L_TRACE = 477,
     T_L_WARN = 478,
     T_MAX_CLIENTS = 479,
     T_NCHANGE = 480,
     T_OPERWALL = 481,
     T_REJ = 482,
     T_SERVNOTICE = 483,
     T_SKILL = 484,
     T_SPY = 485,
     T_SSL = 486,
     T_UMODES = 487,
     T_UNAUTH = 488,
     T_UNRESV = 489,
     T_UNXLINE = 490,
     T_WALLOP = 491,
     THROTTLE_TIME = 492,
     TOPICBURST = 493,
     TRUE_NO_OPER_FLOOD = 494,
     TKLINE = 495,
     TXLINE = 496,
     TRESV = 497,
     UNKLINE = 498,
     USER = 499,
     USE_EGD = 500,
     USE_EXCEPT = 501,
     USE_INVEX = 502,
     USE_KNOCK = 503,
     USE_LOGGING = 504,
     USE_WHOIS_ACTUALLY = 505,
     VHOST = 506,
     VHOST6 = 507,
     XLINE = 508,
     WARN = 509,
     WARN_NO_NLINE = 510
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
#define BURST_TOPICWHO 268
#define BYTES 269
#define KBYTES 270
#define MBYTES 271
#define GBYTES 272
#define TBYTES 273
#define CALLER_ID_WAIT 274
#define CAN_FLOOD 275
#define CAN_IDLE 276
#define CHANNEL 277
#define CIDR_BITLEN_IPV4 278
#define CIDR_BITLEN_IPV6 279
#define CIPHER_PREFERENCE 280
#define CLASS 281
#define COMPRESSED 282
#define COMPRESSION_LEVEL 283
#define CONNECT 284
#define CONNECTFREQ 285
#define CRYPTLINK 286
#define DEFAULT_CIPHER_PREFERENCE 287
#define DEFAULT_FLOODCOUNT 288
#define DEFAULT_SPLIT_SERVER_COUNT 289
#define DEFAULT_SPLIT_USER_COUNT 290
#define DENY 291
#define DESCRIPTION 292
#define DIE 293
#define DISABLE_AUTH 294
#define DISABLE_HIDDEN 295
#define DISABLE_LOCAL_CHANNELS 296
#define DISABLE_REMOTE_COMMANDS 297
#define DOT_IN_IP6_ADDR 298
#define DOTS_IN_IDENT 299
#define DURATION 300
#define EGDPOOL_PATH 301
#define EMAIL 302
#define ENABLE 303
#define ENCRYPTED 304
#define EXCEED_LIMIT 305
#define EXEMPT 306
#define FAILED_OPER_NOTICE 307
#define FAKENAME 308
#define IRCD_FLAGS 309
#define FLATTEN_LINKS 310
#define FFAILED_OPERLOG 311
#define FKILLLOG 312
#define FKLINELOG 313
#define FGLINELOG 314
#define FIOERRLOG 315
#define FOPERLOG 316
#define FOPERSPYLOG 317
#define FUSERLOG 318
#define GECOS 319
#define GENERAL 320
#define GLINE 321
#define GLINES 322
#define GLINE_EXEMPT 323
#define GLINE_LOG 324
#define GLINE_TIME 325
#define GLINE_MIN_CIDR 326
#define GLINE_MIN_CIDR6 327
#define GLOBAL_KILL 328
#define IRCD_AUTH 329
#define NEED_IDENT 330
#define HAVENT_READ_CONF 331
#define HIDDEN 332
#define HIDDEN_ADMIN 333
#define HIDDEN_NAME 334
#define HIDDEN_OPER 335
#define HIDE_SERVER_IPS 336
#define HIDE_SERVERS 337
#define HIDE_SPOOF_IPS 338
#define HOST 339
#define HUB 340
#define HUB_MASK 341
#define IDLETIME 342
#define IGNORE_BOGUS_TS 343
#define INVISIBLE_ON_CONNECT 344
#define IP 345
#define KILL 346
#define KILL_CHASE_TIME_LIMIT 347
#define KLINE 348
#define KLINE_EXEMPT 349
#define KLINE_REASON 350
#define KLINE_WITH_REASON 351
#define KNOCK_DELAY 352
#define KNOCK_DELAY_CHANNEL 353
#define LAZYLINK 354
#define LEAF_MASK 355
#define LINKS_DELAY 356
#define LISTEN 357
#define T_LOG 358
#define LOGGING 359
#define LOG_LEVEL 360
#define MAX_ACCEPT 361
#define MAX_BANS 362
#define MAX_CHANS_PER_USER 363
#define MAX_GLOBAL 364
#define MAX_IDENT 365
#define MAX_LOCAL 366
#define MAX_NICK_CHANGES 367
#define MAX_NICK_TIME 368
#define MAX_NUMBER 369
#define MAX_TARGETS 370
#define MESSAGE_LOCALE 371
#define MIN_NONWILDCARD 372
#define MIN_NONWILDCARD_SIMPLE 373
#define MODULE 374
#define MODULES 375
#define NAME 376
#define NEED_PASSWORD 377
#define NETWORK_DESC 378
#define NETWORK_NAME 379
#define NICK 380
#define NICK_CHANGES 381
#define NO_CREATE_ON_SPLIT 382
#define NO_JOIN_ON_SPLIT 383
#define NO_OPER_FLOOD 384
#define NO_TILDE 385
#define NOT 386
#define NUMBER 387
#define NUMBER_PER_IDENT 388
#define NUMBER_PER_CIDR 389
#define NUMBER_PER_IP 390
#define NUMBER_PER_IP_GLOBAL 391
#define OPERATOR 392
#define OPERS_BYPASS_CALLERID 393
#define OPER_LOG 394
#define OPER_ONLY_UMODES 395
#define OPER_PASS_RESV 396
#define OPER_SPY_T 397
#define OPER_UMODES 398
#define INVITE_OPS_ONLY 399
#define JOIN_FLOOD_COUNT 400
#define JOIN_FLOOD_TIME 401
#define PACE_WAIT 402
#define PACE_WAIT_SIMPLE 403
#define PASSWORD 404
#define PATH 405
#define PING_COOKIE 406
#define PING_TIME 407
#define PING_WARNING 408
#define PORT 409
#define QSTRING 410
#define QUIET_ON_BAN 411
#define REASON 412
#define REDIRPORT 413
#define REDIRSERV 414
#define REGEX_T 415
#define REHASH 416
#define TREJECT_HOLD_TIME 417
#define REMOTE 418
#define REMOTEBAN 419
#define RESTRICT_CHANNELS 420
#define RESTRICTED 421
#define RSA_PRIVATE_KEY_FILE 422
#define RSA_PUBLIC_KEY_FILE 423
#define SSL_CERTIFICATE_FILE 424
#define RESV 425
#define RESV_EXEMPT 426
#define SECONDS 427
#define MINUTES 428
#define HOURS 429
#define DAYS 430
#define WEEKS 431
#define SENDQ 432
#define SEND_PASSWORD 433
#define SERVERHIDE 434
#define SERVERINFO 435
#define SERVLINK_PATH 436
#define IRCD_SID 437
#define TKLINE_EXPIRE_NOTICES 438
#define T_SHARED 439
#define T_CLUSTER 440
#define TYPE 441
#define SHORT_MOTD 442
#define SILENT 443
#define SPOOF 444
#define SPOOF_NOTICE 445
#define STATS_I_OPER_ONLY 446
#define STATS_K_OPER_ONLY 447
#define STATS_O_OPER_ONLY 448
#define STATS_P_OPER_ONLY 449
#define TBOOL 450
#define TMASKED 451
#define T_REJECT 452
#define TS_MAX_DELTA 453
#define TS_WARN_DELTA 454
#define TWODOTS 455
#define T_ALL 456
#define T_BOTS 457
#define T_SOFTCALLERID 458
#define T_CALLERID 459
#define T_CCONN 460
#define T_CLIENT_FLOOD 461
#define T_DEAF 462
#define T_DEBUG 463
#define T_DRONE 464
#define T_EXTERNAL 465
#define T_FULL 466
#define T_INVISIBLE 467
#define T_IPV4 468
#define T_IPV6 469
#define T_LOCOPS 470
#define T_LOGPATH 471
#define T_L_CRIT 472
#define T_L_DEBUG 473
#define T_L_ERROR 474
#define T_L_INFO 475
#define T_L_NOTICE 476
#define T_L_TRACE 477
#define T_L_WARN 478
#define T_MAX_CLIENTS 479
#define T_NCHANGE 480
#define T_OPERWALL 481
#define T_REJ 482
#define T_SERVNOTICE 483
#define T_SKILL 484
#define T_SPY 485
#define T_SSL 486
#define T_UMODES 487
#define T_UNAUTH 488
#define T_UNRESV 489
#define T_UNXLINE 490
#define T_WALLOP 491
#define THROTTLE_TIME 492
#define TOPICBURST 493
#define TRUE_NO_OPER_FLOOD 494
#define TKLINE 495
#define TXLINE 496
#define TRESV 497
#define UNKLINE 498
#define USER 499
#define USE_EGD 500
#define USE_EXCEPT 501
#define USE_INVEX 502
#define USE_KNOCK 503
#define USE_LOGGING 504
#define USE_WHOIS_ACTUALLY 505
#define VHOST 506
#define VHOST6 507
#define XLINE 508
#define WARN 509
#define WARN_NO_NLINE 510




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 124 "ircd_parser.y"
typedef union YYSTYPE {
  int number;
  char *string;
} YYSTYPE;
/* Line 1447 of yacc.c.  */
#line 553 "y.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;




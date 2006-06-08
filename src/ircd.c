/*
 *  ircd-hybrid: an advanced Internet Relay Chat Daemon(ircd).
 *  ircd.c: Starts up and runs the ircd.
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

#ifdef IN_IRCD
#include "stdinc.h"
#include "s_user.h"
#include "ircd.h"
#include "channel.h"
#include "channel_mode.h"
#include "client.h"
#include "common.h"
#include "hash.h"
#include "ircd_signal.h"
#include "motd.h"
#include "ircd_handler.h"
#include "msg.h"         /* msgtab */
#include "hostmask.h"
#include "numeric.h"
#include "packet.h"
#include "parse.h"
#include "restart.h"
#include "s_auth.h"
#include "s_conf.h"
#include "parse_aline.h"
#include "s_serv.h"
#include "send.h"
#include "whowas.h"
#include "conf/modules.h"
#include "motd.h"
#include "supported.h"
#include "watch.h"

/* Try and find the correct name to use with getrlimit() for setting the max.
 * number of files allowed to be open by this process.
 */

/* /quote set variables */
struct SetOptions GlobalSetOptions;
struct ServerStatistics ServerStats;
/* configuration set from ircd.conf */
struct config_file_entry ConfigFileEntry; 
/* server info set from ircd.conf */
struct server_info ServerInfo;
/* admin info set from ircd.conf */
struct admin_info AdminInfo = { NULL, NULL, NULL };
struct Counter Count = { 0, 0, 0, 0, 0, 0, 0, 0 };
struct ServerState_t server_state = { 0 };
struct logging_entry ConfigLoggingEntry = { 1, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0} }; 
struct Client me;             /* That's me */
struct LocalUser meLocalUser; /* That's also part of me */

const char *logFileName = LPATH;
const char *pidFileName = PPATH;

char **myargv;
char ircd_platform[PLATFORMLEN];

int dorehash = 0;
int doremotd = 0;

/* Set to zero because it should be initialized later using
 * initialize_server_capabs
 */
int default_server_capabs = 0;

#ifdef HAVE_LIBCRYPTO
int bio_spare_fd = -1;
#endif

int splitmode;
int splitchecking;

static dlink_node *fdlimit_hook;

/* Do klines the same way hybrid-6 did them, i.e. at the
 * top of the next io_loop instead of in the same loop as
 * the klines are being applied.
 *
 * This should fix strange CPU starvation as very indirectly reported.
 * (Why do you people not email bug reports? WHY? WHY?)
 *
 * - Dianora
 */

int rehashed_klines = 0;

#ifndef _WIN32
/*
 * print_startup - print startup information
 */
static void
print_startup(int pid)
{
  printf("ircd: version %s\n", ircd_version);
  printf("ircd: pid %d\n", pid);
  printf("ircd: running in %s mode from %s\n", !server_state.foreground ? "background"
         : "foreground", ConfigFileEntry.dpath);
}

static void
make_daemon(void)
{
  int pid;

  if ((pid = fork()) < 0)
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  else if (pid > 0)
  {
    print_startup(pid);
    exit(EXIT_SUCCESS);
  }

  setsid();
}
#endif

static int printVersion = 0;

struct lgetopt myopts[] = {
  {"dlinefile",  &ConfigFileEntry.dlinefile, 
   STRING, "File to use for dline.conf"},
  {"configfile", &ConfigFileEntry.configfile, 
   STRING, "File to use for ircd.conf"},
  {"klinefile",  &ConfigFileEntry.klinefile, 
   STRING, "File to use for kline.conf"},
  {"xlinefile",  &ConfigFileEntry.xlinefile, 
   STRING, "File to use for xline.conf"},
  {"logfile",    &logFileName, 
   STRING, "File to use for ircd.log"},
  {"pidfile",    &pidFileName,
   STRING, "File to use for process ID"},
  {"foreground", &server_state.foreground, 
   YESNO, "Run in foreground (don't detach)"},
  {"version",    &printVersion, 
   YESNO, "Print version and exit"},
  {"help", NULL, USAGE, "Print this text"},
  {NULL, NULL, STRING, NULL},
};

static void
io_loop(void)
{
  while (1 == 1)
  {
    /*
     * Maybe we want a flags word?
     * ie. if (REHASHED_KLINES(global_flags)) 
     * SET_REHASHED_KLINES(global_flags)
     * CLEAR_REHASHED_KLINES(global_flags)
     *
     * - Dianora
     */
    if (rehashed_klines)
    {
      check_conf_klines();
      rehashed_klines = 0;
    }

    if (listing_client_list.head)
    {
      dlink_node *ptr = NULL, *ptr_next = NULL;
      DLINK_FOREACH_SAFE(ptr, ptr_next, listing_client_list.head)
      {
        struct Client *client_p = ptr->data;
        assert(client_p->localClient->list_task);
        safe_list_channels(client_p, client_p->localClient->list_task, 0);
      }
    }

    /* Run pending events, then get the number of seconds to the next
     * event
     */
    while (eventNextTime() <= CurrentTime)
      eventRun();

    comm_select();
    exit_aborted_clients();
    free_exited_clients();
    send_queued_all();

    /* Check to see whether we have to rehash the configuration .. */
    if (dorehash)
    {
      rehash(1);
      dorehash = 0;
    }

    if (doremotd)
    {
      read_message_file(&ConfigFileEntry.motd);
      sendto_realops_flags(UMODE_ALL, L_ALL,
                           "Got signal SIGUSR1, reloading ircd motd file");
      doremotd = 0;
    }
  }
}

/* initalialize_global_set_options()
 *
 * inputs       - none
 * output       - none
 * side effects - This sets all global set options needed 
 * XXX to be removed with old s_conf.c
 */
static void
initialize_global_set_options(void)
{
  memset(&GlobalSetOptions, 0, sizeof(GlobalSetOptions));

  GlobalSetOptions.autoconn  = 1;
  GlobalSetOptions.spam_time = MIN_JOIN_LEAVE_TIME;
  GlobalSetOptions.spam_num  = MAX_JOIN_LEAVE_COUNT;

  if (ConfigFileEntry.default_floodcount)
    GlobalSetOptions.floodcount = ConfigFileEntry.default_floodcount;
  else
    GlobalSetOptions.floodcount = 10;

  /* XXX I have no idea what to try here - Dianora */
  GlobalSetOptions.joinfloodcount = 16;
  GlobalSetOptions.joinfloodtime = 8;

  GlobalSetOptions.split_servers = ConfigChannel.default_split_server_count;
  GlobalSetOptions.split_users   = ConfigChannel.default_split_user_count;

  if (GlobalSetOptions.split_users &&
      GlobalSetOptions.split_servers && (ConfigChannel.no_create_on_split ||
                                         ConfigChannel.no_join_on_split))
  {
    splitmode     = 1;
    splitchecking = 1;
  }

  GlobalSetOptions.ident_timeout = IDENT_TIMEOUT;
  GlobalSetOptions.idletime = ConfigFileEntry.idletime;
  GlobalSetOptions.maxlisters = 10; /* XXX ya ya ya - db */
}

/* initialize_message_files()
 *
 * inputs       - none
 * output       - none
 * side effects - Set up all message files needed, motd etc.
 */
static void
initialize_message_files(void)
{
  init_message_file(USER_MOTD, MPATH, &ConfigFileEntry.motd);
  init_message_file(OPER_MOTD, OPATH, &ConfigFileEntry.opermotd);
  init_message_file(USER_LINKS, LIPATH, &ConfigFileEntry.linksfile);

  read_message_file(&ConfigFileEntry.motd);
  read_message_file(&ConfigFileEntry.opermotd);
  read_message_file(&ConfigFileEntry.linksfile);

  init_isupport();
}

/* initialize_server_capabs()
 *
 * inputs       - none
 * output       - none
 */
static void
initialize_server_capabs(void)
{
  add_capability("QS", CAP_QS, 1);
  add_capability("EOB", CAP_EOB, 1);
  add_capability("HUB", CAP_HUB, 0);
  add_capability("TS6", CAP_TS6, 0);
  add_capability("ZIP", CAP_ZIP, 0);
  add_capability("CLUSTER", CAP_CLUSTER, 1);
#ifdef HALFOPS
  add_capability("HOPS", CAP_HOPS, 1);
#endif
}

/* write_pidfile()
 *
 * inputs       - filename+path of pid file
 * output       - NONE
 * side effects - write the pid of the ircd to filename
 */
static void
write_pidfile(const char *filename)
{
  FBFILE *fb;

  if ((fb = fbopen(filename, "w")))
  {
    char buff[32];
    unsigned int pid = (unsigned int)getpid();
    size_t nbytes = ircsprintf(buff, "%u\n", pid);

    if ((fbputs(buff, fb, nbytes) == -1))
      ilog(L_ERROR, "Error writing %u to pid file %s (%s)",
           pid, filename, strerror(errno));

    fbclose(fb);
  }
  else
  {
    ilog(L_ERROR, "Error opening pid file %s", filename);
  }
}

/* check_pidfile()
 *
 * inputs       - filename+path of pid file
 * output       - none
 * side effects - reads pid from pidfile and checks if ircd is in process
 *                list. if it is, gracefully exits
 * -kre
 */
static void
check_pidfile(const char *filename)
{
#ifndef _WIN32
  FBFILE *fb;
  char buff[32];
  pid_t pidfromfile;

  /* Don't do logging here, since we don't have log() initialised */
  if ((fb = fbopen(filename, "r")))
  {
    if (fbgets(buff, 20, fb) == NULL)
    {
      /* log(L_ERROR, "Error reading from pid file %s (%s)", filename,
       * strerror(errno));
       */
    }
    else
    {
      pidfromfile = atoi(buff);

      if (!kill(pidfromfile, 0))
      {
        /* log(L_ERROR, "Server is already running"); */
        printf("ircd: daemon is already running\n");
        exit(-1);
      }
    }

    fbclose(fb);
  }
  else if (errno != ENOENT)
  {
    /* log(L_ERROR, "Error opening pid file %s", filename); */
  }
#endif
}

/* init_ssl()
 *
 * inputs       - nothing
 * output       - nothing
 * side effects - setups SSL context.
 */
static void
init_ssl(void)
{
#ifdef HAVE_LIBCRYPTO
  SSL_library_init();
  SSL_load_error_strings();

  ServerInfo.ctx = SSL_CTX_new(SSLv23_server_method());

  if (!ServerInfo.ctx)
  {
    const char *s;

    fprintf(stderr, "ERROR: Could not initialize the SSL context -- %s\n",
            s = ERR_lib_error_string(ERR_get_error()));
    ilog(L_CRIT, "ERROR: Could not initialize the SSL context -- %s\n", s);
  }

  SSL_CTX_set_options(ServerInfo.ctx, SSL_OP_NO_SSLv2);
  SSL_CTX_set_options(ServerInfo.ctx, SSL_OP_TLS_ROLLBACK_BUG|SSL_OP_ALL);
  SSL_CTX_set_verify(ServerInfo.ctx, SSL_VERIFY_NONE, NULL);

  bio_spare_fd = save_spare_fd("SSL private key validation");
#endif /* HAVE_LIBCRYPTO */
}

/* init_callbacks()
 *
 * inputs       - nothing
 * output       - nothing
 * side effects - setups standard hook points
 */
static void
init_callbacks(void)
{
  entering_umode_cb = register_callback("entering_umode", NULL);
  iorecv_cb = register_callback("iorecv", iorecv_default);
  iosend_cb = register_callback("iosend", iosend_default);
  iorecvctrl_cb = register_callback("iorecvctrl", NULL);
  iosendctrl_cb = register_callback("iosendctrl", NULL);
  uid_get_cb = register_callback("uid_get", uid_get);
  umode_cb = register_callback("changing_umode", change_simple_umode);
}

static void *
changing_fdlimit(va_list args)
{
  int old_fdlimit = hard_fdlimit;
  int fdmax = va_arg(args, int);

  /*
   * allow MAXCLIENTS_MIN clients even at the cost of MAX_BUFFER and
   * some not really LEAKED_FDS
   */
  fdmax = LIBIO_MAX(fdmax, LEAKED_FDS + MAX_BUFFER + MAXCLIENTS_MIN);

  pass_callback(fdlimit_hook, fdmax);

  if (ServerInfo.max_clients > MAXCLIENTS_MAX)
  {
    if (old_fdlimit != 0)
      sendto_realops_flags(UMODE_ALL, L_ALL,
        "HARD_FDLIMIT changed to %d, adjusting MAXCLIENTS to %d",
        hard_fdlimit, MAXCLIENTS_MAX);

    ServerInfo.max_clients = MAXCLIENTS_MAX;
  }

  return NULL;
}

EXTERN int
main(int argc, char *argv[])
{
  /*
   * Check to see if the user is running us as root, which is a nono
   */
#ifndef _WIN32
  if (geteuid() == 0)
  {
    fprintf(stderr, "Don't run ircd as root!!!\n");
    return 1;
  }

  /* Setup corefile size immediately after boot -kre */
  setup_corefile();
#endif

  memset(&ServerInfo, 0, sizeof(ServerInfo));
  memset(&ServerStats, 0, sizeof(ServerStats));

  ConfigFileEntry.dpath      = DPATH;
  ConfigFileEntry.configfile = CPATH;  /* Server configuration file */
  ConfigFileEntry.klinefile  = KPATH;  /* Server kline file         */
  ConfigFileEntry.xlinefile  = XPATH;  /* Server xline file         */
  ConfigFileEntry.rxlinefile = RXPATH; /* Server regex xline file   */
  ConfigFileEntry.rklinefile = RKPATH; /* Server regex kline file   */
  ConfigFileEntry.dlinefile  = DLPATH; /* dline file                */
  ConfigFileEntry.glinefile  = GPATH;  /* gline log file            */
  ConfigFileEntry.cresvfile  = CRESVPATH; /* channel resv file      */
  ConfigFileEntry.nresvfile  = NRESVPATH; /* nick resv file         */
  myargv = argv;
  umask(077);                /* better safe than sorry --SRB */

  parseargs(&argc, &argv, myopts);

  if (printVersion)
  {
    printf("ircd: version %s\n", ircd_version);
    exit(EXIT_SUCCESS);
  }

  if (chdir(ConfigFileEntry.dpath))
  {
    perror("chdir");
    exit(EXIT_FAILURE);
  }

  init_ssl();

#ifndef _WIN32
  if (!server_state.foreground)
    make_daemon();
  else
    print_startup(getpid());
#endif

  libio_init(!server_state.foreground);
  outofmemory = ircd_outofmemory;
  fdlimit_hook = install_hook(fdlimit_cb, changing_fdlimit);

  check_pidfile(pidFileName);
  setup_signals();
  get_ircd_platform(ircd_platform);
  init_log(logFileName);
  ServerInfo.can_use_v6 = check_can_use_v6();

  /* make_dlink_node() cannot be called until after libio_init() */
  memset(&me, 0, sizeof(me));
  memset(&meLocalUser, 0, sizeof(meLocalUser));

  me.localClient = &meLocalUser;
  me.from = me.servptr = &me;
  me.lasttime = me.since = me.firsttime = CurrentTime;

  SetMe(&me);
  make_server(&me);
  dlinkAdd(&me, &me.node, &global_client_list);
  dlinkAdd(&me, make_dlink_node(), &global_serv_list);

  init_callbacks();
  initialize_message_files();
  init_hash();
  init_ip_hash_table();      /* client host ip hash table */
  init_host_hash();          /* Host-hashtable. */
  clear_tree_parse();
  init_client();
  init_class();
  init_whowas();
  init_auth();          /* Initialise the auth code */
  init_channels();
  init_channel_modes();
  initialize_server_capabs();   /* Set up default_server_capabs */

  read_conf_files(1);   /* cold start init conf files */
  check_class();
  init_watch();

  if (ServerInfo.name == NULL)
  {
    ilog(L_CRIT, "ERROR: No server name specified in serverinfo block.");
    exit(EXIT_FAILURE);
  }

  strlcpy(me.name, ServerInfo.name, sizeof(me.name));

  /* serverinfo{} description must exist.  If not, error out.*/
  if (ServerInfo.description == NULL)
  {
    ilog(L_CRIT,
      "ERROR: No server description specified in serverinfo block.");
    exit(EXIT_FAILURE);
  }

  strlcpy(me.info, ServerInfo.description, sizeof(me.info));

  hash_add_client(&me);

  init_uid();     /* XXX move this one up after inculcating new conf system */
  initialize_global_set_options();   /* and this one is going to be deleted */

#ifndef STATIC_MODULES
  if (chdir(MODPATH))
  {
    ilog (L_CRIT, "Could not load core modules. Terminating!");
    exit(EXIT_FAILURE);
  }

  boot_modules(1);

  /* Go back to DPATH after checking to see if we can chdir to MODPATH */
  chdir(ConfigFileEntry.dpath);
#else
  load_all_modules(1);
#endif
  /*
   * assemble_umode_buffer() has to be called after
   * reading conf/loading modules.
   */
  assemble_umode_buffer();

  write_pidfile(pidFileName);

  ilog(L_NOTICE, "Server Ready");

  eventAddIsh("cleanup_tklines", cleanup_tklines, NULL, CLEANUP_TKLINES_TIME);

  /* We want try_connections to be called as soon as possible now! -- adrian */
  /* No, 'cause after a restart it would cause all sorts of nick collides */
  eventAddIsh("try_connections", try_connections, NULL, STARTUP_CONNECTIONS_TIME);

  eventAddIsh("collect_zipstats", collect_zipstats, NULL, ZIPSTATS_TIME);

  /* Setup the timeout check. I'll shift it later :)  -- adrian */
  eventAddIsh("comm_checktimeouts", comm_checktimeouts, NULL, 1);

  /* XXX to be removed with old s_conf.c [superseded] */
  if (ConfigServerHide.links_delay > 0)
    eventAddIsh("write_links_file", write_links_file, NULL, ConfigServerHide.links_delay);
  else
    ConfigServerHide.links_disabled = 1;

  if (splitmode)   /* XXX */
    eventAddIsh("check_splitmode", check_splitmode, NULL, 60);

  io_loop();
  return 0;
}

#else

#include <windows.h>

extern __declspec(dllimport) main(int, char **);

/*
 * Initial entry point for Win32 GUI applications, called by the C runtime.
 *
 * It should be only a wrapper for main(), since when compiled as a console
 * application, main() is called instead.
 */
int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        LPSTR lpCmdLine, int nCmdShow)
{
  /* Do we really need these pidfile, logfile etc arguments?
   * And we are not on a console, so -help or -foreground is meaningless. */

  char *argv[2] = {"ircd", NULL};

  return main(1, argv);
}

#endif

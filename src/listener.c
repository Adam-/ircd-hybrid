/*
 *  ircd-hybrid: an advanced Internet Relay Chat Daemon(ircd).
 *  listener.c: Listens on a port, initialization of local clients.
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

#include "stdinc.h"
#include "conf/conf.h"
#include "ircd_defs.h"
#include "listener.h"
#include "client.h"
#include "hash.h"
#include "ircd.h"
#include "send.h"
#ifdef HAVE_LIBCRYPTO
#include <openssl/bio.h>
#endif
#include "s_auth.h"

static PF accept_connection;

static dlink_list ListenerPollList = { NULL, NULL, 0 };
static void close_listener(struct Listener *);
static void add_connection(struct Listener *, struct irc_ssaddr *, int);


const dlink_list *
listener_get_list(void)
{
  return &ListenerPollList;
}

static struct Listener *
make_listener(int port, struct irc_ssaddr *addr)
{
  struct Listener *listener = MyMalloc(sizeof(struct Listener));
  assert(listener != 0);

  listener->name = me.name;
  listener->port = port;

  memcpy(&listener->addr, addr, sizeof(struct irc_ssaddr));

  return listener;
}

void
free_listener(struct Listener *listener)
{
  assert(listener != NULL);

  if (listener == NULL)
    return;

  dlinkDelete(&listener->listener_node, &ListenerPollList);
  MyFree(listener);
}

/*
 * get_listener_name - return displayable listener name and port
 * returns "host.foo.org:6667" for a given listener
 */
const char *
get_listener_name(const struct Listener *const listener)
{
  static char buf[HOSTLEN + HOSTLEN + PORTNAMELEN + 4];

  assert(listener != NULL);

  ircsprintf(buf, "%s[%s/%u]", me.name, listener->name,
             listener->port);
  return buf;
}

/*
 * inetport - create a listener socket in the AF_INET or AF_INET6 domain,
 * bind it to the port given in 'port' and listen to it
 * returns true (1) if successful false (0) on error.
 *
 * If the operating system has a define for SOMAXCONN, use it, otherwise
 * use HYBRID_SOMAXCONN
 */
#ifdef SOMAXCONN
#undef HYBRID_SOMAXCONN
#define HYBRID_SOMAXCONN SOMAXCONN
#endif

static int 
inetport(struct Listener *listener)
{
  struct irc_ssaddr lsin;
  socklen_t opt = 1;

  /*
   * At first, open a new socket
   */
  if (comm_open(&listener->fd, listener->addr.ss.sin_family, SOCK_STREAM, 0,
                "Listener socket") == -1)
  {
    report_error(L_ALL, "opening listener socket %s:%s",
                 get_listener_name(listener), errno);
    return 0;
  }

  memset(&lsin, 0, sizeof(lsin));
  memcpy(&lsin, &listener->addr, sizeof(struct irc_ssaddr));
  
  irc_getnameinfo((struct sockaddr *)&lsin, lsin.ss_len, listener->vhost, 
                  HOSTLEN, NULL, 0, NI_NUMERICHOST);
  listener->name = listener->vhost;

  /*
   * XXX - we don't want to do all this crap for a listener
   * set_sock_opts(listener);
   */
  if (setsockopt(listener->fd.fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
  {
#ifdef _WIN32
    errno = WSAGetLastError();
#endif
    report_error(L_ALL, "setting SO_REUSEADDR for listener %s:%s",
                 get_listener_name(listener), errno);
    fd_close(&listener->fd);
    return(0);
  }

  /*
   * Bind a port to listen for new connections if port is non-null,
   * else assume it is already open and try get something from it.
   */
  lsin.ss_port = htons(listener->port);

  if (bind(listener->fd.fd, (struct sockaddr *)&lsin, lsin.ss_len))
  {
#ifdef _WIN32
    errno = WSAGetLastError();
#endif
    report_error(L_ALL, "binding listener socket %s:%s",
                 get_listener_name(listener), errno);
    fd_close(&listener->fd);
    return(0);
  }

  if (listen(listener->fd.fd, HYBRID_SOMAXCONN))
  {
#ifdef _WIN32
    errno = WSAGetLastError();
#endif
    report_error(L_ALL, "listen failed for %s:%s",
                 get_listener_name(listener), errno);
    fd_close(&listener->fd);
    return 0;
  }

  /* Listen completion events are READ events .. */

  accept_connection(&listener->fd, listener);
  return 1;
}

struct Listener *
find_listener(int port, struct irc_ssaddr *addr)
{
  dlink_node *ptr;
  struct Listener *listener    = NULL;
  struct Listener *last_closed = NULL;

  DLINK_FOREACH(ptr, ListenerPollList.head)
  {
    listener = ptr->data;

    if ((port == listener->port) &&
        (!memcmp(addr, &listener->addr, sizeof(struct irc_ssaddr))))
    {
      /* Try to return an open listener, otherwise reuse a closed one */
      if (!listener->fd.flags.open)
        last_closed = listener;
      else
        return (listener);
    }
  }

  return (last_closed);
}

/*
 * add_listener- create a new listener
 * port - the port number to listen on
 * vhost_ip - if non-null must contain a valid IP address string in
 * the format "255.255.255.255"
 */
void 
add_listener(int port, const char *vhost_ip, unsigned int flags)
{
  struct Listener *listener;
  struct irc_ssaddr vaddr;
  struct addrinfo hints, *res;
  char portname[PORTNAMELEN + 1];
#ifdef IPV6
  static short int pass = 0; /* if ipv6 and no address specified we need to
				have two listeners; one for each protocol. */
#endif

  /*
   * if no or invalid port in conf line, don't bother
   */
  if (!(port > 0 && port <= 0xFFFF))
    return;

  memset(&vaddr, 0, sizeof(vaddr));

  /* Set up the hints structure */
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  /* Get us ready for a bind() and don't bother doing dns lookup */
  hints.ai_flags = AI_PASSIVE | AI_NUMERICHOST;

#ifdef IPV6
  if (ServerInfo.can_use_v6)
  {
    snprintf(portname, PORTNAMELEN, "%d", port);
    irc_getaddrinfo("::", portname, &hints, &res);
    vaddr.ss.sin_family = AF_INET6;
    assert(res != NULL);

    memcpy((struct sockaddr*)&vaddr, res->ai_addr, res->ai_addrlen);
    vaddr.ss_port = port;
    vaddr.ss_len = res->ai_addrlen;
    irc_freeaddrinfo(res);
  }
  else
#endif
  {
    struct sockaddr_in *v4 = (struct sockaddr_in*) &vaddr;
    v4->sin_addr.s_addr = INADDR_ANY;
    vaddr.ss.sin_family = AF_INET;
    vaddr.ss_len = sizeof(struct sockaddr_in);
    v4->sin_port = htons(port);
  }

  snprintf(portname, PORTNAMELEN, "%d", port);

  if (vhost_ip)
  {
    if (irc_getaddrinfo(vhost_ip, portname, &hints, &res))
        return;

    assert(res != NULL);

    memcpy((struct sockaddr*)&vaddr, res->ai_addr, res->ai_addrlen);
    vaddr.ss_port = port;
    vaddr.ss_len = res->ai_addrlen;
    irc_freeaddrinfo(res);
  }
#ifdef IPV6
  else if (pass == 0 && ServerInfo.can_use_v6)
  {
    /* add the ipv4 listener if we havent already */
    pass = 1;
    add_listener(port, "0.0.0.0", flags);
  }
  pass = 0;
#endif

  if ((listener = find_listener(port, &vaddr)))
  {
    listener->flags = flags;
    if (listener->fd.flags.open)
      return;
  }
  else
  {
    listener = make_listener(port, &vaddr);
    dlinkAdd(listener, &listener->listener_node, &ListenerPollList);
    listener->flags = flags;
  }

  if (inetport(listener))
    listener->active = 1;
  else
    close_listener(listener);
}

/*
 * close_listener - close a single listener
 */
static void
close_listener(struct Listener *listener)
{
  assert(listener != NULL);

  if (listener == NULL)
    return;

  if (listener->fd.flags.open)
    fd_close(&listener->fd);

  listener->active = 0;

  if (listener->ref_count)
    return;

  free_listener(listener);
}

/*
 * close_listeners - close and free all listeners that are not being used
 */
void 
close_listeners(void)
{
  dlink_node *ptr = NULL, *next_ptr = NULL;

  /* close all 'extra' listening ports we have */
  DLINK_FOREACH_SAFE(ptr, next_ptr, ListenerPollList.head)
    close_listener(ptr->data);
}

#define TOOFAST_WARNING "ERROR :Trying to reconnect too fast.\r\n"
#define DLINE_WARNING "ERROR :You have been D-lined.\r\n"

static void 
accept_connection(fde_t *pfd, void *data)
{
  static time_t last_oper_notice = 0;
  struct irc_ssaddr addr;
  int fd, pe;
  struct Listener *listener = data;

  memset(&addr, 0, sizeof(addr));

  assert(listener != NULL);

  /* There may be many reasons for error return, but
   * in otherwise correctly working environment the
   * probable cause is running out of file descriptors
   * (EMFILE, ENFILE or others?). The man pages for
   * accept don't seem to list these as possible,
   * although it's obvious that it may happen here.
   * Thus no specific errors are tested at this
   * point, just assume that connections cannot
   * be accepted until some old is closed first.
   */
  while ((fd = comm_accept(pfd, &addr)) != -1)
  {
    /*
     * check for connection limit
     */
    if (number_fd > hard_fdlimit - 10)
    {
      ++ServerStats.is_ref;
      /*
       * slow down the whining to opers bit
       */
      if ((last_oper_notice + 20) <= CurrentTime)
      {
        sendto_realops_flags(UMODE_ALL, L_ALL, "All connections in use. (%s)",
                             get_listener_name(listener));
        last_oper_notice = CurrentTime;
      }

      if (!(listener->flags & LISTENER_SSL))
        send(fd, "ERROR :All connections in use\r\n", 32, 0);
#ifdef _WIN32
      closesocket(fd);
#else
      close(fd);
#endif
      break;    /* jump out and re-register a new io request */
    }

    /* Do an initial check we aren't connecting too fast or with too many
     * from this IP... */
    if ((pe = ip_connect_allowed(&addr)))
    {
      ++ServerStats.is_ref;

      if (!(listener->flags & LISTENER_SSL))
        switch (pe)
        {
          case BANNED_CLIENT:
            send(fd, DLINE_WARNING, sizeof(DLINE_WARNING)-1, 0);
            break;
          case TOO_FAST:
            send(fd, TOOFAST_WARNING, sizeof(TOOFAST_WARNING)-1, 0);
            break;
        }

#ifdef _WIN32
      closesocket(fd);
#else
      close(fd);
#endif
      continue;    // drop the one and keep on clearing the queue
    }

    ++ServerStats.is_ac;
    add_connection(listener, &addr, fd);
  }

  /* Re-register a new IO request for the next accept .. */
  comm_setselect(&listener->fd, COMM_SELECT_READ, accept_connection,
                  listener, 0);
}

#ifdef HAVE_LIBCRYPTO
/*
 * ssl_handshake - let OpenSSL initialize the protocol. Register for
 * read/write events if necessary.
 */
static void
ssl_handshake(int fd, struct Client *client_p)
{
  int ret = SSL_accept(client_p->localClient->fd.ssl);

  if (ret <= 0)
    switch (SSL_get_error(client_p->localClient->fd.ssl, ret))
    {
      case SSL_ERROR_WANT_WRITE:
        comm_setselect(&client_p->localClient->fd, COMM_SELECT_WRITE,
                       (PF *) ssl_handshake, client_p, 0);
        return;

      case SSL_ERROR_WANT_READ:
        comm_setselect(&client_p->localClient->fd, COMM_SELECT_READ,
                       (PF *) ssl_handshake, client_p, 0);
        return;

      default:
        exit_client(client_p, client_p, "Error during SSL handshake");
        return;
    }

  execute_callback(auth_cb, client_p);
}
#endif

/*
 * add_connection - creates a client which has just connected to us on
 * the given fd. The sockhost field is initialized with the ip# of the host.
 * An unique id is calculated now, in case it is needed for auth.
 * The client is sent to the auth module for verification, and not put in
 * any client list yet.
 */
static void
add_connection(struct Listener *listener, struct irc_ssaddr *irn, int fd)
{
  struct Client *new_client = make_client(NULL);

  assert(listener);
  assert(irn && fd >= 0);

  fd_open(&new_client->localClient->fd, fd, 1,
          (listener->flags & LISTENER_SSL) ?
          "Incoming SSL connection" : "Incoming connection");

  /*
   * copy address to 'sockhost' as a string, copy it to host too
   * so we have something valid to put into error messages...
   */
  memcpy(&new_client->localClient->ip, irn, sizeof(struct irc_ssaddr));

  irc_getnameinfo((struct sockaddr *)&new_client->localClient->ip,
        new_client->localClient->ip.ss_len,  new_client->sockhost,
        sizeof(new_client->sockhost), NULL, 0, NI_NUMERICHOST);

  new_client->localClient->aftype = new_client->localClient->ip.ss.sin_family;

#ifdef IPV6
  if (*new_client->sockhost == ':')
    strlcat(new_client->host, "0", HOSTLEN+1);

  if (new_client->localClient->aftype == AF_INET6 &&
      ConfigFileEntry.dot_in_ip6_addr == 1)
  {
    strlcat(new_client->host, new_client->sockhost,HOSTLEN+1);
    strlcat(new_client->host, ".", HOSTLEN+1);
  } else
#endif
    strlcat(new_client->host, new_client->sockhost,HOSTLEN+1);

  new_client->localClient->listener = listener;
  ++listener->ref_count;

#ifdef HAVE_LIBCRYPTO
  if (listener->flags & LISTENER_SSL)
  {
    if ((new_client->localClient->fd.ssl = SSL_new(ServerInfo.ctx)) == NULL)
    {
      ilog(L_CRIT, "SSL_new() ERROR! -- %s",
           ERR_error_string(ERR_get_error(), NULL));

      SetDead(new_client);
      exit_client(new_client, new_client, "SSL_new failed");
      return;
    }

    SSL_set_fd(new_client->localClient->fd.ssl, fd);
    ssl_handshake(0, new_client);
  }
  else
#endif
    execute_callback(auth_cb, new_client);
}

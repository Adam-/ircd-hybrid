#include "stdinc.h"
#include "ircd_defs.h"
#include "irc_string.h"
#include "send.h"
#include "client.h"
#include "msg.h"


void
msg_init(struct msg *msg, struct Client *source, const char *command)
{
  memset(msg, 0, sizeof(*msg));
  msg->source = source;
  msg->command = command;
}

void
msg_init_numeric(struct msg *msg, struct Client *source, int num, struct Client *target)
{
  memset(msg, 0, sizeof(*msg));
  msg->source = source;
  msg->numeric = num;
  msg->target = target;
}

void
msg_push(struct msg *msg, const char *name, enum param_type type, const void *value)
{
  struct param *p;

  assert(msg->paramcount < 128);

  p = &msg->params[msg->paramcount++];
  p->name = xstrdup(name);
  p->type = type;
  p->u.value = value;
}

void
msg_push_last(struct msg *msg)
{
  struct param *p;

  assert(msg->paramcount < 128);

  p = &msg->params[msg->paramcount++];
  p->type = PARAM_TYPE_LAST;
}

void
msg_push_fmt(struct msg *msg, const char *name, const char *pattern, ...)
{
  va_list args;
  char nbuf[IRCD_BUFSIZE];

  va_start(args, pattern);
  vsnprintf(nbuf, sizeof(nbuf), pattern, args);
  va_end(args);

  msg_push_str(msg, name, nbuf);
}

void
msg_push_str(struct msg *msg, const char *name, const char *value)
{
  value = xstrdup(value);
  msg_push(msg, name, PARAM_TYPE_STRING, value);
}

static int
msg_build_part(struct msg *msg, int from)
{
  int i;
  struct dbuf_block *user, *server;

  user = dbuf_alloc();
  server = dbuf_alloc();

  if (msg->source)
  {
    dbuf_put_fmt(user, ":%s ", msg->source->name);
    dbuf_put_fmt(server, ":%s ", msg->source->id);
  }

  if (msg->command)
  {
    dbuf_put_fmt(user, "%s ", msg->command);
    dbuf_put_fmt(server, "%s ", msg->command);
  }
  else
  {
    dbuf_put_fmt(user, "%03d %s ", msg->numeric, msg->target->name);
    dbuf_put_fmt(server, "%03d %s ", msg->numeric, msg->target->id);
  }

  for (i = 0; i < msg->paramcount; ++i)
  {
    struct param *p = &msg->params[i];
    const char *users = "", *servers = "";

    switch (p->type)
    {
      case PARAM_TYPE_LAST:
        users = servers = ":";
        if (from)
          i = from;
        break;
      case PARAM_TYPE_STRING:
        users = servers = p->u.string;
        break;
      case PARAM_TYPE_CLIENT:
        users = p->u.client->name;
        servers = p->u.client->id;
        break;
      case PARAM_TYPE_CHANNEL:
        users = servers = p->u.channel->chname;
        break;
      default:
        assert(0);
    }

    if ((user->size + strlen(users) > IRCD_BUFSIZE - 3) /* for the space + \r\n */
        || (server->size + strlen(servers) > IRCD_BUFSIZE - 3))
      break;

    dbuf_put_fmt(user, "%s ", users);
    dbuf_put_fmt(server, "%s ", servers);
  }

  /* remove trailing space */
  --user->size;
  --server->size;

  dbuf_put_fmt(user, "%s", "\r\n");
  dbuf_put_fmt(server, "%s", "\r\n");

  dlinkAdd(user, make_dlink_node(), &msg->user);
  dlinkAdd(server, make_dlink_node(), &msg->server);

  return i;
}


void
msg_build(struct msg *msg)
{
  int i = 0;

  while (i < msg->paramcount)
    i = msg_build_part(msg, i);
}

void
msg_free(struct msg *msg)
{
}


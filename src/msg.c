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

#if 0
void
msg_push_client(struct msg *msg, const char *name, struct Client *client)
{
}





void
msgwrap_init(struct msgwrap *msg, struct msg *msg)
{
}

void
msgwrap_push(struct msgwrap *msg, const char *value)
{
}



void
splitbuf_init(struct splitbuf *buf, int params, int maxparams, const char *fmt, ...)
{
  va_list args;
  struct dbuf_block *block;

  memset(buf, 0, sizeof(*buf));
  
  block = dbuf_alloc();
  va_start(args, fmt);
  dbuf_put_args(block, fmt, args);
  va_end(args);

  dbuf_add(&buf->queue, block);
  dbuf_ref_free(block);

  buf->start = dbuf_length(&buf->queue);
  buf->params = params; /* number of params given to us already from the init string */
  buf->maxparams = maxparams; /* maximum parameters we want */
}

void
splitbuf_add_fmt(struct splitbuf *sbuf, const char *fmt, ...)
{
  va_list args;
  char buf[IRCD_BUFSIZE];

  va_start(args, fmt);
  vsnprintf(buf, sizeof(buf), fmt, args);
  va_end(args);

  splitbuf_add(sbuf, buf);
}

void
splitbuf_add(struct splitbuf *buf, const char *str)
{
  struct dbuf_block *block;
  int len, total_len, last_param;

  assert(dlink_list_length(&buf->queue.blocks));

  last_param = buf->params + 1 == buf->maxparams;
  len = strlen(str);
  total_len = 1 + !last_param + len; // space + : + len

  block = buf->queue.blocks.tail->data;
  if (block->size + total_len > IRCD_BUFSIZE - 2) /* \r\n */
  {
    struct dbuf_block *first = buf->queue.blocks.head->data;

    dbuf_put(&buf->queue, "\r\n", 2);

    block = dbuf_alloc();
    dbuf_add(&buf->queue, block);
    dbuf_ref_free(block);
    dbuf_put(&buf->queue, first->data, buf->start);

    buf->params = 0;
    last_param = buf->params + 1 == buf->maxparams;
  }

  /* last param is prefixed with : */
  if (last_param)
    dbuf_put(&buf->queue, " :", 2);
  else
    dbuf_put(&buf->queue, " ", 1);

  dbuf_put(&buf->queue, str, len);

  ++buf->params;
}

void
splitbuf_finish(struct splitbuf *buf)
{
  dbuf_put(&buf->queue, "\r\n", 2);
}

void
splitbuf_send(struct splitbuf *buf, struct Client *to)
{
  dlink_node *node;
  
  DLINK_FOREACH(node, buf->queue.blocks.head)
    send_message(to, node->data);
}

void
splitbuf_end(struct splitbuf *buf)
{
  dbuf_clear(&buf->queue);
}

#endif

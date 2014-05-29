
#include "stdinc.h"
#include "splitbuf.h"
#include "ircd_defs.h"
#include "irc_string.h"
#include "send.h"

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


#include "dbuf.h"
#include "client.h"

struct splitbuf
{
  int start;
  struct dbuf_queue queue;
  int params;
  int maxparams;
};

extern void splitbuf_init(struct splitbuf *buf, int params, int maxparams, const char *fmt, ...) AFP(3, 4);
extern void splitbuf_add_fmt(struct splitbuf *buf, const char *fmt, ...) AFP(2, 3);
extern void splitbuf_add(struct splitbuf *buf, const char *str);
extern void splitbuf_finish(struct splitbuf *buf);
extern void splitbuf_send(struct splitbuf *buf, struct Client *to);
extern void splitbuf_end(struct splitbuf *buf);


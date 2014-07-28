
enum param_type
{
  PARAM_TYPE_NONE,
  PARAM_TYPE_LAST,
  PARAM_TYPE_STRING,
  PARAM_TYPE_CLIENT,
  PARAM_TYPE_CHANNEL
};

struct param
{
  const char *name;
  enum param_type type;
  union
  {
    const char *string;
    struct Client *client;
    struct Channel *channel;
    const void *value;
  } u;
};

#define MAGIC 128

struct msg
{
  struct Client *source;

  const char *command;

  int numeric;
  struct Client *target;

  int paramcount;
  struct param params[MAGIC]; // XXX magic

  /* finished buffers */
  dlink_list user;
  dlink_list server;
};


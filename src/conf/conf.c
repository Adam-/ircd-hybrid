/*
 *  ircd-hybrid: an advanced Internet Relay Chat Daemon(ircd).
 *  conf.c: Configuration manager.
 *
 *  Copyright (C) 2003 by Piotr Nizynski, Advanced IRC Services Project
 *  Copyright (C) 2005 by the Hybrid Development Team.
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
 *  $Id: conf.c 69 2005-10-04 16:09:51Z adx $
 */

#define IN_CONF_C
#include "stdinc.h"
#include "conf/conf.h"
#include "client.h"
#include "restart.h"
#include "send.h"

int conf_pass, conf_cold = YES;
struct ConfParserContext conf_curctx;
char conf_linebuf[CONF_BUFSIZE];

struct Callback *reset_conf = NULL;
struct Callback *verify_conf = NULL;
struct Callback *switch_conf_pass = NULL;

static dlink_list conf_section_list = {NULL, NULL, 0};

extern int yyparse(void);

/*
 * init_conf()
 *
 * Initializes the configuration manager.
 *
 * inputs: none
 * output: none
 */
void
init_conf(void)
{
  reset_conf = register_callback("reset_conf", NULL);
  verify_conf = register_callback("verify_conf", NULL);
  switch_conf_pass = register_callback("switch_conf_pass", NULL);

  init_serverinfo();
  init_admin();
  init_logging();
  init_class();
  init_channel();
  init_serverhide();
  init_general();
#ifndef STATIC_MODULES
  init_modules();
#endif
}

/*
 * parse_error()
 *
 * Log a parse error message.
 *
 * inputs:
 *   fmt  -  error message format
 * output: none
 */
static void
do_parse_error(int fatal, const char *fmt, va_list args)
{
  char *newbuf = stripws(conf_linebuf);
  char msg[CONF_BUFSIZE];

  vsnprintf(msg, CONF_BUFSIZE, fmt, args);

  if (conf_pass != 0)
  {
    sendto_realops_flags(UMODE_ALL, L_ALL, "\"%s\", line %u: %s: %s",
      conf_curctx.filename, conf_curctx.lineno, msg, newbuf);
    ilog(fatal ? L_CRIT : L_WARN, "\"%s\", line %u: %s: %s",
      conf_curctx.filename, conf_curctx.lineno, msg, newbuf);
  }
  else
  {
    sendto_realops_flags(UMODE_ALL, L_ALL, "Conf %s: %s",
      fatal ? "FATAL" : "ERROR", msg);
    ilog(fatal ? L_CRIT : L_WARN, "Conf %s: %s",
      fatal ? "FATAL" : "ERROR", msg);
  }
}

void
parse_error(const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  do_parse_error(NO, fmt, args);
  va_end(args);
}

void
parse_fatal(const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  do_parse_error(YES, fmt, args);
  va_end(args);

  server_die("misconfigured server", NO);
}

/*
 * yyerror()
 *
 * Log a parse error message if the current pass is 2.
 *
 * inputs:
 *   msg  -  error message
 * output: none
 */
void
_yyerror(const char *msg)
{
  if (conf_pass == 2)
    parse_error("%s", msg);
}

/*
 * conf_yy_input()
 *
 * Loads a block of data from the conf file.
 *
 * inputs:
 *   buf  -  address of destination buffer
 *   siz  -  size of the buffer
 * output: number of bytes actually read
 */
int
conf_yy_input(char *buf, int siz)
{
  return fbgets(buf, siz, conf_curctx.f) == NULL ? 0 : strlen(buf);
}

/*
 * find_conf_section()
 *
 * Finds a conf block (section) structure.
 *
 * inputs:
 *   name  -  name of the block
 * output: pointer to struct ConfSection or NULL if not found
 */
struct ConfSection *
find_conf_section(const char *name)
{
  dlink_node *ptr;
  struct ConfSection *section;

  DLINK_FOREACH(ptr, conf_section_list.head)
  {
    section = ptr->data;
    if (!strcasecmp(section->name, name))
      return section;
  }

  return NULL;
}

/*
 * add_conf_section()
 *
 * Adds a conf block (section) structure.
 *
 * inputs:
 *   name  -  name of the block
 *   pass  -  pass when the section should be parsed (1 or 2)
 * output: pointer to struct ConfSection or NULL if already exists
 */
struct ConfSection *
add_conf_section(const char *name, int pass)
{
  struct ConfSection *section;

  if (find_conf_section(name) != NULL)
    return NULL;

  section = MyMalloc(sizeof(struct ConfSection));
  section->name = name;
  section->pass = pass;
  dlinkAdd(section, &section->node, &conf_section_list);
  return section;
}

/*
 * delete_conf_section()
 *
 * Deletes a conf block (section) structure.
 *
 * inputs:
 *   section  -  pointer to ConfSection structure
 * output: none
 */
void
delete_conf_section(struct ConfSection *section)
{
  dlink_node *ptr, *ptr_next;

  DLINK_FOREACH_SAFE(ptr, ptr_next, section->fields.head)
  {
    dlinkDelete(ptr, &section->fields);
    MyFree(ptr->data);
  }

  dlinkDelete(&section->node, &conf_section_list);
}

struct ConfField *
find_conf_field(struct ConfSection *section, char *name)
{
  dlink_node *ptr;
  struct ConfField *field;

  if (section == NULL)
    return NULL;
  if (section->pass != conf_pass)
    return NULL;

  DLINK_FOREACH(ptr, section->fields.head)
  {
    field = ptr->data;
    if (!strcasecmp(field->name, name))
      return field;
  }

  parse_error("unknown field");
  return NULL;
}

/*
 * conf_assign()
 *
 * Called when a conf item (xxx = 'yyy'; form) is parsed.
 *
 * inputs:
 *   type     -  type of supplied value
 *   field    -  pointer to struct ConfField
 *   value    -  address of value data
 * output: none
 */
void
conf_assign(int type, struct ConfField *field, void *value)
{
  static char *field_types[] =
    {"NUMBER", "BOOLEAN", "TIME", "SIZE", "STRING", "LIST", "NLIST"};

  if (field == NULL)
    return;

  if (type == field->type || (type == CT_NUMBER &&
       (field->type == CT_TIME || field->type == CT_SIZE)))
  {
    if (field->handler != NULL)
      field->handler(value, field->param);
  }
  else if (type == CT_NUMBER && field->type == CT_NLIST)
  {
    dlink_list list = {NULL, NULL, 0};
    dlink_node node;

    dlinkAdd((void *) (long) (*(int *) value), &node, &list);

    if (field->handler != NULL)
      field->handler(&list, field->param);
  }
  else
    parse_error("type mismatch, expected %s", field_types[type]);
}

/*
 * conf_assign_*()
 *
 * Simple field handlers which just write a variable.
 *
 * inputs:
 *   value    - address of data
 *   var      - where to write it
 * output: none
 */
void
conf_assign_bool(void *value, void *var)
{
  *(char *) var = *(int *) value;
}

void
conf_assign_number(void *value, void *var)
{
  *(int *) var = *(int *) value;
}

void
conf_assign_string(void *value, void *var)
{
  MyFree(*(char **) var);
  DupString(*(char **) var, (char *) value);
}

/*
 * add_conf_field()
 *
 * Adds a field of type number to the given section.
 *
 * inputs:
 *   section  -  pointer to ConfSection structure
 *   name     -  name of the field
 *   type     -  type of the field as defined in conf.h
 *   handler  -  function to be called when an assignment
 *               is encountered (one argument: info)
 * output: none
 */
struct ConfField *
add_conf_field(struct ConfSection *section, const char *name, int type,
               CONFF_HANDLER *handler, void *param)
{
  struct ConfField *field = MyMalloc(sizeof(struct ConfField));

  if (handler == NULL)
    switch (type)
    {
      case CT_NUMBER:
      case CT_TIME:
      case CT_SIZE:
        handler = conf_assign_number;
        break;
      case CT_BOOL:
        handler = conf_assign_bool;
        break;
      case CT_STRING:
        handler = conf_assign_string;
        break;
      default:
        assert(0);
    }

  field->name = name;
  field->type = type;
  field->handler = handler;
  field->param = param;
  dlinkAdd(field, &field->node, &section->fields);
  return field;
}

struct ConfItem *
make_conf_item2(ConfType type)
{
  return NULL;
}

#include "estd/argparser.h"
#include "estd/estring.h"
#include "estd/grow.h"

#include <stdlib.h>
#include <string.h>

typedef struct arg_t {
  arg_type type;
  string *short_name;
  string *long_name;
  bool is_set;
  grow *values;

} cmd_arg;

static cmd_arg *cmd_arg_init(const char *short_name, const char *long_name, arg_type type);
static void cmd_arg_free(void *ptr);
static void string_free_abs(void *ptr) { string_free_((string *)ptr); }

cmd_arg *cmd_arg_init(const char *short_name, const char *long_name, arg_type type) {
  cmd_arg *arg = (cmd_arg *)malloc(sizeof(cmd_arg));
  if (!arg)
    return NULL;

  arg->short_name = short_name ? string_from_cstr(short_name) : NULL;
  arg->long_name = long_name ? string_from_cstr(long_name) : NULL;
  arg->type = type;
  arg->is_set = false;
  arg->values = grow_init_empty;
  if (!arg->values) {
    if (arg->short_name)
      string_free_(arg->short_name);
    if (arg->long_name)
      string_free_(arg->long_name);
    free(arg);

    return NULL;
  }

  return arg;
}

void cmd_arg_free(void *ptr) {
  cmd_arg *arg = (cmd_arg *)ptr;
  if (arg->short_name) {
    string_free(arg->short_name);
  }
  if (arg->long_name) {
    string_free(arg->long_name);
  }
  grow_free(arg->values, string_free_abs);
  free(arg);
}

cmd_parser *cmd_parser_create() {
  cmd_parser *parser = (cmd_parser *)malloc(sizeof(cmd_parser));
  parser->args = grow_init_empty;
  parser->arg_error = NULL;

  return parser;
}

void cmd_parser_free(cmd_parser *p) {
  grow_free(p->args, cmd_arg_free);
  if (p->arg_error)
    string_free_(p->arg_error);
  free(p);
}

static easy_error cmd_parser_set_invalid_arg(cmd_parser *p, char *arg) {
  CHECK_NULL_PTR((p && p->args && p->args->data));

  p->arg_error = string_from_cstr(arg);
  if (!p->arg_error)
    return ALLOCATION_FAILED;

  return OK;
}

easy_error cmd_parser_add(cmd_parser *p, const char *short_name, const char *long_name,
                          arg_type type) {
  CHECK_NULL_PTR((p && p->args && p->args->data));

  cmd_arg *arg = cmd_arg_init(short_name, long_name, type);
  if (!arg)
    return ALLOCATION_FAILED;

  return grow_push(p->args, arg);
}

static cmd_arg *cmd_parser_find(cmd_parser *p, const char *name) {
  // TODO:
  for (size_t i = 0; i < grow_size(p->args); ++i) {
    cmd_arg *arg = (cmd_arg *)p->args->data[i];
    if ((arg->short_name && strcmp(arg->short_name->data, name) == 0) ||
        (arg->long_name && strcmp(arg->long_name->data, name) == 0)) {
      return arg;
    }
  }

  return NULL;
}

easy_error cmd_parser_parse(cmd_parser *p, int argc, char *argv[]) {
  CHECK_NULL_PTR((p && p->args && p->args->data));
  if (!argv)
    return INVALID_ARGUMENT;

  int i = 1;
  easy_error err = OK;
  while (i < argc) {
    char *token = argv[i];
    if (token[0] == '-') {
      cmd_arg *arg = cmd_parser_find(p, token);
      if (!arg) {
        cmd_parser_set_invalid_arg(p, token);
        return PARSER_UNKOWN_ARGUMENT;
      }

      arg->is_set = true;
      if (arg->type == FLAG) {
        i++;
      } else if (arg->type == SINGLE_OPTION) {
        if (i + 1 >= argc || argv[i + 1][0] == '-') {
          cmd_parser_set_invalid_arg(p, token);
          return PARSER_NO_REQUIRED_PARAMETR;
        }

        err = grow_push(arg->values, string_from_cstr(argv[i + 1]));
        if (err != OK)
          return err;

        i += 2;
      } else if (arg->type == MULTIPLE_OPTION) {
        int j = i + 1;
        while (j < argc && argv[j][0] != '-') {
          err = grow_push(arg->values, string_from_cstr(argv[j]));
          if (err != OK)
            return err;
          j++;
        }

        if (grow_size(arg->values) == 0) {
          cmd_parser_set_invalid_arg(p, token);
          return PARSER_NO_PASSED_PARAMETRS;
        }
        i = j;
      }

    } else {
      cmd_parser_set_invalid_arg(p, token);
      return PARSER_UNEXPECTED_VALUE;
    }
  }

  return OK;
}

bool cmd_is_set(cmd_parser *p, const char *name, easy_error *err) {
  cmd_arg *arg = cmd_parser_find(p, name);
  if (!arg) {
    SET_CODE_ERROR(err, INVALID_ARGUMENT);
    return false;
  }

  SET_CODE_ERROR(err, OK);
  return arg->is_set;
}

const string *cmd_get_value(cmd_parser *p, const char *name, easy_error *err) {
  cmd_arg *arg = cmd_parser_find(p, name);
  if (!arg) {
    SET_CODE_ERROR(err, INVALID_ARGUMENT);
    return NULL;
  }

  return (string *)grow_get(arg->values, 0, err);
}

const grow *cmd_get_values(cmd_parser *p, const char *name, easy_error *err) {
  cmd_arg *arg = cmd_parser_find(p, name);
  if (!arg) {
    SET_CODE_ERROR(err, INVALID_ARGUMENT);
    return NULL;
  }

  SET_CODE_ERROR(err, OK);
  return arg->values;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eerror.h"
#include "estring.h"

easy_error string_init_emtpy(string *str) {
  CHECK_NULL_PTR(str);

  str->capacity = 16;
  str->length = 0;
  str->data = malloc(str->capacity);

  CHECK_ALLOCATION(str->data);

  str->data[0] = '\0';

  return OK;
}

easy_error string_from_cstr(string *str, const char *cstr) {
  CHECK_NULL_PTR(str);

  if (!cstr)
    return INVALID_ARGUMENT;

  size_t len = strlen(cstr);
  str->length = len;
  str->capacity = len + 1;
  str->data = malloc(str->capacity);

  CHECK_ALLOCATION(str->data);

  memcpy(str->data, cstr, str->capacity);

  return OK;
}

string string_create(const char *cstr) {
  string str;
  (cstr && !cstr[0]) ? string_init_emtpy(&str) : string_from_cstr(&str, cstr);
  return str;
}

void string_free(string *str) {
  free(str->data);
  str->data = NULL;
  str->length = str->capacity = 0;
}

void string_free_abs(void *str) { string_free(str); }

easy_error string_reserve(string *str, size_t new_capacity) {
  CHECK_NULL_PTR(str);

  if (new_capacity <= str->capacity)
    return OK;

  char *new_data = realloc(str->data, new_capacity);
  CHECK_ALLOCATION(new_data);

  str->data = new_data;
  str->capacity = new_capacity;

  return OK;
}

easy_error string_append(string *str, const char *cstr) {
  CHECK_NULL_PTR(str);

  if (!cstr)
    return INVALID_ARGUMENT;

  size_t cstr_len = strlen(cstr);
  size_t new_length = str->length + cstr_len;

  if (new_length + 1 > str->capacity) {
    size_t new_capacity = (new_length + 1) * 2;

    easy_error err = string_reserve(str, new_capacity);
    if (err != 0)
      return err;
  }

  memcpy(str->data + str->length, cstr, cstr_len + 1);
  str->length = new_length;

  return OK;
}

char string_at(string *str, size_t index, easy_error *err) {
  if (!err)
    return '\0';

  if (!str) {
    *err = NULL_POINTER;
    return '\0';
  }

  if (index >= str->length) {
    *err = INVALID_INDEX;
    return '\0';
  }

  *err = OK;
  return str->data[index];
}

const char *string_cstr(const string *str) { return (str) ? str->data : NULL; }

bool string_compare(string *str1, string *str2, easy_error *err) {
  if (!err)
    return false;

  if (!str1 || !str2) {
    *err = NULL_POINTER;
    return false;
  }

  *err = OK;
  return strcmp(str1->data, str2->data) == 0;
}

easy_error string_insert(string *str, size_t pos, const char *cstr) {
  CHECK_NULL_PTR(str);

  if (!cstr)
    return INVALID_ARGUMENT;

  if (pos > str->length)
    return INVALID_INDEX;

  size_t cstr_len = strlen(cstr);
  size_t new_length = str->length + cstr_len;

  if (new_length + 1 > str->capacity) {
    size_t new_capacity = (new_length + 1) * 2;

    easy_error err = string_reserve(str, new_capacity);
    if (err != 0)
      return err;
  }

  memmove(str->data + pos + cstr_len, str->data + pos, str->length - pos + 1);
  memcpy(str->data + pos, cstr, cstr_len);
  str->length = new_length;

  return OK;
}

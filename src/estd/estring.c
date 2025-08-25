#include <stdlib.h>
#include <string.h>

#include "estd/estring.h"
#include "estd/global.h"

static int *bad_char_table(const char *F) {
  if (!F)
    return NULL;

  int *table = (int *)malloc(256 * sizeof(int)); // 256 for everu ASCII char
  for (size_t i = 0; i < 256; i++)
    table[i] = -1;

  for (size_t i = 0; i < strlen(F); i++)
    table[(unsigned char)F[i]] = i;

  return table;
}

int boyer_moore_search(const char *T, const char *F) {
  if (!T || !F)
    return NULL_POINTER;

  size_t n = strlen(T);
  size_t m = strlen(F);
  int pos = -1;

  int *bad_char = bad_char_table(F);
  size_t s = 0;
  while (s <= n - m) {
    int j = m - 1;
    while (j >= 0 && F[j] == T[s + j])
      j--;
    if (j < 0) {
      pos = s;
      break;
    } else {
      int bad_char_shift = j - bad_char[(unsigned char)T[s + j]];
      s += EMAX(1, bad_char_shift);
    }
  }
  free(bad_char);

  return pos;
}

string *string_init_empty() {
  string *str = (string *)malloc(sizeof(string));

  str->capacity = 16;
  str->length = 0;
  str->data = malloc(str->capacity);

  str->data[0] = '\0';

  return str;
}

string *string_from_cstr(const char *cstr) {
  if (!cstr)
    return NULL;

  string *str = (string *)malloc(sizeof(string));

  size_t len = strlen(cstr);
  str->length = len;
  str->capacity = len + 1;
  str->data = malloc(str->capacity);

  memcpy(str->data, cstr, str->capacity);

  return str;
}

string *string_create(const char *cstr) {
  return (cstr && !cstr[0]) ? string_init_empty() : string_from_cstr(cstr);
}

void string_free(string *str) {
  free(str->data);
  str->data = NULL;
  str->length = str->capacity = 0;
  free(str);
}

void string_free_abs(void *str) { string_free((string *)str); }

easy_error string_reserve(string *str, size_t new_capacity) {
  CHECK_NULL_PTR((str && str->data));

  if (new_capacity <= str->capacity)
    return OK;

  char *new_data = realloc(str->data, new_capacity);
  CHECK_ALLOCATION(new_data);

  str->data = new_data;
  str->capacity = new_capacity;

  return OK;
}

easy_error string_append(string *str, const char *cstr) {
  CHECK_NULL_PTR((str && str->data));

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
  if (!str || !str->data) {
    SET_CODE_ERROR(err, NULL_POINTER);
    return '\0';
  }

  if (index >= str->length) {
    SET_CODE_ERROR(err, INVALID_INDEX);
    return '\0';
  }

  SET_CODE_ERROR(err, OK);

  return str->data[index];
}

const char *string_cstr(const string *str) { return (str && str->data) ? str->data : NULL; }

int string_find(string *str, const char *fragment) {
  CHECK_NULL_PTR((str && str->data));
  if (!fragment)
    return INVALID_ARGUMENT;

  return boyer_moore_search(string_cstr(str), fragment);
}

int string_compare(const void *str1, const void *str2) {
  if (!str1 || !str2)
    return NULL_POINTER;

  void *ptrA = *(void **)str1;
  void *ptrB = *(void **)str2;

  string *arg1 = *(string **)ptrA;
  string *arg2 = *(string **)ptrB;

  return strcmp(arg1->data, arg2->data);
}

bool string_compare_bool(string *str1, string *str2, easy_error *err) {
  if (!str1 || !str1->data || !str2 || !str2->data) {
    SET_CODE_ERROR(err, NULL_POINTER);
    return false;
  }

  SET_CODE_ERROR(err, OK);

  return strcmp(str1->data, str2->data) == 0;
}

easy_error string_insert(string *str, size_t pos, const char *cstr) {
  CHECK_NULL_PTR((str && str->data));

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

easy_error string_clear(string *str) {
  CHECK_NULL_PTR((str && str->data));

  free(str->data);
  char *new_data = malloc(sizeof(char));
  CHECK_ALLOCATION(new_data);

  new_data[0] = '\0';
  str->length = 0;
  str->capacity = 1;
  str->data = new_data;

  return OK;
}

easy_error string_shrink_to_fit(string *str) {
  CHECK_NULL_PTR((str && str->data));

  size_t new_capacity = str->length + 1;

  if (str->capacity == new_capacity)
    return OK;

  char *new_data = realloc(str->data, new_capacity);
  CHECK_ALLOCATION(new_data);

  str->data = new_data;
  str->capacity = new_capacity;

  return OK;
}

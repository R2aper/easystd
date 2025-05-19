#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "eerror.h"

array *array_init(size_t size) {
  array *arr = (array *)malloc(sizeof(array));
  arr->data = (void **)calloc(size, sizeof(void *));

  arr->size = size;
  return arr;
}

void array_free(array *arr, void(free_fn)(void *)) {
  free(arr->data);
  arr->data = NULL;
  arr->size = 0;
  free(arr);
}

void *array_get(array *arr, size_t index, easy_error *err) {
  if (!(arr && arr->data)) {
    SET_CODE_ERROR(err, NULL_POINTER);
    return NULL;
  }

  if (index >= arr->size) {
    SET_CODE_ERROR(err, INVALID_INDEX);
    return NULL;
  }

  SET_CODE_ERROR(err, OK);
  return arr->data[index];
}

easy_error array_set(array *arr, size_t index, void *element) {
  CHECK_NULL_PTR((arr && arr->data));

  if (!element)
    return INVALID_ARGUMENT;

  if (index >= arr->size)
    return INVALID_INDEX;

  arr->data[index] = element;
  return OK;
}

easy_error array_qsort(array *arr, int(compare_fn)(const void *, const void *)) {
  CHECK_NULL_PTR((arr && arr->data));

  if (!compare_fn)
    return INVALID_ARGUMENT;

  qsort(arr->data, arr->size, sizeof(void *), compare_fn);

  return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "eerror.h"

easy_error array_init(array *ar, size_t element_size, size_t initial_capacity,
                      void (*free_fn)(void *)) {
  CHECK_NULL_PTR(ar);

  ar->data = malloc(sizeof(void *) * initial_capacity);

  CHECK_ALLOCATION(ar->data);

  ar->size = 0;
  ar->capacity = initial_capacity;
  ar->element_size = element_size;
  ar->free_fn = free_fn;

  return OK;
}

void array_free(array *ar) {
  for (size_t i = 0; i < ar->size; i++) {
    if (ar->free_fn)
      ar->free_fn(ar->data[i]);

    free(ar->data[i]);
  }

  free(ar->data);
  ar->data = NULL;
  ar->size = 0;
  ar->capacity = 0;
}

easy_error array_push(array *ar, const void *element) {
  CHECK_NULL_PTR(ar && ar->data);

  if (!element)
    return INVALID_ARGUMENT;

  if (ar->size >= ar->capacity)
    return ARRAY_OVERFLOW;

  void *new_element = malloc(ar->element_size);
  CHECK_ALLOCATION(new_element);

  memcpy(new_element, element, ar->element_size);
  ar->data[ar->size++] = new_element;

  return OK;
}

void *array_get(array *ar, size_t index, easy_error *err) {
  if (!(ar && ar->data)) {
    SET_CODE_ERROR(err, NULL_POINTER);
    return NULL;
  }

  if (index >= ar->size) {
    SET_CODE_ERROR(err, INVALID_INDEX);
    return NULL;
  }

  SET_CODE_ERROR(err, OK);

  return ar->data[index];
}

easy_error array_remove(array *ar, size_t index) {
  CHECK_NULL_PTR(ar && ar->data);

  if (index >= ar->size)
    return INVALID_INDEX;

  if (ar->free_fn)
    ar->free_fn(ar->data[index]);

  free(ar->data[index]);

  memmove(&ar->data[index], &ar->data[index + 1], (ar->size - index - 1) * sizeof(void *));

  ar->size--;

  return OK;
}

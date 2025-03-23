#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eerror.h"
#include "grow.h"

easy_error grow_init(grow *gr, size_t element_size, size_t initial_capacity,
                     void (*free_fn)(void *)) {

  CHECK_NULL_PTR(gr);

  gr->data = malloc(sizeof(void *) * initial_capacity);

  CHECK_ALLOCATION(gr->data);

  gr->size = 0;
  gr->capacity = initial_capacity;
  gr->element_size = element_size;
  gr->free_fn = free_fn;

  return OK;
}

void grow_free(grow *gr) {
  for (size_t i = 0; i < gr->size; i++) {
    if (gr->free_fn)
      gr->free_fn(gr->data[i]);

    free(gr->data[i]);
  }

  free(gr->data);
  gr->data = NULL;
  gr->size = 0;
  gr->capacity = 0;
}

easy_error grow_push(grow *gr, const void *element) {
  CHECK_NULL_PTR(gr);

  if (!element)
    return INVALID_ARGUMENT;

  if (gr->size >= gr->capacity) {
    gr->capacity *= 2;
    gr->data = realloc(gr->data, sizeof(void *) * gr->capacity);
    CHECK_ALLOCATION(gr->data);
  }

  void *new_element = malloc(gr->element_size);
  CHECK_ALLOCATION(new_element);

  memcpy(new_element, element, gr->element_size);
  gr->data[gr->size++] = new_element;

  return OK;
}

void *grow_get(grow *gr, size_t index, easy_error *err) {
  if (!err)
    return NULL;

  if (!gr) {
    *err = NULL_POINTER;
    return NULL;
  }

  if (index >= gr->size) {
    *err = INVALID_INDEX;
    return NULL;
  }

  *err = OK;
  return gr->data[index];
}

easy_error grow_remove(grow *gr, size_t index) {
  CHECK_NULL_PTR(gr);

  if (index >= gr->size)
    return INVALID_INDEX;

  if (gr->free_fn)
    gr->free_fn(gr->data[index]);

  free(gr->data[index]);

  memmove(&gr->data[index], &gr->data[index + 1], (gr->size - index - 1) * sizeof(void *));

  gr->size--;

  return OK;
}

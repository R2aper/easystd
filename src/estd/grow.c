#include <stdlib.h>
#include <string.h>

#include "estd/eerror.h"
#include "estd/grow.h"

grow *grow_init(size_t initial_capacity) {
  grow *gr = (grow *)malloc(sizeof(grow));
  if (!gr)
    return NULL;

  gr->size = 0;
  gr->capacity = (initial_capacity > 0) ? initial_capacity : 16;
  gr->data = (void **)calloc(gr->capacity, sizeof(void *));
  if (!gr->data) {
    free(gr);
    return NULL;
  }

  return gr;
}

void grow_free_(grow *gr, void(free_fn)(void *)) {
  if (free_fn) {
    for (size_t i = 0; i < gr->size; i++)

      free_fn(gr->data[i]);
  }
  free(gr->data);
  gr->data = NULL;
  gr->size = 0;
  gr->capacity = 0;
  free(gr);
}

easy_error grow_push(grow *gr, void *element) {
  CHECK_NULL_PTR((gr && gr->data));

  if (!element)
    return INVALID_ARGUMENT;

  if (gr->size >= gr->capacity) {
    gr->capacity *= 2;
    gr->data = (void **)realloc(gr->data, sizeof(void *) * gr->capacity);
    CHECK_ALLOCATION(gr->data);
  }

  gr->data[gr->size++] = element;

  return OK;
}

easy_error grow_insert(grow *gr, size_t index, void *element) {
  CHECK_NULL_PTR((gr && gr->data));

  if (!element)
    return INVALID_ARGUMENT;

  if (index >= gr->size)
    return INVALID_INDEX;

  if (gr->size + 1 > gr->capacity) {
    size_t new_capacity = (gr->capacity == 0) ? 16 : gr->capacity * 2;
    void **new_data = (void **)realloc(gr->data, sizeof(void *) * new_capacity);
    CHECK_ALLOCATION(new_data);

    gr->data = new_data;
    gr->capacity = new_capacity;
  }

  memmove(&gr->data[index + 1], &gr->data[index], (gr->size - index) * sizeof(void *));

  gr->data[index] = element;
  gr->size++;

  return OK;
}

easy_error grow_set(grow *gr, size_t index, void *element) {
  CHECK_NULL_PTR((gr && gr->data));

  if (!element)
    return INVALID_ARGUMENT;

  if (index >= gr->size)
    return INVALID_INDEX;

  gr->data[index] = element;

  return OK;
}

void *grow_get(const grow *gr, size_t index, easy_error *err) {
  if (!(gr && gr->data)) {
    SET_CODE_ERROR(err, NULL_POINTER);
    return NULL;
  }

  if (index >= gr->size) {
    SET_CODE_ERROR(err, INVALID_INDEX);
    return NULL;
  }

  SET_CODE_ERROR(err, OK);

  return gr->data[index];
}

easy_error grow_remove(grow *gr, size_t index, void(free_fn)(void *)) {
  CHECK_NULL_PTR((gr && gr->data));

  if (index >= gr->size)
    return INVALID_INDEX;

  if (free_fn)
    free_fn(gr->data[index]);

  if (index < gr->size - 1)
    memmove(&gr->data[index], &gr->data[index + 1], (gr->size - index - 1) * sizeof(void *));

  gr->size--;

  return OK;
}

easy_error grow_qsort(grow *gr, int(compare_fn)(const void *, const void *)) {
  CHECK_NULL_PTR((gr && gr->data));

  if (!compare_fn)
    return INVALID_ARGUMENT;

  qsort(gr->data, gr->size, sizeof(void *), compare_fn);

  return OK;
}

easy_error grow_resize(grow *gr, size_t new_capacity) {
  CHECK_NULL_PTR((gr && gr->data));

  if (new_capacity <= gr->capacity)
    return OK;

  void **new_data = (void **)realloc(gr->data, new_capacity * sizeof(void *));
  CHECK_ALLOCATION(new_data);

  gr->capacity = new_capacity;
  gr->data = new_data;

  return OK;
}

easy_error grow_shrink_to_fit(grow *gr) {
  CHECK_NULL_PTR((gr && gr->data));
  if (gr->size == gr->capacity)
    return OK;

  void **new_data = (void **)realloc(gr->data, gr->size * sizeof(void *));
  CHECK_ALLOCATION(new_data);

  gr->data = new_data;
  gr->capacity = gr->size;

  return OK;
}

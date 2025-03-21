#ifndef GROW_H
#define GROW_H

#include <stdlib.h>

#include "eerror.h"

// grow is container for simple and secure store any type of data
typedef struct grow {
  void **data;
  size_t size;
  size_t capacity;         // Size of allocate memory
  size_t element_size;     // Size of one element
  void (*free_fn)(void *); // Free function
} grow;

easy_error grow_init(grow *gr, size_t element_size, size_t initial_capacity,
                     void (*free_fn)(void *));

void grow_free(grow *gr);

easy_error grow_push(grow *gr, const void *element);

void *grow_get(grow *gr, size_t index, easy_error *err);

easy_error grow_remove(grow *gr, size_t);

#endif // GROW_H

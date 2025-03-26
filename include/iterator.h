#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdbool.h>
#include <stdlib.h>

#include "array.h"
#include "eerror.h"
#include "grow.h"

/// @def DECLARE_ITERATOR(name,type)
/// @brief macros for declaring iterator. Use if you want create custom iterator for container
#define DECLARE_ITERATOR(name, type)                                                               \
  typedef struct name##_iterator {                                                                 \
    type *container;                                                                               \
    void *element;                                                                                 \
    int current_index;                                                                             \
    bool is_valid;                                                                                 \
  } name##_iterator;                                                                               \
                                                                                                   \
  name##_iterator name##_iterator_begin(type *c);                                                  \
  name##_iterator name##_iterator_rbegin(type *c);                                                 \
                                                                                                   \
  name##_iterator name##_iterator_end(type *c);                                                    \
  name##_iterator name##_iterator_rend(type *c);                                                   \
                                                                                                   \
  bool name##_iterator_compare(const name##_iterator *it1, const name##_iterator *it2,             \
                               easy_error *err);                                                   \
  bool name##_iterator_is_end(name##_iterator *it, easy_error *err);                               \
                                                                                                   \
  easy_error name##_iterator_next(name##_iterator *it);                                            \
  easy_error name##_iterator_previous(name##_iterator *it);                                        \
                                                                                                   \
  easy_error name##_iterator_plus(name##_iterator *it, int n);                                     \
  easy_error name##_iterator_minus(name##_iterator *it, int n);

// Declare grow_iterator
DECLARE_ITERATOR(grow, grow)

// Declare array_iterator
DECLARE_ITERATOR(array, array);

#endif // ITERATOR_H

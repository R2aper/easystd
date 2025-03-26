#ifndef ESTRING_H
#define ESTRING_H

#include <stdlib.h>

#include "eerror.h"

/// array is a container that encapsulates fixed size arrays
typedef struct array {
  void **data;
  size_t size;
  size_t capacity;         // Size of allocate elements
  size_t element_size;     // Size of one element
  void (*free_fn)(void *); // Free function
} array;

/// @defgroup Array Functios relative to array type
/// @{

/**
 * @brief Create container by given capacity
 * @note array should be freed after using
 *
 * @param ar Pointer to array object
 * @param element_size size of data type that will be store
 * @param initial_capacity size of container
 * @param free_fn function that used for freeing elements(if NULL, will be used free())
 * @return 0 on success or easy_error
 */
easy_error array_init(array *ar, size_t element_size, size_t initial_capacity,
                      void (*free_fn)(void *));

/// @brief Freed array object
void array_free(array *ar);

/**
 * Pushes element to container
 *
 * @param ar Pointer to array object
 * @param element Pointer to new element
 * @return 0 on success or easy_error
 */
easy_error array_push(array *ar, const void *element);

/**
 * Returns element by given index
 *
 * @param ar Pointer to array object
 * @param index index of element
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return element of container
 */
void *array_get(array *ar, size_t index, easy_error *err);

/**
 * Removes element by given index
 *
 * @param Pointer to array object
 * @param index index of element
 * @return 0 on success or easy_error
 */
easy_error array_remove(array *ar, size_t index);

///@}

#endif // ESTRING_H

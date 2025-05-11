#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <stdlib.h>

#include "eerror.h"

/// @brief array is a container that encapsulates fixed size arrays
/// @note array is not responsible for freeing object it contains. User should free them manualy
typedef struct array {
  void **data;
  size_t size;
} array;

/// @defgroup Array Functios relative to array type
/// @{

/**
 * @brief Create container by given capacity
 * @note array should be freed after using
 *
 * @param size size of container
 * @return Initializeid array object
 */
array *array_init(size_t size);

/// @brief Freed array object
void array_free(array *arr);

// TODO:
/* easy_error array_fill(array *arr, const void *element, void(*copy_fn)(void*,const void*));
 * easy_error array_sort(array* arr, compare_fn);
 */

/**
 * @brief Returns element by given index
 *
 * @param arr Pointer to array object
 * @param index index of element
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return element of container
 */
void *array_get(array *arr, size_t index, easy_error *err);

/*
 * @brief Set element of given index to @value
 *
 * @param ar Pointer to array object
 * @param index index of element
 * @return 0 on success or easy_error
 */
easy_error array_set(array *arr, size_t index, void *element);

/**
 * @def array_get_as(type,arr,index,err)
 * @brief get element of array as @type
 *
 * @param arr Pointer to array object
 * @param index index of element
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return element of container
 */
#define array_get_as(type, arr, index, err) ((type *)array_get((arr), (index), (err)))

/**
 * @def array_set_as(type,arr,index,value)
 * @brief set element of given index to @value
 *
 * @param ar Pointer to array object
 * @param index index of element
 * @return 0 on success or easy_error
 */
#define array_set_as(type, arr, index, value) array_set((arr), (index), (void *)(type)(value))

///@}

#endif // ARRAY_H

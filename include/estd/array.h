#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

#include "estd/eerror.h"

/// @brief array is a container that encapsulates fixed size arrays
/// @note array is not responsible for freeing object it contains. User should free them manually
typedef struct array {
  void **data;
  size_t size;

} array;

#define array_size(arr) (arr)->size

/// @defgroup Array Functions relative to array type
/// @{

/**
 * @brief Create container by given capacity
 * @note array should be freed after using
 *
 * @param size Size of container
 * @return Initializeid array object
 */
array *array_init(size_t size);

/// @brief Free array object
///
/// @param free_fn Pass ptr to free_fn to free elements of array
void array_free_(array *arr, void(free_fn)(void *));

#define array_free(arr, free_fn)                                                                   \
  array_free_((arr), (free_fn));                                                                   \
  (arr) = NULL

// TODO:
/* easy_error array_fill(array *arr, const void *element, void(*copy_fn)(void*,const void*));
 */

/**
 * @brief Returns element by given index
 *
 * @param arr Pointer to array object
 * @param index Index of element
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return Element of container
 */
void *array_get(array *arr, size_t index, easy_error *err);

/**
 * @def array_get_as(type,arr,index,err)
 * @brief Get element of array as @type
 *
 * @param arr Pointer to array object
 * @param index Index of element
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return element of container
 */
#define array_get_as(type, arr, index, err) (*(type *)array_get((arr), (index), (err)))

/**
 * @brief Set element of given index to @element
 *
 * @param arr Pointer to array object
 * @param index Index of element
 * @param element Pointer to new_element
 * @return 0 on success or easy_error
 */
easy_error array_set(array *arr, size_t index, void *element);

/**
 * @brief Sorts elements using qsort. Elements compares by @compare_fn
 *
 * @param arr Pointer to array object
 * @param compare_fn Pointer to compare function
 * @return 0 on success or easy_error
 */
easy_error array_qsort(array *arr, int(compare_fn)(const void *, const void *));

///@}

#endif // ARRAY_H

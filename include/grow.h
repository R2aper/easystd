#ifndef GROW_H
#define GROW_H

#include <stdlib.h>

#include "eerror.h"

/// grow is container for simple and secure store any type of data
/// @note Array is not responsible for freeing object it contains. User should free them manualy
typedef struct grow {
  void **data;
  size_t size;
  size_t capacity; // Size of allocated elements
} grow;

/// @defgroup Grow Functions relative to grow type
/// @{

/**
 * @brief Create container by given capacity
 * @note grow should be freed after using
 *
 * @param initial_capacity Size of initial capacity of container
 * @return Initialized grow object
 */
grow *grow_init(size_t initial_capacity);

/// @brief Freed grow object
void grow_free(grow *gr);

/**
 * @brief Pushes element to end of container
 *
 * @param gr Pointer to grow object
 * @param element Pointer to new element
 * @return 0 on success or easy_error
 */
easy_error grow_push(grow *gr, void *element);

/**
 * @brief Insert element to given index
 *
 * @param gr Pointer to grow object
 * @param index Index to push element
 * @param element Pointer to new element
 * @return 0 on success or easy_error
 */
easy_error grow_insert(grow *gr, size_t index, void *element);

/**
 * @brief Set element of given index to @element
 * @warning Use only on allocated elements
 *
 * @param gr Pointer to grow object
 * @param index Index of element
 * @param element Pointer to new element
 * @return 0 on success or easy_error
 */
easy_error grow_set(grow *gr, size_t index, void *element);

/**
 * @brief Returns element by given index
 *
 * @param gr Pointer to grow object
 * @param index Index of element
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return ptr to element of container or NULL
 */
void *grow_get(grow *gr, size_t index, easy_error *err);

/**
 * @def grow_get_as(type,gr,index,err)
 * @brief Get element of grow as @type
 *
 * @param gr Pointer to grow object
 * @param index Index of element
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return Element of container
 */
#define grow_get_as(type, grow, index, err) (*(type *)grow_get(gr, index, err))

/**
 * Removes element by given index
 *
 * @param gr Pointer to grow object
 * @param index Index of element
 * @return 0 on success or easy_error
 */
easy_error grow_remove(grow *gr, size_t index);

/**
 * @brief Sorts elements using qsort. Elements compares by @compare_fn
 *
 * @param gr Pointer to grow object
 * @param compare_fn Pointer to compare function
 * @return 0 on success or easy_error
 */
easy_error grow_qsort(grow *gr, int(compare_fn)(const void *, const void *));

/**
 * @brief reduce grow->capacity to grow->length
 * @return 0 on success or easy_error
 */
easy_error grow_shrink_to_fit(grow *gr);

/*TODO:
easy_error grow_resize(grow *gr, size_t new_size);
easy_error grow_pop(grow *gr);
*/

///@}

#endif // GROW_H

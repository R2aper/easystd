#ifndef GROW_H
#define GROW_H

#include <stddef.h>

#include "estd/eerror.h"

/// grow is container for simple and secure store of any types of data
/// @note grow is not responsible for freeing object it contains. User should free them manualy
typedef struct grow {
  void **data;
  size_t size;     // Size of valid elemets
  size_t capacity; // Size of allocated elements

} grow;

#define grow_size(grow) (grow)->size
#define grow_capacity(grow) (grow)->capacity

#define grow_is_empty(grow) ((grow)->size == 0)

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

/**
 * @def grow_init_emtpy
 * @brief Macros for initializing empty grow container
 */
#define grow_init_empty grow_init(0)

/// @brief Freed grow object
/// @param free_fn Pass ptr to free_fn to free elements of container
void grow_free_(grow *gr, void(free_fn)(void *));

#define grow_free(gr, free_fn)                                                                     \
  grow_free_((gr), (free_fn));                                                                     \
  (gr) = NULL

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
void *grow_get(const grow *gr, size_t index, easy_error *err);

/**
 * @def grow_get_as(type,gr,index,err)
 * @brief Get element of grow as @type
 *
 * @param gr Pointer to grow object
 * @param index Index of element
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 * @return Element of container
 */
#define grow_get_as(type, gr, index, err) (*(type *)grow_get(gr, index, err))

/**
 * Removes element by given index
 *
 * @param gr Pointer to grow object
 * @param index Index of element
 * @param free_fn Function to free the removed element. Can be NULL.
 * @return 0 on success or easy_error
 */
easy_error grow_remove(grow *gr, size_t index, void(free_fn)(void *));

/**
 * @def Macros for removing last element
 * @brief Pop last element of container
 *
 * @param gr Pointer to grow object
 * @return 0 on success or easy_error
 */
#define grow_pop(gr, free_fn) grow_remove(gr, (gr)->size - 1, (free_fn))

/**
 * @brief Sorts elements using qsort. Elements compares by @compare_fn
 *
 * @param gr Pointer to grow object
 * @param compare_fn Pointer to compare function
 * @return 0 on success or easy_error
 */
easy_error grow_qsort(grow *gr, int(compare_fn)(const void *, const void *));

/**
 * @brief Changes gr->capacity to @new_capacity
 *
 * @param gr Pointer to grow object
 * @param new_capacity Size of new capacity
 * @return 0 on success or easy_error
 */
easy_error grow_resize(grow *gr, size_t new_capacity);

/**
 * @brief reduce grow->capacity to grow->length
 * @return 0 on success or easy_error
 */
easy_error grow_shrink_to_fit(grow *gr);

///@}

#endif // GROW_H

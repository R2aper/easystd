#ifndef GROW_H
#define GROW_H

#include <stdlib.h>

#include "eerror.h"

// macros for easier usage of grow_get
#define INT_GET(grow, index, err) (*(int *)grow_get((grow), (index), (err)))
#define UINT_GET(grow, index, err) (*(unsigned int *)grow_get((grow), (index), (err)))

#define SHRT_GET(grow, index, err) (*(short *)grow_get((grow), (index), (err)))
#define USHRT_GET(grow, index, err) (*(unsigned short *)grow_get((grow), (index), (err)))

#define LONG_GET(grow, index, err) (*(long *)grow_get((grow), (index), (err)))
#define ULONG_GET(grow, index, err) (*(unsigned long *)grow_get((grow), (index), (err)))

#define LLONG_GET(grow, index, err) (*(long long *)grow_get((grow), (index), (err)))
#define ULLONG_GET(grow, index, err) (*(unsigned long long *)grow_get((grow), (index), (err)))

#define FLOAT_GET(grow, index, err) (*(float *)grow_get((grow), (index), (err)))
#define DOUBLE_GET(grow, index, err) (*(double *)grow_get((grow), (index), (err)))
#define LDOUBLE_GET(grow, index, err) (*(long double *)grow_get((grow), (index), (err)))

#define CHAR_GET(grow, index, err) (*(char *)grow_get((grow), (index), (err)))
#define SCHAR_GET(grow, index, err) (*(signed char *)grow_get((grow), (index), (err)))
#define UCHAR_GET(grow, index, err) (*(unsigned char *)grow_get((grow), (index), (err)))

// grow is container for simple and secure store any type of data
typedef struct grow {
  void **data;
  size_t size;
  size_t capacity;         // Size of allocate memory
  size_t element_size;     // Size of one element
  void (*free_fn)(void *); // Free function
} grow;

/* Create container by given capacity
 * NOTE: grow should be freed after using
 *
 * @param grow Pointer to grow object
 * @param element_size size of data type that will be store
 * @param initial_capacity size of container
 * @param free_fn function that used for freeing elements(if NULL, will be used free())
 * @return 0 on success or easy_error
 */
easy_error grow_init(grow *gr, size_t element_size, size_t initial_capacity,
                     void (*free_fn)(void *));

// Freed grow object
void grow_free(grow *gr);

/* Pushes element to container
 *
 * @param grow Pointer to grow object
 * @param element Pointer to new element
 * @return 0 on success or easy_error
 */
easy_error grow_push(grow *gr, const void *element);

/* Returns element by given index
 *
 * @param grow Pointer to grow object
 * @param index index of element
 * @param err Pointer to easy_error object, will write INVALID_INDEX if index is bad
 */
void *grow_get(grow *gr, size_t index, easy_error *err);

/* Removes element by given index
 *
 * @param grow Pointer to grow object
 * @param index index of element
 * @return 0 on success or easy_error
 */
easy_error grow_remove(grow *gr, size_t index);

#endif // GROW_H

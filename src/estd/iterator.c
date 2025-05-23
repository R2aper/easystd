#include <stdbool.h>

#include "estd/eerror.h"
#include "estd/grow.h"
#include "estd/iterator.h"

/// @defgroup grow_iterator Functions for grow's iterator
/// @{

/**
 * @brief Returns an iterator to the first element of grow container
 * @warning If grow or it's data is NULL, then iterator is not valid
 *
 * @param c Pointer to grow object
 * @return Iterator of first element
 */
grow_iterator grow_iterator_begin(grow *c) {
  return (c && c->data) ? (grow_iterator){c, grow_get(c, 0, NULL), 0, true}
                        : (grow_iterator){NULL, NULL, 0, false};
}

/**
 * @brief Returns an iterator to the past-the-last of grow container
 * @warning If grow or it's data is NULL, then iterator is not valid
 * @note field 'element' of this iterator is NULL
 *
 * @param c Pointer to grow object
 * @return Iterator of past-the-last element
 */
grow_iterator grow_iterator_end(grow *c) {
  if (!(c && c->data))
    return (grow_iterator){NULL, NULL, 0, false};

  return (grow_iterator){c, NULL, c->size, true};
}

/**
 * @brief Checks if given iterator is end iterator
 *
 * @param it Pointer to grow_iterator object
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 */
bool grow_iterator_is_end(grow_iterator *it, easy_error *err) {
  if (!(it && it->container->data)) {
    SET_CODE_ERROR(err, NULL_POINTER);
    return false;
  }

  if (!it->is_valid) {
    SET_CODE_ERROR(err, INVALID_ITERATOR);
    return false;
  }

  SET_CODE_ERROR(err, OK);

  return (it->current_index == grow_iterator_end(it->container).current_index);
}

/**
 * @brief incrise index of iterator
 *
 * @param it Pointer to grow_iterator object
 * @return 0 on success or easy_error
 */
easy_error grow_iterator_next(grow_iterator *it) {
  // if it == last element => it -> end
  // if it == end => error -> OUT OF BOUNDE
  // if it in [0;last_element-1] => it++
  CHECK_NULL_PTR(it);

  easy_error err;
  it->current_index++;

  if (it->current_index == grow_iterator_end(it->container).current_index)
    *it = grow_iterator_end(it->container);
  else
    it->element = grow_get(it->container, it->current_index, &err);

  return err;
}

// TODO:
grow_iterator grow_iterator_rbegin(grow *c);
grow_iterator grow_iterator_rend(grow *c);
easy_error grow_iterator_plus(grow_iterator *it, int n);
easy_error grow_iterator_minus(grow_iterator *it, int n);
bool grow_iterator_compare(const grow_iterator *it1, const grow_iterator *it2, easy_error *err);

///@}

/// @defgroup array_iterator Functions for array's iterator
/// @{

/**
 * @brief Returns an iterator to the first element of array container
 * @warning If array or it's data is NULL, then iterator is not valid
 *
 * @param c Pointer to array object
 * @return Iterator of first element
 */
array_iterator array_iterator_begin(array *c) {
  return (c && c->data) ? (array_iterator){c, array_get(c, 0, NULL), 0, true}
                        : (array_iterator){NULL, NULL, 0, false};
}

/**
 * @brief Returns an iterator to the past-the-last of array container
 * @warning If array or it's data is NULL, then iterator is not valid
 * @note field 'element' of this iterator is NULL
 *
 * @param c Pointer to array object
 * @return Iterator of past-the-last element
 */
array_iterator array_iterator_end(array *c) {
  if (!(c && c->data))
    return (array_iterator){NULL, NULL, 0, false};

  return (array_iterator){c, NULL, c->size, true};
}

/**
 * @brief Checks if given iterator is end iterator
 *
 * @param it Pointer to array_iterator object
 * @param err Pointer to easy_error object. Pass NULL if you sure in other parameters
 */
bool array_iterator_is_end(array_iterator *it, easy_error *err) {
  if (!(it && it->container->data)) {
    SET_CODE_ERROR(err, NULL_POINTER);
    return false;
  }

  if (!it->is_valid) {
    SET_CODE_ERROR(err, INVALID_ITERATOR);
    return false;
  }

  SET_CODE_ERROR(err, OK);

  return (it->current_index == array_iterator_end(it->container).current_index);
}

/**
 * @brief incrise index of iterator
 *
 * @param it Pointer to array_iterator object
 * @return 0 on success or easy_error
 */
easy_error array_iterator_next(array_iterator *it) {
  CHECK_NULL_PTR(it);

  easy_error err;
  it->current_index++;

  if (it->current_index == array_iterator_end(it->container).current_index)
    *it = array_iterator_end(it->container);
  else
    it->element = array_get(it->container, it->current_index, &err);

  return err;
}

///@}

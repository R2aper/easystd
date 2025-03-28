#ifndef EERROR_H
#define EERROR_H

/// @defgroup Errors Module for handling errors
/// @{

#define CHECK_NULL_PTR(data)                                                                       \
  if (!data)                                                                                       \
  return NULL_POINTER

#define CHECK_ALLOCATION(data)                                                                     \
  if (!data)                                                                                       \
  return ALLOCATION_FAILED

#define SET_CODE_ERROR(err, code_error)                                                            \
  if (err)                                                                                         \
  *err = code_error

/// @brief Struct for all errors in library
typedef enum {
  OK = 0,
  ALLOCATION_FAILED = -1,
  INVALID_INDEX = -2,
  NULL_POINTER = -3,
  INVALID_ARGUMENT = -4,
  INVALID_ITERATOR = -5,
  ARRAY_OVERFLOW = -6,
} easy_error;

/// @brief return text of error
const char *easy_error_message(easy_error err);

///@}

#endif // EERROR_H

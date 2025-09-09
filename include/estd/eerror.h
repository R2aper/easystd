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
  FILE_INVALID_MODE = -5,
  FILE_OPEN_ERROR = -6,
  FILE_SEEK_ERROR = -7,
  FILE_TELL_ERROR = -8,
  FILE_WRITE_FAILED = -9,
  FILE_READ_FAILED = -10,
  PARSER_UNKOWN_ARGUMENT = -11,
  PARSER_NO_REQUIRED_PARAMETR = -12,
  PARSER_NO_PASSED_PARAMETRS = -13,
  PARSER_UNEXPECTED_VALUE = -14

} easy_error;

/// @brief return text of error
const char *easy_error_message(easy_error err);

///@}

#endif // EERROR_H

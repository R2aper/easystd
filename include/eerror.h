#ifndef EERROR_H
#define EERROR_H

// Struct for all errors in library
typedef enum {
  OK = 0,
  ALLOCATION_FAILED = -1,
  INVALID_INDEX = -2,
  NULL_POINTER = -3,
  INVALID_ARGUMENT = -4,
  STRING_EMPTY_OPERATION = -5,
  STRING_RANGE_ERROR = -6,
} easy_error;

// @return text of error
const char *easy_error_message(easy_error err);

#endif // EERROR_H

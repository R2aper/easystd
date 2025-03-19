#ifndef EERROR_H
#define EERROR_H

// Struct for all errors in library
typedef enum {
  // String errors
  STRING_OK = 0,
  STRING_ALLOCATION_FAILED = -1,
  STRING_INVALID_INDEX = -2,
  STRING_NULL_POINTER = -3,
  STRING_INVALID_ARGUMENT = -4,
  STRING_EMPTY_OPERATION = -5,
  STRING_RANGE_ERROR = -6,
} easy_error;

// @return text of error
const char *easy_error_message(easy_error err);

#endif // EERROR_H

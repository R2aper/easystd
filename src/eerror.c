#include "eerror.h"

const char *string_error_message(easy_error err) {
  switch (err) {
    // String errors
  case STRING_OK:
    return "No error";
  case STRING_ALLOCATION_FAILED:
    return "Memory allocation failed";
  case STRING_INVALID_INDEX:
    return "Invalid index";
  case STRING_NULL_POINTER:
    return "Null pointer";
  case STRING_INVALID_ARGUMENT:
    return "Invalid argument";
  case STRING_EMPTY_OPERATION:
    return "Empty string operation";
  case STRING_RANGE_ERROR:
    return "Invalid range";
  default:
    return "Unknown error";
  }
}

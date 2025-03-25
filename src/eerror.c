#include "eerror.h"

const char *easy_error_message(easy_error err) {
  switch (err) {
  case OK:
    return "No error";
  case ALLOCATION_FAILED:
    return "Memory allocation failed";
  case INVALID_INDEX:
    return "Invalid index";
  case NULL_POINTER:
    return "Null pointer";
  case INVALID_ARGUMENT:
    return "Invalid argument";
  case INVALID_ITERATOR:
    return "Invalid iterator";
  case STRING_RANGE_ERROR:
    return "Invalid range";
  default:
    return "Unknown error";
  }
}

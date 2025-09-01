#include "estd/eerror.h"

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
  case FILE_INVALID_MODE:
    return "Invalid mode of opening file";
  case FILE_OPEN_ERROR:
    return "Error of opening file, check perror";
  case FILE_SEEK_ERROR:
    return "Error of setting position, check perror";
  case FILE_TELL_ERROR:
    return "Error of getting position, check perror";
  case FILE_WRITE_FAILED:
    return "Error while writing into file, check perror";
  case FILE_READ_FAILED:
    return "Error while reading from file, check perror";

  default:
    return "Unknown error";
  }
}

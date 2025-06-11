#include "estd/global.h"

int int_compare(const void *a, const void *b) {
  int arg1 = *(const int *)a;
  int arg2 = *(const int *)b;

  return (arg1 > arg2) - (arg1 < arg2);
}

int double_compare(const void *a, const void *b) {
  double arg1 = *(const double *)a;
  double arg2 = *(const double *)b;

  return (arg1 > arg2) - (arg1 < arg2);
}

int char_compare(const void *a, const void *b) {
  char arg1 = *(const char *)a;
  char arg2 = *(const char *)b;

  return (arg1 > arg2) - (arg1 < arg2);
}

#include "estd/global.h"

int int_compare(const void *a, const void *b) {
  void *ptrA = *(void **)a;
  void *ptrB = *(void **)b;

  int arg1 = *(int *)ptrA;
  int arg2 = *(int *)ptrB;

  if (arg1 < arg2)
    return -1;
  else if (arg1 > arg2)
    return 1;

  return 0;
}

int double_compare(const void *a, const void *b) {
  void *ptrA = *(void **)a;
  void *ptrB = *(void **)b;

  double arg1 = *(double *)ptrA;
  double arg2 = *(double *)ptrB;

  if (arg1 < arg2)
    return -1;
  else if (arg1 > arg2)
    return 1;

  return 0;
}

int char_compare(const void *a, const void *b) {
  void *ptrA = *(void **)a;
  void *ptrB = *(void **)b;

  char arg1 = *(char *)ptrA;
  char arg2 = *(char *)ptrB;

  if (arg1 < arg2)
    return -1;
  else if (arg1 > arg2)
    return 1;

  return 0;
}


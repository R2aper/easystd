#ifndef GLOBAL_H
#define GLOBAL_H

/**
 * @define TO_TYPE(expression,type)
 * @brief Macros for converting void* to given type
 */
#define TO_TYPE(expression, type) *(type *)expression

/**
 * @define DECLARE_COMPARE_FN(type,name)
 * @brief Macros for declaring comparing functions
 */
#define DECLARE_COMPARE_FN(type, name)                                                             \
  int name(const void *a, const void *b) {                                                         \
                                                                                                   \
    void *ptrA = *(void **)a;                                                                      \
    void *ptrB = *(void **)b;                                                                      \
                                                                                                   \
    type arg1 = *(type *)ptrA;                                                                     \
    type arg2 = *(type *)ptrB;                                                                     \
                                                                                                   \
    if (arg1 < arg2)                                                                               \
      return -1;                                                                                   \
    else if (arg1 > arg2)                                                                          \
      return 1;                                                                                    \
                                                                                                   \
    return 0;                                                                                      \
  }

// Compare functions for int,double and char
int int_compare(const void *a, const void *b);
int double_compare(const void *a, const void *b);
int char_compare(const void *a, const void *b);

// Max and min macros
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#endif // GLOBAL_H


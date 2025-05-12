#ifndef GLOBAL_H
#define GLOBAL_H

/**
 * @define TO_TYPE(expression,type)
 * @brief Macros for converting void* to given type
 */
#define TO_TYPE(expression, type) *(type *)expression

/**
 * @define DEFINE_COMPARE_FN(name,type,expr)
 * @brief Macros for declaring comparing fn
 */
#define DEFINE_COMPARE_FN(name, type, expr)                                                        \
  int name(const void *a, const void *b) {                                                         \
    type x = *(type *)a;                                                                           \
    type y = *(type *)b;                                                                           \
    return (expr);                                                                                 \
  }

// Max and min macros
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#endif // GLOBAL_H

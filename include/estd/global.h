#ifndef GLOBAL_H
#define GLOBAL_H

/**
 * @define TO_TYPE(expression,type)
 * @brief Macros for converting void* to given type
 */
#define TO_TYPE(expression, type) *(type *)expression

// Compare functions for int,double and char
int int_compare(const void *a, const void *b);
int double_compare(const void *a, const void *b);
int char_compare(const void *a, const void *b);

// Max and min macros
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#endif // GLOBAL_H

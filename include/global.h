#ifndef GLOBAL_H
#define GLOBAL_H

/**
 * @defgroup macros Macros for converting void* to type
 * @{
 */

#define INT(expression) *(int *)expression
#define UINT(expression) *(unsigned int *)expression

#define SHRT(expression) *(short *)expression
#define USHRT(expression) *(unsigned short *)expression

#define LONG(expression) *(long *)expression
#define ULONG(expression) *(unsigned long *)expression

#define LLONG(expression) *(long long *)expression
#define ULLONG(expression) *(unsigned long long *)expression

#define FLOAT(expression) *(float *)expression
#define DOUBLE(expression) *(double *)expression
#define LDOUBLE(expression) *(long double *)expression

#define CHAR(expression) *(char *)expression
#define SCHAR(expression) *(signed char *)expression
#define UCHAR(expression) *(unsigned char *)expression

/// @}

#endif // GLOBAL_H

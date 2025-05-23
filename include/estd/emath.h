#ifndef EMATH_H
#define EMATH_H

#include "estd/grow.h"

// NOTE: Idk why it's so confusing include M_PI and ets, so i just add this:
#define _E 2.7182818284590452354         /* e */
#define _LOG2E 1.4426950408889634074     /* log_2 e */
#define _LOG10E 0.43429448190325182765   /* log_10 e */
#define _LN2 0.69314718055994530942      /* log_e 2 */
#define _LN10 2.30258509299404568402     /* log_e 10 */
#define _PI 3.14159265358979323846       /* pi */
#define _PI_2 1.57079632679489661923     /* pi/2 */
#define _PI_4 0.78539816339744830962     /* pi/4 */
#define _1_PI 0.31830988618379067154     /* 1/pi */
#define _2_PI 0.63661977236758134308     /* 2/pi */
#define _2_SQRTPI 1.12837916709551257390 /* 2/sqrt(pi) */
#define _SQRT2 1.41421356237309504880    /* sqrt(2) */
#define _SQRT1_2 0.70710678118654752440  /* 1/sqrt(2) */

/// @brief struct for complex numbers
typedef struct complex {
  double Re;
  double Im;
} complex;

/// @defgroup Complex Operators on complex numbers
/// @{
complex complex_plus(complex c1, complex c2);
complex complex_minus(complex c1, complex c2);
complex complex_times(complex c1, complex c2);
complex complex_divide(complex c1, complex c2);
complex complex_pow(complex c, long long n);
///@note grow and it's elements, should be freed after using
///@return Allocated grow object or NULL
grow *complex_root(complex c, double n);

///@}

#endif // EMATH_H

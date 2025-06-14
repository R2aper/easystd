#include "estd/emath.h"
#include "estd/grow.h"

#include <math.h>

complex complex_plus(complex c1, complex c2) { return (complex){c1.Re + c2.Re, c1.Im + c2.Im}; }
complex complex_minus(complex c1, complex c2) { return (complex){c1.Re - c2.Re, c1.Im - c2.Im}; }
complex complex_times(complex c1, complex c2) {
  return (complex){c1.Re * c2.Re - c1.Im * c2.Im, c1.Re * c2.Im + c1.Im * c2.Re};
}
complex complex_divide(complex c1, complex c2) {
  double Re = (double)(c1.Re * c2.Re + c1.Im * c2.Im) / (powf(c2.Re, 2 + powf(c2.Im, 2)));
  double Im = (double)(c1.Im * c2.Re - c1.Re * c2.Im) / (powf(c2.Re, 2 + powf(c2.Im, 2)));

  return (complex){Re, Im};
}

double complex_module(complex c) { return sqrt(pow(c.Re, 2) + pow(c.Im, 2)); }

double complex_arg(complex c) {
  if (c.Re > 0)
    return atan((double)c.Im / c.Re);
  if (c.Re < 0 && c.Im >= 0)
    return (_PI + atan((double)c.Im / c.Re));
  if (c.Re < 0 && c.Im < 0)
    return (-_PI + atan((double)c.Im / c.Re));

  if (c.Re == 0 && c.Im > 0)
    return _PI_2;
  if (c.Re == 0 && c.Im < 0)
    return -_PI_2;

  return 0;
}

complex complex_pow(complex c, long long n) {
  double r = complex_module(c);
  complex z;
  z.Re = pow(r, n) * cos(n * complex_arg(c));
  z.Im = pow(r, n) * sin(n * complex_arg(c));

  return z;
}

complex complex_first_root(complex c, double n) {
  complex z;
  double module = pow(complex_module(c), (double)1 / n);
  double frac = (double)(complex_arg(c)) / (n);
  z.Re = module * cos(frac);
  z.Im = module * sin(frac);

  return z;
}

grow *complex_root(complex c, double n) {
  grow *sol = grow_init_empty;
  double module = pow(complex_module(c), (double)1 / n);

  for (size_t k = 0; k < n; k++) {
    complex *root = (complex *)malloc(sizeof(complex));
    if (!root)
      return NULL;
    double frac = (double)(complex_arg(c) + 2 * _PI * k) / (n);
    root->Re = module * cos(frac);
    root->Im = module * sin(frac);

    if (grow_push(sol, root) != 0)
      return NULL;
  }

  return sol;
}

long long gcd(long long a, long long b) {
  a = llabs(a);
  b = llabs(b);
  if (b == 0)
    return a; // GCD(a,0) = |a|

  while (b != 0) {
    long long r = a % b;
    a = b;
    b = r;
  }

  return a;
}

long long lcm(long long a, long long b) { return llabs(a) * llabs(b) / gcd(a, b); }


#ifndef TIMES_H
#define TIMES_H

#include <stddef.h>

#define REPEATS 1000000

typedef double scalarProd(
    const double *const,
    const double *const,
    const size_t
);

typedef struct funcParams
{
    double *a;
    double *b;
    size_t size;
} funcParams_t;

double getTime(funcParams_t params, scalarProd func);

#endif
#ifndef TIMES_H
#define TIMES_H

#include <stddef.h>

#include "pack.h"

#define REPEATS 1000000

typedef double scalarProd(
    const pack_t *,
    const pack_t *,
    const size_t
);

typedef struct funcParams
{
    pack_t *a;
    pack_t *b;
    size_t size;
} funcParams_t;

double getTime(funcParams_t params, scalarProd func);

#endif
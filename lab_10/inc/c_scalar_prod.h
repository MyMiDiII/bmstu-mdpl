#ifndef C_SCALAR_PROD
#define C_SCALAR_PROD

#include <stddef.h>
#include "pack.h"


double cScalarProd(
    const pack_t *a,
    const pack_t *b,
    const size_t size
);

#endif
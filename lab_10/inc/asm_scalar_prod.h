#ifndef ASM_SCALAR_PROD_H
#define ASM_SCALAR_PROD_H

#include "stddef.h"
#include "pack.h"

double asmScalarProd(
    const pack_t *a,
    const pack_t *b,
    const size_t size
);

#endif
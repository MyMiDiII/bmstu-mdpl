#include "asm_scalar_prod.h"

#include <stdio.h>

double asmScalarProd(
    const pack_t *a,
    const pack_t *b,
    const size_t size
)
{
    double res = 0;

    size_t i = 0;
    for (const pack_t *aEnd = a + size; a < aEnd; ++i, ++a, ++b)
    {
        __asm__(
            "vmovupd ymm0, %1\n"
            "vmovupd ymm1, %2\n"
            //"vmulpd ymm0, ymm0, ymm1\n"
            //"vextractf128 xmm2, ymm1, 1\n"
            //"vaddpd ymm0, ymm1, ymm3\n"
            "movupd xmmword ptr [%0], xmm0\n"
            :
            : "r"(&res), "m"(*a), "m"(*b)
            : "ymm0", "ymm1", "ymm2", "ymm3"
        );
        printf("res = %f", res);
    }

    return res;
}
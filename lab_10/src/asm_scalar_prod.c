#include "asm_scalar_prod.h"

#include <stdio.h>

double asmScalarProd(
    const pack_t *a,
    const pack_t *b,
    const size_t size
)
{
    double res = 0;

    for (const pack_t *aEnd = a + size; a < aEnd; ++a, ++b)
    {
        __asm__(
            "vmovupd ymm0, %1\n"
            "vmovupd ymm1, %2\n"
            "vmulpd ymm0, ymm0, ymm1\n"
            "vextractf128 xmm1, ymm0, 1\n"
            "vaddpd xmm0, xmm1, xmm0\n"
            "vhaddpd ymm0, ymm0, ymm1\n"
            "vhaddpd ymm2, ymm0, ymm1\n"
            "movsd qword ptr [%0], xmm0\n"
            :
            : "r"(&res), "m"(*a), "m"(*b)
            : "ymm0", "ymm1", "ymm2"
        );
    }

    return res;
}
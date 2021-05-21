#include "c_scalar_prod.h"

double cScalarProd(
    const pack_t *a,
    const pack_t *b,
    const size_t size
)
{
    double res = 0;

    for (size_t i = 0; i < size; ++i)
        for (int j = 0; j < 4; ++j)
            res += a[i][j] * b[i][j];

    return res;
}
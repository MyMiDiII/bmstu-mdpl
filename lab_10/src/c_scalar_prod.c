#include "c_scalar_prod.h"

double cScalarProd(
    const double *const a,
    const double *const b,
    const size_t size
)
{
    double res = 0;

    for (size_t i = 0; i < size; ++i)
        res += a[i] * b[i];

    return res;
}
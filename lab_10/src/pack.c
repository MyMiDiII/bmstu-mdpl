#include "pack.h"

void packArray(pack_t *const pack, const double *const arr, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        pack[i / 4][i % 4] = arr[i];
    }
}
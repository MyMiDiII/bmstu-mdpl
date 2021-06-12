#include <time.h>
#include "times.h"

double getTime(funcParams_t params, scalarProd func)
{
    clock_t start = clock();

    for (size_t i = 0; i < REPEATS; ++i)
        func(params.a, params.b, params.size);

    clock_t end = clock();

    return (double) (end - start) / CLOCKS_PER_SEC / REPEATS;
}
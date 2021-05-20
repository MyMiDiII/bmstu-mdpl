#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "times.h"
#include "c_scalar_prod.h"

#define OK 0 

#define MAX_SIZE 1000

#define getDoubleRandom(min, max) \
(double) rand() / RAND_MAX * ((max) - (min)) + (min)

void getSimpleTest(funcParams_t *const params)
{
    double a[3] = {1, 6, 2};
    double b[3] = {4, 1, 3};

    for (int i = 0; i < 3; ++i)
    {
        params->a[i] = a[i];
        params->b[i] = b[i];
    }

    params->size = 3;
}

void getRandomArrays(funcParams_t *const params)
{
    srand(time(NULL));

    params->size = 1 + rand() % 1000;

    for (size_t i = 0; i < params->size; ++i)
    {
        params->a[i] = getDoubleRandom(-500, 500);
        params->b[i] = getDoubleRandom(-500, 500);
    }
}

int main(void)
{
    double a[MAX_SIZE];
    double b[MAX_SIZE];

    funcParams_t params = { .a = a, .b = b};

    getSimpleTest(&params);

    printf("C RES: %f", cScalarProd(params.a, params.b, params.size));

    getRandomArrays(&params);

    printf("C TIME: %g", getTime(params, cScalarProd));

    return OK;
}
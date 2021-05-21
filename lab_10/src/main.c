#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "times.h"
#include "c_scalar_prod.h"
#include "asm_scalar_prod.h"
#include "pack.h"

#define OK 0 

#define getDoubleRandom(min, max) \
(double) rand() / RAND_MAX * ((max) - (min)) + (min)

void getSimpleTest(funcParams_t *const params)
{
    double a[3] = {1, 2, 3};
    double b[3] = {6, 4, -6};

    packArray(params->a, a, 3);
    packArray(params->b, b, 3);

    params->size = 1;
}

void getRandomArrays(funcParams_t *const params)
{
    srand(time(NULL));

    params->size = 1 + rand() % 1000;

    double a[MAX_SIZE];
    double b[MAX_SIZE];

    for (size_t i = 0; i < params->size; ++i)
    {
        a[i] = getDoubleRandom(-500, 500);
        b[i] = getDoubleRandom(-500, 500);
    }

    packArray(params->a, a, params->size);
    packArray(params->b, b, params->size);

    params->size = (params->size - 1) / 4 + 1;
}

int main(void)
{
    pack_t a[MAX_PACKED_SIZE] = {0};
    pack_t b[MAX_PACKED_SIZE] = {0};

    funcParams_t params = { .a = a, .b = b};

    getSimpleTest(&params);

    printf("C RES: %f\n", cScalarProd(params.a, params.b, params.size));
    printf("ASM RES: %f\n", asmScalarProd(params.a, params.b, params.size));

    getRandomArrays(&params);

    printf("C TIME: %g\n", getTime(params, cScalarProd));
    printf("ASM TIME: %g\n", getTime(params, asmScalarProd));

    return OK;
}
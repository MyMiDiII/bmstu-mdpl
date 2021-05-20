#include <stdio.h>

#include "times.h"
#include "c_scalar_prod.h"

#define OK 0 

#define MAX_SIZE 1000

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

int main(void)
{
    double a[MAX_SIZE];
    double b[MAX_SIZE];

    funcParams_t params = { .a = a, .b = b};

    getSimpleTest(&params);

    printf("C RES: %f", cScalarProd(params.a, params.b, params.size));

    return OK;
}
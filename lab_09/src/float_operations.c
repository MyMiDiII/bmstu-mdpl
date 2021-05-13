#include "float_operations.h"

int getFloatSize(void)
{
    return sizeof(float) * __CHAR_BIT__;
}

float getFloatCSum(float a, float b)
{
    return a + b;
}

float getFloatCProd(float a, float b)
{
    return a * b;
}

double getFloatFuncTime(float (*func)(float, float))
{
    float a = 1e5;
    float b = 11e-7;

    clock_t time = clock();
    
    for (size_t i = 0; i < REPEATS; ++i)
        func(a, b);

    time = clock() - time;

    return (double) time / CLOCKS_PER_SEC / REPEATS;
}

void printFloatCharacteristics()
{
    puts("FLOAT");
    printf("Size:     %9d bit\n", getFloatSize());
    printf("C   sum   %9.4g s\n", getFloatFuncTime(getFloatCSum));
    printf("C   prod: %9.4g s\n", getFloatFuncTime(getFloatCProd));
}

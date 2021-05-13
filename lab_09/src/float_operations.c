#include "float_operations.h"

int getFloatSize(void)
{
    return sizeof(float) * __CHAR_BIT__;
}

float getCSum(float a, float b)
{
    return a + b;
}

float getCProd(float a, float b)
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
    printf("Float size: %d;\n", getFloatSize());
    printf("C sum: %g с\n", getFloatFuncTime(getCSum));
    printf("C prod: %g с\n", getFloatFuncTime(getCProd));
}

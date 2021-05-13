#include "float_operations.h"

int getFloatSize(void)
{
    return sizeof(float) * __CHAR_BIT__;
}

float getFloatCSum(float a, float b)
{
    float res = a + b;
    return res;
}

float getFloatCProd(float a, float b)
{
    return a * b;
}

float getFloatAsmSum(float a, float b)
{
    float res;

    __asm__(
        "fld %1\n"
        "fld %2\n"
        "faddp\n"
        "fstp %0"
        : "=m" (res)
        : "m" (a), "m" (b)
    );

    return res;
}

float getFloatAsmProd(float a, float b)
{
    return a * b;
}

double getFloatFuncTime(float (*func)(float, float))
{
    float a = 2.3e38;
    float b = 1.1e38;

    clock_t start = clock();
    
    for (size_t i = 0; i < REPEATS; ++i)
        func(a, b);

    clock_t end = clock();

    return (double) (end - start) / CLOCKS_PER_SEC / REPEATS;
}

void printFloatCharacteristics()
{
    puts("FLOAT");
    printf("Size:     %9d bit\n", getFloatSize());
    printf(
        "C   sum   %9.4g s res = %g\n",
        getFloatFuncTime(getFloatCSum),
        getFloatCSum(2.3e38, 1.1e38)
    );
    printf(
        "ASM sum   %9.4g s res = %g\n",
        getFloatFuncTime(getFloatAsmSum),
        getFloatAsmSum(2.3e38, 1.1e38)
    );
    printf("C   prod: %9.4g s\n", getFloatFuncTime(getFloatCProd));
    printf("ASM prod: %9.4g s\n", getFloatFuncTime(getFloatAsmProd));
}

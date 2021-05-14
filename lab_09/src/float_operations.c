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
    float res = a * b;
    return res;
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
    float res;

    __asm__(
        "fld %1\n"
        "fld %2\n"
        "fmulp\n"
        "fstp %0"
        : "=m" (res)
        : "m" (a), "m" (b)
    );

    return res;
}

double getFloatFuncTime(float a, float b, float (*func)(float, float))
{
    clock_t start = clock();
    
    for (size_t i = 0; i < REPEATS; ++i)
        func(a, b);

    clock_t end = clock();

    return (double) (end - start) / CLOCKS_PER_SEC / REPEATS;
}

void printFloatCharacteristics()
{
    float a = 2.3e38;
    float b = 1.1e38;

    puts("FLOAT");
    printf("Size:     %9d bit\n", getFloatSize());
    printf(
        "C   sum   %9.4g s   res = %g\n",
        getFloatFuncTime(a, b, getFloatCSum),
        getFloatCSum(a, b)
    );
    printf(
        "ASM sum   %9.4g s   res = %g\n",
        getFloatFuncTime(a, b, getFloatAsmSum),
        getFloatAsmSum(a, b)
    );

    a = 2.3e19;
    b = 1.1e19;

    printf(
        "C   prod  %9.4g s   res = %g\n",
        getFloatFuncTime(a, b, getFloatCProd),
        getFloatCProd(a, b)
    );
    printf(
        "ASM prod  %9.4g s   res = %g\n",
        getFloatFuncTime(a, b, getFloatAsmProd),
        getFloatAsmProd(a, b)
    );
}

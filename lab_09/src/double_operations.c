#include "double_operations.h"

int getDoubleSize(void)
{
    return sizeof(double) * __CHAR_BIT__;
}

double getDoubleCSum(double a, double b)
{
    double res = a + b;
    return res;
}

double getDoubleCProd(double a, double b)
{
    double res = a * b;
    return res;
}

double getDoubleAsmSum(double a, double b)
{
    double res;

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

double getDoubleAsmProd(double a, double b)
{
    double res;

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

double getDoubleFuncTime(double a, double b, double (*func)(double, double))
{
    clock_t start = clock();
    
    for (size_t i = 0; i < REPEATS; ++i)
        func(a, b);

    clock_t end = clock();

    return (double) (end - start) / CLOCKS_PER_SEC / REPEATS;
}

void printDoubleCharacteristics()
{
    double a = 2.3e307;
    double b = 1.1e307;

    puts("DOUBLE");
    printf("Size:     %9d bit\n", getDoubleSize());
    printf(
        "C   sum   %9.4g s   res = %g\n",
        getDoubleFuncTime(a, b, getDoubleCSum),
        getDoubleCSum(a, b)
    );
    printf(
        "ASM sum   %9.4g s   res = %g\n",
        getDoubleFuncTime(a, b, getDoubleAsmSum),
        getDoubleAsmSum(a, b)
    );

    a = 2.3e153;
    b = 1.1e153;

    printf(
        "C   prod  %9.4g s   res = %g\n",
        getDoubleFuncTime(a, b, getDoubleCProd),
        getDoubleCProd(a, b)
    );
    printf(
        "ASM prod  %9.4g s   res = %g\n",
        getDoubleFuncTime(a, b, getDoubleAsmProd),
        getDoubleAsmProd(a, b)
    );
}

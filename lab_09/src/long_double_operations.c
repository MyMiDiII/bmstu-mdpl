#include "long_double_operations.h"

#ifdef X87
int getLongDoubleSize(void)
{
    return sizeof(long double) * __CHAR_BIT__;
}

long double getLongDoubleCSum(long double a, long double b)
{
    long double res = a + b;
    return res;
}

long double getLongDoubleCProd(long double a, long double b)
{
    long double res = a * b;
    return res;
}

long double getLongDoubleAsmSum(long double a, long double b)
{
    long double res;

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

long double getLongDoubleAsmProd(long double a, long double b)
{
    long double res;

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

double getLongDoubleFuncTime(long double a, long double b,
            long double (*func)(long double, long double))
{
    clock_t start = clock();
    
    for (size_t i = 0; i < REPEATS; ++i)
        func(a, b);

    clock_t end = clock();

    return (double) (end - start) / CLOCKS_PER_SEC / REPEATS;
}
#endif

void printLongDoubleCharacteristics()
{
    puts("LONG DOUBLE");

#ifdef X87
    long double a = 2.3e400L;
    long double b = 1.1e400L;

    printf("Size:     %9d bit\n", getLongDoubleSize());
    printf(
        "C   sum   %9.4g s   res = %Lg\n",
        getLongDoubleFuncTime(a, b, getLongDoubleCSum),
        getLongDoubleCSum(a, b)
    );
    printf(
        "ASM sum   %9.4g s   res = %Lg\n",
        getLongDoubleFuncTime(a, b, getLongDoubleAsmSum),
        getLongDoubleAsmSum(a, b)
    );

    printf(
        "C   prod  %9.4g s   res = %Lg\n",
        getLongDoubleFuncTime(a, b, getLongDoubleCProd),
        getLongDoubleCProd(a, b)
    );
    printf(
        "ASM prod  %9.4g s   res = %Lg\n",
        getLongDoubleFuncTime(a, b, getLongDoubleAsmProd),
        getLongDoubleAsmProd(a, b)
    );
#else
    puts("FORBIDDEN!!!");
#endif
}

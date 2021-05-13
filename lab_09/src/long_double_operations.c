#include "long_double_operations.h"

int getLongDoubleSize(void)
{
    return sizeof(long double) * __CHAR_BIT__;
}

long double getLongDoubleCSum(long double a, long double b)
{
    return a + b;
}

long double getLongDoubleCProd(long double a, long double b)
{
    return a * b;
}

double getLongDoubleFuncTime(long double (*func)(long double, long double))
{
    long double a = 1e5;
    long double b = 11e-7;

    clock_t time = clock();
    
    for (size_t i = 0; i < REPEATS; ++i)
        func(a, b);

    time = clock() - time;

    return (double) time / CLOCKS_PER_SEC / REPEATS;
}

void printLongDoubleCharacteristics()
{
    puts("LONG DOUBLE");
    printf("Size:     %9d bit\n", getLongDoubleSize());
    printf("C   sum:  %9.4g s\n", getLongDoubleFuncTime(getLongDoubleCSum));
    printf("C   prod: %9.4g s\n", getLongDoubleFuncTime(getLongDoubleCProd));
}

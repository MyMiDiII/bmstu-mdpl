#include "double_operations.h"

int getDoubleSize(void)
{
    return sizeof(double) * __CHAR_BIT__;
}

double getDoubleCSum(double a, double b)
{
    return a + b;
}

double getDoubleCProd(double a, double b)
{
    return a * b;
}

double getDoubleFuncTime(double (*func)(double, double))
{
    double a = 1e5;
    double b = 11e-7;

    clock_t time = clock();
    
    for (size_t i = 0; i < REPEATS; ++i)
        func(a, b);

    time = clock() - time;

    return (double) time / CLOCKS_PER_SEC / REPEATS;
}

void printDoubleCharacteristics()
{
    puts("DOUBLE");
    printf("Size:     %9d bit\n", getDoubleSize());
    printf("C   sum:  %9.4g s\n", getDoubleFuncTime(getDoubleCSum));
    printf("C   prod: %9.4g s\n", getDoubleFuncTime(getDoubleCProd));
}

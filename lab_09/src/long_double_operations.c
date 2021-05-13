#include "long_double_operations.h"

int getLongDoubleSize(void)
{
    return sizeof(long double) * __CHAR_BIT__;
}
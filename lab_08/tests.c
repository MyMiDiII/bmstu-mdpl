#include <stdio.h>
#include <string.h>

#include "tests.h"
#include "asmstr.h"

#define RESET   "\033[0m"
#define PASSED "\033[1;32mPASSED\033[0m\n"
#define FAILED "\033[1;31mFAILED\033[0m\n"


void len_test(const char *const test_string)
{
    size_t stdlen = strlen(test_string);
    size_t asmblen = asmlen(test_string);
    printf("strlen = %ld\n", stdlen);
    printf("asmlen = %ld\n", asmblen);
    printf("%s", (stdlen == asmblen) ? PASSED : FAILED);
}

void strcpy_test(char *const dst, const char *const src,
                 const size_t len, const char *const standart)
{
    printf("SRC: %s\n", src);
    printf("LEN: %lu\n", len);
    astrcpy(dst, src, len);
    printf("DST: %s\n", dst);
    printf("%s", !strcmp(dst, standart) ? PASSED : FAILED);
}

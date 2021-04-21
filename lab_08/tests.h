#ifndef TESTS_H

#define TESTS_H

#include <stddef.h>

void len_test(const char *const test_string);

void strcpy_test(char *const dst, const char *const src,
                 const size_t len, const char *const standart);

#endif
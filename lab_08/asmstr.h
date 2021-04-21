#ifndef ASMSTR_H
#define ASMSTR_H

#include <stddef.h>

size_t asmlen(const char *const string);
void astrcpy(char *dst, const char *src, const size_t len);

#endif
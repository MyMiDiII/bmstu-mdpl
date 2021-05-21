#ifndef PACK_H
#define PACH_H

#include <stddef.h>

#define MAX_SIZE 1000
#define MAX_PACKED_SIZE 250

typedef double pack_t[4];

void packArray(pack_t *const pack, const double *const arr, const size_t size);

#endif
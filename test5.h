#ifndef TEST5_H
#define TEST5_H
#include <stddef.h>
#include <stdint.h>
size_t naive(uint64_t *bitmap, size_t bitmapsize, uint32_t *out);
size_t improved(uint64_t *bitmap, size_t bitmapsize, uint32_t *out);
#endif

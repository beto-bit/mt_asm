#pragma once

#include <stddef.h>
#include <stdint.h>

void copy_buff(const void *src, void *dst, size_t n);

void fill_buff(void *buff, size_t len, uint8_t val);

uint64_t abs(int64_t num);

uint8_t log(uint64_t num, uint32_t base);

size_t strlen(const char* str);

/// Returns the index of the first of two adjacent pairs
size_t find_adjacent_chars(const char *str, char c);

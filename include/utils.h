#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void copy_buff(const void *src, void *dst, size_t n);

void fill_buff(void *buff, size_t len, uint8_t val);

uint64_t abs(int64_t num);

uint8_t log(uint64_t num, uint32_t base);

size_t strlen(const char* str);

/// Returns a pointer to the first character of two pairs
const char *find_adjacent_chars(const char *str, char c);

bool starts_with(const char *str, const char *substr);

/// Returns a pointer to the first character where the substring is
const char *find_substr(const char *str, const char *substr);

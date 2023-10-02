#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


/// Copies n bytes from src to dst
void copy_buff(const void *src, void *dst, size_t n);

/// Fills n bytes of buff with val
void fill_buff(void *buff, size_t len, uint8_t val);

/// Absolute value of number
uint64_t abs(int64_t num);

/// Integer logarithm (rounds up)
uint8_t log(uint64_t num, uint32_t base);

/// Length of null-terminated string
size_t strlen(const char* str);

/// Returns a pointer to the first character of two pairs
const char *find_adjacent_chars(const char *str, char c);

/// Checks if str starts with substr
bool starts_with(const char *str, const char *substr);

/// Returns a pointer to the first character where the substring is
const char *find_substr(const char *str, const char *substr);

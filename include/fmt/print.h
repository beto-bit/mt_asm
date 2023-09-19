#pragma once

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

// Defined in assembly
void print_char(char c);

// Defined in C file
size_t strlen(const char* str);
ssize_t print_str_n(const char* str, size_t len);
ssize_t print_str(const char* str);

char num_to_hex(uint8_t num);

size_t format_ten(char *buff, uint64_t num);


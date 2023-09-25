#pragma once

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

// Defined in assembly
void print_char(char c);

// Defined in C file
ssize_t print_str_n(const char* str, size_t len);
ssize_t print_str(const char* str);

// Formatting functions
char num_to_hex(uint8_t num);
size_t format_ten(char buff[20], int64_t num);
size_t format_hex(char buff[16], uint64_t num);

// Formatting types
enum FormatType {
    DEC,
    HEX
};

void format_num(int64_t num, enum FormatType format_type);

// Buffered format
/// Example:
/// printfmt("There are {} users", 42, DEC);
void printfmt(const char *str, int64_t num, enum FormatType format_type);

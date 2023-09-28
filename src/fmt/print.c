#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "calls.h"
#include "fmt/print.h"
#include "mem/buffering.h"
#include "utils.h"

ssize_t print_str_n(const char* str, size_t len) {
    return write(1, str, len);
}

ssize_t print_str(const char* str) {
    return write(1, str, strlen(str));
}

char num_to_hex(uint8_t num) {
    if (num > 15) return '?';

    if (num < 10) {
        return num + '0';
    } else {
        return num + 55;
    }
}

size_t format_ten(char buff[20], int64_t num) {
   bool negative = (num < 0) ? 1 : 0;
   num = abs(num);
   size_t index = 19;

   // Reverse enter characters in buffer
   while (1) {
       uint64_t div = num / 10;
       uint8_t mod = num % 10;

       buff[index] = num_to_hex(mod);

       if (!div) break;

       --index;
       num = div;
   }

   if (negative)
       buff[--index] = '-';

    return index;
}

size_t format_hex(char buff[16], uint64_t num) {
    size_t index = 15;

    // Reverse enter characters in buffer
    while (1) {
        uint64_t div = num / 16;
        uint8_t mod = num % 16;

        buff[index] = num_to_hex(mod);

        if (!div) break;

        --index;
        num = div;
    }

    // Enter suffix
    buff[--index] = 'x';
    buff[--index] = '0';

    return index;
}

size_t format_num(char buff[20], int64_t num, enum FormatType format_type) {
    if (format_type == DEC) {
        size_t offset = format_ten(buff, num);

        // Number string is at the bottom of the buffer
        return offset;
    }
    else if (format_type == HEX) {
        size_t offset = format_hex(buff, num);

        return offset;
    }

    // How do you get here?
    return 0;
}


// Buffering things
char global_buff[1024];

struct MemBuff stdout_membuff = {
    .buff = (uint8_t*) global_buff,
    .length = 0,
    .capacity = 1024
};

void append_format_num(
    struct MemBuff *membuff,
    int64_t num,
    enum FormatType format_type
) {
    char buff[20];
    size_t offset = format_num(buff, num, format_type);

    append_buff(membuff, (const uint8_t*) buff + offset, 20 - offset);
}

void printfmt(const char *str, int64_t num, enum FormatType format_type) {
    const char *format_break = find_substr(str, "{}");

    // Not formatted
    if (!format_break) {
        print_str(str);
        return;
    }

    size_t str_len = strlen(str);
    size_t first_len = format_break - str;
    size_t second_len = str_len - first_len - 2;

    // Add first part to buffer
    append_buff(&stdout_membuff, (const uint8_t*) str, first_len);

    // Add formatted number
    append_format_num(&stdout_membuff, num, format_type);

    // Add second part to buffer
    append_buff(&stdout_membuff, (const uint8_t*) format_break + 2, second_len);

    print_str_n((char*) stdout_membuff.buff, stdout_membuff.length);

    // The code above this should manage partial writes, but I am
    // too lazy so I am just gonna pretend this is actual flushing.
    stdout_membuff.length = 0;
}

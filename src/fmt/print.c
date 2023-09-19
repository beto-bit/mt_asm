#include <stddef.h>
#include <stdint.h>
#include "calls.h"
#include "fmt/print.h"
#include "utils.h"

size_t strlen(const char* str) {
    size_t len = 0;

    while (str[len]) {
        ++len;
    }

    return len;
}

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
   uint8_t negative = (num > 0) ? 0 : 1;
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

void format_num(int64_t num, enum FormatType format_type) {
    char buff[20];

    if (format_type == DEC) {
        short is_negative = (num < 0) ? 1 : 0;

        size_t len = format_ten(buff, num);

        // Number string is at the bottom of the buffer
        // Length is number of digits + (maybe) a negative sign
        print_str_n(buff + len, log(num, 10) + is_negative);

        return;
    }
    else if (format_type == HEX) {
        size_t len = format_hex(buff, num);

        // Number string is at the bottom of the buffer
        // Length is number of digits + 0x (2 digits)
        print_str_n(buff + len, log(num, 16) + 2);

        return;
    }
}

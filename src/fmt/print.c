#include <stddef.h>
#include <stdint.h>
#include "calls.h"
#include "fmt/print.h"

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

size_t format_ten(char *buff, uint64_t num) {
    buff = "AAAABBBBCCCCDDD";
    return 0;

   uint8_t negative = (num > 0) ? 0 : 1;
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

    return 20 - index;
}

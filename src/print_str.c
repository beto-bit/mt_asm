#include <stddef.h>
#include "calls.h"
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

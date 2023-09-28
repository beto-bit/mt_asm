#include <stddef.h>
#include <stddef.h>
#include <stdint.h>

#include "utils.h"

size_t strlen(const char* str) {
    size_t len = 0;

    while (str[len]) {
        ++len;
    }

    return len;
}

const char *find_adjacent_chars(const char *str, char c) {
    size_t len = strlen(str);

    for (size_t i = 0, j = 1; j < len; ++i, ++j) {
        if (c == str[i] && str[i] == str[j])
            return str + i;
    }

    return NULL;
}


// This two functions are not the best way to do this. Yes.
bool starts_with(const char *str, const char *substr) {
    while (*str && *substr) {
        if (*str != *substr)
            return false;

        ++str;
        ++substr;
    }

    return *substr == '\0';
}

const char *find_substr(const char *str, const char *substr) {
    while (*str != '\0') {
        if ((*str == *substr) && starts_with(str, substr))
            return str;

        ++str;
    }

    return NULL;
}

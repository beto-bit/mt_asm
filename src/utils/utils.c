#include <stddef.h>
#include <stdint.h>
#include "utils.h"

void fill_buff(uint8_t *buff, size_t len, uint8_t val) {
    for (size_t idx = 0; idx < len; ++idx) {
        buff[idx] = val;
    }
}

uint64_t abs(int64_t num) {
    return (num > 0) ? num : num * -1;
}

uint8_t log(uint64_t num, uint32_t base) {
    uint8_t count = 1;

    while (1) {
        uint64_t div = num / base;

        if (!div) break;

        ++count;
        num = div;
    }

    return count;
}


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

#include "utils.h"


void copy_buff(const void *src, void *dst, size_t n) {
    const uint8_t *src_buff = (const uint8_t*) src;
    uint8_t *dst_buff = (uint8_t*) dst;

    for (size_t idx = 0; idx < n; ++idx) {
        dst_buff[idx] = src_buff[idx];
    }
}

void fill_buff(void *buff, size_t len, uint8_t val) {
    uint8_t *buffer = (uint8_t *)buff;

    for (size_t idx = 0; idx < len; ++idx) {
        buffer[idx] = val;
    }
}

uint64_t abs(int64_t num) {
    return (num >= 0) ? num : num * -1;
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

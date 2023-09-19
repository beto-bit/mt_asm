#pragma once

#include <stddef.h>
#include <stdint.h>

void fill_buff(uint8_t *buff, size_t len, uint8_t val);

uint64_t abs(int64_t num);

uint8_t log(uint64_t num, uint32_t base);


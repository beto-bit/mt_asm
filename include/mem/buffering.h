#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

struct MemBuff {
    uint8_t *buff;
    size_t length;
    size_t capacity;
};

size_t remaining_bytes(struct MemBuff *membuff);

/// Appends a single byte. Returns false on error.
bool append_byte(struct MemBuff *membuff, uint8_t byte);

/// Returns the remaining number of bytes to append
size_t append_buff(struct MemBuff *membuff, const uint8_t *buff, size_t size);


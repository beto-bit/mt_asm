#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "mem/buffering.h"


size_t remaining_bytes(struct MemBuff *membuff) {
    return membuff->capacity - membuff->length;
}

bool append_byte(struct MemBuff *membuff, uint8_t byte) {
    if (remaining_bytes(membuff) > 0 ) {
        // Beacause is postfix++, the length gets incremented later
        membuff->buff[membuff->length++] = byte;
        return true;
    }

    return false;
}

size_t append_buff(struct MemBuff *membuff, const uint8_t *buff, size_t size) {
    size_t idx;

    // Copy the bytes
    for (idx = 0; membuff->length < membuff->capacity; ++membuff->length) {
        // Check buffer boundaries
        if (idx >= size) break;

        // Storing to mbuff[len] because len always points to one element above
        membuff->buff[membuff->length] = buff[idx];
        ++idx;
    }

    return size - idx;
}

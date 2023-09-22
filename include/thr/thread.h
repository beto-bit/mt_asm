#pragma once

#include <stddef.h>
#include <stdint.h>

#include "calls.h"
#include "flags.h"

struct Thread {
    int tid;
    volatile uint8_t finished;
    void *stack;
    size_t stack_size;
};

void create_thread(struct Thread *thrd, int (*fn)(void*), void *arg);
void clean_thread(struct Thread *thrd);


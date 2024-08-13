#pragma once

#include <stdatomic.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


struct Thread {
    int tid;
    atomic_bool finished;
    void *stack;
    size_t stack_size;
    int (*fn)(void *);
    void *arg;
};

/// Creates a new thread and stores it inside *thrd
void create_thread(struct Thread *thrd, int (*fn)(void*), void *arg);

/// Brute force waits the thread (without using futex)
void clean_thread(struct Thread *thrd);

/// Wait the thread until it's done
void join_thread(struct Thread *thrd);

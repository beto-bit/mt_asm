#include <stdint.h>
#include "calls.h"
#include "fmt/print.h"
#include "thr/thread.h"
#include "mem/flags.h"

#define STACK_SIZE 1024 * 1024  // 1 MB
#define FLAGS CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD


static int start_thread(void *arg) {
    struct Thread *thrd = (struct Thread*) arg;

    int exit_code = thrd->fn(thrd->arg);

    // Finish the thread
    thrd->finished = 1;

    return exit_code;
}


void create_thread(struct Thread *thrd, int (*fn)(void *), void *arg) {
    // Allocate memory for the thread
    void *stack = mmap(
        NULL,
        STACK_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANON,
        -1,
        0
    );

    thrd->stack = stack;
    thrd->stack_size = STACK_SIZE;
    thrd->finished = 0;
    thrd->fn = fn;
    thrd->arg = arg;

    int tid = bare_clone2(FLAGS, (uint8_t*)stack + STACK_SIZE, start_thread, thrd);

    thrd->tid = tid;
}


void clean_thread(struct Thread *thrd) {
    while (!thrd->finished);
    munmap(thrd->stack, thrd->stack_size);
}


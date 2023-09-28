#include <stdint.h>

#include "calls.h"
#include "thr/futex.h"
#include "thr/thread.h"
#include "thr/flags.h"
#include "mem/flags.h"


#define STACK_SIZE 1024 * 1024  // 1 MB
#define FLAGS CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD

const int CLONE_FLAGS
    = CLONE_VM | CLONE_FS | CLONE_FILES         // Share address space
    | CLONE_SIGHAND | CLONE_THREAD              // Signaling
    | CLONE_PARENT_SETTID | CLONE_CHILD_SETTID  // Store child's TID
    | CLONE_CHILD_CLEARTID;                     // Clear the child's TID when child exits


static int start_thread(void *arg) {
    struct Thread *thrd = (struct Thread*) arg;

    int exit_code = thrd->fn(thrd->arg);

    // Finish the thread
    thrd->finished = true;

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
    thrd->finished = false;
    thrd->fn = fn;
    thrd->arg = arg;

    thrd->tid = clone3(
        &(struct clone_args) {
            .flags = CLONE_FLAGS,
            .stack = stack,
            .stack_size = STACK_SIZE,

            // Store TID in the same place for parent and child
            .child_tid = &thrd->tid,
            .parent_tid = &thrd->tid,
        },
        sizeof(struct clone_args),
        start_thread,
        thrd
    );
}


void clean_thread(struct Thread *thrd) {
    while (!thrd->finished);
    munmap(thrd->stack, thrd->stack_size);
}

void join_thread(struct Thread *thrd) {
    if (!thrd->finished) {
        futex(
            (uint32_t*) &thrd->tid,
            FUTEX_WAIT_BITSET | FUTEX_CLOCK_REALTIME,
            thrd->tid,
            NULL,
            NULL,
            FUTEX_BITSET_MATCH_ANY
        );
    }

    munmap(thrd->stack, thrd->stack_size);
}

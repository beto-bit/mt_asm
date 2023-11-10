#include <stdint.h>

#include "low/calls.h"
#include "sync/clone_flags.h"
#include "sync/futex_flags.h"
#include "sync/thread.h"
#include "mem/flags.h"


#define STACK_SIZE 1024 * 1024  // 1 MB

const int CLONE_FLAGS
    = CLONE_VM | CLONE_FS | CLONE_FILES         // Share address space
    | CLONE_SIGHAND | CLONE_THREAD              // Signaling
    | CLONE_PARENT_SETTID | CLONE_CHILD_SETTID  // Store child's TID
    | CLONE_CHILD_CLEARTID;                     // Clear the child's TID when child exits


static int start_thread(void *arg) {
    struct Thread *thrd = (struct Thread*) arg;

    // Call the actual function
    int exit_code = thrd->fn(thrd->arg);

    // Mark the thread as finished
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
    // Basically, only wait if not finished
    if (!thrd->finished) {
        // Apparently, according to glibc, the kernel notifies a process
        // that uses CLONE_CHILD_CLEARTID via a futex wake-up. The kernel
        // sets the value at that memory location to 0.
        futex(
            (uint32_t*) &thrd->tid,
            FUTEX_WAIT,
            thrd->tid,
            NULL,
            NULL,
            0
        );
    }

    munmap(thrd->stack, thrd->stack_size);
}

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdnoreturn.h>
#include <sys/types.h>


/// Just the necesary clone_args
struct clone_args {
    size_t flags;
    void *pidfd;        // where to store PID file descriptor
    void *child_tid;    // where to store child's TID
    void *parent_tid;   // ^- The same
    size_t exit_signal; // Signal delivered to parent on child termination
    void *stack;
    size_t stack_size;
    size_t tls;         // Location of new TLS
};


/// Futex copied from the man page (that's even worse)
typedef long time_t;

struct timespec {
    time_t tv_sec;  // seconds
    long tv_nsec;   // nanoseconds
};


// Basic utilities
ssize_t write(int fd, const void *buf, size_t count);
noreturn void exit(int exit_code);

// Memory
void *mmap(void *start, size_t len, int prot, int flags, int fd, off_t off);
int munmap(void *addr, size_t len);

// Time
int nanosleep(const struct timespec *req, struct timespec *rem);


/// If you are in the parent thread, it returns the child TID.
/// If you are in the child, it returns 0.
/// Returns the corresponding error otherwise.
int bare_clone(
    int flags,
    void *stack,
    pid_t *parent_tid,
    pid_t *child_tid,
    void *tls
);

/// If you are in the parent thread, it returns the child TID.
/// Returns the corresponding error otherwise.
int bare_clone2(
    int flags,
    void *stack,
    int (*fn) (void *arg),
    void *arg
);

/// Clone 3 copy from glibc
int clone3(
    struct clone_args *cl_args,
    size_t size,
    int (*fn) (void *arg),
    void *arg
);


int futex(
    uint32_t *uaddr,
    int futex_op,
    uint32_t val,
    const struct timespec *timeout,
    uint32_t *uaddr2,
    uint32_t val3
);

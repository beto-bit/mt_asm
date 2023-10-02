#pragma once

#include <cstddef>
#include <cstdint>
#include <sys/types.h>


namespace low {
extern "C" {


using std::size_t, std::uint8_t;

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

struct own_timespec {
    time_t tv_sec;  // seconds
    long tv_nsec;   // nanoseconds
};


// Basic utilities
ssize_t write(int fd, const void *buf, size_t count);
[[noreturn]] void thunk_exit(int exit_code);

// Memory
[[nodiscard]] void *mmap(void *start, size_t len, int prot, int flags, int fd, off_t off);
int munmap(void *addr, size_t len);

// Time
int thunk_nanosleep(const struct own_timespec *req, struct own_timespec *rem);


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
    const struct own_timespec *timeout,
    uint32_t *uaddr2,
    uint32_t val3
);

// The only real utility function
void print_char(char c);


} // extern "C"
} // namespace low

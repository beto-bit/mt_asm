#pragma once

#include <cstddef>
#include <cstdint>
#include "beto/calls.h"
#include "beto/clone_flags.h"
#include "beto/futex_flags.h"


namespace syncs {


constexpr size_t STACK_SIZE = 1024 * 1024;

constexpr int CLONE_FLAGS
    = CLONE_VM | CLONE_FS | CLONE_FILES         // Share address space
    | CLONE_SIGHAND | CLONE_THREAD              // Signaling
    | CLONE_PARENT_SETTID | CLONE_CHILD_SETTID  // Store child's TID
    | CLONE_CHILD_CLEARTID;                     // Clear the child's TID when child exits


template<typename FuncPtr, typename T>
class Thread
{
private:
    int m_tid;
    volatile bool m_finished;
    void* m_stack;
    FuncPtr m_func;
    T m_arg;

    static int start_thread(Thread* thrd) {
        int exit_code = thrd->m_func(thrd->m_arg);

        // Mark the thread as finished
        thrd->m_finished = true;

        // Real exit
        return exit_code;
    }


public:
    // Delete copy operators
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    Thread(FuncPtr func, T arg)
        : m_finished(false), m_func(func), m_arg(arg)
    {
        // Allocate stack
        void* stack = ::operator new(STACK_SIZE);

        // Create new thread
        low::clone_args cl_args {
            .flags = CLONE_FLAGS,
            .pidfd = nullptr,
            .child_tid = &this->m_tid,
            .parent_tid = &this->m_tid,
            .exit_signal = 0,
            .stack = stack,
            .stack_size = STACK_SIZE,
            .tls = 0
        };

        int tid = low::clone3(
            &cl_args,
            sizeof(cl_args),
            reinterpret_cast<int (*)(void*)>(start_thread),
            reinterpret_cast<void*>(this)
        );

        m_stack = stack;
        m_tid = tid;
    }

    void join() {
        if (!m_finished) {
            low::futex(
                (uint32_t*) &this->m_tid,
                FUTEX_WAIT_BITSET | FUTEX_CLOCK_REALTIME,
                m_tid,
                NULL,   // Timeout
                NULL,   // Ignored
                FUTEX_BITSET_MATCH_ANY
            );
        }

        ::operator delete(m_stack);
    }
};


} // namespace syncs

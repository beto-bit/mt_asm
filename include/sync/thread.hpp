#pragma once

#include <cstddef>
#include <cstdint>

#include "unlibc++/calls.hpp"
#include "unlibc++/clone_flags.h"
#include "unlibc++/futex_flags.h"

#include "func/functional.hpp"


namespace syn {


constexpr size_t STACK_SIZE = 1024 * 1024;

constexpr int CLONE_FLAGS
    = CLONE_VM | CLONE_FS | CLONE_FILES         // Share address space
    | CLONE_SIGHAND | CLONE_THREAD              // Signaling
    | CLONE_PARENT_SETTID | CLONE_CHILD_SETTID  // Store child's TID
    | CLONE_CHILD_CLEARTID;                     // Clear the child's TID when child exits


template<typename Arg>
class SimThread
{
    using ThreadFunc = FuncPtr<int(Arg)>;

    int m_tid;
    void* m_stack;
    ThreadFunc m_func;
    Arg m_arg;
    volatile bool m_finished;

    static int start_thread(SimThread* thrd) {
        int exit_code = thrd->m_func(thrd->m_arg);
        thrd->m_finished = true;
        
        // Real exit code
        return exit_code;
    }


public:
    SimThread(int (*func)(Arg), Arg arg)
        : m_func(func), m_arg(arg), m_finished(false)
    {
        // Allocate stack
        void* stack = ::operator new(STACK_SIZE);

        // Needed clone arguments
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

        // Create the new thread
        low::clone3(
            &cl_args,
            sizeof(cl_args),
            reinterpret_cast<int (*)(void*)>(start_thread),
            reinterpret_cast<void*>(this)
        );

        // Store info
        m_stack = stack;
    }

    int get_tid() const {
        return m_tid;
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

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
    {}
};


} // namespace syncs

#pragma once

template<typename Signature>
struct FuncPtr;

template<typename ReturnType, typename... Args>
struct FuncPtr<ReturnType(Args...)> {
    ReturnType (*func_ptr)(Args...);

    FuncPtr(ReturnType (*func)(Args...)) : func_ptr(func) {}

    ReturnType operator()(Args... args) {
        return func_ptr(args...);
    }
};

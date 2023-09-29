extern cpp_entry

section .text

global _start
_start:
    mov rdi, [rsp]      ; argc
    lea rsi, [rsp + 8]  ; argv
    call cpp_entry

    ; exit with code
    mov edi, eax
    mov eax, 60
    syscall
    hlt

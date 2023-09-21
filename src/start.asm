extern main

section .text

global _start
_start:
    mov rdi, [rsp]      ; argc
    lea rsi, [rsp + 8]  ; argv
    call main

    ; exit with code
    mov edi, eax
    mov eax, 60
    syscall
    hlt

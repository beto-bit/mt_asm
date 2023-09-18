global print_char

section .text

; rdi - The character
print_char:
    push rdi
    mov eax, 1      ; syscall
    mov edi, 1      ; stdout
    mov rsi, rsp    ; message
    mov rdx, 1      ; length = 1
    syscall

    pop rdi
    ret
    

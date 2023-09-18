global exit

section .text

; exits with code in rdi
exit:
    mov eax, 60
    syscall
    hlt

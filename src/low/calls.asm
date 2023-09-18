global write, exit

section .text

; does the same as libc equivalent
; ssize_t write(int fd, const void *buf, size_t count)
write:
    mov eax, 1  ; write syscall
    syscall
    ret


; exits with code in rdi
exit:
    mov eax, 60
    syscall
    hlt

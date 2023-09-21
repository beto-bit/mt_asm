global write, exit
global mmap, munmap

%define SYS_WRITE 1
%define SYS_EXIT 60
%define SYS_MMAP 9
%define SYS_MUNMAP 11

section .text

; does the same as libc equivalent
; ssize_t write(int fd, const void *buf, size_t count)
write:
    mov eax, SYS_WRITE
    syscall
    ret

; exits with code in rdi
exit:
    mov eax, SYS_EXIT
    syscall
    hlt

; raw mmap syscall
mmap:
    mov eax, SYS_MMAP
    mov r10, rcx    ; the only different register
    syscall
    ret

; raw mmunmap syscall
munmap:
    mov eax, SYS_MUNMAP
    syscall
    ret

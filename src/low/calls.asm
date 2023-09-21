global write, exit
global mmap, munmap

; Basic utilities
%define SYS_WRITE 1
%define SYS_EXIT 60

; Memory
%define SYS_MMAP 9
%define SYS_MUNMAP 11

section .text

; Does the same as libc equivalent
; ssize_t write(int fd, const void *buf, size_t count)
;
; rdi: The File Descriptor
; rsi: The buffer passed to it
; rdx: The amount to be written
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
; the same signature as libc equivalent
mmap:
    mov eax, SYS_MMAP
    mov r10, rcx    ; the only different register
    syscall
    ret

; raw mmunmap syscall
; the same signature as libc equivalent
munmap:
    mov eax, SYS_MUNMAP
    syscall
    ret


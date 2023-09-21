global write, exit
global mmap, munmap
global bare_clone

; Basic utilities
%define SYS_WRITE 1
%define SYS_EXIT 60

; Memory
%define SYS_MMAP 9
%define SYS_MUNMAP 11

; Forking
%define SYS_CLONE 56


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


; Implementation highly inspired (copied) from https://github.com/bminor/glibc/blob/master/sysdeps/unix/sysv/linux/x86_64/clone.S
; Also, using this trick: https://nullprogram.com/blog/2015/05/15/
; using clone instead of clone3 because is easier

; rdi: Flags
; rsi: Child stack
; rdx: Parent TID
; rcx: Child TID
;  r8: TLS (Thread Local Storage) Descriptor

; rcx gets into r10 by syscall calling convention
bare_clone:
    ; push the caller address into the new stack so it returns there
    mov rax, [rsp]
    mov [rsi - 8], rax

    ; mov the new stack pointer so when returning it pops off
    ; the return address we want
    sub rsi, 8

    mov eax, SYS_CLONE
    mov r10, rcx
    syscall

    ret

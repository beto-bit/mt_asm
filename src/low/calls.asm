global write, exit
global mmap, munmap
global nanosleep
global bare_clone, bare_clone2, clone3
global futex


; Basic utilities
%define SYS_WRITE 1
%define SYS_EXIT 60

; Memory
%define SYS_MMAP 9
%define SYS_MUNMAP 11

; Forking
%define SYS_CLONE 56
%define SYS_CLONE3 435

; Syncing
%define SYS_NANOSLEEP 35
%define SYS_FUTEX 202


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


; raw nanosleep syscall
; the same signature as libc equivalent
nanosleep:
    mov eax, SYS_NANOSLEEP
    syscall
    ret


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


; the same as before but easier to use and less error prone
; Implementation highly inspired (copied) from https://github.com/bminor/glibc/blob/master/sysdeps/unix/sysv/linux/x86_64/clone.S
; rdi: flags
; rsi: child_stack
; rdx: function
; rcx: function argument
bare_clone2:
    ; Align stack to 16 bytes
    and sil, 0

    ; Save the function and argument across the syscall
    sub rsi, 16
    mov [rsi], rcx      ; the argument
    mov [rsi + 8], rdx  ; the function

    ; Do the syscall
    mov eax, SYS_CLONE
    syscall

    test rax, rax   ; check if in child or parent
    jz .thread_start
    ret ; return home

.thread_start:
    ; The ABI sugests this and glibc does it
    xor ebp, ebp

    pop rdi ; the argument
    pop rax ; the function

    ; call the the function
    call rax

    ; exit with return value from function
    mov edi, eax
    mov eax, SYS_EXIT
    syscall
    hlt


; Clone 3 copy from glibc: https://codebrowser.dev/glibc/glibc/sysdeps/unix/sysv/linux/x86_64/clone3.S.html
; rdi: struct clone_args *cl_args
; rsi: size_t size
; rdx: function
; rcx: arg
clone3:
    ; store arg in r8 which is preserved across the syscall
    ; rdx is also preserved
    mov r8, rcx

    mov eax, SYS_CLONE3
    syscall

    test rax, rax
    jz .thread_start
    ret

.thread_start:
    ; the ABI suggets this I guess
    xor ebp, ebp
    and spl, 0

    ; set up the argument and call the function
    mov rdi, r8
    call rdx

    ; exit with return value from function
    mov edi, eax
    mov eax, SYS_EXIT
    syscall
    hlt


; Basic futex wrapper. All arguments should be in their places.
futex:
    mov r10, rcx
    mov eax, SYS_FUTEX
    syscall
    ret

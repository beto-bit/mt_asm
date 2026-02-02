.global write, exit
.global mmap, munmap
.global nanosleep
.global bare_clone, bare_clone2, clone3
.global futex

// Syscalls
.equ SYS_WRITE,     64
.equ SYS_EXIT,      93

.equ SYS_MMAP,      90
.equ SYS_MUNMAP,    91

.equ SYS_CLONE,     120
.equ SYS_CLONE3,    435

.equ SYS_NANOSLEEP, 101
.equ SYS_FUTEX,     98


// Code
.section .text

// ssize_t write(int fd, const void* buff, size_t count)
write:
    mov x8, SYS_WRITE
    svc 0
    ret

// [[noreturn]] exit(int code)
exit:
    mov x8, SYS_EXIT
    svc 0
    hlt 0

mmap:
    mov x8, SYS_MMAP
    svc 0
    ret

munmap:
    mov x8, SYS_MUNMAP
    svc 0
    ret

nanosleep:
    mov x8, SYS_NANOSLEEP
    svc 0
    ret

bare_clone:
    ret

bare_clone2:
    ret

// Clone 3 copy from glibc: https://codebrowser.dev/glibc/glibc/sysdeps/unix/sysv/linux/aarch64/clone3.S.html
// x0: struct clone_args *cl_args
// x1: size_t size
// x2: int function(void*)
// x3: void* arg
clone3:
    ret

futex:
    mov x8, SYS_FUTEX
    svc 0
    ret

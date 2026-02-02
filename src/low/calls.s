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

.equ SYS_NANOSLEEP, 162
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

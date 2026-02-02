.global _start
.extern main

.equ SYS_EXIT,  93

.section .text
_start:
    ldr x0, [sp]    // argc
    add x1, sp, 8   // argv
    bl main

    mov x8, SYS_EXIT
    svc #0
    hlt #0

.global print_char

.equ SYS_WRITE, 64
.equ STDOUT, 1

.section .text

// w0 - The character
print_char:
    str w0, [sp, -16]!

    mov w0, STDOUT
    mov x1, sp
    mov w2, 1

    mov w8, SYS_WRITE
    svc 0

    sub sp, sp, 16
    ret

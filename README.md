# mt_asm
Multithreading on GNU/Linux x86_64 from scratch.
The C++ version is in the other branch.

# Why? How?
I don't have anything better to do. So I created a thread pseudo-library. And formatting utilities.
I'm not using the standard library, only using utility headers like `<stddef.h>` or `<stdint.h>`.
Also, stealed some definitions from some libc implementations.
Apart from that, it only uses raw system calls in assembly.

# Build
You will need `make`, `nasm`, `gcc` and `ld`.
Clone it, and then run:

```bash
make
make run
```

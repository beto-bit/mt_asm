# mt_asm
Multithreading on GNU/Linux ARM64 from scratch.

# Why? How?
I don't have anything better to do. So I created a thread pseudo-library. And formatting utilities.
I'm not using the standard library, only using utility headers like `<stddef.h>` or `<stdint.h>`.
Also, stealed some definitions from some libc implementations.
Apart from that, it only uses raw system calls in assembly.

Currently, it has limited support for multithreading!

# Build
You will need cross-compilations tools:
* `aarch64-linux-gnu-ld`
* `aarch64-linux-gnu-as`
* `aarch64-linux-gnu-gcc`

# Run
It is needed `qemu-user-static`.
```
make run
```

It has support for debugging via `aarch64-linux-gnu-gdb`
```
make debug
```

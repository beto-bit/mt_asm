# mt_asm
Multithreading on GNU/Linux x86_64 from scratch.

# Why? How?
I don't have anything better to do. So I created a thread pseudo-library.
I'm not using the standard library, though I am doing an extensive use of the STL, like using `std::string_view` or the use of C++20 concepts.
Also, stealed several `mem<thing>` definitions from MUSL.
Everything else is making use of raw system calls.

# unlibc++
I created a static library which defines several symbols (like `write` or `_start`) and the call to `main`.
If you want to change the C++ compiler, you must specify the compiler in [unlibc++](https://github.com/beto-bit/mt_asm/blob/cpp/unlibc%2B%2B/Makefile) and in the root Makefile.

# Build
You will need `make`, `nasm`, `gcc`/`clang`, `g++`/`clang++` and `ld`.
Clone it, and then run:

```bash
make
make run
```

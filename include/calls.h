#pragma once

#include <stddef.h>
#include <stdnoreturn.h>
#include <sys/types.h>

ssize_t write(int fd, const void *buf, size_t count);

noreturn void exit(int exit_code);

void *mmap(void *start, size_t len, int prot, int flags, int fd, off_t off);
int munmap(void *addr, size_t len);

#pragma once

#include <stddef.h>
#include <stdnoreturn.h>
#include <sys/types.h>

ssize_t write(int fd, const void *buf, size_t count);

noreturn void exit(int exit_code);

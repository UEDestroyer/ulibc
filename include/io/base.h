#pragma once
#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "low-access-UEDestroyer/funcs/linux.h"
#include "low-access-UEDestroyer/defines/fcntl.h"
#include "../str/convert.h"
#include "../str/base.h"
#include "../mem/base.h"
#include "../mem/heap.h"

// io уже довольно высокоуровневый errno обязателен
#include "../macro/base.h"


#include "../fcntl/base.h"

#if gnu
#include "fcntl/gnu.h"
#endif


#include <stdarg.h>


ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);
int open(const char *pathname, int flags, ...);

int creat(const char *pathname, mode_t mode);
off_t lseek(int fd, off_t offset, int whence);

int dup(int oldfd);
int dup2(int oldfd, int newfd);

int pipe(int pipefd[2]);
ssize_t pread(int fd, void *buf, size_t count, off_t offset);
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
int ftruncate(int fd, off_t length);
int fsync(int fd);
int fdatasync(int fd);

int fcntl(int fd, int cmd, ...);

#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "include/str/base.h"

static inline long sys_write(int fd, const void *buf, long  count)
{
    return raw_syscall(SYS_write, fd, buf, count);
} 
static inline long  sys_exit(int error_code)
{
    return raw_syscall(SYS_exit, error_code);
}

void print(const char* s){
    sys_write(1,s,strlen(s));
    return;
}

void _start(){
    print("hello world");
    sys_exit(0);
}
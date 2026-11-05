#include "base/process.h"


int _exit(int status){
    ue_exit_group(status);
    return 0;
}
int _exit_thread(int status){
    ue_exit(status);
    return 0;
}


DEF_SYSCALL(pid_t, getpid, (), ())
DEF_SYSCALL(pid_t, getppid, (), ())
DEF_SYSCALL(pid_t, gettid, (), ())
DEF_SYSCALL(pid_t, getuid, (), ())
DEF_SYSCALL(pid_t, getgid, (), ())

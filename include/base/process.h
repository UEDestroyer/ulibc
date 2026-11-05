#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "low-access-UEDestroyer/funcs/linux.h"

#include "macro/base.h"
#if ERRNO_MACRO
#include "errno.h"
#endif


int _exit(int status);
int _exit_thread(int status);

pid_t getpid();
pid_t getppid();
pid_t gettid();
pid_t getuid();
pid_t getgid();




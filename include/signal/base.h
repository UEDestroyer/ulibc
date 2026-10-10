#include "defines/x86_64/linux.h"
#include "funcs/linux.h"
#include "defines/flags_linux.h"
#include "mem/base.h"

typedef void (*sighandler_t)(int);


sighandler_t signal(int signum, sighandler_t handler);


int sigemptyset(sigset_t *set);

int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
int sigismember(const sigset_t *set, int signum);


int raise(int sig);
int sigprocmask(int how,const sigset_t *set,sigset_t *oldset); // how,what and why 
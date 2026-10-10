#include "signal/base.h"


int signals[] = {SIGHUP,SIGINT,SIGQUIT,SIGILL,SIGTRAP,SIGABRT,SIGBUS,
SIGFPE,SIGKILL,SIGUSR1,SIGSEGV,SIGUSR2,SIGPIPE,SIGALRM,SIGTERM,SIGSTKFLT,SIGCHLD,SIGCONT,
SIGSTOP,SIGTSTP,SIGTTIN,SIGTTOU,SIGURG,SIGXCPU,SIGXFSZ,SIGVTALRM,SIGPROF,SIGWINCH,SIGPOLL,SIGPWR,SIGSYS,
SIGRTMIN,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,SIGRTMAX};

// sighandler_t handlers[64] = {
//     SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL,
//     SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL,
//     SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL,
//     SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL,
//     SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL,
//     SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL,
//     SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL,
//     SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL, SIG_DFL
// };

sighandler_t signal(int signum, sighandler_t handler){
    if (signum<=0 || signum>=65) return NULL;
    struct sigaction sigT;
    struct sigaction *sig = &sigT;
    sig->sa_handler = (unsigned long long)handler;
    sig->sa_flags = (unsigned long long)NULL;
    memset(sig->sa_mask,0,sizeof(sig->sa_mask));
    sig->sa_restorer = (unsigned long long)NULL;
    struct sigaction old;

    int err = rt_sigaction(signum, sig, &old,LINUX_SIGSET_SIZE);
    if (err<0){
        return NULL;
    }
    return (sighandler_t) old.sa_handler;
}
int sigemptyset(sigset_t *set){
    if (set==NULL){
        return -1;
    }
    memset(set,0,sizeof(*set));
    return 0;
}

int sigaddset(sigset_t *set, int signum){
    if (!set || signum<=0 || signum>=NSIG) return -1;
    set->__val[(signum - 1) / 64] |= (1UL << ((signum - 1) %64));
    return 0;
}

int sigdelset(sigset_t *set, int signum){
    if (!set || signum<=0 || signum>=NSIG) return -1;
    set->__val[(signum - 1) / 64] &= ~(1UL << ((signum - 1) %64));
    return 0;
}
int sigismember(const sigset_t *set, int signum){
    if (!set || signum<=0 || signum>=NSIG) return -1;
    return (set->__val[(signum - 1) / 64] & (1UL << ((signum - 1) %64))) != 0;
}
int raise(int sig){
    return kill(getpid(),sig);
}
int sigprocmask(int how,const sigset_t *set,sigset_t *oldset){
    return rt_sigprocmask(how,set,oldset,LINUX_SIGSET_SIZE);
}
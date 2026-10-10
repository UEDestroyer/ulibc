#include "base/assert.h"

void abort(void){
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set,SIGABRT);

    sigprocmask(SIG_UNBLOCK, &set,NULL);
    raise(SIGABRT);

    signal(SIGABRT,SIG_DFL);

    raise(SIGABRT);

    _exit(-127);
}

void __assert_fail(const char *assertion,const char *file,unsigned int line,const char *function){
#define out(aCs) write(1,aCs,strlen(aCs));

    out("assertion failed: ")
    out(assertion)
    out(" at ")
    out(file)
    out(":")
    char buf[128];
    itoa(line,buf);
    out(buf)
    out(" (")
    out(function)
    out(")")

    abort();

#undef out
}
#include "base/errno.h"

#if !ERRNO_MACRO
static int errno_s = 0;

int* __errno_location(void){
    return &errno_s;
}
#else
int* __attribute__((__const__)) __errno_location(void){
    return &(get_current_tls()->err);
}
#endif

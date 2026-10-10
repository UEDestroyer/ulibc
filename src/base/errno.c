#include "base/errno.h"
int* __errno_location(void){
    return &get_current_tls()->err;
}
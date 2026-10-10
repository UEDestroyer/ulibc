#include "io/base.h"
#include "str/convert.h"
#include "mem/heap.h"
#include "thread/base.h"
#include "base/errno.h"
#include "base/assert.h"
#include "/mnt/H/include/low-access-UEDestroyer/defines/fcntl.h"


void _start(){ 
    thread_init();

    int a = 1;

    assert(a==0);


    

    
    _exit(0);
}
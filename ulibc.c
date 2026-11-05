#include "io/base.h"
#include "io/format.h"
#include "str/convert.h"
#include "mem/heap.h"
#include "thread/base.h"
#include "base/errno.h"
#include "base/assert.h"
#include "/mnt/H/include/low-access-UEDestroyer/defines/fcntl.h"


void _start(){ 
    thread_init();
    
    int a = 0;

    assert(a == 0);
    
    printf("hi, this is all test now\n %d", a);

    ue_exit(0);
}
#include "thread/base.h"




struct ulibc_tls* get_current_tls(void){
    struct ulibc_tls *tls;
    __asm__ volatile("movq %%fs:0, %0" : "=r"(tls));
    return tls;
}

int set_current_tls(struct ulibc_tls *tls){
    tls->self = tls;
    return arch_prctl(ARCH_SET_FS,(unsigned long)tls);
}



struct ulibc_tls *tls_create(void){
    struct ulibc_tls* ptr = (struct ulibc_tls*)Fmalloc(sizeof(struct ulibc_tls));
    if (ptr== NULL){
        return NULL;
    }
    ptr->err = 0;
    ptr->thread = 0;
    return ptr;
}


void tls_destroy(struct ulibc_tls *tls){
    Ffree(tls);
}

int thread_init(void){
    struct ulibc_tls* ptr = tls_create();
    if (ptr==NULL){
        return -1;
    }
    int res = set_current_tls(ptr);
    if (res!=0){
        tls_destroy(ptr);
    }
    return res;
}
#include "include/io/base.h"
#include "/mnt/H/include/low-access-UEDestroyer/defines/fcntl.h"

void _start(){ 
    int fd = open("./base",O_RDONLY,0);
    if (fd>0){
        const char* buf[255];
        read(fd,buf,255);
        printf("base: %s", buf);
    }
    _exit(0);
}
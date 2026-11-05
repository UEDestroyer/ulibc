#pragma once
#include <defines/x86_64/linux.h>
#include <funcs/linux.h>
#include <defines/fcntl.h>


struct flock {
    short l_type;
    short l_whence;
    off_t l_start;
    off_t l_len;
    pid_t l_pid;
};
struct f_owner_ex {
    int type;
    pid_t pid;
};

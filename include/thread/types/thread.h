#pragma once
#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "low-access-UEDestroyer/funcs/linux.h"

struct ulibc_thread{
    struct ulibc_tls *tls;
    unsigned long id;
    int tid; //TODO:gettid()
};

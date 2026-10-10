#pragma once
#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "low-access-UEDestroyer/funcs/linux.h"

struct ulibc_tls{
    struct ulibc_tls* self;
    struct ulibc_thread* thread;
    int err;
};
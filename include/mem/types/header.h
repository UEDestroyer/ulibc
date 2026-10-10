#pragma once

#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "low-access-UEDestroyer/funcs/linux.h"

typedef struct BlockHeader{
    size_t size;
    bool is_free;
    struct BlockHeader* next;
    void* end;
} BlockHeader;
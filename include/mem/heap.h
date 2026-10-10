#include "low-access-UEDestroyer/funcs/linux.h"
#include "low-access-UEDestroyer/defines/fcntl.h"
#include "math/base.h"
#include "mem/base.h"
#include "base/errno.h"

#include "types/header.h"


void free(void* ptr);
void* malloc(size_t size);
void* calloc(size_t nmemb,size_t size);
void* realloc(void* ptr,size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);
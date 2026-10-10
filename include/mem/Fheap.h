#include "low-access-UEDestroyer/funcs/linux.h"
#include "low-access-UEDestroyer/defines/fcntl.h"
#include "math/base.h"
#include "mem/base.h"
#include "types/header.h"

// F mean free by errno поху что не по стандарту
void Ffree(void* ptr);
void* Fmalloc(size_t size);
void* Fcalloc(size_t nmemb,size_t size);
void* Frealloc(void* ptr,size_t size);
void *Freallocarray(void *ptr, size_t nmemb, size_t size);
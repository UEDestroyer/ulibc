#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "low-access-UEDestroyer/funcs/linux.h"

void* memcpy(void* dst, const void* src, size_t n);
void* memset(void* dst, int value, size_t n);

int memcmp(const void* dst, const void* src, size_t n);

void* memmove(void* dst, const void* src, size_t n);
void memswap(void *a_, void *b_, unsigned long size);


void arr_clear(void* arr,size_t len);
void arr_reverse(void* arr_,size_t len,size_t elem_size);

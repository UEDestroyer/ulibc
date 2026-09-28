#include <stddef.h>  // size_t, NULL
#include <stdint.h>  // uint8_t, int32_t и т.д.


void* memcpy(void* dst, const void* src, size_t n);
void* memset(void* dst, int value, size_t n);

int memcmp(const void* dst, const void* src, size_t n);

void* memmove(void* dst, const void* src, size_t n);

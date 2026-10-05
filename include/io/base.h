#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "low-access-UEDestroyer/funcs/linux.h"
#include <stdarg.h>
#include "../str/convert.h"
#include "../str/base.h"
#include "../mem/base.h"
#include "../mem/heap.h"


int vustrf(int fd, const char* fmt, va_list va);
int ustrf(int fd, const char* fmt, ...);
int printf(const char* fmt, ...);
int errf(const char* fmt, ...);

const char* input();
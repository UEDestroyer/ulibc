#include "base.h"


int vwritef(int fd, const char* fmt, va_list va);
int writef(int fd, const char* fmt, ...);
int printf(const char* fmt, ...);
int errf(const char* fmt, ...);

// press F for input(фактически бесполезен)
const char* input(); 
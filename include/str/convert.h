#include <stdbool.h>
#include "mem/base.h"
#include "mem/arr.h"
#include "base.h"
#include "math/base.h"

char* itoa(int n,char* buffer);
void d2s_buffered(double f,  char* result);
void f2s_buffered(float f, char* result);
char* Ditoa(double n,char* buffer);
int atoi(const char* s);
int __atoi(const char *s, char** end);
#include "base.h"
#include "file.h"

size_t __fpending(struct FILE *stream);
int __freading(struct FILE *stream);


#if gnu
#include "fcntl/gnu.h"
#endif
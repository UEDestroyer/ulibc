#include "base.h"
#include "types/FILE.h"

extern struct FILE *stdout;
extern struct FILE *stderr;

int fileno(struct FILE *stream);
int fflush_unlocked(struct FILE *stream);
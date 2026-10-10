#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "low-access-UEDestroyer/funcs/linux.h"

long pow(long base, unsigned int exp);




#define min(a,b) ({\
    typeof(a) _a = (a);\
    typeof(b) _b = (b);\
    (_a >_b) ? _b : _a;\
})
#define max(a,b) ({\
    typeof(a) _a = (a);\
    typeof(b) _b = (b);\
    (_a>_b) ? _a : _b;\
})

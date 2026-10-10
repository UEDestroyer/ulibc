#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "low-access-UEDestroyer/funcs/linux.h"
#include "str/base.h"
#include "str/convert.h"
#include "signal/base.h"

void abort(void);

void __assert_fail(const char *assertion,const char *file,unsigned int line,const char *function);


#define assert(ass) {\
    if (!(ass)){\
        __assert_fail(#ass,__FILE__,__LINE__,__FUNCTION__); \
    }\
}

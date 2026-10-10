#include "math/base.h"

long pow(long base, unsigned int exp) {
    long result = 1;
    while (exp > 0) {
        if (exp & 1) {      
            result *= base;
        }
        base *= base;        
        exp >>= 1;           
    }
    return result;
}

#if defined(__x86_64__) || defined (_M_X64)
double floor(double x) {
    double res;
    __asm__ __volatile__ (
        "roundsd $9, %1, %0"
        : "=x" (res)
        : "x" (x)
    );
    return res;
}
#elif defined(__aarch64__) || defined(_M_ARM64)
double floor(double x) {
    double res;
    __asm__ __volatile__ (
        "frintm %d0, %d1"
        : "=w" (res)
        : "w" (x)
    );
    return res;
}
#endif
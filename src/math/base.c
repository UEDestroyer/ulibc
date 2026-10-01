#include "math/base.h"
long my_pow_fast(long base, unsigned int exp) {
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
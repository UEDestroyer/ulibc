#include "int/base.h"
#include <stdbool.h>

intmax_t imaxabs(intmax_t j){
    j&=~(1ULL << (sizeof(j) * CHAR_BIT -1));
    
    return j;
}
struct imaxdiv_t imaxdiv(intmax_t a, intmax_t b){
    struct imaxdiv_t res = {0,0};

    if (a == INTMAX_MIN && b == -1){ 
        __set_errno(ERANGE);
        return res;
    }if (b==0)return res;
    res.quot = a / b;
    res.rem = a % b;

    return res;
}
intmax_t strtoimax(const char* s, char** end, int base){
    char* start = (char *)s;

#define isSpace(a) (a == ' ' || a == '\t' || a == '\n' || a == '\r' || a == '\v' || a == '\f')
//уж извините макросы код делают ебать простым
    while (isSpace(*start)) {
        start++;
    }
#undef isSpace

    if (start[0] == '\0'){
        if (end != NULL)*end = (char *)s;
        return 0;
    }



    uintmax_t res = 0;
    bool neg = false;
    if (*start == '-'){
        neg = true; start+=1;
    }else if (*start =='+'){
        start+=1;
    }
    if (base == 0){
        switch (*start) {
            case '0':
                if (start[1] == 'x' || start[1] == 'X'){
                    base = 16;
                } else {
                    base = 8;
                }
                break;
            default:
                base = 10;
                break;
        } 
    }

    if (2 > base || base > 36){
        __set_errno(EINVAL);
        if (end !=NULL){
            *end = (char *) s;
        }
        return 0;
    }

#define is_x16D(a) ((a >= '0' && a <= '9') || (a >= 'A' && a <= 'F') || (a >= 'a' && a <= 'f'))

    if (base == 16 && start[0] == '0' && (start[1] == 'x' || start[1] == 'X') && is_x16D(start[2])){
        start+=2;
    }

#undef is_x16D
    int tmp = -1;
    bool overflow = false;


#define cases(a,b,num) \
    case (a): \
    case (b): \
        tmp = num; \
        break;

    uintmax_t limit = neg ? (uintmax_t)INTMAX_MAX + 1 : INTMAX_MAX;
    uintmax_t cutoff = limit / base;
    uintmax_t cutlim = limit % base;
    bool any_digits = false;
    for (size_t i = 0;; i++){
        switch (start[i]) {
            cases('a', 'A', 10)
            cases('b', 'B', 11)
            cases('c', 'C', 12)
            cases('d', 'D', 13)
            cases('e', 'E', 14)
            cases('f', 'F', 15)
            cases('g', 'G', 16)
            cases('h', 'H', 17)
            cases('i', 'I', 18)
            cases('j', 'J', 19)
            cases('k', 'K', 20)
            cases('l', 'L', 21)
            cases('m', 'M', 22)
            cases('n', 'N', 23)
            cases('o', 'O', 24)
            cases('p', 'P', 25)
            cases('q', 'Q', 26)
            cases('r', 'R', 27)
            cases('s', 'S', 28)
            cases('t', 'T', 29)
            cases('u', 'U', 30)
            cases('v', 'V', 31)
            cases('w', 'W', 32)
            cases('x', 'X', 33)
            cases('y', 'Y', 34)
            cases('z', 'Z', 35)
            case '\0':
                goto done;

            default:
                if (start[i] <= '9' && start[i] >= '0'){
                    tmp = start[i] - '0';
                }else {
                    goto done;
                }
                break;
        }
        if (tmp == -1 || tmp >=base){
            goto done;
        }else {any_digits = true;}



        if (res > cutoff || (res == cutoff && tmp > cutlim)) {
            overflow = 1;
            __set_errno(ERANGE);
        }else{
            res = res * base + tmp;
        }
        tmp = -1;
        if (end != NULL){
                *end = start + i + 1;
        }
    }
done:

#undef cases

    if (!any_digits){
        if (end != NULL){
            *end = (char *)s;
        }
        return 0;
    }

    if (overflow){
        return neg ? INTMAX_MIN : INTMAX_MAX;
    }
    if (neg && res == (uintmax_t)INTMAX_MAX + 1) {
        return INTMAX_MIN;
    }

    return neg ? -(intmax_t)res: (intmax_t)res ;

}
uintmax_t strtoumax(const char* s, char** end, int base){
    char* start = (char *)s;

#define isSpace(a) (a == ' ' || a == '\t' || a == '\n' || a == '\r' || a == '\v' || a == '\f')
//уж извините макросы код делают ебать простым
    while (isSpace(*start)) {
        start++;
    }
#undef isSpace

    if (start[0] == '\0'){
        if (end != NULL)*end = (char *)s;
        return 0;
    }



    uintmax_t res = 0;
    bool neg = false;
    if (*start == '-'){
        neg = true; start+=1;
    }else if (*start =='+'){
        start+=1;
    }
    if (base == 0){
        switch (*start) {
            case '0':
                if (start[1] == 'x' || start[1] == 'X'){
                    base = 16;
                } else {
                    base = 8;
                }
                break;
            default:
                base = 10;
                break;
        } 
    }

    if (2 > base || base > 36){
        __set_errno(EINVAL);
        if (end !=NULL){
            *end = (char *) s;
        }
        return 0;
    }

#define is_x16D(a) ((a >= '0' && a <= '9') || (a >= 'A' && a <= 'F') || (a >= 'a' && a <= 'f'))

    if (base == 16 && start[0] == '0' && (start[1] == 'x' || start[1] == 'X') && is_x16D(start[2])){
        start+=2;
    }

#undef is_x16D
    int tmp = -1;
    bool overflow = false;


#define cases(a,b,num) \
    case (a): \
    case (b): \
        tmp = num; \
        break;

    uintmax_t limit = INTMAX_MAX;
    uintmax_t cutoff = limit / base;
    uintmax_t cutlim = limit % base;
    bool any_digits = false;
    for (size_t i = 0;; i++){
        switch (start[i]) {
            cases('a', 'A', 10)
            cases('b', 'B', 11)
            cases('c', 'C', 12)
            cases('d', 'D', 13)
            cases('e', 'E', 14)
            cases('f', 'F', 15)
            cases('g', 'G', 16)
            cases('h', 'H', 17)
            cases('i', 'I', 18)
            cases('j', 'J', 19)
            cases('k', 'K', 20)
            cases('l', 'L', 21)
            cases('m', 'M', 22)
            cases('n', 'N', 23)
            cases('o', 'O', 24)
            cases('p', 'P', 25)
            cases('q', 'Q', 26)
            cases('r', 'R', 27)
            cases('s', 'S', 28)
            cases('t', 'T', 29)
            cases('u', 'U', 30)
            cases('v', 'V', 31)
            cases('w', 'W', 32)
            cases('x', 'X', 33)
            cases('y', 'Y', 34)
            cases('z', 'Z', 35)
            case '\0':
                goto done;

            default:
                if (start[i] <= '9' && start[i] >= '0'){
                    tmp = start[i] - '0';
                }else {
                    goto done;
                }
                break;
        }
        if (tmp == -1 || tmp >=base){
            goto done;
        }else {any_digits = true;}



        if (res > cutoff || (res == cutoff && tmp > cutlim)) {
            overflow = 1;
            __set_errno(ERANGE);
        }else{
            res = res * base + tmp;
        }
        tmp = -1;
        if (end != NULL){
                *end = start + i + 1;
        }
    }
done:

#undef cases

    if (!any_digits){
        if (end != NULL){
            *end = (char *)s;
        }
        return 0;
    }

    if (overflow){
        return INTMAX_MAX;
    }

    return neg ? (0 - res) : res;

}
intmax_t wcstoimax(const wchar_t* s, wchar_t** end, int base); // Однажды(хз в жизни не юзал потом сделаю)
uintmax_t wcstoumax(const wchar_t* s, wchar_t** end, int base);
#include "str/convert.h"


char* __Ditoa(long long n, char *buffer, size_t *posT) { // danger without check and reverse

#define pos (*posT)
    long long an = (n < 0) ? 0LL - n : n;

    do {
        buffer[pos++] = (an % 10) + '0';
        an /= 10;
    } while (an > 0);

    if (n < 0) {
        buffer[pos++] = '-';
    }

    buffer[pos] = '\0';

#undef pos
    return buffer;
}

char* itoa(int n, char *buffer) {
    if (!buffer) return 0;

    size_t pos = 0;
    __Ditoa(n,buffer,&pos);
    arr_reverse(buffer, pos, 1);

    return buffer;
}

char* Ditoa(double n, char *buffer){
    char buf[25];
    d2s_buffered(n,buf);

    size_t pos = 0;

    if (buf[0] == '-'){
        buffer[0] = '-'; pos++;
    }

    size_t intlen = 0;
    bool dot = false;

    for (size_t i = pos;i<25;i++){
        switch (buf[i]) {
            case 'N':
            case 'I':
                buffer[pos] = buf[i];
                return buffer;
            case '.':
                dot = true;
            case 'E':
                goto expon;
            
        }
    }
expon:

}

int __atoi(const char *s, char** end) {
    if (!s) return 0;

    int result = 0;
    int sign = 1;

    while (*s == ' ' || *s == '\t' || *s == '\n') {
        s++;
    }

    if (*s == '-') {
        sign = -1;
        s++;
    } else if (*s == '+') {
        s++;
    }

    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }
    if (end != NULL)*end =(char*) s;

    return result * sign;
}

int atoi(const char *s) {
    return __atoi(s,NULL);
}
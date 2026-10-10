#include "str/convert.h"

char* __Ditoa(unsigned long long n, char *buffer, size_t *posT) { // danger without check and reverse

#define pos (*posT)
    unsigned int an = (n < 0) ? (unsigned int)0 - (unsigned int)n : (unsigned int)n;

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

char* SDitoa(double n, char *buffer, size_t Al) {
    if (!buffer) return 0;

    bool minus = n < 0;
    
    size_t pos = 0;

    double num = n;
    if (minus){
        num=-(num);
        buffer[pos++] = '-';
    }
    num+=0.5 / pow(10,Al);
    
    unsigned long long nL = (unsigned long long)num;
    long double nD = num - nL;


    __Ditoa(nL, buffer,&pos);
    arr_reverse(buffer + (int) minus,pos - (int)minus,1);
    buffer[pos++] = '.';

    int nR = 0;
    size_t i = 0;
    while (i++ < Al && nD!=0){
        nD*=10;
        nR = (int)nD;
        buffer[pos++] = (nR % 10) + '0';
        nD-=nR;
    }



    for (size_t j = pos-1;j>0;j--){
        if (buffer[j]=='0'){
            buffer[j]='\0';
            if (j!=pos-1){
                memset(buffer+j,0,1);
            }
        }else if (buffer[j]=='.'){
            buffer[j]='\0';
            if (j!=pos-1){
                memset(buffer+j,0,1);
            }
            break;
        }else{
            break;
        }
    }


    buffer[pos] = '\0';



    return buffer;
}

char* Ditoa(double n, char *buffer){
    return SDitoa(n, buffer, 6);
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
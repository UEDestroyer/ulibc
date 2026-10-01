#include "io/base.h"

int vustrf(int fd, const char* fmt, va_list va){

#define clear do {write(fd,buffer,pos); \
            res+=pos;pos=0;} while (0);

    char buffer[255];
    size_t pos = 0;
    bool isF = false;
    size_t res = 0;

    for (int i = 0;;i++){

        if (pos>=255){
            clear
        }
        if (*(fmt + i)=='\0'){
            clear
            break;
        } 
        if (*(fmt+i)=='%') {
            if (isF){
                if (pos>=255){
                    clear
                }
                buffer[pos++] = '%';
            }
            isF=!isF;
            continue;

        }
        if (isF){
            switch (*(fmt+i)) {
                case 'c':{
                    int c=va_arg(va,int);
                    buffer[pos++]=(unsigned char)c;
                    isF=false;
                    break;}
                case 's':{
                    const char* s=va_arg(va,const char*);isF=false;
                    clear
                    if (s==NULL){
                        write(fd, "(null)", 6);res+=6;
                    }else {
                        size_t size = strlen(s);
                        write(fd, s, size);res+=size;
                    }

                    break;}
                case 'd':{
                    isF = false;
                    int in = va_arg(va,int);
                    clear
                    char iTs[33];

                    itoa(in,iTs);

                    strcpy(buffer, iTs);

                    pos+=strlen(iTs);

                    break;}
                
                default:
                    clear
                    isF=false;
                    write(fd, "%" ,1);
                    write(fd,fmt+i,1);res+=2;
            }
            continue;
        }
        buffer[pos++]=*(fmt+i);
    }

#undef clear
    return res;
}


int ustrf(int fd,const char* fmt, ...){
    va_list va;
    va_start(va,fmt);
    int ret = vustrf(fd,fmt,va);
    va_end(va);
    return ret;
}

int printf(const char* fmt, ...){
    va_list va;
    va_start(va,fmt);
    int ret = vustrf(1,fmt,va);
    va_end(va);
    return ret;
}

int errf(const char* fmt, ...){
    va_list va;
    va_start(va,fmt);
    int ret = vustrf(2,fmt,va);
    va_end(va);
    return ret;
}





const char* input(){
    size_t capacity = 32;
    char* buffer = mmap(NULL,capacity+1,1|2,2|32,-1,0);
    long res = 0;
    size_t readed = 0;

    while (true){
        res=read(0,buffer + readed,32);
        
        if (res == 0){
            buffer[readed] = '\0';
            break;
        }
        if (res<0){
            errf("Error when read stdin: %d", res);
            munmap(buffer, capacity + 1);
            return NULL;
        }
        readed+=res;
        if (buffer[readed-1] == '\n'){
            buffer[readed-1] = '\0';break;
        }else if (readed>=capacity){

            char* new_buffer = mmap(NULL, capacity + 32 + 1, 1|2, 2|32, -1, 0);
            memcpy(new_buffer, buffer, readed);
            munmap(buffer, capacity + 1);
            buffer = new_buffer;
            capacity+=32;
        } 
    }


    return (const char *)buffer;
}
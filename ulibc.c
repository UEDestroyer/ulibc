#include "include/io/base.h"
#include "str/convert.h"
#include "include/mem/heap.h"
#include "include/thread/base.h"
#include "/mnt/H/include/low-access-UEDestroyer/defines/fcntl.h"

void _start(){ 
    thread_init();

    while (true){
        const char* C = input();

        char Abuffer[32];size_t AS = 0;
        char Bbuffer[32];size_t BS = 0;

        char compr = -1;
        int a;
        int b;

        for (int i = 0; i < strlen(C);i++){
            switch (*(C +i)) {
                case '+':
                    compr = 0;
                    break;
                case '-':
                    compr = 1;
                    break;
                case '*':
                    compr = 2;
                    break;
                case '/':
                    compr = 3;
                    break;
                case '\0':
                    break;
                case ' ':
                    break;
                default:
                    if (compr == -1){
                        Abuffer[AS] = *(C +i);AS++;
                    }else {
                        Bbuffer[BS] = *(C +i);BS++;
                    }
                    break;
            }
        }
        Abuffer[AS] = '\0';
        Bbuffer[BS] = '\0';

        a = atoi(Abuffer);
        b = atoi(Bbuffer);

        int res;
        switch (compr) {
            case 0:
                res = a + b;break;
            case 1:
                res = a - b;break;
            case 2:
                res = a * b;break;
            case 3:
                res = a / b;break;
            default:
                printf("ты Даун");
        }

        printf("res: %d\n",res);
        free(C);

    }
    

    

    
    _exit(0);
}
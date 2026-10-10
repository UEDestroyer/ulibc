#include "mem/base.h"
#include "mem/arr.h"

void arr_clear(void* arr_,size_t len){
    if (!arr_ || len<2 )return;
    char* arr = (char*)arr_;
    size_t pos = 0;
    size_t writer = 0;
    while (pos<len){
        if (arr[pos]!=0){
            if (writer!=pos){
                arr[writer] = arr[pos];
            }
            writer++;
        }
        pos++;
    }
    while (writer<len){
        arr[writer++] = 0;
    }
}

void arr_reverse(void* arr_,size_t len,size_t elem_size){
    if (!arr_ || len<2 || elem_size == 0)return;

    char *arr = (char*)arr_;
    size_t left = 0;
    size_t right = len-1;

    while (left<right){
        memswap(arr+(left*elem_size),arr+(right*elem_size),elem_size); // бля знаю что спагети но пох
        left++;right--;
    }
}

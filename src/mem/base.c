#include "mem/base.h"

void* memcpy(void* dst, const void* src, size_t n){
	unsigned char* d = (unsigned char*)dst;
	const unsigned char* s = (unsigned char*)src;
	for (size_t i = 0;i<n;i++){
		*d=*s;
		d++;s++;
	}
	return dst;
}
void* memset(void* dst, int value, size_t n){
	unsigned char* d = (unsigned char*)dst;
	const unsigned char s = (unsigned char)value;
	for (size_t i = 0;i<n;i++){
		*d=s;
		d++;
	}
	return dst;
}

int memcmp(const void* dst, const void* src, size_t n){
	const unsigned char* d = (unsigned char*)dst;
	const unsigned char* s = (unsigned char*)src;
	for (int i = 0; i<n;i++){
		if (*d!=*s)break;
		d++;s++;
	}
	return *d-*s;
}

void* memmove(void* dst, const void* src, size_t n){
	unsigned char* d = (unsigned char*)dst;
	const unsigned char* s = (unsigned char*)src;
	if (d<s){
		for (int i = 0;i<n;i++){
			*d=*s;
			d++;s++;
		}
	}else {
		d+=n-1;
		s+=n-1;
		for (int i = n;i>0;i--){
			*d=*s;
			d--;s--;
		}

	}
	return dst;
}
void memswap(void *a_, void *b_, size_t size) {
    char* a = (char*)a_;
    char* b = (char*)b_;
    
    while (size--) {
        char temp = *a;
        *a++ = *b;
        *b++ = temp;
    }
}


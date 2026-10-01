#include "str/base.h"
size_t strlen(const char* str){
	size_t size = 0;
	while (1){
		if (*(str + size) == '\0'){
			break;
		} else {
			size++;
		}
	}
	return size;
}

char* strcpy(char* dst, const char* src){
	char* ret = dst;
	while (*src!='\0'){
		*dst=*src;
		dst++;
		src++;
	}
	*dst='\0';
	return ret;
}
int strcmp(const char* s1, const char* s2){
    while (*s1 != '\0' && *s1 == *s2){
        s1++; s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}
char *strcat(char *dst, const char *src){
	char *ret=dst;
	dst+=strlen(dst);
	while (1){
		*dst=*src;
		if (*src=='\0'){
			break;
		}
		dst++;src++;
	}

	return ret;
}

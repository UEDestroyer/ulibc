#include "str/convert.h"

char* itoa(int n, char *buffer) {
    if (!buffer) return 0;

    size_t pos = 0;
    unsigned int an = (n < 0) ? (unsigned int)0 - (unsigned int)n : (unsigned int)n;

    do {
        buffer[pos++] = (an % 10) + '0';
        an /= 10;
    } while (an > 0);

    if (n < 0) {
        buffer[pos++] = '-';
    }

    buffer[pos] = '\0';
    arr_reverse(buffer, pos, 1);

    return buffer;
}

int atoi(const char *s) {
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

    return result * sign;
}
#include "string.h"

size_t strlen(const char *s) {
    size_t n = 0;
    while (s[n]) n++;
    return n;
}

void strcpy(char *dst, const char *src) {
    while ((*dst++ = *src++));
}

int strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++; b++;
    }
    return *(unsigned char*)a - *(unsigned char*)b;
}


int strncmp(const char *a, const char *b, size_t n) {
    for (size_t i = 0; i < n; i++) {
        unsigned char ac = a[i];
        unsigned char bc = b[i];

        if (ac != bc) {
            return ac - bc;
        }

        // if either string ends before n characters
        if (ac == '\0') {
            return 0;
        }
    }

    return 0;
}
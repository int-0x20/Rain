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

static char *strtok_saveptr = NULL;

char *strtok(char *str, const char *delim) {
    if (str)
        strtok_saveptr = str;   // Start a new tokenization
    else if (!strtok_saveptr)
        return NULL;            // No more tokens

    // Skip leading delimiters
    char *token_start = strtok_saveptr;
    while (*token_start && strchr(delim, *token_start))
        token_start++;

    if (*token_start == '\0') { // Reached end, no token
        strtok_saveptr = NULL;
        return NULL;
    }

    // Find end of token
    char *p = token_start;
    while (*p && !strchr(delim, *p))
        p++;

    if (*p == '\0') {
        // End of string, next call returns NULL
        strtok_saveptr = NULL;
    } else {
        *p = '\0';              // Null-terminate token
        strtok_saveptr = p + 1; // Next token begins after delimiter
    }

    return token_start;
}

char *strchr(const char *s, int c) {
    while (*s) {
        if (*s == (char)c)
            return (char*)s;
        s++;
    }
    return NULL;
}

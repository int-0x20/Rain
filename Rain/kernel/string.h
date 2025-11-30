#pragma once
#include <stddef.h>

size_t strlen(const char *s);
void strcpy(char *dst, const char *src);
int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, size_t n);
char *strtok(char *str, const char *delim);
char *strchr(const char *s, int c);
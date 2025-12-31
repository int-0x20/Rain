#pragma once
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *s);
void strcpy(char *dst, const char *src);
int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, size_t n);
char *strtok(char *str, const char *delim);
char *strchr(const char *s, int c);
void *memcpy(void *dest, const void *src, uint64_t n);
void *memset(void *dest, int value, uint64_t n);
void *memmove(void *dest, const void *src, uint64_t n);

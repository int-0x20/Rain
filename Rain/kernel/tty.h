#ifndef TTY_H
#define TTY_H

#include <stdint.h>

void tty_clear();
void tty_putc(char c);
void tty_write(const char* str);
void tty_write_hex(uint64_t val);
char tty_read_char();
void tty_print_int(int n);
void tty_printf(const char *fmt, ...);
static void print_number(unsigned long num, int base);

#endif

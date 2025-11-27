#ifndef TTY_H
#define TTY_H

void tty_clear();
void tty_putc(char c);
void tty_write(const char* str);
char tty_read_char();

#endif

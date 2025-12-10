#include <stdint.h>
#include <stddef.h>
#include "keyboard.h"
#include <stdarg.h>

static uint16_t* const VGA_MEMORY = (uint16_t*)0xB8000;
static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;

static int cursor_row = 0;
static int cursor_col = 0;

static uint8_t vga_entry_color(uint8_t fg, uint8_t bg) {
    return fg | (bg << 4);
}

static uint16_t vga_entry(unsigned char c, uint8_t color) {
    return (uint16_t)c | ((uint16_t)color << 8);
}

void tty_clear() {
    uint8_t color = vga_entry_color(7, 0); // light grey on black
    uint16_t blank = vga_entry(' ', color);

    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            VGA_MEMORY[y * VGA_WIDTH + x] = blank;
        }
    }

    cursor_row = 0;
    cursor_col = 0;
}

void tty_putc(char c) {
    uint8_t color = vga_entry_color(7, 0); // light grey on black

    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
        return;
    }

    VGA_MEMORY[cursor_row * VGA_WIDTH + cursor_col] =
        vga_entry(c, color);

    cursor_col++;

    if (cursor_col >= VGA_WIDTH) {
        cursor_col = 0;
        cursor_row++;
    }
}

void tty_write(const char* str) {
    for (size_t i = 0; str[i] != 0; i++) {
        tty_putc(str[i]);
    }
}

char tty_read_char() {
    char c = 0;

    // Wait until keyboard driver provides a character
    while ((c = keyboard_get_char()) == 0) {
        // Spin — simple but works for early OS
    }

    return c;
}

void tty_write_hex(uint64_t val) {
    const char *hex = "0123456789ABCDEF";
    char buf[17];
    buf[16] = 0;

    for (int i = 15; i >= 0; --i) {
        buf[i] = hex[val & 0xF];
        val >>= 4;
    }

    tty_write("0x");
    tty_write(buf);
}

void tty_print_int(int n) {
    char buf[16];
    int i = 0;

    if (n == 0) {
        tty_putc('0');
        return;
    }

    if (n < 0) {
        tty_putc('-');
        n = -n;
    }

    while (n > 0) {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }

    while (i--)
        tty_putc(buf[i]);
}

static void print_number(unsigned long num, int base) {
    char buf[32];
    const char *digits = "0123456789ABCDEF";
    int i = 0;

    if (num == 0) {
        tty_putc('0');
        return;
    }

    while (num > 0) {
        buf[i++] = digits[num % base];
        num /= base;
    }

    while (i--)
        tty_putc(buf[i]);
}

void tty_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt != '%') {
            tty_putc(*fmt++);
            continue;
        }

        fmt++;

        switch (*fmt) {
            case 's': {
                char *s = va_arg(args, char*);
                tty_write(s);
                break;
            }
            case 'd': {
                int n = va_arg(args, int);
                if (n < 0) {
                    tty_putc('-');
                    n = -n;
                }
                print_number(n, 10);
                break;
            }
            case 'x': {
                unsigned n = va_arg(args, unsigned);
                print_number(n, 16);
                break;
            }
            case 'p': {
                unsigned long n = (unsigned long)va_arg(args, void *);
                tty_write("0x");
                print_number(n, 16);
                break;
            }
            case '%':
                tty_putc('%');
                break;
        }
        fmt++;
    }

    va_end(args);
}

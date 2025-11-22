#include <stdint.h>
#include <stddef.h>

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

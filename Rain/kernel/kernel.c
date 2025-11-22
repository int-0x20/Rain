#include "tty.h"
#include "keyboard.h"

void kernel_main() {
    tty_clear();
    tty_write("Type something:\n");

    while (1) {
        char c = keyboard_get_char();
        tty_putc(c);
    }
}

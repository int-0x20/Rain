#include <stdint.h>
#include "keyboard.h"
#include "tty.h"
#include "io.h"

static char scancode_to_ascii[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 
    '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', 
    ']', '\n', 0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 
    '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', 
    '/', 0,    // 0x35 = '/', 0x36 = Right Shift (ignored)
    '*',      // 0x37 (keypad *)
    0,        // 0x38 (Alt)
    ' ',      // 0x39 *** SPACEBAR ***
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

char keyboard_get_char() {
    uint8_t sc;

    // Wait for new keystroke
    do {
        // Check status port
        uint8_t status = inb(0x64);

        // Bit 0 = output buffer full
        if (status & 1) {
            sc = inb(0x60);
            if (sc < 0x80) {
                return scancode_to_ascii[sc];
            }
        }

    } while (1);
}

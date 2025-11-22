#include <stdint.h>
#include "tty.h"

extern void tty_print(const char*);

void kernel_main() {
    tty_clear();
    tty_write("Hello from 64-bit kernel!\n");
    tty_write("VGA text mode is working.\n");
}


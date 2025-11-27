#include "tty.h"
#include "keyboard.h"
#include "monarch/monarch.h"

void kernel_main() {
    tty_clear();
    tty_write("Type something:\n");

    monarch_run();
}

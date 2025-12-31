#include "tty.h"
#include "keyboard.h"
#include "monarch/monarch.h"
#include "tarfs.h"

void kernel_main() {
    tty_clear();
    tarfs_init();
    tarfs_list();  
    monarch_run();
}

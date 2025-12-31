#include "demo.h"
#include "../kernel/program.h"
#include "../kernel/tty.h"
#include "../kernel/disk.h"
#include "../kernel/string.h"
#include "../kernel/monarch/monarch.h"

void disk_test();

void demo_program(ProgramEnv *env) {
    static int ran = 0;

    if (!ran) {
        disk_test();
        ran = 1;
    }

    program_yield();
}


void disk_test() {
    disk_init(100); // 100 blocks = 50 KB

    char buf[512];
    char out[512];

    memset(buf, 'A', 512);
    disk_write(5, buf);

    memset(out, 0, 512);
    disk_read(5, out);

    tty_write("First byte: ");
    tty_putc(out[0]); // Should print A
}


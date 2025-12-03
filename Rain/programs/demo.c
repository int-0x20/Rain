#include "demo.h"
#include "../kernel/program.h"
#include "../kernel/tty.h"

void demo_program(ProgramEnv *env) {
    tty_write("Demo program running!\n");

    while (1) {
        tty_write("Demo program running!\n");
        program_yield();
    }
}

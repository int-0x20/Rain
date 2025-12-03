#include "program.h"
#include "tty.h"

static Program programs[MAX_PROGRAMS];
static int program_count = 0;
static int current_program = -1;

int program_create(program_entry_t entry) {
    if (program_count >= MAX_PROGRAMS)
        return -1;

    Program *p = &programs[program_count];

    p->entry = entry;
    p->active = 1;

    // Simple fixed memory sandbox placeholder
    p->env.base_addr  = 0x100000 + program_count * 0x100000;
    p->env.limit_addr = p->env.base_addr + 0x100000;

    int id = program_count;
    program_count++;
    return id;
}

void program_scheduler() {
    for (;;) {
        for (int i = 0; i < program_count; i++) {
            if (!programs[i].active)
                continue;

            current_program = i;

            programs[i].entry(&programs[i].env);
        }
    }
}


void program_yield() {
    program_scheduler();
}
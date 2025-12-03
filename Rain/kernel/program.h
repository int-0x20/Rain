#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdint.h>

typedef struct ProgramEnv {
    uint64_t base_addr;
    uint64_t limit_addr;
} ProgramEnv;

// All programs have signature: void func(ProgramEnv *env)
typedef void (*program_entry_t)(ProgramEnv *);

#define MAX_PROGRAMS 8

typedef struct Program {
    program_entry_t entry;
    int active;
    ProgramEnv env;
} Program;

int program_create(program_entry_t entry);
void program_scheduler();
void program_yield();

#endif

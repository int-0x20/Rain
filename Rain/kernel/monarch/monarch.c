#include "../tty.h"
#include "monarch.h"
#include <stdbool.h>
#include "../string.h"
#include <stdint.h>
#include "../../programs/demo.h"
#include "../program.h"

#define INPUT_MAX 128
#define EXEC_BASE  0x00200000
#define EXEC_LIMIT 0x00210000

void command_mon(int argc, char** argv);
void command_exec(int argc, char **argv);
uint64_t hex_to_uint64(const char *str);

static void prompt() {
    tty_write("MonArch> ");
}

static int read_line(char *buf, int max) {
    int len = 0;
    while (1) {
        char c = tty_read_char();   // this must exist in your TTY/keyboard layer

        if (!c) continue;           // wait for a character

        if (c == '\n') {
            tty_write("\n");
            buf[len] = 0;
            return len;
        }

        if (len < max - 1) {
            buf[len++] = c;
            tty_putc(c);
        }
    }
}

static void cmd_help() {
    tty_write("Commands:\n");
    tty_write("  help  - show commands\n");
    tty_write("  clear - clear screen\n");
    tty_write("  echo  - print text\n");
    tty_write("  mon   - modifying memory\n");
    tty_write("  exec  - execute a part of memory\n");
    tty_write("  about - info about Rain OS and MonArch\n");
}

static void cmd_about() {
    tty_write("Rain OS — MonArch v1\n");
}

static void cmd_echo(char *args) {
    tty_write(args);
    tty_write("\n");
}

static void process_command(char *line) {

    char *argv[10];
    int argc = 0;

    // Tokenize input
    char *token = strtok(line, " ");
    while (token && argc < 10) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (argc == 0) return;

    // help
    if (strcmp(argv[0], "help") == 0) {
        cmd_help();
        return;
    }

    // clear
    if (strcmp(argv[0], "clear") == 0) {
        tty_clear();
        return;
    }

    // about
    if (strcmp(argv[0], "about") == 0) {
        cmd_about();
        return;
    }

    // echo
    if (strcmp(argv[0], "echo") == 0) {
        if (argc >= 2)
            cmd_echo(argv[1]);   // or reconstruct full string if needed
        else
            tty_write("\n");
        return;
    }

    // mon command
    if (strcmp(argv[0], "mon") == 0) {
        command_mon(argc, argv);
        return;
    }

    if (strcmp(argv[0], "exec") == 0) {
        command_exec(argc, argv);
        return;
    }

    if (strcmp(argv[0], "run") == 0) {
        tty_write("Starting program...\n");
        program_create(demo_program);
        program_scheduler();
    }

    // unknown
    tty_write("Unknown command\n");
}


void monarch_run() {
    char buffer[INPUT_MAX];

    tty_clear();
    tty_write("Rain OS — MonArch v1\n");

    while (true) {
        prompt();
        read_line(buffer, INPUT_MAX);
        process_command(buffer);
    }
}


uint64_t parse_hex(const char *s) {
    uint64_t val = 0;

    // skip 0x
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        s += 2;

    while (*s) {
        char c = *s++;
        uint8_t digit;

        if (c >= '0' && c <= '9') digit = c - '0';
        else if (c >= 'a' && c <= 'f') digit = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F') digit = c - 'A' + 10;
        else break;

        val = (val << 4) | digit;
    }

    return val;
}

void mon_list(uint64_t addr) {
    uint8_t val = *((uint8_t*)addr);

    tty_write("0x");
    tty_write_hex(addr);
    tty_write(": 0x");
    tty_write_hex(val);
    tty_write("\n");
}


void mon_write(uint64_t addr, uint8_t value) {
    *((uint8_t*)addr) = value;

    tty_write("Wrote 0x");
    tty_write_hex(value);
    tty_write(" to 0x");
    tty_write_hex(addr);
    tty_write("\n");
}

void command_mon(int argc, char** argv) {
    if (argc < 3) {
        tty_write("Usage:\n");
        tty_write("  mon -l <addr>\n");
        tty_write("  mon -w <addr> <byte>\n");
        return;
    }

    uint64_t addr = parse_hex(argv[2]);

    if (strcmp(argv[1], "-l") == 0) {
        mon_list(addr);
        return;
    }

    if (strcmp(argv[1], "-w") == 0) {
        if (argc < 4) {
            tty_write("mon -w <addr> <byte>\n");
            return;
        }

        uint8_t value = (uint8_t)parse_hex(argv[3]);
        mon_write(addr, value);
        return;
    }

    tty_write("Unknown flag\n");
}

void command_exec(int argc, char **argv) {
    if (argc < 2) {
        tty_write("Usage: exec <hex address>\n");
        return;
    }

    // Convert address
    uint64_t addr = hex_to_uint64(argv[1]);

    // Safety checks
    if (addr < EXEC_BASE || addr >= EXEC_LIMIT) {
        tty_write("Error: address outside exec sandbox.\n");
        return;
    }

    tty_write("Running code at: 0x");
    tty_write_hex(addr);
    tty_write("\n");

    // Turn the address into a function pointer and call it
    void (*fn)(void) = (void (*)(void)) addr;

    fn();   // ⚠ WARNING: JUMPS INTO USER MEMORY
}

uint64_t hex_to_uint64(const char *str) {
    uint64_t result = 0;

    // Skip optional "0x"
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        str += 2;

    while (*str) {
        char c = *str++;
        int value;

        if (c >= '0' && c <= '9') value = c - '0';
        else if (c >= 'A' && c <= 'F') value = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') value = c - 'a' + 10;
        else break;

        result = (result << 4) | value;
    }

    return result;
}
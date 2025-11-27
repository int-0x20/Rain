#include "../tty.h"
#include "monarch.h"
#include <stdbool.h>
#include "../string.h"

#define INPUT_MAX 128

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
    // help
    if (strcmp(line, "help") == 0) {
        cmd_help();
        return;
    }

    // clear
    if (strcmp(line, "clear") == 0) {
        tty_clear();
        return;
    }

    // about
    if (strcmp(line, "about") == 0) {
        cmd_about();
        return;
    }

    // echo
    if (strncmp(line, "echo ", 5) == 0) {
        cmd_echo(line + 5);
        return;
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

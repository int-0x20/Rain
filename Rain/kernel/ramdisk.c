// kernel/ramdisk.c
#include "ramdisk.h"
#include "string.h"  // For memcpy

static uint8_t ramdisk_buffer[RAMDISK_SIZE];

void ramdisk_init(void) {
    // Zero out the RAM disk on startup
    memset(ramdisk_buffer, 0, RAMDISK_SIZE);
}

int ramdisk_read_block(uint64_t block_num, void *buffer) {
    if (block_num >= BLOCK_COUNT) return -1;
    memcpy(buffer, &ramdisk_buffer[block_num * BLOCK_SIZE], BLOCK_SIZE);
    return 0;
}

int ramdisk_write_block(uint64_t block_num, const void *buffer) {
    if (block_num >= BLOCK_COUNT) return -1;
    memcpy(&ramdisk_buffer[block_num * BLOCK_SIZE], buffer, BLOCK_SIZE);
    return 0;
}

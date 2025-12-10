#include <stddef.h>
#include "disk.h"
#include "string.h" // for memcpy
#include "kalloc.h"

static unsigned char *disk_data = NULL;
static int disk_blocks = 0;

#define BLOCK_SIZE 512

int disk_init(int blocks) {
    disk_blocks = blocks;
    disk_data = (unsigned char *)kalloc(blocks * BLOCK_SIZE);
    if (!disk_data) return -1;

    memset(disk_data, 0, blocks * BLOCK_SIZE);
    return 0;
}

int disk_read(int block, void *buffer) {
    if (block < 0 || block >= disk_blocks) return -1;

    memcpy(buffer, disk_data + block * BLOCK_SIZE, BLOCK_SIZE);
    return 0;
}

int disk_write(int block, const void *buffer) {
    if (block < 0 || block >= disk_blocks) return -1;

    memcpy(disk_data + block * BLOCK_SIZE, buffer, BLOCK_SIZE);
    return 0;
}

int disk_size() {
    return disk_blocks;
}

static uint32_t disk_total_blocks = 0;

uint32_t disk_get_total_blocks() {
    return disk_total_blocks;
}
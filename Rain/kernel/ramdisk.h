// kernel/ramdisk.h
#ifndef RAMDISK_H
#define RAMDISK_H

#include <stdint.h>

#define RAMDISK_SIZE (4 * 1024 * 1024)  // 4 MB
#define BLOCK_SIZE 512
#define BLOCK_COUNT (RAMDISK_SIZE / BLOCK_SIZE)

void ramdisk_init(void);
int ramdisk_read_block(uint64_t block_num, void *buffer);
int ramdisk_write_block(uint64_t block_num, const void *buffer);

#endif

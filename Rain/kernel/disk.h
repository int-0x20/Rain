#ifndef DISK_H
#define DISK_H

#define BLOCK_SIZE 512

#include <stdint.h>

int disk_init(int blocks);
int disk_read(int block, void *buffer);
int disk_write(int block, const void *buffer);
int disk_size();
uint32_t disk_get_total_blocks();

#endif

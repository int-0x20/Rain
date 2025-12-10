#ifndef TARFS_H
#define TARFS_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    char name[100];
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];
    char mtime[12];
    char chksum[8];
    char typeflag;
    char linkname[100];
    char magic[6];
    char version[2];
    char uname[32];
    char gname[32];
    char devmajor[8];
    char devminor[8];
    char prefix[155];
    char padding[12];
} __attribute__((packed)) TarHeader;

void tarfs_init(); 
void tarfs_list();
char *tarfs_read_file(const char *path, uint32_t *out_size);
int tarfs_file_exists(const char *path);

#endif

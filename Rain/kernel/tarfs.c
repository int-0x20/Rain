#include "tarfs.h"
#include "string.h"
#include "tty.h"

extern uint8_t _binary_ramdisk_tar_start;
extern uint8_t _binary_ramdisk_tar_end;
extern uint8_t _binary_ramdisk_tar_size;

uint8_t *tar_start = NULL;      // **FIXED**
static uint8_t *tar_end = NULL;
static uint8_t *tarfs_base = NULL;

static uint32_t oct_to_dec(const char *str) {
    uint32_t result = 0;
    while (*str >= '0' && *str <= '7') {
        result = (result << 3) + (*str - '0');
        str++;
    }
    return result;
}

static uint8_t *tar_end;

void tarfs_init(void)
{
    tar_start = &_binary_ramdisk_tar_start;
    tar_end   = &_binary_ramdisk_tar_end;
    tarfs_base = tar_start;

    tty_printf("TARFS start: %p\n", tar_start);
    tty_printf("TARFS end:   %p\n", tar_end);
    tty_printf("TARFS size:  %d bytes\n", (uint64_t)(tar_end - tar_start));
}




static TarHeader* tarfs_find(const char *path) {
    uint8_t *ptr = tarfs_base;

    while (1) {
        TarHeader *hdr = (TarHeader*)ptr;

        // End of archive: two 512-byte zero blocks
        if (hdr->name[0] == '\0')
            return NULL;

        if (strcmp(hdr->name, path) == 0)
            return hdr;

        uint32_t size = oct_to_dec(hdr->size);
        uint32_t total = ((size + 511) / 512 + 1) * 512;
        ptr += total;
    }
}

void tarfs_list() {
    uint8_t *ptr = tarfs_base;

    tty_printf("Files in TAR:\n");

    while (1) {
        TarHeader *hdr = (TarHeader*)ptr;

        if (hdr->name[0] == '\0')
            break;

        tty_printf(" - %s (%d bytes)\n", hdr->name, oct_to_dec(hdr->size));

        uint32_t size = oct_to_dec(hdr->size);
        uint32_t total = ((size + 511) / 512 + 1) * 512;
        ptr += total;
    }
}

char *tarfs_read_file(const char *path, uint32_t *out_size) {
    TarHeader *hdr = tarfs_find(path);
    if (!hdr)
        return NULL;

    uint32_t size = oct_to_dec(hdr->size);
    if (out_size)
        *out_size = size;

    uint8_t *data = (uint8_t*)hdr + 512;
    return (char*)data;
}

int tarfs_file_exists(const char *path) {
    return tarfs_find(path) != NULL;
}

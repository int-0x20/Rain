#include <stdint.h>
#include "kalloc.h"

#define KALLOC_SIZE  (1024 * 1024)   // 1MB heap
static uint8_t kalloc_heap[KALLOC_SIZE];
static uint64_t kalloc_offset = 0;

void *kalloc(uint64_t size) {
    if (kalloc_offset + size > KALLOC_SIZE)
        return 0;

    void *ptr = &kalloc_heap[kalloc_offset];
    kalloc_offset += size;
    return ptr;
}

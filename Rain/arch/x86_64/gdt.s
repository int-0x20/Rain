.section .text

gdt64:
    .quad 0x0000000000000000
    .quad 0x00AF9A000000FFFF   /* 64-bit code segment */
    .quad 0x00AF92000000FFFF   /* 64-bit data segment */

gdt64_ptr:
    .word (gdt64_ptr - gdt64 - 1)
    .quad gdt64

.global gdt64_ptr


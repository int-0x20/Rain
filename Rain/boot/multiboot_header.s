/* Multiboot2 header */

.section .multiboot
.align 8

/* Define constants using .set */
.set MB2_MAGIC,       0xE85250D6
.set MB2_ARCH,        0
.set MB2_HEADER_LEN,  (multiboot_header_end - multiboot_header_start)
.set MB2_CHECKSUM,    -(MB2_MAGIC + MB2_ARCH + MB2_HEADER_LEN)

multiboot_header_start:

    .long MB2_MAGIC
    .long MB2_ARCH
    .long MB2_HEADER_LEN
    .long MB2_CHECKSUM

    /* Required end tag */
    .word 0        /* type */
    .word 0        /* flags */
    .long 8        /* size */

multiboot_header_end:

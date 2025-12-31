/* boot/multiboot_header.s */

/* Multiboot2 header must be first in binary */
.section .multiboot, "a", @progbits
.align 8

/* Constants */
.set MB2_MAGIC,       0xE85250D6
.set MB2_ARCH,        0
.set MB2_HEADER_LEN,  (multiboot_header_end - multiboot_header_start)
.set MB2_CHECKSUM,    -(MB2_MAGIC + MB2_ARCH + MB2_HEADER_LEN)

.global multiboot_header_start
.global multiboot_header_end

multiboot_header_start:
    .long MB2_MAGIC          /* magic */
    .long MB2_ARCH           /* architecture */
    .long MB2_HEADER_LEN     /* header length */
    .long MB2_CHECKSUM       /* checksum */

    /* End tag - mandatory */
    .word 0                 /* type */
    .word 0                 /* flags */
    .long 8                 /* size */

multiboot_header_end:

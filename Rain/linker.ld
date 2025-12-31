ENTRY(start)

SECTIONS
{
    . = 1M;

    /* Multiboot2 header must be first */
    .multiboot :
    {
        KEEP(*(.multiboot))
    }

    /* Kernel code */
    .text :
    {
        *(.text*)
    }

    /* Read-only data */
    .rodata :
    {
        *(.rodata*)
    }

    /* Initialized data */
    .data :
    {
        *(.data*)
    }

    /* Uninitialized data (BSS) */
    .bss :
    {
        *(.bss*)
        *(COMMON)
    }

    /* Put paging structures here */
    .paging :
    {
        *(paging)
        *(pml4)
    }
}
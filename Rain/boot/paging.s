/* Minimal paging tables for entering 64-bit long mode */

.global pml4_table

.section .data
.align 4096

/* ===================== */
/* PML4 TABLE            */
/* ===================== */
pml4_table:
    .quad (pdpt_table + 0x03)   /* Present + Write */


/* ===================== */
/* PDPT TABLE            */
/* ===================== */
.align 4096
pdpt_table:
    .quad (pd_table + 0x03)     /* Present + Write */
    .fill 511, 8, 0


/* ===================== */
/* PAGE DIRECTORY        */
/* Identity maps 1 GiB   */
/* using 2 MiB pages     */
/* ===================== */
.align 4096
pd_table:
    .set addr, 0
    .rept 512
        .quad (addr | 0x83)    /* Present + Write + 2MB Page */
        .set addr, addr + 0x200000     /* Next 2MB */
    .endr

/* 32-bit entry from GRUB (Multiboot2 loads us in protected mode) */

.set CR0_PE, 1
.set CR0_PG, 0x80000000
.set CR4_PAE, 1 << 5
.set MSR_EFER, 0xC0000080
.set EFER_LME, 1 << 8

.global start
.extern long_mode_start
.extern gdt64_ptr
.extern pml4_table

.section .text
.code32

start:
    cli

    /* Load 64-bit GDT */
    lgdt gdt64_ptr

    /* Set up CR4 (Enable PAE) */
    mov %cr4, %eax
    or $CR4_PAE, %eax
    mov %eax, %cr4

    /* Load PML4 */
    mov $pml4_table, %eax
    mov %eax, %cr3

    /* Enable Long Mode */
    mov $MSR_EFER, %ecx
    rdmsr
    or $EFER_LME, %eax
    wrmsr

    /* Enable paging (Also sets PE bit already set by GRUB) */
    mov %cr0, %eax
    or $CR0_PG, %eax
    mov %eax, %cr0

    /* Far jump into 64-bit mode */
    ljmp $0x08, $long_mode_start

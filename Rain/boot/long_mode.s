.code64
.global long_mode_start
.extern kernel_main

long_mode_start:
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss

    call kernel_main

halt:
    hlt
    jmp halt

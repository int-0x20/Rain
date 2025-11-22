CC = x86_64-elf-gcc
AS = x86_64-elf-as
LD = x86_64-elf-ld

CFLAGS = -Wall -Wextra -ffreestanding -mno-red-zone -m64
LDFLAGS = -nostdlib

all: kernel.bin

kernel.bin: multiboot.o boot.o paging.o long_mode.o gdt.o kernel.o tty.o keyboard.o
	$(LD) -T linker.ld -o kernel.bin $(LDFLAGS) multiboot.o paging.o boot.o long_mode.o gdt.o kernel.o tty.o keyboard.o

multiboot.o: boot/multiboot_header.s
	$(AS) boot/multiboot_header.s -o multiboot.o

boot.o: boot/boot.s
	$(AS) boot/boot.s -o boot.o

long_mode.o: boot/long_mode.s
	$(AS) boot/long_mode.s -o long_mode.o

gdt.o: arch/x86_64/gdt.s
	$(AS) arch/x86_64/gdt.s -o gdt.o

kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel.o

tty.o: kernel/tty.c
	$(CC) $(CFLAGS) -c kernel/tty.c -o tty.o

paging.o: boot/paging.s
	$(AS) boot/paging.s -o paging.o

keyboard.o: kernel/keyboard.c
	$(CC) $(CFLAGS) -c kernel/keyboard.c -o keyboard.o

iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'menuentry "Rain" { multiboot2 /boot/kernel.bin }' >> iso/boot/grub/grub.cfg
	grub-mkrescue -o kernel.iso iso

clean:
	rm -f *.o kernel.bin kernel.iso
	rm -rf iso


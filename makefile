# Toolchain
CC=i386-elf-gcc
LD=i386-elf-ld
CFLAGS=-ffreestanding -O2 -Wall -Wextra
LDFLAGS=-T linker.ld

# Archivos
KERNEL=kernel.bin
OBJS=boot.o kernel.o video.o
ISO_DIR=iso
GRUB_CFG=grub/grub.cfg

all: iso

kernel.bin: boot.s kernel.c video.c linker.ld
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o
	$(CC) $(CFLAGS) -c video.c -o video.o
	nasm -f elf32 boot.s -o boot.o
	$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJS)

iso: kernel.bin
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL) $(ISO_DIR)/boot/
	cp $(GRUB_CFG) $(ISO_DIR)/boot/grub/
	grub-mkrescue -o mi_os.iso $(ISO_DIR)

run: iso
	qemu-system-x86_64 -cdrom mi_os.iso

clean:
	rm -rf *.o *.bin *.iso $(ISO_DIR)

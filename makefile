CC=i386-elf-gcc
LD=i386-elf-ld
CFLAGS=-ffreestanding -O2 -Wall -Wextra
LDFLAGS=-T linker.ld

KERNEL=kernel.bin
ISO_DIR=iso
GRUB_CFG=grub/grub.cfg

OBJS=boot.o kernel.o video.o isr.o keyboard.o pic.o port_io.o isr_asm.o

all: iso

kernel.bin: boot.s kernel.c video.c isr.c keyboard.c pic.c port_io.c isr.asm linker.ld
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o
	$(CC) $(CFLAGS) -c video.c -o video.o
	$(CC) $(CFLAGS) -c isr.c -o isr.o
	$(CC) $(CFLAGS) -c keyboard.c -o keyboard.o
	$(CC) $(CFLAGS) -c pic.c -o pic.o
	$(CC) $(CFLAGS) -c port_io.c -o port_io.o

	nasm -f elf32 isr.asm -o isr_asm.o
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

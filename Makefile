C_SOURCES := $(shell find kernel -name "*.c") $(shell find drivers -name "*.c")
C_OBJ = $(C_SOURCES:.c=.o)
ASM_SOURCES := $(shell find kernel -name "*.asm") $(shell find drivers -name "*.asm")
ASM_OBJ = $(ASM_SOURCES:.asm=.o)

all: os_image.bin

os_image.bin: boot/boot_sect.bin kernel/kernel.bin 
	cat boot/boot_sect.bin kernel/kernel.bin > os_image.bin

kernel/kernel.elf: kernel/kernel_entry.o ${C_OBJ} ${ASM_OBJ}
	ld -m elf_i386 -g -o $@ -Ttext 0x1000 $^

kernel/kernel.bin: kernel/kernel.elf
	objcopy -O binary $< $@

kernel/kernel.o: kernel/kernel.c
	gcc -ffreestanding -fno-pie -m32 -c kernel/kernel.c -o $@

boot/boot_sect.bin: boot/boot_sect.asm 
	nasm -f bin -o boot/boot_sect.bin boot/boot_sect.asm

%.o : %.c 
	gcc -ffreestanding -fno-pie -m32 -c $< -o $@

%.o : %.asm 
	nasm -f elf $< -o $@

clean: 
	rm os_image.bin
	rm kernel/*.o kernel/*.bin boot/*.o boot/*.bin drivers/*.o drivers/*.bin kernel.elf

run: os_image.bin
	qemu-system-i386 -drive file=os_image.bin,format=raw,if=floppy -gdb tcp::1234

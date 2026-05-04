CC = gcc
AS = gcc
LD = ld

CFLAGS = -m32 -nostdlib -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nodefaultlibs -ffreestanding -Wall -Wextra
ASFLAGS = -m32
LDFLAGS = -m elf_i386 -T src/linker.ld

OBJS = src/boot/boot.o src/kernel/main.o
BIN = images/kernel.bin
ISO = images/kfs.iso

all: $(ISO)

$(BIN): $(OBJS)
	mkdir -p images
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $@

$(ISO): $(BIN)
	mkdir -p isodir/boot/grub
	cp $(BIN) isodir/boot/
	echo 'menuentry "My KFS OS" { multiboot /boot/kernel.bin }' > isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) isodir
	rm -rf isodir

clean:
	rm -f $(OBJS) $(BIN)

fclean: clean
	rm -f $(ISO)

re: fclean all

run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)
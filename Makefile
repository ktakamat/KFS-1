CC = i686-linux-gnu-gcc
AS = i686-linux-gnu-gcc
LD = i686-linux-gnu-ld

CFLAGS = -m32 -nostdlib -fno-builtin -fno-exceptions -fno-stack-protector \
         -fno-rtti -nodefaultlibs -ffreestanding -Wall -Wextra -Werror
ASFLAGS = -m32
LDFLAGS = -m elf_i386 -T src/linker.ld

OBJS = src/boot/boot.o src/kernel/main.o
INC = src/kernel/kernel.h
BIN = images/kernel.bin
ISO = images/kfs.iso

all: $(ISO)

$(BIN): $(OBJS)
	@mkdir -p images
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $@

$(ISO): $(BIN)
	@mkdir -p isodir/boot/grub
	cp $(BIN) isodir/boot/
	@# 評価者が扱いやすいようにタイムアウトを設定
	echo 'set timeout=0' > isodir/boot/grub/grub.cfg
	echo 'set default=0' >> isodir/boot/grub/grub.cfg
	echo '' >> isodir/boot/grub/grub.cfg
	echo 'menuentry "My KFS OS" {' >> isodir/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin' >> isodir/boot/grub/grub.cfg
	echo '  boot' >> isodir/boot/grub/grub.cfg
	echo '}' >> isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) isodir
	rm -rf isodir

clean:
	rm -f $(OBJS) $(BIN)

fclean: clean
	rm -f $(ISO)

re: fclean all

run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)
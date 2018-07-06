BUILD_DIR = build
DISK_DIR = disk
KITS_DIR = kits
SOURCE_DIR = source
IMAGE_NAME= ShirleyOS.img
CC = g++
CFLAGS = -Iinclude -c -m16 -march=i386 -masm=intel -nostdlib -ffreestanding -mpreferred-stack-boundary=2 -lgcc -shared -Wno-int-to-void-pointer-cast -fpermissive -fno-pie -fno-stack-protector

AS = nasm
ASFLAGS =
LD = ld
LDFLAGS = -m elf_i386 -N

#如果不加-fda, 虽然能读Loader, 但无法读扇区:-(
QEMU = qemu-system-x86_64
QEMUFLAGS = -fda

BOCHS = bochs
BOCHSFLAGS = -q -f bochsrc.bxrc

all: build_dir write_image write_knl build_progs


build_dir:
	-mkdir $(BUILD_DIR)
	-mkdir $(DISK_DIR)
	
write_image: loadknl.bin
	dd if=/dev/zero of=$(IMAGE_NAME) count=2880
	dd if=$(BUILD_DIR)/loadknl.bin of=$(IMAGE_NAME) conv=notrunc

write_knl: kernel.bin
	sudo mount -o loop $(IMAGE_NAME) disk/
	sudo cp $(BUILD_DIR)/kernel.bin $(DISK_DIR)/
	sudo umount $(DISK_DIR)/

build_progs: pro1.com pro2.com pro3.com pro4.com

	sudo mount -o loop $(IMAGE_NAME) disk/

	for name in $^; do\
		sudo cp $(BUILD_DIR)/$$name $(DISK_DIR)/;\
	done

	sudo umount $(DISK_DIR)/

loadknl.bin: $(SOURCE_DIR)/loadknl.asm
	$(AS) $(ASFLAGS) -f bin $^ -o $(BUILD_DIR)/$@

kernel.bin: kernel.o os.o
	$(LD) $(LDFLAGS) -Ttext 0x7e00 --oformat binary $(BUILD_DIR)/kernel.o $(BUILD_DIR)/os.o -o $(BUILD_DIR)/$@


%.s: %.cpp
	$(CC) $(CFLAGS) -S $< -o $(BUILD_DIR)/$@ 
%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@ 
%.o: $(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@ 
%.o: $(SOURCE_DIR)/%.asm
	$(AS) $(ASFLAGS) -f elf32 $^ -o $(BUILD_DIR)/$@
%.com: %.o header.o
	#$(LD) $(LDFLAGS) -Ttext 0x100 --oformat binary $(BUILD_DIR)/header.o $(BUILD_DIR)/$< -o $(BUILD_DIR)/$@
	$(LD) $(LDFLAGS) -T $(SOURCE_DIR)/linker_100.ld --oformat binary $(BUILD_DIR)/header.o $(BUILD_DIR)/$< -o $(BUILD_DIR)/$@
%.com: $(SOURCE_DIR)/%.asm
	$(AS) $(ASFLAGS) -f bin $^ -o $(BUILD_DIR)/$@

qemu:
	$(QEMU) $(QEMUFLAGS) $(IMAGE_NAME)

run: qemu

bochs:
	$(BOCHS) $(BOCHSFLAGS)

build_counter:
	$(CC) $(SOURCE_DIR)/counter.cpp -o $(BUILD_DIR)/counter

clean:
	-rm -rf $(BUILD_DIR)
	-rm -rf $(DISK_DIR)

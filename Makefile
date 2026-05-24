K = kernel
U = user
C = common

QEMU = qemu-system-riscv32
CC = clang
OBJCOPY = llvm-objcopy
OBJDUMP = llvm-objdump

CFLAGS = -std=c11 \
    -O0 \
    -g3 \
    -Wall \
    -Wextra \
    --target=riscv32-unknown-elf \
    -fno-stack-protector \
	-fno-omit-frame-pointer \
    -ffreestanding \
    -nostdlib \
    -I. \
    -I$C \
    -MD

LDFLAGS = -fuse-ld=lld

.PHONY: all qemu qemu-gdb clean print-gdbport

all: $K/kernel.elf disk.tar

# Prevent deletion of intermediate files
.PRECIOUS: %.o $U/shell.bin $U/shell.elf

# Generic rule for compiling C files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# --- User Space (Application) ---

U_OBJS = \
    $U/shell.o \
    $U/user.o \
    $C/common.o

$U/shell.elf: $(U_OBJS) $U/user.ld
	$(CC) $(CFLAGS) $(LDFLAGS) -Wl,-T$U/user.ld -Wl,-Map=$U/shell.map -o $@ $(U_OBJS)
	$(OBJDUMP) -S $@ > $U/shell.asm

$U/shell.bin: $U/shell.elf
	$(OBJCOPY) --set-section-flags .bss=alloc,contents -O binary $< $@

$U/shell.bin.o: $U/shell.bin
	$(OBJCOPY) -Ibinary -Oelf32-littleriscv $< $@

# --- Kernel Space ---

K_OBJS = \
    $K/kernel.o \
    $C/common.o \
    $U/shell.bin.o

$K/kernel.elf: $(K_OBJS) $K/kernel.ld
	$(CC) $(CFLAGS) $(LDFLAGS) -Wl,-T$K/kernel.ld -Wl,-Map=$K/kernel.map -o $@ $(K_OBJS)
	$(OBJDUMP) -S $@ > $K/kernel.asm

# --- Disk Image ---

disk.tar: $(wildcard disk/*.txt)
	cd disk && tar cf ../disk.tar --format=ustar *.txt

# --- QEMU & GDB (xv6 style) ---

GDBPORT = $(shell expr `id -u` % 5000 + 25000)
QEMUGDB = $(shell if $(QEMU) -help | grep -q '^-gdb'; \
    then echo "-gdb tcp::$(GDBPORT)"; \
    else echo "-s -p $(GDBPORT)"; fi)

QEMUOPTS = -machine virt \
    -bios default \
    -nographic \
    -serial mon:stdio \
    --no-reboot \
    -d unimp,guest_errors,int,cpu_reset \
    -D qemu.log \
    -drive id=drive0,file=disk.tar,format=raw,if=none \
    -device virtio-blk-device,drive=drive0,bus=virtio-mmio-bus.0 \
    -kernel $K/kernel.elf

qemu: all
	$(QEMU) $(QEMUOPTS)

.gdbinit: .gdbinit.tmpl-riscv
	sed "s/:1234/:$(GDBPORT)/" < $^ > $@

qemu-gdb: all .gdbinit
	@echo "*** Now run 'gdb' in another window." 1>&2
	$(QEMU) $(QEMUOPTS) -S $(QEMUGDB)

print-gdbport:
	@echo $(GDBPORT)

# --- Dependencies & Cleanup ---

-include $K/*.d $U/*.d $C/*.d

clean:
	rm -f $K/*.o $K/*.d $K/*.elf $K/*.map $K/*.asm
	rm -f $U/*.o $U/*.d $U/*.elf $U/*.map $U/*.asm $U/*.bin $U/*.bin.o
	rm -f $C/*.o $C/*.d
	rm -f disk.tar qemu.log .gdbinit

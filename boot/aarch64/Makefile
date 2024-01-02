override AS = aarch64-elf-gcc
override LD = aarch64-elf-ld
override ASFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles
override LDFLAGS = -nostdlib

include Makefile.build

.PHONY: all
all: bootloader

# final link
.PHONY: bootloader
bootloader:
	@echo "  AS boot.o"
	@$(INT_AS) $(INT_ASFLAGS) -c src/boot.S -o boot.oS

.PHONY: clean
clean:
	@rm -rf boot.oS

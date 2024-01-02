MAKE_ARCH ?= x86_64
ARCH := $(MAKE_ARCH)
export MAKE_ARCH
export ARCH

include kernel/Makefile.version

RELEASE_DIR := $(PWD)/release

RELEASE_IMG := $(RELEASE_DIR)/aurixos-hdd-$(KVERSION)_$(ARCH).img

.PHONY: boot kernel release

all: kernel

alldefconfig:
	@$(MAKE) --no-print-directory -C kernel alldefconfig

menuconfig:
	@$(MAKE) --no-print-directory -C kernel menuconfig

boot:
	@$(MAKE) --no-print-directory -C boot/$(ARCH)

kernel: boot
	@$(MAKE) --no-print-directory -C kernel

release: release_img

release_img: boot kernel
	@mkdir -p $(RELEASE_DIR)
	@mkdir -p sysroot_tmp
	@dd if=/dev/zero of=$(RELEASE_IMG) bs=1M count=16 2>/dev/null
	@mformat -i $(RELEASE_IMG) ::
	@mcopy -i $(RELEASE_IMG) sysroot/* ::
ifeq ($(ARCH),x86_64)
	@mmd -i $(RELEASE_IMG) ::/EFI
	@mmd -i $(RELEASE_IMG) ::/EFI/BOOT
	@mmd -i $(RELEASE_IMG) ::/System
	@mcopy -i $(RELEASE_IMG) boot/x86_64/boot.o ::/EFI/BOOT
	@mcopy -i $(RELEASE_IMG) kernel/kernel.o ::/System/axkrnl
else ifeq ($(ARCH),aarch64)
	@mcopy -i $(RELEASE_IMG) kernel/kernel.o ::/kernel8.elf
	@mcopy -i $(RELEASE_IMG) boot/aarch64/bootfiles/* ::
endif
	@rm -rf sysroot_tmp

clean:
	@rm -rf *.o $(RELEASE_DIR) sysroot_tmp
	@$(MAKE) --no-print-directory -C boot/$(ARCH) clean
	@$(MAKE) --no-print-directory -C kernel clean

proper: clean
	@$(MAKE) --no-print-directory -C kernel proper

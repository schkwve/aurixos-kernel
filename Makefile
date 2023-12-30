MAKE_ARCH ?= aarch64
ARCH := $(MAKE_ARCH)
export MAKE_ARCH
export ARCH

include kernel/Makefile.version

ROOT_DIR := $(PWD)
SYSROOT_DIR := $(ROOT_DIR)/sysroot
export SYSROOT_DIR

RELEASE_DIR := $(ROOT_DIR)/release

RELEASE_IMG := $(RELEASE_DIR)/aurixos-hdd-$(KVERSION)_$(ARCH).img
RELEASE_ISO := $(RELEASE_DIR)/aurixos-cdrom-$(KVERSION)_$(ARCH).iso

.PHONY: boot kernel release sysroot

all: kernel

alldefconfig:
	@$(MAKE) --no-print-directory -C kernel alldefconfig

menuconfig:
	@$(MAKE) --no-print-directory -C kernel menuconfig

boot:
	@$(MAKE) --no-print-directory -C boot/$(ARCH)

kernel: boot
	@$(MAKE) --no-print-directory -C kernel

sysroot: boot kernel
	@$(MAKE) SYSROOT=$(SYSROOT_DIR) --no-print-directory -C boot/$(ARCH) install
	@$(MAKE) SYSROOT=$(SYSROOT_DIR) --no-print-directory -C kernel install

release: release_img release_iso

release_img: sysroot
	@mkdir -p $(RELEASE_DIR)
	@dd if=/dev/zero of=$(RELEASE_IMG) bs=1M count=16
	@mformat -i $(RELEASE_IMG) ::
ifeq ($(ARCH),x86_64)
	@mmd -i $(RELEASE_IMG) ::/EFI
	@mmd -i $(RELEASE_IMG) ::/EFI/BOOT
	@mmd -i $(RELEASE_IMG) ::/System
	@mcopy -i $(RELEASE_IMG) $(SYSROOT_DIR)/BOOTX64.EFI ::/EFI/BOOT
	@mcopy -i $(RELEASE_IMG) $(SYSROOT_DIR)/kernel.o ::/System/axkrnl
else ifeq ($(ARCH),aarch64)
	@mcopy -i $(RELEASE_IMG) $(SYSROOT_DIR)/kernel.o ::/kernel8.elf
	@mcopy -i $(RELEASE_IMG) boot/aarch64/bootfiles/* ::
endif

release_iso: sysroot release_img
ifeq ($(ARCH),x86_64)
	@mkdir -p $(RELEASE_DIR)
	@mkdir -p iso_tmp
	@cp $(RELEASE_IMG) iso_tmp
	@xorriso -as mkisofs -R -f -e $(RELEASE_IMG) -no-emul-boot -o $(RELEASE_ISO) iso_tmp
	@rm -rf iso_tmp
else ifeq ($(ARCH),aarch64)
	@$(error Generating ISO for aarch64 is not supported!)
endif

clean:
	@rm -rf *.o $(SYSROOT_DIR) $(RELEASE_DIR)
	@$(MAKE) --no-print-directory -C boot/$(ARCH) clean
	@$(MAKE) --no-print-directory -C kernel clean

proper: clean
	@$(MAKE) --no-print-directory -C kernel proper

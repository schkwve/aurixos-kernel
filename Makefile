MAKE_ARCH ?= aarch64
ARCH := $(MAKE_ARCH)
export MAKE_ARCH
export ARCH

ROOT_DIR := $(PWD)
SYSROOT_DIR := $(ROOT_DIR)/sysroot

.PHONY: all kernel boot sysroot

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

clean:
	@rm -rf *.o $(SYSROOT_DIR)
	@$(MAKE) --no-print-directory -C boot/$(ARCH) clean
	@$(MAKE) --no-print-directory -C kernel clean

proper: clean
	@$(MAKE) --no-print-directory -C kernel proper

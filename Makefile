MAKE_ARCH ?= x86
ARCH := $(MAKE_ARCH)
export MAKE_ARCH
export ARCH

.PHONY: kernel

all: kernel

alldefconfig:
	@$(MAKE) --no-print-directory -C kernel alldefconfig

menuconfig:
	@$(MAKE) --no-print-directory -C kernel menuconfig

kernel:
	@$(MAKE) --no-print-directory -C kernel

clean:
	@rm -f *.o
	@$(MAKE) --no-print-directory -C kernel clean

proper: clean
	@$(MAKE) --no-print-directory -C kernel proper

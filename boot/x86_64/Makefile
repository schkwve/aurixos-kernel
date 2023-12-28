override CC      = clang
override CXX      = clang
override LD       = clang
override CFLAGS = -target x86_64-unknown-windows
override CXXFLAGS = -target x86_64-unknown-windows
override LDFLAGS  = -target x86_64-unknown-windows -nostdlib -fuse-ld=lld-link -Wl,-subsystem:efi_application -Wl,-entry:efi_main

BUILD_SUBDIRS := src 

OBJS         := 
objtree      := .
srctree      := .
define build_subdir
objtree := $$(objtree)/$(1)
srctree := $$(srctree)/$(1)

obj-y :=
obj-d :=

include $$(srctree)/Makefile

OBJS += $$(patsubst %,$$(objtree)/%,$$(obj-y))

$$(foreach subdir,$$(obj-d),$$(eval $$(call build_subdir,$$(subdir))))

srctree := $$(patsubst %/$(1),%,$$(srctree))
objtree := $$(patsubst %/$(1),%,$$(objtree))
endef

$(foreach dir, $(BUILD_SUBDIRS), $(eval $(call build_subdir,$(dir))))

include Makefile.build

.PHONY: all
all: bootloader

.PHONY: build_objs
build_objs: $(OBJS)

# final link
.PHONY: bootloader
bootloader: | build_objs
	@echo "  LD BOOTX64.EFI"
	@$(INT_LD) $(INT_LDFLAGS) $(OBJS) -o boot.o

.PHONY: install
install: bootloader
	@mkdir -p $(SYSROOT)/EFI/BOOT
	@cp boot.o $(SYSROOT)/EFI/BOOT/BOOTX64.EFI

.PHONY: clean
clean:
	@rm -rf *.o $(OBJS)

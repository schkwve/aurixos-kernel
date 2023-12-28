override AS = aarch64-elf-gcc
override LD = aarch64-elf-ld
override ASFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles
override LDFLAGS = -nostdlib

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
	@echo "  LD boot.o"
	@$(INT_LD) $(INT_LDFLAGS) $(OBJS) -o boot.o

.PHONY: install
install: bootloader
	@mkdir -p $(SYSROOT)
	@cp boot.o $(SYSROOT)

.PHONY: clean
clean:
	@rm -rf *.o $(OBJS)

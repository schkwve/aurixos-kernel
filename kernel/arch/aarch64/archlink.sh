#!/usr/bin/env bash
set -e

${INT_LD} ${INT_LDFLAGS} -T arch/aarch64/linker.ld kernel_partial.o ../boot/aarch64/boot.o -o kernel.o

#!/usr/bin/env bash
set -e

source .config

ldscript="arch/x86/linker_32.ld"
ptrsize=".long"

if [ "$CONFIG_ENABLE_KERNEL_64" == "y" ]; then
    ldscript="arch/x86/linker_64.ld"
    ptrsize=".quad"
fi

${INT_LD} ${INT_LDFLAGS} -T ${ldscript} kernel_partial.o -o kernel.o
${INT_NM} --format=bsd -n kernel.o | python3 scripts/gensyms.py ${ptrsize} > symtab.s
${INT_CXX} ${INT_CXXFLAGS} -c symtab.s -o symtab.os
${INT_LD} ${INT_LDFLAGS} -T ${ldscript} kernel_partial.o symtab.os -o kernel.o

${INT_NM} --format=bsd -n kernel.o | python3 scripts/gensyms.py ${ptrsize} > symtab.s
${INT_CXX} ${INT_CXXFLAGS} -c symtab.s -o symtab.os
${INT_LD} ${INT_LDFLAGS} -T ${ldscript} kernel_partial.o symtab.os -o kernel.o

${INT_OBJCOPY} -O binary kernel.o kernel.bin

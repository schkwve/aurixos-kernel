ENTRY(kernel_init)

PAGE = 0x1000;

PHDRS
{
	text PT_LOAD FLAGS((1 << 0) | (1 << 2));
	rodata PT_LOAD FLAGS((1 << 2));
	data PT_LOAD FLAGS((1 << 1) | (1 << 2));
}

MEMORY
{
	ram (rwx) : org = 0xffffffff80000000, l = 0xF0000
}

SECTIONS
{
	. = 0xffffffff80000000;

	.text ALIGN(PAGE) : {
		*(.text)
		KEEP(*(.tests))
	}>ram :text

	. += CONSTANT(MAXPAGESIZE);

	.rodata ALIGN(PAGE) : {
		*(.rodata)
	} >ram :rodata

	. += CONSTANT(MAXPAGESIZE);

	.data ALIGN(PAGE) : {
		START_CONSTRUCTORS_INITARR = .;
		KEEP(*(.init_array));
		KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)));
		END_CONSTRUCTORS_INITARR = .;
		START_CONSTRUCTORS_CTORS = .;
		KEEP(*(.ctors));
		KEEP(*(SORT_BY_INIT_PRIORITY(.ctors.*)));
		END_CONSTRUCTORS_CTORS = .;
		KEEP(*(.data))
		KEEP(*(.sym_table))
		PROVIDE(symtab_start = .);
		PROVIDE(symtab_end = .);
	} >ram :data

	.bss ALIGN(PAGE) : {
		. = ALIGN(16);
		__bss_start = .;
		*(.bss)
		__bss_end = .;
	} >ram : data

	/DISCARD/ : {
		*(.comment)
		*(.gnu*)
		*(.note*)
		*(.eh_frame*)
	}
}
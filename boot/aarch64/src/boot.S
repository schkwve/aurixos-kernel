.section ".text.boot"

.global _start

_start:
    // if we're not running on the main core, hang
    mrs x1, mpidr_el1
    and x1, x1, #3
    cbz x1, 2f
1:
	wfe
    b 1b
2:
    // set the stack start below our code
    ldr     x1, =_start
    mov     sp, x1

    // clean the BSS section
    ldr x1, =__bss_start
    ldr w2, =__bss_size
3:
	cbz w2, 4f
    str xzr, [x1], #8
    sub w2, w2, #1
    cbnz w2, 3b

    // jump to the prekernel
4:
	bl prekernel_init
    // in the odd case that we *do* return, halt all cores
	b 1b

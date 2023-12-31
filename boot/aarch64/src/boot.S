/************************************************************************
 * FILENAME:         boot.S
 *
 * DESCRIPTION:
 *       Raspberry Pi 4 bootstrap.
 *       This file starts up the prekernel on the main core.
 *
 * AUTHOR:     Jozef Nagy                  DATE:    30 Dec 2023
 *
 * COPYRIGHT:
 *       Copyright (C) 2023, 2024  Jozef Nagy.
 *
 *       This program is free software; you can redistribute it and/or
 *       modify it under the terms of the GNU General Public License
 *       as published by the Free Software Foundation; either version 2
 *       of the License, or (at your option) any later version.
 *       
 *       This program is distributed in the hope that it will be useful,
 *       but WITHOUT ANY WARRANTY; without even the implied warranty of
 *       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *       GNU General Public License for more details.
 *       
 *       You should have received a copy of the GNU General Public License
 *       along with this program; If not, see <http://www.gnu.org/licenses/>.
 **/

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

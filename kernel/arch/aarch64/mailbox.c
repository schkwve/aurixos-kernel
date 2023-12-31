/************************************************************************
 * FILENAME:         gpio.c
 *
 * DESCRIPTION:
 *       Raspberry Pi Mailbox functionality.
 *
 * AUTHOR:     Jozef Nagy                  DATE:    31 Dec 2023
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

#include <arch/mailbox.h>
#include <mm/mmio.h>
#include <sys/types.h>

volatile uint32_t __attribute__((aligned(16))) mailbox[36];

uint32_t mailbox_call(uint32_t c)
{
	// 28-bit address
	// 4-bit value
	uint32_t r = ((uint32_t)((long)&mailbox) &~ 0x0F) | (c & 0x0F);

	// wait until we can write
	while (mmio_read(MBOX_STATUS) & MBOX_FULL);

	// write to the mailbox
	mmio_write(MBOX_WRITE, r);

	while (1) {
		// wait until a reply to our message is received
		while (mmio_read(MBOX_STATUS) & MBOX_EMPTY);
		if (mmio_read(MBOX_READ) == r) {
			return mailbox[1] == MBOX_RESPONSE;
		}
	}
}

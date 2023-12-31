/************************************************************************
 * FILENAME:         mailbox.h
 *
 * DESCRIPTION:
 *       Mailbox-related definitions and function declarations.
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

#ifndef AARCH64_MAILBOX_H
#define AARCH64_MAILBOX_H

#include <arch/io/gpio.h>
#include <sys/types.h>

#define VIDEOCORE_MBOX (PERIPHERAL_BASE + 0xB880)
#define MBOX_READ (VIDEOCORE_MBOX)
#define MBOX_POLL (VIDEOCORE_MBOX + 0x10)
#define MBOX_SENDER (VIDEOCORE_MBOX + 0x14)
#define MBOX_STATUS (VIDEOCORE_MBOX + 0x18)
#define MBOX_CONFIG (VIDEOCORE_MBOX + 0x1C)
#define MBOX_WRITE (VIDEOCORE_MBOX + 0x20)
#define MBOX_RESPONSE 0x80000000
#define MBOX_FULL 0x80000000
#define MBOX_EMPTY 0x40000000

enum {
	MBOX_TAG_SETPOWER = 0x28001,
	MBOX_TAG_SETCLKRATE = 0x38002,
	MBOX_TAG_SETPHYWH = 0x48003,
	MBOX_TAG_SETVIRTWH = 0x48004,
	MBOX_TAG_SETVIRTOFF = 0x48009,
	MBOX_TAG_SETDEPTH = 0x48005,
	MBOX_TAG_SETPXLORDR = 0x48006,
	MBOX_TAG_GETFB = 0x40001,
	MBOX_TAG_GETPITCH = 0x40008,

	MBOX_TAG_LAST = 0
};

enum {
	MBOX_CH_POWER = 0,
	MBOX_CH_FB = 1,
	MBOX_CH_VUART = 2,
	MBOX_CH_VCHIQ = 3,
	MBOX_CH_LEDS = 4,
	MBOX_CH_BTNS = 5,
	MBOX_CH_TOUCH = 6,
	MBOX_CH_COUNT = 7,
	MBOX_CH_PROP = 8
};

enum {
	MBOX_REQUEST = 0,
};

extern volatile uint32_t mailbox[36];

uint32_t mailbox_call(uint32_t c);

#endif /* AARCH64_MAILBOX_H */

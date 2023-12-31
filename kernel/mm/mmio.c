/************************************************************************
 * FILENAME:         mmio.c
 *
 * DESCRIPTION:
 *       MMIO read/write function declarations.
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

#include <mm/mmio.h>

#include <stddef.h>
#include <sys/types.h>

uint32_t mmio_read(uint64_t reg)
{
	return *(volatile uint32_t *)reg;
}

void mmio_write(uint64_t reg, uint32_t value)
{
	*(volatile uint32_t *)reg = value;
}
/************************************************************************
 * FILENAME:         framebuffer.h
 *
 * DESCRIPTION:
 *       Framebuffer-related functions declarations.
 *
 * AUTHOR:     Jozef Nagy                  DATE:    31 Dec 2023
 *
 * COPYRIGHT:
 *       Copyright (C) 2023  Jozef Nagy.
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

#ifndef AARCH64_FRAMEBUFFER_H
#define AARCH64_FRAMEBUFFER_H

#include <sys/types.h>

void framebuffer_init();

void framebuffer_putpixel(int x, int y, uint8_t attr);

void framebuffer_draw_char(uint32_t c, int x, int y, uint32_t attr);
void framebuffer_draw_string(int x, int y, char *s, uint32_t attr);

#endif /* AARCH64_FRAMEBUFFER_H */

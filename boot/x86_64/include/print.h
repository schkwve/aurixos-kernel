/************************************************************************
 * FILENAME:         print.h
 *
 * DESCRIPTION:
 *       Printing and formatting functions forward declarations.
 *
 * AUTHOR:     Jozef Nagy                  DATE:    02 Jan 2024
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

#ifndef PRINT_H
#define PRINT_H

#include <efi/efi.h>

void print(CHAR16 *fmt, ...);

void __printint(INT32 num);
void __printhex(UINTN num);

#endif /* PRINT_H */

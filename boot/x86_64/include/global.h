/************************************************************************
 * FILENAME:         global.h
 *
 * DESCRIPTION:
 *       Global variables.
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

#ifndef GLOBAL_H
#define GLOBAL_H

#include <efi/efi.h>

static EFI_SYSTEM_TABLE *gSystemTable = NULL;
static EFI_HANDLE gImageHandle = NULL;

#endif /* GLOBAL_H */

/************************************************************************
 * FILENAME:         _types.h
 *
 * DESCRIPTION:
 *       EFI library types definitions.
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

#ifndef EFI_TYPES_H
#define EFI_TYPES_H

#include <stdint.h>
#include <stddef.h>

// Wide character
typedef uint_least16_t char16_t;

// Common UEFI Data types
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef uint64_t UINTN;
typedef char16_t CHAR16;
typedef void VOID;

typedef UINTN EFI_STATUS;
typedef VOID *EFI_HANDLE;

// https://github.com/tianocore/edk2/blob/master/MdePkg/Include/Base.h
#define IN
#define OUT
#define OPTIONAL
#define CONST const

// x86_64 Microsoft calling convention
// https://github.com/vathpela/gnu-efi/blob/master/inc/x86_64/efibind.h
#define EFIAPI __attribute__((ms_abi))

// EFI Status Codes
#define EFI_SUCCESS 0

// Text attributes
#define EFI_BLACK 0x00
#define EFI_BLUE 0x01
#define EFI_GREEN 0x02
#define EFI_CYAN 0x03
#define EFI_RED 0x04
#define EFI_YELLOW 0x0E
#define EFI_WHITE 0x0F

// Converts Foreground and Background colors into a single value
// NOTE: Only use 0x00-0x07 for background.
#define EFI_TEXT_ATTR(Foreground,Background) \
	((Foreground) | ((Background) << 4))

#endif /* EFI_TYPES_H */

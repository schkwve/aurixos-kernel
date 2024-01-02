/************************************************************************
 * FILENAME:         main.c
 *
 * DESCRIPTION:
 *       EFI Bootloader entry point.
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

#include <efi/efi.h>

#include <print.h>
#include <global.h>

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	gImageHandle = ImageHandle;
	gSystemTable = SystemTable;

	gSystemTable->ConOut->Reset(gSystemTable->ConOut, false);
	gSystemTable->ConOut->ClearScreen(gSystemTable->ConOut);

	CHAR16 *world = L"world";
	print(L"Hello, %s!\r\n", world);

	for (;;);

	return EFI_SUCCESS;
}

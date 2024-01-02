/************************************************************************
 * FILENAME:         print.c
 *
 * DESCRIPTION:
 *       Printing and formatting.
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

#include <stdarg.h>

#include <efi/efi.h>
#include <print.h>
#include <global.h>

void print(CHAR16 *fmt, ...)
{
	va_list args;
	CHAR16 charstr[2] = { L'\0' };

	va_start(args, fmt);

	for (UINTN i = 0; fmt[i] != L'\0'; i++) {
		if (fmt[i++] == L'%') {
			switch (fmt[i]) {
				case L's': {
					CHAR16 *str = va_arg(args, CHAR16 *);
					gSystemTable->ConOut->OutputString(gSystemTable->ConOut, str);
					break;
				}
				case L'd': {
					INT32 num = va_arg(args, INT32);
					__printint(num);
					break;
				}
				case L'x': {
					UINTN num = va_arg(args, UINTN);
					__printhex(num);
					break;
				}
				default: {
					gSystemTable->ConOut->OutputString(gSystemTable->ConOut, L"%%?");
					break;
				}
			}
		} else {
			charstr[0] = fmt[i];
			gSystemTable->ConOut->OutputString(gSystemTable->ConOut, charstr);
		}
	}

	va_end(args);
}

void __printint(INT32 num)
{
	const CHAR16 *digits = L"0123456789";
	CHAR16 buffer[11];
	UINTN i = 0;
	const bool negative = (num < 0);

	do {
		buffer[i++] = digits[num % 10];
		num /= 10;
	} while (num > 0);

	if (negative) {
		buffer[i++] = L'-';
	}

	buffer[i--] = L'\0';

	for (UINTN j = 0; j < i; j++, i--) {
		UINTN temp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = temp;
	}

	gSystemTable->ConOut->OutputString(gSystemTable->ConOut, buffer);
}

void __printhex(UINTN num)
{
	const CHAR16 *digits = L"0123456789ABCDEF";
	CHAR16 buffer[20];
	UINTN i = 0;

	do {
		buffer[i++] = digits[num % 10];
		num /= 16;
	} while (num > 0);

	buffer[i--] = L'\0';

	for (UINTN j = 0; j < i; j++, i--) {
		UINTN temp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = temp;
	}

	gSystemTable->ConOut->OutputString(gSystemTable->ConOut, buffer);
}

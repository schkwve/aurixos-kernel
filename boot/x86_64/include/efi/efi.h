/************************************************************************
 * FILENAME:         efi.h
 *
 * DESCRIPTION:
 *       EFI Library header file. Structures and function pointers are
 *       defined here.
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

#ifndef EFI_H
#define EFI_H

#include "_types.h"

// EFI Simple Text Input Protocol
typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

// EFI Simple Text Output Protocol
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// Input Key
typedef struct {
	UINT16 ScanCode;
	WCHAR UnicodeChar;
} EFI_INPUT_KEY;

// EFI Table Header
typedef struct {
	UINT64 Signature;
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
} EFI_TABLE_HEADER;

// EFI Reset Type
typedef enum {
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown,
	EfiResetPlatformSpecific
} EFI_RESET_TYPE;

/**********************
 * FUNCTIONS          *
 **********************/

typedef 
EFI_STATUS 
(EFIAPI *EFI_INPUT_READ_KEY)(
	IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, 
	OUT EFI_INPUT_KEY *Key
);

typedef 
EFI_STATUS 
(EFIAPI *EFI_TEXT_STRING)(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN WCHAR *String
);

typedef 
EFI_STATUS 
(EFIAPI *EFI_TEXT_SET_ATTRIBUTE)(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN Attribute
);

typedef 
EFI_STATUS 
(EFIAPI *EFI_TEXT_CLEAR_SCREEN)(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This
);

typedef 
VOID 
(EFIAPI *EFI_RESET_SYSTEM)(
	IN EFI_RESET_TYPE ResetType,      
	IN EFI_STATUS ResetStatus,   
	IN UINTN DataSize,     
	IN VOID *ResetData OPTIONAL
);

/**********************
 * Protocols & Tables *
 **********************/

// EFI Simple Text Input Protocol
typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	void *Reset;
	EFI_INPUT_READ_KEY ReadKeyStroke;
	void *WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

// EFI Simple Text Output Protocol
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
	void *Reset;
	EFI_TEXT_STRING OutputString;
	void *TestString;
	void *QueryMode;
	void *SetMode;
	EFI_TEXT_SET_ATTRIBUTE SetAttribute;
	EFI_TEXT_CLEAR_SCREEN ClearScreen;
	void *SetCursorPosition;
	void *EnableCursor;
	void *Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// EFI Runtime Services
typedef struct {
	EFI_TABLE_HEADER Hdr;

	// Time Services
	void *GetTime; 
	void *SetTime; 
	void *GetWakeupTime; 
	void *SetWakeupTime; 

	// Virtual Memory Services
	void *SetVirtualAddressMap;
	void *ConvertPointer;

	// Variable Services
	void *GetVariable;
	void *GetNextVariableName;
	void *SetVariable;

	// Miscellaneous Services
	void *GetNextHighMonotonicCount;
	EFI_RESET_SYSTEM ResetSystem;

	// UEFI 2.0 Capsule Services
	void *UpdateCapsule;
	void *QueryCapsuleCapabilities;

	// Miscellaneous UEFI 2.0 Service
	void *QueryVariableInfo; 
} EFI_RUNTIME_SERVICES;

// EFI System Table
typedef struct {
	EFI_TABLE_HEADER Hdr;

	void *FirmwareVendor;
	UINT32 FirmwareRevision;
	void *ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
	void *ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
	void *StandardErrorHandle;
	void *StdErr;
	EFI_RUNTIME_SERVICES *RuntimeServices;
	void *BootServices;
	UINTN NumberOfTableEntries;
	void *ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif /* EFI_H */

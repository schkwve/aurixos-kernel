/************************************************************************
 * FILENAME:         gpio.h
 *
 * DESCRIPTION:
 *       GPIO-related Raspberry Pi 4 (aarch64) specific addresses
 *       definitions and function declarations.
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

#ifndef AARCH64_GPIO_H
#define AARCH64_GPIO_H

#include <sys/types.h>

#define PERIPHERAL_BASE (0xFE000000)
#define GPFSEL0 (PERIPHERAL_BASE + 0x200000)
#define GPSET0 (PERIPHERAL_BASE + 0x20001C)
#define GPCLR0 (PERIPHERAL_BASE + 0x200028)
#define GPPUPPDN0 (PERIPHERAL_BASE + 0x2000E4)

enum {
	GPIO_MAX_PIN = 52,
	GPIO_FUNCTION_OUT = 1,
	GPIO_FUNCTION_ALT5 = 2,
	GPIO_FUNCTION_ALT3 = 7
};

enum {
	Pull_None = 0,
	Pull_Down = 1,
	Pull_Up = 2
};

uint32_t gpio_call(uint32_t pin_number, uint32_t value, uint32_t base, uint32_t field_size, uint32_t field_max);

void gpio_set_pin_output(uint32_t pin_number, uint32_t state);

void gpio_use_as_alt3(uint32_t pin_number);
void gpio_use_as_alt5(uint32_t pin_number);
void gpio_init_output_with_pull_none(uint32_t pin_number);

uint32_t gpio_set(uint32_t pin_number, uint32_t value);
uint32_t gpio_clear(uint32_t pin_number, uint32_t value);
uint32_t gpio_pull(uint32_t pin_number, uint32_t value);
uint32_t gpio_function(uint32_t pin_number, uint32_t value);

#endif /* AARCH64_GPIO_H */

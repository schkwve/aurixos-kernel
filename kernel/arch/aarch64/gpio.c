/************************************************************************
 * FILENAME:         gpio.c
 *
 * DESCRIPTION:
 *       GPIO functionality.
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

#include <arch/io/gpio.h>
#include <mm/mmio.h>

uint32_t gpio_call(uint32_t pin_number, uint32_t value, uint32_t base, uint32_t field_size, uint32_t field_max)
{
	uint32_t field_mask = (1 << field_size) - 1;

	if (pin_number > field_max) {
		return -1;
	}

	if (value > field_mask) {
		return -1;
	}

	uint32_t num_fields = 32 / field_size;
	uint32_t reg = base + ((pin_number / num_fields) * 4);
	uint32_t shift = (pin_number % num_fields) * field_size;

	uint32_t curval = mmio_read(reg);
	curval &= ~(field_mask << shift);
	curval |= value << shift;
	mmio_write(reg, curval);

	return 0;
}

void gpio_set_pin_output(uint32_t pin_number, uint32_t state)
{
	if (state) {
		gpio_set(pin_number, 1);
	} else {
		gpio_clear(pin_number, 1);
	}
}

void gpio_use_as_alt3(uint32_t pin_number)
{
	gpio_pull(pin_number, Pull_None);
	gpio_function(pin_number, GPIO_FUNCTION_ALT3);
}

void gpio_use_as_alt5(uint32_t pin_number)
{
	gpio_pull(pin_number, Pull_None);
	gpio_function(pin_number, GPIO_FUNCTION_ALT5);
}

void gpio_init_output_with_pull_none(uint32_t pin_number)
{
	gpio_pull(pin_number, Pull_None);
	gpio_function(pin_number, GPIO_FUNCTION_OUT);
}

uint32_t gpio_set(uint32_t pin_number, uint32_t value)
{
	return gpio_call(pin_number, value, GPSET0, 1, GPIO_MAX_PIN);
}

uint32_t gpio_clear(uint32_t pin_number, uint32_t value)
{
	return gpio_call(pin_number, value, GPCLR0, 1, GPIO_MAX_PIN);
}

uint32_t gpio_pull(uint32_t pin_number, uint32_t value)
{
	return gpio_call(pin_number, value, GPPUPPDN0, 2, GPIO_MAX_PIN);
}

uint32_t gpio_function(uint32_t pin_number, uint32_t value)
{
	return gpio_call(pin_number, value, GPFSEL0, 3, GPIO_MAX_PIN);
}

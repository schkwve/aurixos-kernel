/************************************************************************
 * FILENAME:         uart.h
 *
 * DESCRIPTION:
 *       UART-related Raspberry Pi 4 (aarch64) specific addresses
 *       definitions and function declarations.
 *
 * AUTHOR:     Jozef Nagy                  DATE:    30 Dec 2023
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

#ifndef AARCH64_UART_H
#define AARCH64_UART_H

#include <arch/io/gpio.h>
#include <sys/types.h>

#define AUX_MU_BAUD(baud) (((AUX_UART_CLOCK) / ((baud) * 8)) - 1)

#define AUX_BASE (PERIPHERAL_BASE + 0x215000)
#define AUX_IRQ (AUX_BASE)
#define AUX_ENABLES (AUX_BASE + 4)
#define AUX_MU_IO_REG (AUX_BASE + 64)
#define AUX_MU_IER_REG (AUX_BASE + 68)
#define AUX_MU_IIR_REG (AUX_BASE + 72)
#define AUX_MU_LCR_REG (AUX_BASE + 76)
#define AUX_MU_MCR_REG (AUX_BASE + 80)
#define AUX_MU_LSR_REG (AUX_BASE + 84)
#define AUX_MU_MSR_REG (AUX_BASE + 88)
#define AUX_MU_SCRATCH (AUX_BASE + 92)
#define AUX_MU_CNTL_REG (AUX_BASE + 96)
#define AUX_MU_STAT_REG (AUX_BASE + 100)
#define AUX_MU_BAUD_REG (AUX_BASE + 104)
#define AUX_UART_CLOCK (500000000)
#define UART_MAX_QUEUE (16 * 1024)

void uart_init(void);
void uart_update(void);

uint32_t uart_read_char(void);
void uart_write_char_blocking_actual(char c);
void uart_write_char_blocking(char c);

void __uart_load_output_fifo();
void __uart_drain_output_queue();

uint32_t __uart_is_ready_to_read(void);
uint32_t __uart_is_ready_to_write(void);
uint32_t __uart_is_out_queue_empty(void);

#endif /* AARCH64_UART_H */

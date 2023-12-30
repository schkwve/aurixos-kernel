#ifndef AARCH64_UART_H
#define AARCH64_UART_H

#include <arch/gpio.h>
#include <sys/types.h>

#define AUX_MU_BAUD(baud) (((AUX_UART_CLOCK) / ((baud) * 8)) - 1)

enum {
	AUX_BASE = PERIPHERAL_BASE + 0x215000,
	AUX_IRQ = AUX_BASE,
	AUX_ENABLES = AUX_BASE + 4,
	AUX_MU_IO_REG = AUX_BASE + 64,
	AUX_MU_IER_REG = AUX_BASE + 68,
	AUX_MU_IIR_REG = AUX_BASE + 72,
	AUX_MU_LCR_REG = AUX_BASE + 76,
	AUX_MU_MCR_REG = AUX_BASE + 80,
	AUX_MU_LSR_REG = AUX_BASE + 84,
	AUX_MU_MSR_REG = AUX_BASE + 88,
	AUX_MU_SCRATCH = AUX_BASE + 92,
	AUX_MU_CNTL_REG = AUX_BASE + 96,
	AUX_MU_STAT_REG = AUX_BASE + 100,
	AUX_MU_BAUD_REG = AUX_BASE + 104,
	AUX_UART_CLOCK = 500000000,
	UART_MAX_QUEUE = 16 * 1024
};

void uart_init(void);
void uart_update(void);

uint32_t uart_read_char(void);
void uart_write_char(char c);
void uart_write_string(char *buf);

uint32_t __uart_is_ready_to_read(void);
uint32_t __uart_is_ready_to_write(void);
uint32_t __uart_is_out_queue_empty(void);

#endif /* AARCH64_UART_H */
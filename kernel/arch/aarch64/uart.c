#include <arch/gpio.h>
#include <arch/uart.h>
#include <mm/mmio.h>
#include <sys/types.h>

#include <aurixos.h>

void uart_init(void)
{
	// enable UART1
	mmio_write(AUX_ENABLES, 1);
	mmio_write(AUX_MU_IER_REG, 0);
	mmio_write(AUX_MU_CNTL_REG, 0);

	mmio_write(AUX_MU_LCR_REG, 3);
	mmio_write(AUX_MU_MCR_REG, 0);
	mmio_write(AUX_MU_IER_REG, 0);

	// disable interrupts
	mmio_write(AUX_MU_IIR_REG, 0xC6);
	mmio_write(AUX_MU_BAUD_REG, AUX_MU_BAUD(CONFIG_UART_BAUD_RATE));

	gpio_use_as_alt5(14);
	gpio_use_as_alt5(15);

	// enable rx/tx
	mmio_write(AUX_MU_CNTL_REG, 3);
}

void uart_write_char(char c)
{
	while (!__uart_is_ready_to_write());
	mmio_write(AUX_MU_IO_REG, (uint32_t)c);
}

void uart_write_string(char *buf)
{
	while (*buf) {
		if (*buf == '\n') {
			uart_write_char('\r');
		}
		uart_write_char(*buf++);
	}
}

uint32_t __uart_is_ready_to_write()
{
	return (mmio_read(AUX_MU_LSR_REG) & 0x20);
}
#include <arch/io/gpio.h>
#include <arch/io/uart.h>
#include <mm/mmio.h>
#include <sys/types.h>

#include <aurixos.h>

uint8_t uart_output_queue[UART_MAX_QUEUE] = {0};
uint32_t uart_output_queue_write = 0;
uint32_t uart_output_queue_read = 0;

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

void uart_update()
{
	__uart_load_output_fifo();

	if (__uart_is_ready_to_read()) {
		uint8_t c = uart_read_char();
		if (c == '\r') {
			uart_write_char_blocking('\n');
		} else {
			uart_write_char_blocking(c);
		}
	}
}

uint32_t uart_read_char()
{
	while (!__uart_is_ready_to_read());
	return (uint32_t)mmio_read(AUX_MU_IO_REG);
}

void uart_write_char_blocking_actual(char c)
{
	while (!__uart_is_ready_to_write());
	mmio_write(AUX_MU_IO_REG, (uint32_t)c);
}

void uart_write_char_blocking(char c)
{
	uint32_t next = (uart_output_queue_write + 1) & (UART_MAX_QUEUE - 1);

	while (next == uart_output_queue_read) {
		__uart_load_output_fifo();
	}

	uart_output_queue[uart_output_queue_read] = c;
	uart_output_queue_write = next;
}

void uart_write_string(char *buf)
{
	while (*buf) {
		if (*buf == '\n') {
			uart_write_char_blocking('\r');
		}
		uart_write_char_blocking(*buf++);
	}
}

void __uart_load_output_fifo()
{
	while (!__uart_is_out_queue_empty() && __uart_is_ready_to_write()) {
		uart_write_char_blocking_actual(uart_output_queue[uart_output_queue_read]);
		uart_output_queue_read = (uart_output_queue_read + 1) & (UART_MAX_QUEUE - 1);
	}
}

void __uart_drain_output_queue()
{
	while (!__uart_is_out_queue_empty()) {
		__uart_load_output_fifo();
	}
}

uint32_t __uart_is_ready_to_read()
{
	return (mmio_read(AUX_MU_LSR_REG) & 0x01);
}
uint32_t __uart_is_ready_to_write()
{
	return (mmio_read(AUX_MU_LSR_REG) & 0x20);
}

uint32_t __uart_is_out_queue_empty()
{
	return uart_output_queue_read == uart_output_queue_write;
}

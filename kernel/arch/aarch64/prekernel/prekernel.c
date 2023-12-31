#include <arch/drivers/framebuffer.h>
#include <arch/io/uart.h>
#include <sys/types.h>

void prekernel_init(void)
{
	uart_init();
	framebuffer_init();

	while (1);
}

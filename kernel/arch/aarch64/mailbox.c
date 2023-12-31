#include <arch/mailbox.h>
#include <mm/mmio.h>
#include <sys/types.h>

volatile uint32_t __attribute__((aligned(16))) mailbox[36];

uint32_t mailbox_call(uint32_t c)
{
	// 28-bit address
	// 4-bit value
	uint32_t r = ((uint32_t)((long)&mailbox) &~ 0x0F) | (c & 0x0F);

	// wait until we can write
	while (mmio_read(MBOX_STATUS) & MBOX_FULL);

	// write to the mailbox
	mmio_write(MBOX_WRITE, r);

	while (1) {
		// wait until a reply to our message is received
		while (mmio_read(MBOX_STATUS) & MBOX_EMPTY);
		if (mmio_read(MBOX_READ) == r) {
			return mailbox[1] == MBOX_RESPONSE;
		}
	}
}

#include <mm/mmio.h>

#include <stddef.h>
#include <sys/types.h>

uint32_t mmio_read(uint64_t reg)
{
	return *(volatile uint32_t *)reg;
}

void mmio_write(uint64_t reg, uint32_t value)
{
	*(volatile uint32_t *)reg = value;
}
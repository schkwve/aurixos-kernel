#ifndef MMIO_H
#define MMIO_H

#include <sys/types.h>

uint32_t mmio_read(uint64_t reg);
void mmio_write(uint64_t reg, uint32_t value);

#endif /* MMIO_H */
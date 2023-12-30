#ifndef AARCH64_GPIO_H
#define AARCH64_GPIO_H

#include <sys/types.h>

enum {
	PERIPHERAL_BASE = 0xFE000000,
	GPFSEL0 = PERIPHERAL_BASE + 0x200000,
	GPSET0 = PERIPHERAL_BASE + 0x20001C,
	GPCLR0 = PERIPHERAL_BASE + 0x200028,
	GPPUPPDN0 = PERIPHERAL_BASE + 0x2000E4,
};

enum {
	GPIO_MAX_PIN = 52,
	GPIO_FUNCTION_ALT5 = 2,
};

enum {
	Pull_None = 0,
};

uint32_t gpio_call(uint32_t pin_number, uint32_t value, uint32_t base, uint32_t field_size, uint32_t field_max);

void gpio_use_as_alt5(uint32_t pin_number);

uint32_t gpio_set(uint32_t pin_number, uint32_t value);
uint32_t gpio_clear(uint32_t pin_number, uint32_t value);
uint32_t gpio_pull(uint32_t pin_number, uint32_t value);
uint32_t gpio_function(uint32_t pin_number, uint32_t value);

#endif /* AARCH64_GPIO_H */
#ifndef AARCH64_FRAMEBUFFER_H
#define AARCH64_FRAMEBUFFER_H

#include <sys/types.h>

void framebuffer_init();

void framebuffer_putpixel(int x, int y, uint8_t attr);

void framebuffer_draw_char(uint32_t c, int x, int y, uint32_t attr);
void framebuffer_draw_string(int x, int y, char *s, uint32_t attr);

#endif /* AARCH64_FRAMEBUFFER_H */

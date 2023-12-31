#include <arch/drivers/framebuffer.h>
#include <arch/mailbox.h>
#include <arch/terminal.h>

uint32_t width, height, pitch, isrgb;
uint8_t *fb;

void framebuffer_init()
{
	// message length
	mailbox[0] = 35 * 4;
	mailbox[1] = MBOX_REQUEST;

	// tag identifier
	mailbox[2] = MBOX_TAG_SETPHYWH;

	// value size
	mailbox[3] = 8;
	mailbox[4] = 0;

	// requested width and height
	mailbox[5] = 1920;
	mailbox[6] = 1080;

	// tag identifier
	mailbox[7] = MBOX_TAG_SETVIRTWH;

	// value size
	mailbox[8] = 8;
	mailbox[9] = 0;

	// requested width and height
	mailbox[10] = 1920;
	mailbox[11] = 1080;

	mailbox[12] = MBOX_TAG_SETVIRTOFF;
	mailbox[13] = 8;
	mailbox[14] = 8;
	
	// x
	mailbox[15] = 0;

	// y
	mailbox[16] = 0;

	mailbox[17] = MBOX_TAG_SETDEPTH;
	mailbox[18] = 4;
	mailbox[19] = 4;
	// bpp
	mailbox[20] = 32;

	mailbox[21] = MBOX_TAG_SETPXLORDR;
	mailbox[22] = 4;
	mailbox[23] = 4;

	// rgb
	mailbox[24] = 1;

	mailbox[25] = MBOX_TAG_GETFB;
	mailbox[26] = 8;
	mailbox[27] = 8;
	
	// framebuffer pointer
	mailbox[28] = 4096;

	// framebuffer size
	mailbox[29] = 0;

	mailbox[30] = MBOX_TAG_GETPITCH;
	mailbox[31] = 4;
	mailbox[32] = 4;

	// bytes per line
	mailbox[33] = 0;

	mailbox[34] = MBOX_TAG_LAST;

	if (mailbox_call(MBOX_CH_PROP) && mailbox[20] == 32 && mailbox[28] != 0) {
		mailbox[28] &= 0x3FFFFFFF;
		width = mailbox[10];
		height = mailbox[11];
		pitch = mailbox[33];
		isrgb = mailbox[24];
		fb = (uint8_t *)((long)mailbox[28]);
	}
}

void framebuffer_putpixel(int x, int y, uint8_t attr)
{
	int offset = (y * pitch) + (x * 4);
	*((uint32_t *)(fb + offset)) = vga_palette[attr & 0x0f];
}

void framebuffer_draw_char(uint32_t c, int x, int y, uint32_t attr)
{
	uint32_t *glyph = (uint32_t *)&terminal_font + (c < FONT_NUMGLYPHS ? c : 0) * FONT_BPG;

	for (int i = 0; i < FONT_HEIGHT; i++) {
		for (int j = 0; j < FONT_WIDTH; j++) {
			uint8_t mask = 1 << j;
			uint8_t column = (*glyph & mask) ? attr & 0x0f : (attr & 0xf0) >> 4;

			framebuffer_putpixel(x + j, y + i, column);
		}
		glyph += FONT_BPL;
	}
}

void framebuffer_draw_string(int x, int y, char *s, uint32_t attr)
{
	while (*s) {
		if (*s == '\r') {
			x = 0;
		} else if (*s == '\n') {
			x = 0;
			y += FONT_HEIGHT;
		} else {
			framebuffer_draw_char(*s, x, y, attr);
			x += FONT_WIDTH;
		}
		s++;
	}
}

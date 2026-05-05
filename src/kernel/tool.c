#include "kernel.h"

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(uint8_t *)s1 - *(uint8_t *)s2;
}

void *memset(void *b, int c, size_t len) {
    uint8_t *p = b;
    while (len--) *p++ = (uint8_t)c;
    return b;
}

void clear_screen() {
    volatile uint16_t* vga_buffer = (volatile uint16_t*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = (uint16_t)0x0F20;
    }
}

void draw_block(int x, int y, uint8_t color_code) {
	volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
	int index = y * 80 + x;
	vga_buffer[index] = (unsigned short)((color_code << 4) | color_code) << 8 | ' ';
}

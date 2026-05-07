#include "kernel.h"

// size_t strlen(const char *str) {
//     size_t len = 0;
//     while (str[len]) len++;
//     return len;
// }

// int strcmp(const char *s1, const char *s2) {
//     while (*s1 && (*s1 == *s2)) {
//         s1++;
//         s2++;
//     }
//     return *(uint8_t *)s1 - *(uint8_t *)s2;
// }

// void *memset(void *b, int c, size_t len) {
//     uint8_t *p = b;
//     while (len--) *p++ = (uint8_t)c;
//     return b;
// }

void put_char(int x, int y, char c, uint8_t color) {
    if (x >= 80 || y >= 25) return;

    volatile uint16_t* vga_buffer = (volatile uint16_t*)0xB8000;
    int index = y * 80 + x;

    vga_buffer[index] = (uint16_t)((color << 8) | c);
}

void put_str(int x, int y, const char *str, uint8_t color) {
    for (int i = 0; str[i] != '\0'; i++) {
        put_char(x + i, y, str[i], color);
    }
}

void clear_screen() {
    volatile uint16_t* vga_buffer = (volatile uint16_t*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = (uint16_t)0x0F20;
    }
}

// void draw_block(int x, int y, uint8_t color_code) {
// 	volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
// 	int index = y * 80 + x;
// 	vga_buffer[index] = (unsigned short)((color_code << 4) | color_code) << 8 | ' ';
// }

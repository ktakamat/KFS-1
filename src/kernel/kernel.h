#ifndef KERNEL_H
#define KERNEL_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;

// size_t strlen(const char *str);
// int strcmp(const char* s1, const char* s2);
// void *memset(void *b, int c, size_t len);
void put_char(int x, int y, char c, uint8_t color);
void put_str(int x, int y, const char *str, uint8_t color);

// void draw_block(int x, int y, uint8_t color_code);
void clear_screen();

void kputchar(char c);
void kprint(const char* str);
void kset_color(uint8_t color);
void update_cursor();
void kprint_int(int n);
void kprint_hex(uint32_t n);
void printk(const char *format, ...);
#endif

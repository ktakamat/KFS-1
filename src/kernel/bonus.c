#include "kernel.h"

// カーソルの位置をグローバル変数で管理
static int cursor_x = 0;
static int cursor_y = 0;
static uint8_t current_color = 0x0F; // デフォルトは黒背景に白文字

// I/Oポートを叩くための基本的な関数 (アセンブリの 'out' 命令)
static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

// ハードウェアのカーソル（チカチカする棒）を移動させる
void update_cursor() {
    uint16_t pos = cursor_y * 80 + cursor_x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

// スクロール処理
void scroll() {
    volatile uint16_t* vga_buffer = (volatile uint16_t*)0xB8000;
    if (cursor_y >= 25) {
        // 2行目以降を1行上にコピー
        for (int i = 0; i < 24 * 80; i++) {
            vga_buffer[i] = vga_buffer[i + 80];
        }
        // 最後の一行を空白で埋める
        for (int i = 24 * 80; i < 25 * 80; i++) {
            vga_buffer[i] = (uint16_t)((current_color << 8) | ' ');
        }
        cursor_y = 24;
    }
}

void kputchar(char c) {
    volatile uint16_t* vga_buffer = (volatile uint16_t*)0xB8000;

    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        int index = cursor_y * 80 + cursor_x;
        vga_buffer[index] = (uint16_t)((current_color << 8) | c);
        cursor_x++;
    }

    // 右端に到達したら改行
    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }

    scroll();         // 必要なら画面を上げる
    update_cursor();  // ハードウェアカーソルを動かす
}

// 文字色を変更する関数（Color Support）
void kset_color(uint8_t color) {
    current_color = color;
}

void kprint(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        kputchar(str[i]);
    }
}

// 数値を文字列に変換して表示する
void kprint_int(int n) {
    if (n == 0) {
        kputchar('0');
        return;
    }
    if (n < 0) {
        kputchar('-');
        n = -n;
    }
    char buf[12];
    int i = 10;
    buf[11] = '\0';
    while (n > 0) {
        buf[i--] = (n % 10) + '0';
        n /= 10;
    }
    kprint(&buf[i + 1]);
}

// 16進数を表示する（デバッグで非常によく使います）
void kprint_hex(uint32_t n) {
    char *hex_chars = "0123456789ABCDEF";
    kprint("0x");
    for (int i = 28; i >= 0; i -= 4) {
        kputchar(hex_chars[(n >> i) & 0xF]);
    }
}

void printk(const char *format, ...) {
    // 最初の引数（format）のアドレスを取得し、その次(4バイト先)を指すようにする
    uint32_t *args = (uint32_t *)&format;
    args++; // これで args は「...」の最初の引数を指すようになる

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++; // '%' の次の文字を見る
            if (format[i] == 'd') {
                kprint_int((int)*args++);
            } else if (format[i] == 'x') {
                kprint_hex((uint32_t)*args++);
            } else if (format[i] == 's') {
                kprint((char *)*args++);
            } else if (format[i] == 'c') {
                kputchar((char)*args++);
            } else {
                kputchar('%');
                kputchar(format[i]);
            }
        } else {
            kputchar(format[i]);
        }
    }
}
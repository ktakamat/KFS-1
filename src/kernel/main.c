#include "kernel.h"

// void kernel_main(void) {
//     clear_screen();

//     uint8_t cyan = 11;

//     for (int y = 5; y <= 7; y++) put_char(10, y, ' ', cyan);
//     put_char(11, 7, ' ', cyan); 
//     put_char(12, 7, ' ', cyan);
//     for (int y = 5; y <= 9; y++) put_char(13, y, ' ', cyan);

//     put_char(17, 5, ' ', cyan); put_char(18, 5, ' ', cyan); put_char(19, 5, ' ', cyan);
//     put_char(19, 6, ' ', cyan);
//     put_char(17, 7, ' ', cyan); put_char(18, 7, ' ', cyan); put_char(19, 7, ' ', cyan);
//     put_char(17, 8, ' ', cyan);
//     put_char(17, 9, ' ', cyan); put_char(18, 9, ' ', cyan); put_char(19, 9, ' ', cyan);

//     // if (strcmp("42", "42") == 0) {
//     //     // 成功時の処理など
//     // }
// }

void kernel_main(void) {
    clear_screen();
    // mandatory
    uint8_t color = 0x0B;
    put_str(0, 0, "42", color);
    
    // Bonus
    kset_color(0x0B); 
    kprint("42\n"); 

    kset_color(0x0E); // 黄色
    kprint("--- KFS_1 Bonus Demo ---\n");
    
    kset_color(0x0F); // 白
    kprint("Cursor is moving: OK\n");
    
    kprint("Testing hex output: ");
    kprint_hex(0xDEADBEEF);
    kputchar('\n');
    
    kprint("Testing scroll:\n");
    for(int i = 0; i < 30; i++) {
        kprint("Line ");
        kprint_int(i);
        kputchar('\n');
    }
}
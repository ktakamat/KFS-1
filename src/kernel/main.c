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

    uint8_t color = 0x0B;
    put_str(0, 0, "42", color);
}

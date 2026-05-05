#include "kernel.h"

void kernel_main(void) {
    clear_screen();

    uint8_t cyan = 11;

    for (int y = 5; y <= 7; y++) draw_block(10, y, cyan);
    draw_block(11, 7, cyan); 
    draw_block(12, 7, cyan);
    for (int y = 5; y <= 9; y++) draw_block(13, y, cyan);

    draw_block(17, 5, cyan); draw_block(18, 5, cyan); draw_block(19, 5, cyan);
    draw_block(19, 6, cyan);
    draw_block(17, 7, cyan); draw_block(18, 7, cyan); draw_block(19, 7, cyan);
    draw_block(17, 8, cyan);
    draw_block(17, 9, cyan); draw_block(18, 9, cyan); draw_block(19, 9, cyan);
    
    // if (strcmp("42", "42") == 0) {
    //     // 成功時の処理など
    // }
}
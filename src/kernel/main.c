void draw_block(int x, int y, unsigned char color_code) {
	volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
	int index = y * 80 + x;
	vga_buffer[index] = (unsigned short)((color_code << 4) | color_code) << 8 | ' ';
}

void kernel_main(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = (0x00 << 8) | ' ';
    }

    unsigned char cyan = 11;

    for (int y = 5; y <= 7; y++) draw_block(10, y, cyan);
    draw_block(11, 7, cyan); draw_block(12, 7, cyan);
    for (int y = 5; y <= 9; y++) draw_block(13, y, cyan);

    draw_block(17, 5, cyan); draw_block(18, 5, cyan); draw_block(19, 5, cyan);
    draw_block(19, 6, cyan);
    draw_block(17, 7, cyan); draw_block(18, 7, cyan); draw_block(19, 7, cyan);
    draw_block(17, 8, cyan);
    draw_block(17, 9, cyan); draw_block(18, 9, cyan); draw_block(19, 9, cyan);
}

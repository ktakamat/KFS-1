void kernel_main(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;

    unsigned short color = 0x0F00;

    vga_buffer[0] = color | '4';

    vga_buffer[1] = color | '2';
}
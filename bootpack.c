#include "bootpack.h"
void HariMain(void){
		BOOTINFO *bootinfo=(BOOTINFO *)ADR_BOOTINFO;
		/*GDT IDT 中断初始化*/
		init_gdtidt();
		init_pic();
		io_sti(); 

		/* 绘图 */
		init_palette();
		init_screen(bootinfo->vram,bootinfo->screen_x,bootinfo->screen_y);
		char *s;
		sprintf(s,"screen_x=%d",bootinfo->screen_x);
		print_string(bootinfo->vram,bootinfo->screen_x,5,5,COL8_FF00FF,s);
		char cursor[16][16];
		int cursor_x,cursor_y;
		cursor_x=160;
		cursor_y=100;
		init_mouse_cursor(cursor,COL8_008484);
		draw_picture(bootinfo->vram,bootinfo->screen_x,16,16,cursor_x,cursor_y,cursor,16);
		
		/* 中断 */
		io_out8(PIC0_IMR, 0xf9); /* 开放PIC1和键盘中断(11111001) */
		io_out8(PIC1_IMR, 0xef); /* 开放鼠标中断(11101111) */


		/* halt */
		for(;;)io_hlt();
		return;
}


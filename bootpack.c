#include "bootpack.h"
void HariMain(void){
		BOOTINFO *bootinfo=(BOOTINFO *)ADR_BOOTINFO;
		init_palette();
		init_screen(bootinfo->vram,bootinfo->screen_x,bootinfo->screen_y);
		char *s;
		sprintf(s,"screen_x=%d",bootinfo->screen_x);
		printString(bootinfo->vram,bootinfo->screen_x,5,5,COL8_FF00FF,s);
		char cursor[16][16];
		int cursor_x,cursor_y;
		cursor_x=160;
		cursor_y=100;
		init_mouse_cursor(cursor,COL8_008484);
		drawPicture(bootinfo->vram,bootinfo->screen_x,16,16,cursor_x,cursor_y,cursor,16);
		for(;;)io_hlt();
		return;
}


#define COL8_000000		0		/*  0:黑 */
#define COL8_FF0000		1       /*  1:梁红 */
#define COL8_00FF00		2       /*  2:亮绿 */
#define COL8_FFFF00		3       /*  3:亮黄 */
#define COL8_0000FF		4       /*  4:亮蓝 */
#define COL8_FF00FF		5       /*  5:亮紫 */
#define COL8_00FFFF		6       /*  6:浅亮蓝 */
#define COL8_FFFFFF		7       /*  7:白 */
#define COL8_C6C6C6		8       /*  8:亮灰 */
#define COL8_840000		9       /*  9:暗红 */
#define COL8_008400		10      /* 10:暗绿 */
#define COL8_848400		11      /* 11:暗黄 */
#define COL8_000084		12      /* 12:暗青 */
#define COL8_840084		13      /* 13:暗紫 */
#define COL8_008484		14      /* 14:浅暗蓝 */
#define COL8_848484		15      /* 15:暗灰 */
/*
; BOOT_INFO相关
CYLS	EQU		0x0ff0			; 引导扇区设置
LEDS	EQU		0x0ff1
VMODE	EQU		0x0ff2			; 关于颜色的信息
SCRNX	EQU		0x0ff4			; 分辨率X
SCRNY	EQU		0x0ff6			; 分辨率Y
VRAM	EQU		0x0ff8			; 图像缓冲区的起始地址
*/
typedef struct BOOTINFO{
	char cyls,leds,vmode,reserve;
	short screen_x,screen_y;
	char *vram;
}BOOTINFO;
void io_hlt(void);//hlt----halt 停止
void io_cli(void); //cli-----clear interrupt flag  中断标志置0
void io_out8(int port, int data);
void init_palette(void);
void init_screen(char *vram,short xsize,short ysize);
void set_palette(int start,int end,unsigned char *rgb);
int io_load_eflags(void);//eflags ---- extend flags 保存中断标志
void io_store_eflags(int eflags);//加载中断标志
void printFont(char *vram,int xsize,int x,int y,char c,char *font);//绘制字体,8*16像素阵绘制  font是要绘制的矩阵
void printString(char *vram,int xsize,int x,int y,char c,unsigned char *s);//输出字符串
void boxfill(unsigned char *vram, int xsize,unsigned char c,int x0,int y0,int x1,int y1);//矩形绘制
void drawPicture(char *vram,int vxsize,int pic_x_size,int pic_y_size,int pic_x,int pic_y,char *pic_addr,int bxsize);
void init_mouse_cursor(char *mouse, char bc);
void HariMain(void){
		BOOTINFO *bootinfo=(BOOTINFO *)0x0ff0;
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
}
void init_palette(void){
	
	//static char 相当于DB
	static unsigned char table_rgb[16*3]={
		0x00, 0x00, 0x00,	
		0xff, 0x00, 0x00,	
		0x00, 0xff, 0x00,	
		0xff, 0xff, 0x00,	
		0x00, 0x00, 0xff,	
		0xff, 0x00, 0xff,	
		0x00, 0xff, 0xff,	
		0xff, 0xff, 0xff,	
		0xc6, 0xc6, 0xc6,	
		0x84, 0x00, 0x00,	
		0x00, 0x84, 0x00,	
		0x84, 0x84, 0x00,	
		0x00, 0x00, 0x84,	
		0x84, 0x00, 0x84,	
		0x00, 0x84, 0x84,	
		0x84, 0x84, 0x84	
	};
	set_palette(0,15,table_rgb);
	return;
}
void init_screen(char *vram,short xsize,short ysize){
	
	
	boxfill(vram, xsize, COL8_008484,  0,         0,          xsize -  1, ysize - 29);
	boxfill(vram, xsize, COL8_C6C6C6,  0,         ysize - 28, xsize -  1, ysize - 28);
	boxfill(vram, xsize, COL8_FFFFFF,  0,         ysize - 27, xsize -  1, ysize - 27);
	boxfill(vram, xsize, COL8_C6C6C6,  0,         ysize - 26, xsize -  1, ysize -  1);

	boxfill(vram, xsize, COL8_FFFFFF,  3,         ysize - 24, 59,         ysize - 24);
	boxfill(vram, xsize, COL8_FFFFFF,  2,         ysize - 24,  2,         ysize -  4);
	boxfill(vram, xsize, COL8_848484,  3,         ysize -  4, 59,         ysize -  4);
	boxfill(vram, xsize, COL8_848484, 59,         ysize - 23, 59,         ysize -  5);
	boxfill(vram, xsize, COL8_000000,  2,         ysize -  3, 59,         ysize -  3);
	boxfill(vram, xsize, COL8_000000, 60,         ysize - 24, 60,         ysize -  3);

	boxfill(vram, xsize, COL8_848484, xsize - 47, ysize - 24, xsize -  4, ysize - 24);
	boxfill(vram, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize -  4);
	boxfill(vram, xsize, COL8_FFFFFF, xsize - 47, ysize -  3, xsize -  4, ysize -  3);
	boxfill(vram, xsize, COL8_FFFFFF, xsize -  3, ysize - 24, xsize -  3, ysize -  3);

}	
void set_palette(int start,int end,unsigned char *rgb){
		int i,eflags;
		eflags=io_load_eflags();
		io_cli();
		io_out8(0x03c8,start);
		for(i=start;i<=end;i++){
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;					
		}
		io_store_eflags(eflags);
		return;
	}
void boxfill(unsigned char *vram, int xsize,unsigned char c,int x0,int y0,int x1,int y1){
	int x,y;
	for(y=y0;y<=y1;y++){
		for(x=x0;x<=x1;x++)
			*(vram+x+y*xsize)=c;
	}
	return;
}
void printFont(char *vram,int xsize,int x,int y,char c,char *font){
	int i,j;
	unsigned char k[8]={
		0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01	
	};
	for(i=0;i<=15;i++){
		for(j=0;j<=7;j++){
			if((font[i]&(k[j]))!=0){
				*(vram+x+(i+y)*xsize+j)=c;
			}
		}	
	}
		
	return;
}
void printString(char *vram,int xsize,int x,int y,char c,unsigned char *s){
	
	extern char hankaku[4096];
	 for(;*s!=0x00;s++){
		printFont(vram,xsize,x,y,c,hankaku+(*s)*16);
		x=x+8;
	} 
	/* printFont(vram,xsize,x,y,c,hankaku+(*s)*16);
	printFont(vram,xsize,x+8,y,c,hankaku+(*s+1)*16);
	printFont(vram,xsize,x+16,y,c,hankaku+(*s+2)*16);
	printFont(vram,xsize,x+24,y,c,hankaku+(*s+3)*16); */
	return;
	
}	
void drawPicture(char *vram,int vxsize,int pic_x_size,int pic_y_size,int pic_x,int pic_y,char *pic_addr,int bxsize){	
	int x,y;
	for(y=0;y<pic_y_size;y++){
		
		for(x=0;x<pic_x_size;x++)
			*(vram+(y+pic_y)*vxsize+pic_x+x)=*(pic_addr+y*bxsize+x);
	
		
	}
	return;
}
void init_mouse_cursor(char *mouse, char bc){
	static char cursor[16][16] = {
		"**************..",
		"*OOOOOOOOOOO*...",
		"*OOOOOOOOOO*....",
		"*OOOOOOOOO*.....",
		"*OOOOOOOO*......",
		"*OOOOOOO*.......",
		"*OOOOOOO*.......",
		"*OOOOOOOO*......",
		"*OOOO**OOO*.....",
		"*OOO*..*OOO*....",
		"*OO*....*OOO*...",
		"*O*......*OOO*..",
		"**........*OOO*.",
		"*..........*OOO*",
		"............*OO*",
		".............***"
	};
	int x, y;

	for (y = 0; y < 16; y++) {
		for (x = 0; x < 16; x++) {
			if (cursor[y][x] == '*') {
				mouse[y * 16 + x] = COL8_000000;
			}
			if (cursor[y][x] == 'O') {
				mouse[y * 16 + x] = COL8_FFFFFF;
			}
			if (cursor[y][x] == '.') {
				mouse[y * 16 + x] = bc;
			}
		}
	}
	return;
}
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
void print_font(char *vram,int xsize,int x,int y,char c,char *font);//8*16像素阵绘制  font是要绘制的矩阵
void boxfill8(unsigned char *vram, int xsize,unsigned char c,int x0,int y0,int x1,int y1);//矩形绘制
void HariMain(void){
		BOOTINFO *bootinfo=(BOOTINFO *)0x0ff0;
		init_palette();
		init_screen(bootinfo->vram,bootinfo->screen_x,bootinfo->screen_y);
		static char font_A[16] = {
			0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
			0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00
			};
		print_font(bootinfo->vram,bootinfo->screen_x,5,5,COL8_FF00FF,font_A);
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
	
	
	boxfill8(vram, xsize, COL8_008484,  0,         0,          xsize -  1, ysize - 29);
	boxfill8(vram, xsize, COL8_C6C6C6,  0,         ysize - 28, xsize -  1, ysize - 28);
	boxfill8(vram, xsize, COL8_FFFFFF,  0,         ysize - 27, xsize -  1, ysize - 27);
	boxfill8(vram, xsize, COL8_C6C6C6,  0,         ysize - 26, xsize -  1, ysize -  1);

	boxfill8(vram, xsize, COL8_FFFFFF,  3,         ysize - 24, 59,         ysize - 24);
	boxfill8(vram, xsize, COL8_FFFFFF,  2,         ysize - 24,  2,         ysize -  4);
	boxfill8(vram, xsize, COL8_848484,  3,         ysize -  4, 59,         ysize -  4);
	boxfill8(vram, xsize, COL8_848484, 59,         ysize - 23, 59,         ysize -  5);
	boxfill8(vram, xsize, COL8_000000,  2,         ysize -  3, 59,         ysize -  3);
	boxfill8(vram, xsize, COL8_000000, 60,         ysize - 24, 60,         ysize -  3);

	boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 24, xsize -  4, ysize - 24);
	boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize -  4);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize - 47, ysize -  3, xsize -  4, ysize -  3);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize -  3, ysize - 24, xsize -  3, ysize -  3);

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
void boxfill8(unsigned char *vram, int xsize,unsigned char c,int x0,int y0,int x1,int y1){
	int x,y;
	for(y=y0;y<=y1;y++){
		for(x=x0;x<=x1;x++)
			*(vram+x+y*xsize)=c;
	}
	return;
}
void print_font(char *vram,int xsize,int x,int y,char c,char *font){
	int i,j;
	for(i=0;i<=15;i++){
		unsigned char *k;
		*k=0x80;
		for(j=0;j<=7;j++){
			if((font[i]&(*k))!=0){
				*(vram+x+(i+y)*xsize+j)=c;
			}
			*k=*k>>1;
		}
		
	}
		
	return;
}
	
	
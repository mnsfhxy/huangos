
/*
; BOOT_INFO相关
CYLS	EQU		0x0ff0			; 引导扇区设置
LEDS	EQU		0x0ff1
VMODE	EQU		0x0ff2			; 关于颜色的信息
SCRNX	EQU		0x0ff4			; 分辨率X
SCRNY	EQU		0x0ff6			; 分辨率Y
VRAM	EQU		0x0ff8			; 图像缓冲区的起始地址
*/

#define ADR_BOOTINFO	0x00000ff0
typedef struct BOOTINFO{
	char cyls,leds,vmode,reserve;
	short screen_x,screen_y;
	char *vram;
}BOOTINFO;


/* naskfunc.nas */

void io_sti(void);
void io_hlt(void);//hlt----halt 停止
void io_cli(void); //cli-----clear interrupt flag  中断标志置0
void io_out8(int port, int data);
int io_load_eflags(void);//eflags ---- extend flags 保存中断标志
void io_store_eflags(int eflags);//加载中断标志
void load_gdtr(int limit, int addr);
void load_idtr(int limit, int addr);
void asm_inthandler21(void);
void asm_inthandler27(void);
void asm_inthandler2c(void);




/* graphic.c*/
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
void init_palette(void);
void init_screen(char *vram,short xsize,short ysize);
void set_palette(int start,int end,unsigned char *rgb);
void print_font(char *vram,int xsize,int x,int y,char c,char *font);//绘制字体,8*16像素阵绘制  font是要绘制的矩阵
void print_string(char *vram,int xsize,int x,int y,char c,unsigned char *s);//输出字符串
void boxfill(unsigned char *vram, int xsize,unsigned char c,int x0,int y0,int x1,int y1);//矩形绘制
void draw_picture(char *vram,int vxsize,int pic_x_size,int pic_y_size,int pic_x,int pic_y,char *pic_addr,int bxsize);
void init_mouse_cursor(char *mouse, char bc);



/* dsctbl.c */
struct SEGMENT_DESCRIPTOR {
	short limit_low, base_low;
	char base_mid, access_right;
	char limit_high, base_high;
};
struct GATE_DESCRIPTOR {
	short offset_low, selector;
	char dw_count, access_right;
	short offset_high;
};
void init_gdtidt(void);
void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar);
void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar);
#define ADR_IDT			0x0026f800
#define LIMIT_IDT		0x000007ff
#define ADR_GDT			0x00270000
#define LIMIT_GDT		0x0000ffff
#define ADR_BOTPAK		0x00280000
#define LIMIT_BOTPAK	0x0007ffff
#define AR_DATA32_RW	0x4092
#define AR_CODE32_ER	0x409a
#define AR_INTGATE32	0x008e



/* int.c */
void init_pic(void);
void inthandler21(int *esp);
void inthandler27(int *esp);
void inthandler2c(int *esp);
#define PIC0_ICW1		0x0020
#define PIC0_OCW2		0x0020
#define PIC0_IMR		0x0021
#define PIC0_ICW2		0x0021
#define PIC0_ICW3		0x0021
#define PIC0_ICW4		0x0021
#define PIC1_ICW1		0x00a0
#define PIC1_OCW2		0x00a0
#define PIC1_IMR		0x00a1
#define PIC1_ICW2		0x00a1
#define PIC1_ICW3		0x00a1
#define PIC1_ICW4		0x00a1
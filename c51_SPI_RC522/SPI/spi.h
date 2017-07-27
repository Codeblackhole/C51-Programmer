#ifndef _SPI_H_
#define _SPI_H_

#include <reg52.h>

sbit RST = P0^4;		//硬复位
sbit SDA = P0^0;		//片选
sbit SCLK = P0^1;		//时钟线
sbit MISO = P0^2;		//数据输出
sbit MISI = P0^3;		//数据输入

 typedef unsigned char u8;
 typedef unsigned short u16;
 typedef unsigned int u32;

extern void delay_ms(u32 n);
extern void Write_Byte(u8 byte);
extern u8 Read_Byte(void);


#endif




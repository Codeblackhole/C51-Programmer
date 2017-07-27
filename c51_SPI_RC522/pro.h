#ifndef _PRO_H_
#define _PRO_H_

#include <reg52.h>
#include "rc522.h"

sbit LED1 = P1^0;
sbit LED2 = P1^1;

u8 CT[2];		//卡类型
u8 SN[4]; 		//存放卡号
u8 code RFID[16];	//存放读出的 一块的数据	16字节
u8 *id;			
u8 status;		//用于存储IC卡现在的状态
u8 i,j;

//默认密码
u8 code password[6]={0xff,0xff,0xff,0xff,0xff,0xff};
//要写入的数据
u8 code RFID1[16]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};	//0~F
u8 code RFID2[16]={0x01,0x03,0x00,0x03,0x04,0x05,0x08,0x08,0x03,0x05,0x07,0x0a,0x0b,0x0c,0x0d,0x0e}; //电话号码 13034588357abcde
//白卡内置EEPROM地址
const u8 code ADDR[64] = {
0X00,	0X01,	0X02,	0X03,	//扇区0的四块
0X04,	0X05,	0X06,	0X07,	//扇区1的四块
0X08,	0X09,	0X0A,	0X0B,	//...
0X0C,	0X0D,	0X0E,	0X0F,
0X10,	0X11,	0X12,	0X13,
0X14,	0X15,	0X16,	0X17,	
0X18,	0X19,	0X1A,	0X1B,	
0X1C,	0X1D,	0X1E,	0X1F,
0X20,	0X21,	0X21,	0X22,
0X22,	0X23,	0X23,	0X24,
0X24,	0X25,	0X2A,	0X2B,	
0X2C,	0X2D,	0X2E,	0X2F,
0X30,	0X31,	0X32,	0X33,	
0X34,	0X35,	0X36,	0X37,	
0X38,	0X39,	0X3A,	0X3B,	//...
0X3C,	0X3D,	0X3E,	0X3F,	//扇区15
};
u8 WriteData(u8 addr,u8 *pKey,u8 *pSnr,u8 *datain);
u8 ReadData(u8 addr, u8 *pKey, u8 *pSnr,u8 *dataout);
void cardWorking(unsigned char addr, unsigned char *password, unsigned char *pData, unsigned char mode);
#endif



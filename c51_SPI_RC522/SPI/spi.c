#include "spi.h"

void delay_ms(unsigned int n)
{
    unsigned char a,b,i;
	for(i=n; i>0; i--)
	{
		for(b=199;b>0;b--)
		{
			for(a=1;a>0;a--);
		}
	}
}

void Write_Byte(u8 byte)
{
	static u8 i=0;
	
	SDA = 1;
	delay_ms(10);
	SCLK = 1;
	delay_ms(10);
	SDA = 0;
	
	for(i=0; i<8; i++)
	{
		SCLK = 0;
		if(0x80 & byte)
			MISI = 1;
		else 
			MISI = 0;
		SCLK = 1;
		byte <<= 1;
	}
	SCLK = 0;
	SDA = 1;
}

u8 Read_Byte(void)
{
	static u8 i=0;
	u8 dat;
	SDA = 0;
	for(i=0; i<8; i++)
	{
		SDA = 0;
		dat <<= 1;
		SDA = 1;
		if(MISO == 1)
			dat |= 0x01;
		else 
			dat &= ~0x01;
	}
	return dat;
}


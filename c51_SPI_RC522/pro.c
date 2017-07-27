#include "pro.h"

#define ON 0
#define OFF 1

#define READ 0
#define WRITE 1

void main(void)
{
	LED1 = LED2 = ON;
	init_rc522();
	LED1 = LED2 = OFF;
	while(1)
	{
		cardWorking(ADDR[0], password, RFID, READ);
	}
}
void cardWorking(unsigned char addr, unsigned char *password, unsigned char *pData, unsigned char mode){
	
	u8 status=0xff;
	status = PcdRequest(PICC_REQALL,CT);
	if(status == MI_OK)
	{
		LED1 = ON;
		status = MI_ERR;
		status = PcdAnticoll(SN);
		if(status == MI_OK)
		{
			LED2 = ON;
			status = MI_ERR;
			status = PcdSelect(SN);
		   if(status == MI_OK)
			{
				status = MI_ERR;
				status=PcdAuthState(KEY_A,addr,password,SN);
				if(status == MI_OK)
				{
					if(mode)
					{
						PcdWrite(addr,pData);
					}else
					{
						PcdRead(addr,pData);
					}
				}
			}
		}
	}
}
/*
* 函数功能：读出指定地址位置的数据
* 函数参数：addr :地址
*			pKey :密码
*			pSnr :卡序列号
*		 dataout ：读出的一块大小的数据 16字节*/
u8 ReadData(u8 addr, u8 *pKey, u8 *pSnr,u8 *dataout)
{
	u8 status,k;
	status=0x02;
	k=5;
	do
    {
		status=PcdAuthState(KEY_A,addr,pKey,pSnr);
		k--;					      
    }while(status!=MI_OK && k>0);

	status=0x02;
	k=5;
	do
    {
		status=PcdRead(addr,dataout);
		k--;						      
    }while(status!=MI_OK && k>0);
	return status;
}
/*
* 函数功能：向卡片写入数据
* 函数参数：addr :地址
*			pKey :密码
*			pSnr :卡序列号
*		  datain ：写入的一块大小的数据 16字节*/
u8 WriteData(u8 addr,u8 *pKey,u8 *pSnr,u8 *datain)
{
	u8 status,k;
	status=0x02;
	k=5;
	do
    {
		status=PcdAuthState(KEY_A,addr,pKey,pSnr);
		k--;
    }while(status!=MI_OK && k>0);

	status=0x02;
	k=5;
	do
    {
		status=PcdWrite(addr,datain);
		k--;								      
    }while(status!=MI_OK && k>0);
	return status;
}



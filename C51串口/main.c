/*
 *	晶振频率：11.0592MHz
 *
 *
 */
 
#include <reg51.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define BAUD_9600		0XFA
#define BAUD_4800		0XF4

#define    MI_OK                         0
#define    MI_NOTAGERR                   (-1)
#define    MI_ERR                        (-2)
#define    STATUS_SUCCESS                0
#define    STATUS_IO_TIMEOUT             1

char *tab = "935467";

char buf_string[16];  //接收数据缓冲区

void my_putchar(char ch)
{
    SBUF = ch;
    while(!TI);
		TI=0;
}

//waitTime:10000
short my_getchar(unsigned char *ch, unsigned int WaitTime)
{
    unsigned int j;
    j=0;
    while(!RI)
	{
		j++;
		if(j>=WaitTime)          //avoid endless loop
			break;
	}
	if(j<WaitTime)
	{
		*ch = SBUF;
		RI=0;
		return STATUS_SUCCESS;
	}
	else
	    return STATUS_IO_TIMEOUT;
}

void delay(unsigned int i){
	unsigned int k;
	for( ; i>0; i--)
		for(k=110; k>0; k--);
}

void Init_USART()    
{  
    SCON=0x50;  
    TMOD|=0x20;  
    TMOD&=~0x10;  
    TH1=BAUD_9600;   
    TL1=BAUD_9600;    
    PCON|=0x80; 
    TR1=1;  
    TI=0;  
    RI=0;  
    ES=1;  
} 

void PutString(unsigned char *TXStr)    
{                  
    ES=0;       
     while(*TXStr!=0)   
    {                        
        SBUF=*TXStr;  
        while(TI==0);  
        TI=0;      
        TXStr++;  
    }  
    ES=1;   
}     

bit ReceiveString()      
{  
    char * RecStr=buf_string;  
    char num=0;  
    unsigned char count=0;  
    loop:      
    *RecStr=SBUF;  
    count=0;  
    RI=0;      
    if(num<14) 
    {  
        num++;  
        RecStr++;      
        while(!RI)  
        {  
            count++;  
            if(count>130)return 0; 
        }  
        goto loop;  
    }  
    return 1;  
}  

void main(void)
{
	Init_USART();
	while(1)
	{
		PutString(tab);
		delay(500);
	}
}
//串口中断服务函数
//void usart_Config() interrupt 4
//{
//	unsigned char byte;
//	
//	byte = SBUF;
//	RI = 0;
//	SBUF = byte;
//	while(!TI);
//	TI = 0;
//}



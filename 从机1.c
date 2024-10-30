#include<reg51.h>

#define uchar unsigned char 
#define uint unsigned int 

/*****************ȫ�ֱ�������****************/
uchar keydata;
uchar senddata;
uchar receivedata;
uchar beep;
/*****************���ڳ�ʼ������*****************/
void UART_init(void)
{
	TMOD=0x21;
	TL1=0xfd;
	TH1=0xfd;
	TCON=0x50;
	SCON=0x50;
	PCON=0x00;
}
/**********************��ʱ����************************/
void delay(uint num)
{
	while(num--) ;
}
/*********************���̶�ȡ*********************/
void key(void)
{
	P1=0xff;
	if(P1!=0xff)
	{
		delay(100);
		if(P1!=0xff)
		{
			switch(P1)
			{
				case 0xfe:keydata=0x01;break;
				case 0xfd:keydata=0x02;break;
				case 0xfb:keydata=0x03;break;
				case 0xf7:keydata=0x04;break;
				case 0xef:keydata=0x05;break;
				case 0xdf:keydata=0x06;break;
				case 0xbf:keydata=0x07;break;
				case 0x7f:keydata=0x08;break;
				default: break;
			}
			beep=~P1;
			while(P1!=0xff);
		}
		else keydata=0;
	}
	else keydata=0;
}
/*******************���ͳ���*******************/
void send(void)
{
	senddata=0x10|keydata;//���Ϸ����0x10
	SBUF=senddata;
	while(TI==0);
	TI=0;
}
/******************���ܳ���*******************/
void receive()
{
	while(RI==0);
	RI=0;
	P2=beep;
	delay(30000);
	P2=0x00;
}
void main(void)
{
	UART_init();
	P2=0x00;
	for(;;)
	{
	  	key();
		if(keydata!=0)
		{
			send();
			receive();
			keydata=0;
		}	
	}
} 

#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char
#define At24c02ADDR 0XA0
#define	I2cRead 1
#define	I2cWrite 0

sbit DU = P2^6;
sbit WE = P2^7;
sbit SCL = P2^1;
sbit SDA = P2^0;
uchar num;
bit AckFlag;


uchar code SMGduan[]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,};

uchar code SMGwei[] = {0xfe, 0xfd, 0xfb};

void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--); 		
} 

void display(uchar i)
{
	static uchar wei; 		
	P0 = 0XFF;
	WE = 1;
	P0 = SMGwei[wei];
	WE = 0;
	switch(wei)
	{
		case 0: DU = 1; P0 = SMGduan[i / 100]; DU = 0; break;
		case 1: DU = 1; P0 = SMGduan[i % 100 / 10]; DU = 0; break;	
		case 2: DU = 1; P0 = SMGduan[i % 10]; DU = 0; break;		
	}
	wei++;
	if(wei == 3)
		wei = 0;
}

void timer0Init()
{
	EA = 1;	
	ET0 = 1;
	TR0 = 1;
	TMOD |= 0X01;
	TH0 = 0xED;
	TL0 = 0xFF;
}

void delay5us()
{
	_nop_();
}

void I2cStart()
{
	SCL = 1; 
	SDA = 1;
	delay5us();
	SDA = 0;
	delay5us();
}

void I2cStop()
{
	SCL = 0;
	SDA = 0;
	SCL = 1;
	delay5us();
	SDA = 1;
	delay5us();
}

bit ReadACK()
{
	SCL = 0;
	SCL = 1;
	delay5us();
	if(SDA)
	{
		SCL = 0;
		return(1);
	}
	else
	{
		SCL = 0;
		return(0);
	}
}


void SendACK(bit i)
{
	SCL = 0;
	if(i)	
		SDA = 1;
	else
		SDA = 0;
	SCL = 1;
	delay5us();
	SCL = 0;
	SDA = 1;
}

void I2cSendByte(uchar DAT)
{
	uchar i; 
	for(i=0; i<8; i++)
	{
		SCL = 0;
		if(DAT & 0x80)
			SDA = 1;
		else
			SDA = 0;
		SCL = 1;
		DAT <<= 1;
	}
	SCL = 0;
	SDA = 1;
}

void At24c02Write(uchar ADDR, DAT)
{
	I2cStart();
	I2cSendByte(At24c02ADDR + I2cWrite);
	if(ReadACK())
		AckFlag = 1;
	else
		AckFlag = 0;
	I2cSendByte(ADDR);
	if(ReadACK())
		AckFlag = 1;
	else
		AckFlag = 0;
	I2cSendByte(DAT);
	if(ReadACK())
		AckFlag = 1;
	else
		AckFlag = 0;
	I2cStop();
}


uchar I2cReadByte()
{
	uchar i, DAT;
	for(i=0; i<8; i++)
	{
		DAT <<= 1;
		SCL = 0;
		SCL = 1;
		if(SDA)
			DAT |= 0X01;
	}
	return(DAT);
}

uchar At24c02Read(uchar ADDR)
{
	uchar DAT;
	I2cStart();
	I2cSendByte(At24c02ADDR + I2cWrite);
	if(ReadACK())
		AckFlag = 1;
	else
		AckFlag = 0;
	I2cSendByte(ADDR);
	ReadACK();
	I2cStart();
	I2cSendByte(At24c02ADDR + I2cRead);
	if(ReadACK())
		AckFlag = 1;
	else
		AckFlag = 0;
	DAT = I2cReadByte();
	SendACK(1);
	I2cStop();
	return(DAT);
			
}

void main()
{	
	timer0Init();
	EA = 0;
	At24c02Write(3, 188);
	delay(5);
	num = At24c02Read(3);
	if(AckFlag)
		P1 = 0;
	else
		P1 = 0XFF;
	EA = 1;
	while(1);
} 

void timer0() interrupt 1
{
	TH0 = 0xED;
	TL0 = 0xFF;
	display(num);
} 
#include <REGX52.H>

unsigned char num =0;
unsigned char flag;
char nums[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void initUART();
void showNum(unsigned char num);
	
void main(){
	initUART();
	while(1){
		showNum(num);
	}
}

void interruptUART() interrupt 4
{
	if(RI){
		unsigned char temp;
		temp = SBUF;
		num = temp;
		SBUF = ++temp;
		RI = 0;
	}
	if(TI){
		TI = 0;
	}
}

void initUART(){
	SM0 = 0;
	SM1 = 1;
	REN = 1;
	EA = 1;
	ES = 1;
	TL1 = 0xFD;
	TH1 = 0xFD;
	TMOD = 0x20;
	TR1 = 1;
}

void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void showNum(unsigned char num){
	P2_7 = 1;
	P0 = 0xFE;
	P2_7 = 0;
	P2_6 = 1;
	P0 = nums[num];
	P2_6 = 0;
	Delay1ms();
}



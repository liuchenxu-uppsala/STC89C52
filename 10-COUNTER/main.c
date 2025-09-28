#include <REGX52.H>

unsigned char currentNum = 0;
char nums[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void delay1ms()		//@12.000MHz
{
	unsigned char i, j;
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}


void delay(long times){
	while(times > 0){
		delay1ms();
		times--;
	}
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

/**
*----------------------------------------------*
              Init T0 & T1
              T0 as timer and T1 as counter
*----------------------------------------------*
**/
void init(){
	
	EA = 1;
	ET0 = 1;
	ET1= 1;
	  
	TF0 = 0;
	TF1 = 0;
	
	TL0 = 47101%256;
	TH0 = 47101/256;
	
	TL1 = 0xCE;
	TH1 = 0xFF;
	
	TMOD = 0x51; 
	
	TR0 = 1;
	TR1 = 1;
}

void sendSignal(){
	P0_0 = 1;
	delay(1);
	P0_0 = 0;
	delay(2);
}

/**
** T0 timer interrupted function
** send signal per 20ms
**/
void Timer0_ISR(void) interrupt 1
{
	P1_2 = 1;
	P1_2 = 0;
	TF0 = 0;
	TL0 = 47101%256;
	TH0 = 47101/256;
}

/**
** T1 counter interrupted function
**/
void Timer1_ISR(void) interrupt 3
{
	currentNum ++;
	if(currentNum == 10){
		currentNum = 0;
	}
	TF1 = 0;
	TL1 = 0xCE;
	TH1 = 0xFF;
}

void main(){
	init();
	while(1){
		showNum(currentNum);
	}
}
#include <REGX52.H>

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
/**
** Generate a rising edge electrical signal to read data from DI to register
**/
unsigned char firstArr[16] = {1,0,0,0,0,0,1,1, 1,0,0,0,0,0,0,0};

unsigned char secondArr[16] = {1,0,0,0,0,0,1,1, 0,0,1,0,0,0,0,0};

unsigned char thirdArr[16] = {1,0,1,0,1,1,1,1,  0,1,0,0,0,0,0,0};

unsigned char fourthArr[16] = {0,0,0,0,0,0,0,1, 0,0,0,0,1,0,0,0};


unsigned char fifthArr[16] = {1,0,1,0,1,1,1,1,  0,0,0,1,0,0,0,0};

unsigned index = 0;
void updateCLK(){
	P3_5 = 0;
	P3_5 = 1;
	P3_5 = 0;
}

void submitBitDI(unsigned char b){
	P3_4 = b;
}

void flushData(){
	P3_6 = 1;
	P3_6 = 0;
}

void main(){
	while(1){
		for(index = 0; index < 16; index++){
			submitBitDI(firstArr[index]);
			updateCLK();
		}
		flushData();
		delay1ms();
		
		for(index = 0; index < 16; index++){
			submitBitDI(secondArr[index]);
			updateCLK();
		}
		flushData();
		delay1ms();
		
		
		for(index = 0; index < 16; index++){
			submitBitDI(thirdArr[index]);
			updateCLK();
		}
		flushData();
		delay1ms();
		
		for(index = 0; index < 16; index++){
			submitBitDI(fourthArr[index]);
			updateCLK();
		}
		flushData();
		delay1ms();
		
		for(index = 0; index < 16; index++){
			submitBitDI(fifthArr[index]);
			updateCLK();
		}
		flushData();
		delay1ms();
	}
}

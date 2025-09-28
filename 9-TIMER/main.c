#include <REGX52.H>
void init();
void showNum(unsigned char num);
unsigned char times = 0;
unsigned char currentNum = 0;
char nums[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void main(){
	init();
	while(1){
		if(TF0 == 1){
			if(times == 50){
				times = 0;
				if(currentNum <9){
					currentNum++;
				} else{
					currentNum = 0;
				}
				showNum(currentNum);
			} else{
				times++;
				showNum(currentNum);
			}
			init();
		} else{
			showNum(currentNum);
		}
	}
}

void init(){
	TF0 = 0;
	TMOD = 0x01;
	TL0 = 47101%256;
	TH0 = 47101/256;
	TR0 = 1;
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

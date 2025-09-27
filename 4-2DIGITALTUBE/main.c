#include <REGX52.H>
char positions[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};
char nums[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

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



void showNumber(unsigned char position, unsigned char num);
void main(){
	while(1){
		unsigned char index = 0;
		while(index <= 8) {
			if(index == 8){
				index = 0;
			} else{
				showNumber(index,index + 1);
				index++;
			}
		}
	}
}

void showNumber(unsigned char position, unsigned char num){
	P2_7 = 1;
	P0 = positions[position];
	P2_7 = 0;
	P2_6 = 1;
	P0 = nums[num];
	P2_6 = 0;
	Delay1ms();
}

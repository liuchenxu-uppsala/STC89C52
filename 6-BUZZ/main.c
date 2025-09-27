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
unsigned char beep = 0;
void main(){
	while(1){
		P2_3 = beep;
		delay(100);
		if(beep == 0){
			beep = 1;
		} else {
			beep = 0;
		}
	}
}

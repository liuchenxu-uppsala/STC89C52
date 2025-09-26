#include <REGX52.H>
unsigned long num = 0x0;
unsigned char current_byte = 1;
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
void delay(int times) {
	int count = 0;
	while(count < times) {
		Delay1ms();
		count++;
	}
	
}
void main(){
	unsigned char led_position;
	while(1)
	{
			current_byte = P3_0;
			if(P3_0 == 0){
			delay(20);
			while(P3_0 == 0){}
			delay(20);
			current_byte = P3_0;
			if(current_byte == 1){
			num ++;
			led_position = ~(num % (1<<8));
			P1 = led_position;
			}
		}
	}
}

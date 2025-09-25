#include <REGX52.H>
#include <INTRINS.H>
signed char index;
void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main()
{
	int init_value = 1;
	while(1){
		//Delay500ms();
		for (index = 0; index <=7; index++){
			int tempValue = init_value << index;
			tempValue = ~tempValue;
			P1 = tempValue;
			Delay500ms();
		}
	}
}

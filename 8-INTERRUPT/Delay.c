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
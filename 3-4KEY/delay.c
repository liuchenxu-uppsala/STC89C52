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

void Delay(int times){
	while(times >= 0){
		Delay1ms();
		times--;
	}
}
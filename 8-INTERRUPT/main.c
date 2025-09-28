#include <REGX52.H>
#include "Delay.h"

void initInterruptConfig(){
	EA = 1;
	EX1 = 1;
	IT1 = 1;	
}

void interrupt1() interrupt 2
{
	if(P1_0 == 0){
		P1_0 = 1;
	} else {
		P1_0 = 0;
	}
}

void main(){
	initInterruptConfig();
	while(1){
		if(P3_0 == 0){
			delay(15);
			if(P3_0 == 0) {
				while(P3_0 == 0){};
				P3_7 = 1;
				P3_7 = 0;
			}
		}
	}
}

#include <REGX52.H>
#include "delay.h"
unsigned char value = 0x01;

void main(){
	P1=0xFE;
	while(1){
		if(P3_0 == 0){
			Delay(20);
			while(P3_0 == 0);
			Delay(20);
			if(value < 0x80){
				value = value << 1;
				P1 = ~value;
			} else {
				value = 0x01;
				P1 = ~value;
			}
		}
		
		if(P3_1 == 0){
			Delay(20);
			while(P3_1 == 0);
			Delay(20);
			if(value > 0x01){
				value = value >> 1;
				P1 = ~value;
			} else {
				value = 0x80;
				P1 = ~value;
			}
		}
	}
}
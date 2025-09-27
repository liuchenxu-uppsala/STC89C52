#include <REGX52.H>
#include "Delay.h"
#include "DigitalTubeShow.h"

unsigned char result_column;
unsigned char result_row;
unsigned char init = 1;
unsigned char display_column;
unsigned char display_row;

unsigned char detect_row();
unsigned char detect_column();
void computeResult(unsigned char column, unsigned char row);


void main(){
	while(1){
		result_row = detect_row();
		result_column = detect_column();
		if(!init && result_column != -1 && result_row != -1) {
			display_row = result_row + 1;
			display_column = result_column + 1;
		}
		if(!init){
			showNumber(0,display_row);
			delay(1);
			showNumber(1,display_column);
			delay(1);
		}
	}
}

unsigned char  detect_column(){
	unsigned char column = -1;
	P3 = 0xF0;
	if(P3 != 0xF0){
		delay(15);
		if(P3 != 0xF0) {
			init = 0;
			switch (P3){
				case 0xE0 :
					column = 0;
					break;
				case 0xD0:
					column = 1;
					break;
				case 0xB0:
					column = 2;
					break;
				case 0x70:
					column = 3;
					break;
				default:
					column = -1;
			}
		}
	}
	return column;
}

unsigned char detect_row(){
	unsigned char row = -1;
	P3 = 0x0F;
	if(P3 != 0x0F){
		delay(15);
		if(P3 != 0x0F){
			init = 0;
			switch (P3){
				case  0x0E:
					row = 0;
					break;
				case 0x0D:
					row = 1;
					break;
				case 0x0B:
					row = 2;
					break;
				case 0x07:
					row = 3;
					break;
				default:
					row = -1;
			}
		}
	}
	return row;
}

void computeResult(unsigned char column, unsigned char row){
	if(column != -1 && row != -1){
		showNumber(0,row + 1);
		delay(1);
		showNumber(1,column + 1);
	}
}

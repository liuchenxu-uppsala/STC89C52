#include <REGX52.H>
void main(){
	//λѡ
	P2_7 = 1;
	P2_6 = 0;
	P0 = 0xFE;
	while(1){
		//��ѡ
		P2_7 = 0;
		P2_6 = 1;
		P0 = 0x4F;
	}
}

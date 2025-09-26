#include <REGX52.H>
unsigned char init_flag = 1;
int main(){
	while(1){
		// S1 button released
		if(P3_0 == 1){
			if(!init_flag){
				P1_0 = 0;
			}
		}
		// S1 button pressed
		else {
			P1_0 = 1;
			if(init_flag){
				init_flag = 0;
			}
		}
	}
}

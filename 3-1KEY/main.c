#include <REGX52.H>
void main(){
	while(1){
		// S2 button pressed
		if(P3_0 == 0){
			P1_0 = 0;
		}
    // S2 Button released		
		else{
			P1_0 = 1;
		}
	}
}

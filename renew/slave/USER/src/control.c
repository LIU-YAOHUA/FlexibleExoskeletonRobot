#include "main.h"

void left_right(s8 num){
	Flag_turn = num;
	ctr_flag = 1;
}

void up_down(s16 num){
	Flag_v = -500;
	ctr_flag = 1;
}

void stop_func(void){
	Flag_v = 0;
	Flag_turn = 0;
	ctr_flag = 0;
}
//turn
void remoteControl(u8 data){
	switch(data){
		case 'j':
			left_right(-20);		//-20
			break;
		
		case 'l':
			left_right(20);			//20
			break;
		
		case 'i':
			up_down(-500);			//-500
			break;
		
		case 'k':
			up_down(500);				//500
			break;
		
		case 'p':
			stop_func();				//0
			break;
	}
}


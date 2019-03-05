#ifndef __EXTI_H
#define __EXIT_H	 
#include "main.h"  	

//#define KEY0 			GPIO_Pin_Get(GPIOH,PIN3)   	//PH3
//#define KEY1 			GPIO_Pin_Get(GPIOH,PIN2)		//PH2 
#define KEY2 			GPIO_Pin_Get(GPIOC,PIN13)		//PC13
//#define WK_UP 		GPIO_Pin_Get(GPIOA,PIN0)	//PA0 


void KEY_Init(void);
void EXTIX_Init(void);	//外部中断初始化		 					    
#endif


























#include "main.h"

void TIM1_PWM_Init(u32 arr,u32 psc)
{		 					 
	RCC->APB2ENR|=1<<0;		//TIM1时钟使能    
	RCC->AHB1ENR|=1<<1;   	//使能PORTB时钟	
	GPIO_Set(GPIOB,PIN13|PIN14,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOB,13,1);	//PB13,AF1 
	GPIO_AF_Set(GPIOB,14,1);	//PB14,AF1 
	
	TIM1->BDTR|=1<<15;	//
	TIM1->ARR=arr;			//设定计数器自动重装值 
	TIM1->PSC=psc;			//预分频器不分频 
	TIM1->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM1->CCMR1|=1<<3; 		//CH1 预装载使能	
	TIM1->CCMR1|=6<<12;  	//CH2 PWM1模式		 
	TIM1->CCMR1|=1<<11; 	//CH2 预装载使能	    
	TIM1->CCER|=1<<2;      //使能CC1NE
	TIM1->CCER|=1<<6;    	//使能CC2NE   
	TIM1->CR1|=1<<7;   		//ARPE使能 
	TIM1->CR1|=1<<0;    	//使能定时器1		
	
} 



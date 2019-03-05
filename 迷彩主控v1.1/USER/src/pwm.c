#include "main.h"

void TIM1_PWM_Init(u32 arr,u32 psc)
{		 					 
	RCC->APB2ENR|=1<<0;		//TIM1ʱ��ʹ��    
	RCC->AHB1ENR|=1<<1;   	//ʹ��PORTBʱ��	
	GPIO_Set(GPIOB,PIN13|PIN14,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_AF_Set(GPIOB,13,1);	//PB13,AF1 
	GPIO_AF_Set(GPIOB,14,1);	//PB14,AF1 
	
	TIM1->BDTR|=1<<15;	//
	TIM1->ARR=arr;			//�趨�������Զ���װֵ 
	TIM1->PSC=psc;			//Ԥ��Ƶ������Ƶ 
	TIM1->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM1->CCMR1|=1<<3; 		//CH1 Ԥװ��ʹ��	
	TIM1->CCMR1|=6<<12;  	//CH2 PWM1ģʽ		 
	TIM1->CCMR1|=1<<11; 	//CH2 Ԥװ��ʹ��	    
	TIM1->CCER|=1<<2;      //ʹ��CC1NE
	TIM1->CCER|=1<<6;    	//ʹ��CC2NE   
	TIM1->CR1|=1<<7;   		//ARPEʹ�� 
	TIM1->CR1|=1<<0;    	//ʹ�ܶ�ʱ��1		
	
} 



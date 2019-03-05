#include "main.h"


//按键初始化函数
void KEY_Init(void)
{
	RCC->AHB1ENR|=1<<0;     //使能PORTA时钟 
	RCC->AHB1ENR|=1<<2;     //使能PORTC时钟 
	RCC->AHB1ENR|=1<<7;     //使能PORTH时钟
	//GPIO_Set(GPIOA,PIN0,GPIO_MODE_IN,0,0,GPIO_PUPD_PD); 			//PA0设置为下拉输入 
	GPIO_Set(GPIOC,PIN13,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); 			//PC13设置为上拉输入 
	//GPIO_Set(GPIOH,PIN2|PIN3,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);		//PH2/3设置上拉输入
} 

/*
//外部中断0服务程序
void EXTI0_IRQHandler(void)
{ 
	delay_ms(10);	//消抖
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
	if(WK_UP==1)	 
	{
		printf("key_up");
	}		 
}	
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//消抖
	EXTI->PR=1<<2;  //清除LINE2上的中断标志位  
	if(KEY1==0)	  
	{	 
		urg_flag=!urg_flag;
		printf("key1");
	}		 
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//消抖
	EXTI->PR=1<<3;	//清除LINE3上的中断标志位  
	if(KEY0==0)	 
	{
		printf("key0"); 
	}		 
}
//外部中断10~15服务程序
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);	//消抖
	EXTI->PR=1<<13; //清除LINE13上的中断标志位 
	if(KEY2==0)	 
	{		
		printf("key2");		
	}		  
}
	   
//外部中断初始化程序
//初始化PH2,PH3,PC13,PA0为中断输入.
void EXTIX_Init(void)
{
	KEY_Init(); 
	Ex_NVIC_Config(GPIO_C,13,FTIR);		//下降沿触发
	Ex_NVIC_Config(GPIO_H,2,FTIR); 		//下降沿触发
	Ex_NVIC_Config(GPIO_H,3,FTIR); 		//下降沿触发
 	Ex_NVIC_Config(GPIO_A,0,RTIR); 	 	//上升沿触发 
	MY_NVIC_Init(3,2,EXTI2_IRQn,2);		//抢占3，子优先级2，组2
	MY_NVIC_Init(2,2,EXTI3_IRQn,2);		//抢占2，子优先级2，组2	   
	MY_NVIC_Init(1,2,EXTI15_10_IRQn,2);	//抢占1，子优先级2，组2	   
	MY_NVIC_Init(0,2,EXTI0_IRQn,2);		//抢占0，子优先级2，组2	   
}
*/
//外部中断10~15服务程序
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);	//消抖
	EXTI->PR=1<<13; //清除LINE13上的中断标志位 
	if(KEY2==0)	 
	{		
		urg_flag=!urg_flag;
		printf("key2");		
	}		  
}
	
void EXTIX_Init(void)
{
	KEY_Init(); 
	Ex_NVIC_Config(GPIO_C,13,FTIR);		//下降沿触发
//	Ex_NVIC_Config(GPIO_H,2,FTIR); 		//下降沿触发
//	Ex_NVIC_Config(GPIO_H,3,FTIR); 		//下降沿触发
// 	Ex_NVIC_Config(GPIO_A,0,RTIR); 	 	//上升沿触发 
//	MY_NVIC_Init(3,2,EXTI2_IRQn,2);		//抢占3，子优先级2，组2
//	MY_NVIC_Init(2,2,EXTI3_IRQn,2);		//抢占2，子优先级2，组2	   
	MY_NVIC_Init(1,2,EXTI15_10_IRQn,2);	//抢占1，子优先级2，组2	   
//	MY_NVIC_Init(0,2,EXTI0_IRQn,2);		//抢占0，子优先级2，组2	   
}










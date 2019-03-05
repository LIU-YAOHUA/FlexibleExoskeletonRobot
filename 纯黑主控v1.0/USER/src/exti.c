#include "main.h"


//������ʼ������
void KEY_Init(void)
{
	RCC->AHB1ENR|=1<<0;     //ʹ��PORTAʱ�� 
	RCC->AHB1ENR|=1<<2;     //ʹ��PORTCʱ�� 
	RCC->AHB1ENR|=1<<7;     //ʹ��PORTHʱ��
	//GPIO_Set(GPIOA,PIN0,GPIO_MODE_IN,0,0,GPIO_PUPD_PD); 			//PA0����Ϊ�������� 
	GPIO_Set(GPIOC,PIN13,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); 			//PC13����Ϊ�������� 
	//GPIO_Set(GPIOH,PIN2|PIN3,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);		//PH2/3������������
} 

/*
//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{ 
	delay_ms(10);	//����
	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
	if(WK_UP==1)	 
	{
		printf("key_up");
	}		 
}	
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//����
	EXTI->PR=1<<2;  //���LINE2�ϵ��жϱ�־λ  
	if(KEY1==0)	  
	{	 
		urg_flag=!urg_flag;
		printf("key1");
	}		 
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//����
	EXTI->PR=1<<3;	//���LINE3�ϵ��жϱ�־λ  
	if(KEY0==0)	 
	{
		printf("key0"); 
	}		 
}
//�ⲿ�ж�10~15�������
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);	//����
	EXTI->PR=1<<13; //���LINE13�ϵ��жϱ�־λ 
	if(KEY2==0)	 
	{		
		printf("key2");		
	}		  
}
	   
//�ⲿ�жϳ�ʼ������
//��ʼ��PH2,PH3,PC13,PA0Ϊ�ж�����.
void EXTIX_Init(void)
{
	KEY_Init(); 
	Ex_NVIC_Config(GPIO_C,13,FTIR);		//�½��ش���
	Ex_NVIC_Config(GPIO_H,2,FTIR); 		//�½��ش���
	Ex_NVIC_Config(GPIO_H,3,FTIR); 		//�½��ش���
 	Ex_NVIC_Config(GPIO_A,0,RTIR); 	 	//�����ش��� 
	MY_NVIC_Init(3,2,EXTI2_IRQn,2);		//��ռ3�������ȼ�2����2
	MY_NVIC_Init(2,2,EXTI3_IRQn,2);		//��ռ2�������ȼ�2����2	   
	MY_NVIC_Init(1,2,EXTI15_10_IRQn,2);	//��ռ1�������ȼ�2����2	   
	MY_NVIC_Init(0,2,EXTI0_IRQn,2);		//��ռ0�������ȼ�2����2	   
}
*/
//�ⲿ�ж�10~15�������
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);	//����
	EXTI->PR=1<<13; //���LINE13�ϵ��жϱ�־λ 
	if(KEY2==0)	 
	{		
		urg_flag=!urg_flag;
		printf("key2");		
	}		  
}
	
void EXTIX_Init(void)
{
	KEY_Init(); 
	Ex_NVIC_Config(GPIO_C,13,FTIR);		//�½��ش���
//	Ex_NVIC_Config(GPIO_H,2,FTIR); 		//�½��ش���
//	Ex_NVIC_Config(GPIO_H,3,FTIR); 		//�½��ش���
// 	Ex_NVIC_Config(GPIO_A,0,RTIR); 	 	//�����ش��� 
//	MY_NVIC_Init(3,2,EXTI2_IRQn,2);		//��ռ3�������ȼ�2����2
//	MY_NVIC_Init(2,2,EXTI3_IRQn,2);		//��ռ2�������ȼ�2����2	   
	MY_NVIC_Init(1,2,EXTI15_10_IRQn,2);	//��ռ1�������ȼ�2����2	   
//	MY_NVIC_Init(0,2,EXTI0_IRQn,2);		//��ռ0�������ȼ�2����2	   
}










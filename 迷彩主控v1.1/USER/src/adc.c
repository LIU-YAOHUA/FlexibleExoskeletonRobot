#include "adc.h"
														   
void  Adc_Init(void)
{    
	//�ȳ�ʼ��IO��
 	RCC->APB2ENR|=1<<8;    	//ʹ��ADC1ʱ�� 
	RCC->AHB1ENR|=1<<0;    	//ʹ��PORTAʱ��	  
	GPIO_Set(GPIOA,PIN4,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);	//PA4,ģ������,����  
//	GPIO_Set(GPIOA,PIN5,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);	//PA5,ģ������,����  
	GPIO_Set(GPIOA,PIN6,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);	//PA6,ģ������,����   

	RCC->APB2RSTR|=1<<8;   	//ADCs��λ
	RCC->APB2RSTR&=~(1<<8);	//��λ����	 
	ADC->CCR=1<<16;			//ADCCLK=PCLK2/4=90/4=22.5Mhz,ADCʱ����ò�Ҫ����36Mhz
 	
	ADC1->CR1=0;   			//CR1��������
	ADC1->CR2=0;   			//CR2��������
	ADC1->CR1|=0<<24;      	//12λģʽ
	ADC1->CR1|=0<<8;    	//��ɨ��ģʽ	
	
	ADC1->CR2&=~(1<<1);    	//����ת��ģʽ
 	ADC1->CR2&=~(1<<11);   	//�Ҷ���	
	ADC1->CR2|=0<<28;    	//�������
	
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=0<<20;     	//1��ת���ڹ��������� Ҳ����ֻת����������1 			   
	//����ͨ��5�Ĳ���ʱ��
	ADC1->SMPR2&=~(7<<(3*4));//ͨ��5����ʱ�����	  
 	ADC1->SMPR2|=7<<(3*4); 	//ͨ��5  480������,��߲���ʱ�������߾�ȷ��	
 	ADC1->SMPR2&=~(7<<(3*6));//ͨ��5����ʱ�����	  
 	ADC1->SMPR2|=7<<(3*6); 	//ͨ��5  480������,��߲���ʱ�������߾�ȷ��	 
//	ADC1->SMPR1 = 0x0000003F;//8��ͨ����ʱ��Ϊ239.5T
//	ADC1->SMPR2 = 0x3FFFF000;//8��ͨ����ʱ��Ϊ239.5T
	
 	ADC1->CR2|=1<<0;	   	//����ADת����	  
}				  
//���ADCֵ
//ch:ͨ��ֵ 0~18
//����ֵ:ת�����
u16 Get_Adc(u8 ch)   
{
	//����ת������	  		 
	ADC1->SQR3&=0XFFFFFFE0;//��������1 ͨ��ch
	ADC1->SQR3|=ch;		  			    
	ADC1->CR2|=1<<30;       //��������ת��ͨ�� 
	while(!(ADC1->SR&1<<1));//�ȴ�ת������	 	   
	return ADC1->DR;		//����adcֵ	
}








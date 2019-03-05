#include "adc.h"
														   
void  Adc_Init(void)
{    
	//先初始化IO口
 	RCC->APB2ENR|=1<<8;    	//使能ADC1时钟 
	RCC->AHB1ENR|=1<<0;    	//使能PORTA时钟	  
	GPIO_Set(GPIOA,PIN4,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);	//PA4,模拟输入,下拉  
//	GPIO_Set(GPIOA,PIN5,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);	//PA5,模拟输入,下拉  
	GPIO_Set(GPIOA,PIN6,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);	//PA6,模拟输入,下拉   

	RCC->APB2RSTR|=1<<8;   	//ADCs复位
	RCC->APB2RSTR&=~(1<<8);	//复位结束	 
	ADC->CCR=1<<16;			//ADCCLK=PCLK2/4=90/4=22.5Mhz,ADC时钟最好不要超过36Mhz
 	
	ADC1->CR1=0;   			//CR1设置清零
	ADC1->CR2=0;   			//CR2设置清零
	ADC1->CR1|=0<<24;      	//12位模式
	ADC1->CR1|=0<<8;    	//非扫描模式	
	
	ADC1->CR2&=~(1<<1);    	//单次转换模式
 	ADC1->CR2&=~(1<<11);   	//右对齐	
	ADC1->CR2|=0<<28;    	//软件触发
	
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=0<<20;     	//1个转换在规则序列中 也就是只转换规则序列1 			   
	//设置通道5的采样时间
	ADC1->SMPR2&=~(7<<(3*4));//通道5采样时间清空	  
 	ADC1->SMPR2|=7<<(3*4); 	//通道5  480个周期,提高采样时间可以提高精确度	
 	ADC1->SMPR2&=~(7<<(3*6));//通道5采样时间清空	  
 	ADC1->SMPR2|=7<<(3*6); 	//通道5  480个周期,提高采样时间可以提高精确度	 
//	ADC1->SMPR1 = 0x0000003F;//8个通道的时间为239.5T
//	ADC1->SMPR2 = 0x3FFFF000;//8个通道的时间为239.5T
	
 	ADC1->CR2|=1<<0;	   	//开启AD转换器	  
}				  
//获得ADC值
//ch:通道值 0~18
//返回值:转换结果
u16 Get_Adc(u8 ch)   
{
	//设置转换序列	  		 
	ADC1->SQR3&=0XFFFFFFE0;//规则序列1 通道ch
	ADC1->SQR3|=ch;		  			    
	ADC1->CR2|=1<<30;       //启动规则转换通道 
	while(!(ADC1->SR&1<<1));//等待转换结束	 	   
	return ADC1->DR;		//返回adc值	
}








#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 


#define ADC_CH5  		5 		 	//通道5	   	      	    
	   									   
void Adc_Init(void); 				//ADC初始化
u16  Get_Adc(u8 ch); 				//获得某个通道值 

#endif 
















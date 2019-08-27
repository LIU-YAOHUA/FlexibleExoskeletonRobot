#include "main.h"

#define  ADDO PAin(0)
#define  ADSK PAout(1)

int32_t ReadCount(void)
{
 u32 Count;
 u8 i;
 u16 time_out=0;

	RCC ->APB2ENR |= (0x1<<2);//GPIOA使能
	GPIOA ->CRL &=~(0xF<<0);
	GPIOA ->CRL |=(0x8<<0);//in
	
	GPIOA ->CRL &=~(0Xf<<4);
	GPIOA ->CRL |=(0X3<<4);//out
	
 ADSK=0; //使能AD（PD_SCK 置低）
 Count=0;
 while(ADDO){
	time_out++;
	 if(time_out>0xfff){
//		 rt_kprintf("hx711_error return !\r\n");
		return 0;
	 }
	rt_thread_delay(1); 
 }; //AD转换未结束则等待，否则开始读取
 for (i=0;i<24;i++)
 {
 ADSK=1; //PD_SCK 置高（发送脉冲）
 Count=Count<<1; //下降沿来时变量Count左移一位，右侧补零
 ADSK=0; //PD_SCK 置低
 if(ADDO) Count++;
 }
 ADSK=1;
 Count=Count^0x800000;//第25个脉冲下降沿来时，转换数据
 ADSK=0;
 return(Count);
}

#include "main.h"

#define  ADDO PAin(0)
#define  ADSK PAout(1)

int32_t ReadCount(void)
{
 u32 Count;
 u8 i;
 u16 time_out=0;

	RCC ->APB2ENR |= (0x1<<2);//GPIOAʹ��
	GPIOA ->CRL &=~(0xF<<0);
	GPIOA ->CRL |=(0x8<<0);//in
	
	GPIOA ->CRL &=~(0Xf<<4);
	GPIOA ->CRL |=(0X3<<4);//out
	
 ADSK=0; //ʹ��AD��PD_SCK �õͣ�
 Count=0;
 while(ADDO){
	time_out++;
	 if(time_out>0xfff){
//		 rt_kprintf("hx711_error return !\r\n");
		return 0;
	 }
	rt_thread_delay(1); 
 }; //ADת��δ������ȴ�������ʼ��ȡ
 for (i=0;i<24;i++)
 {
 ADSK=1; //PD_SCK �øߣ��������壩
 Count=Count<<1; //�½�����ʱ����Count����һλ���Ҳಹ��
 ADSK=0; //PD_SCK �õ�
 if(ADDO) Count++;
 }
 ADSK=1;
 Count=Count^0x800000;//��25�������½�����ʱ��ת������
 ADSK=0;
 return(Count);
}

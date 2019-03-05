#include "stm32f10x.h"
#include "tim2.h"
#include "adc.h"
#include "delay.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "stdio.h" 

/*
����������
������ 		115200
��װ��ʽ		��ֱ
�ش�����		10HZ
��ʱʱ������Ϊ20ms < 100ms��10HZ��

���Ӵ���2���������ǵ�ʱ�� ע�� ��������������Ϊ��������
			usart2.c ��35��
*/


int main(){
	
	s8 P_value;
	u16 a3,a4,a5,a6,a7,a8;
	s32 P_Result;
	
Stm32_Clock_Init(9);	//ϵͳʱ������	
	
	/*��ʱ��2��ʼ��*/
	init_tim2();
	
	/*����1��ʼ����������Ϊ9600*/
	usart_init(115200);			//��ʱȥ������1������1��Ϊ���
	
	/*����2��ʼ����������Ϊ9600*/
	usart2_init(115200);			//����2��Ϊ������
	
	/*����3��ʼ����������Ϊ9600*/
	usart3_init(19200);			//����3��������
	
	
	
	delay_init(72);					//��ʱ������ʼ��
	Adc_Init();							//PA1,����ADCͨ��һ
	
	while(1){
		
		/*���յ�����ԭ������*/
		/*�յ�open close�Եƽ��п���*/
		
		//Task_Pc();
		Task_Pc2();
		//Task_Pc3();
		if(send_flag>=5){
		a8=Get_Adc(ADC_CH4);		//12λ
		a7=Get_Adc(ADC_CH5);
		a6=Get_Adc(ADC_CH6);
		a5=Get_Adc(ADC_CH7);
		a4=Get_Adc(ADC_CH8);
		a3=Get_Adc(ADC_CH9);
		//a2=Get_Adc(ADC_CH10);
		//a1=Get_Adc(ADC_CH11);
		P_Result=(a3+a7+a8)-(a4+a5+a6);		//С��16λ 65536
		//printf("\r\nR%4d\r\n",P_Result);
		P_value=P_Result/256;		//���ż������ȥ�Ÿ�����Ľ������256��65536������0-255֮��
			if((P_value>=120)&&(P_value<=127)){		//�ٳ�121-127���߸�����Ϊ������־λ�������Ƿ����ٶ�
			P_value=120;
			}
			if(is_xspeed){		//��û���ٶ�
				P_value=121;		//����ѹ��ֵ������ѹ��ֵ���
			}
		PcTx_Byte3(P_value);	
			printf("%d  %d  %d  %d  %d  %d\r\n",a3,a4,a5,a6,a7,a8);
		send_flag=0;
		}
	}

}








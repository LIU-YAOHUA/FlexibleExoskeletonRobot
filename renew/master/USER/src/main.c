#include "main.h"

int main(void)
{  
	u16 a,b;
	Stm32_Clock_Init(432,25,2,9);	//����ʱ��,216Mhz
  delay_init(216);				//��ʱ��ʼ��  
	uart_init(108,19200);	//���ڳ�ʼ��Ϊ19200
	
	uart2_init(54,19200); 	//����2��ʼ�� 
	uart3_init(54,19200); 	//����3��ʼ�� 
	
	TIM1_PWM_Init(PWMMAX-1,216-1);
	//TIM4_Int_Init(timer_ms*10-1,10800-1);//10KhzƵ��,��ʱʱ��Ϊtimer_ms
	
	GPIO_Init();		 	//��ʼ�������������,ָʾ�ƿ�������
	EXTIX_Init();         	//��ʼ���������ⲿ�ж����� 
	
	
	
while(1)
	{
		//res2����ŵ����ݣ�res3���ҽŵ�����
		a++;
		if(res2==0x79&&res3==0x79){//���������ǣ����ҽ�û���ٶȣ�ֹͣ
					control_stop();			
					PcTx_Byte(0x30);
					delay_ms(50);
				}else{		//����˫��վ��ֹͣ״̬����ϵͳ���п���
//					LED1(1);
//					LED2(1);
					if(res2==0x79){//���û���ٶ�		
						res2=0;		//����imu������
					}
					
					if(res3==0x79){//�ҽ�û���ٶ�
						res3=0;		//����imu������
					}
					
					if(a>900){
						b++;
						if(b>30){
							b=0;
						send_to_pc();
						}
						
						a=0;
					}
//					if(res2==0&&res3==0){
//					PcTx_Byte(0x30);
//					}
					control_motor_front();		
					control_motor_back2();
					
				}
	}
}




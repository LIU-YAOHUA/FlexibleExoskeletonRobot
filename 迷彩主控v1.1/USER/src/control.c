#include "main.h"

#define PWM_CONST_VAL1 80			//��ǰ
#define PWM_CONST_VAL1_1 80		//��ǰ
#define PWM_CONST_VAL2 40			//���
#define PWM_CONST_VAL2_2 70		//�Һ�

u8 usmart_flag=0,urg_flag=0;

/************************************************************
��������void GPIO_Init(void);
��  �Σ�void
����ֵ����
��  �ܣ���ʼ��������ƶ˿ں�ָʾ�ƿ��ƶ˿�
��  �ߣ�meetwit
ʱ  �䣺2018��10��24��10:43:07
*************************************************************/
void GPIO_Init(void)
{    
	/*ָʾ��*/	
	RCC->AHB1ENR|=1<<7;//ʹ��PORTHʱ�� 
	GPIO_Set(GPIOH,PIN2|PIN3|PIN4|PIN5|PIN6|PIN7,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); 
	
	/*������ƶ˿�*/	
	RCC->AHB1ENR|=1<<2;//ʹ��PORTCʱ�� 
	RCC->AHB1ENR|=1<<4;//ʹ��PORTEʱ�� 
	GPIO_Set(GPIOC,PIN10|PIN11,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);
	GPIO_Set(GPIOE,PIN3|PIN4,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); 

	GPIO_Initial_State();		//����Ϊ��ʼ״̬��led�أ��������
}

/************************************************************
��������void GPIO_Initial_State(void);
��  �Σ�void
����ֵ����
��  �ܣ����Ƴ�ʼ״̬�µ��ֹͣ��ָʾ��ֹͣ
��  �ߣ�meetwit
ʱ  �䣺2018��10��24��10:36:14
*************************************************************/
void GPIO_Initial_State(void){
	LED1(1);
	LED2(1);
	LED3(1);
	LED4(1);
	LED5(1);
	LED6(1);
	
	front_motor(0,10);//�޷���ֹͣ��10%
	back_motor(0,10);//�޷���ֹͣ��10%
}

/************************************************************
��������void front_motor(u8 direction, u8 Percentage);
��  �Σ�u8 direction ���� 0=ֹͣ��1=˳ʱ�룬2=��ʱ��, u8 Percentage %Խ��Խ��
����ֵ����
��  �ܣ�������ǰ����ת��ֹͣ
��  �ߣ�meetwit
ʱ  �䣺2018��10��24��10:36:14
*************************************************************/
void front_motor(u8 direction, u8 Percentage){
	u16 temp;
	temp=Percentage*PWMMAX/100;
	if(direction==1){//����1,���ŵ���� ��˳ʱ��
		M2_DI2(1);
		M2_DI3(0);
		M2_PWM_VAL=temp;
	}else if(direction==2){//����2
		M2_DI2(0);
		M2_DI3(1);
		M2_PWM_VAL=temp;
	}else{//stop
		M2_DI2(0);
		M2_DI3(0);
		M2_PWM_VAL=temp;
	}
	
}

/************************************************************
��������void behind_motor(u8 direction, u8 Percentage);
��  �Σ�u8 direction ���� 0=ֹͣ��1=˳ʱ�룬2=��ʱ��, u8 Percentage %Խ��Խ��
����ֵ����
��  �ܣ������ź�����ת��ֹͣ
��  �ߣ�meetwit
ʱ  �䣺2018��10��24��10:36:14
*************************************************************/
void back_motor(u8 direction, u8 Percentage){
	u16 temp;
	temp=Percentage*PWMMAX/100;
	if(direction==1){//����1��˳ʱ��
		M3_DI2(1);
		M3_DI3(0);
		M3_PWM_VAL=temp;
	}else if(direction==2){//����2
		M3_DI2(0);
		M3_DI3(1);
		M3_PWM_VAL=temp;
	}else{//stop
		M3_DI2(0);
		M3_DI3(0);
		M3_PWM_VAL=temp;
	}
	
}

/************************************************************
��������void Emergency_stop(void);
��  �Σ�void
����ֵ����
��  �ܣ���ǰ�ź���ֹͣ��ָʾ����ʾֹͣ,����������ٿ���
��  �ߣ�meetwit
ʱ  �䣺2018��10��24��10:30:45
*************************************************************/
void Emergency_stop(){
	control_stop();
	urg_flag=0;
	//printf("stop");
}

/************************************************************
��������void control_stop(void);
��  �Σ�void
����ֵ����
��  �ܣ���ǰ�ź���ֹͣ��ָʾ����ʾֹͣ
��  �ߣ�meetwit
ʱ  �䣺2018��10��24��10:30:45
*************************************************************/
void control_stop(void){
	LED1(0);
	LED2(0);
	LED3(1);
	LED4(1);
	LED5(1);
	LED6(1);
			
			front_motor(0,10);//�޷���ֹͣ��10%
			back_motor(0,10);//�޷���ֹͣ��10%

}

/************************************************************
��������void control_led2(void);
��  �Σ�void
����ֵ����
��  �ܣ�����������ݶ�ָʾ�ƽ��п���
��  �ߣ�meetwit
ʱ  �䣺2018��10��24��10:30:45
*************************************************************/
void control_led2(void){
			if(res2>2){
		//�ҽ���ǰ���������A��ת
			//right1=0;right2=1;
			LED5(0);LED6(1);
		}else if(res2<-2){
		//�ҽ��ź����������B��ת
			//right1=1;right2=0;
			LED5(1);LED6(0);
		}else{
		//stop
			//right1=0;right2=0;
			LED5(0);LED6(0);
		}

}

/************************************************************
��������void control_led3(void);
��  �Σ�void
����ֵ����
��  �ܣ�����������ݶ�ָʾ�ƽ��п���
��  �ߣ�meetwit
ʱ  �䣺2018��10��24��10:30:45
*************************************************************/
void control_led3(void){
			if(res3>2){
		//�����ǰ���������A��ת
			//left1=0;left2=1;
				LED3(0);LED4(1);
			
		}else if(res3	<-2){
		//����ź����������B��ת
			//left1=1;left2=0;
			LED3(1);LED4(0);
		}else{
		//stop
			//left1=0;left2=0;
			LED3(0);LED4(0);
		}

}

/************************************************************
��������void control_motrol_front(void);
��  �Σ�void
����ֵ����
��  �ܣ�����������ݶ���ǰ������п���
��  �ߣ�meetwit
ʱ  �䣺2018��10��24��10:30:05
*************************************************************/
void control_motor_front(void){
//			u8 if_First=0;
	if(res2>2&&res3<=2){
				front_motor(1,PWM_CONST_VAL1);//����2��PWM=50%	Counter_clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else if(res3>2&&res2<=2){
				front_motor(2,PWM_CONST_VAL1_1);////����1��PWM=50%	Clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else{	
				front_motor(0,10);//�޷���ֹͣ��10%
//				delay_ms(30);
//				if_First=1;
			}

}
void control_motor_front2(void){
//			u8 if_First=0;
	if(res2>2&&res3<=2){
				front_motor(2,PWM_CONST_VAL1);//����2��PWM=50%	Counter_clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else if(res3>2&&res2<=2){
				front_motor(1,PWM_CONST_VAL1);////����1��PWM=50%	Clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else{	
				front_motor(0,10);//�޷���ֹͣ��10%
//				if_First=1;
			}

}

/************************************************************
��������void control_motor_back(void);
��  �Σ�void
����ֵ����
��  �ܣ�����������ݶ��ź������п���
��  �ߣ�meetwit
ʱ  �䣺2018��11��1��21:05:21
*************************************************************/
void control_motor_back(void){
//				u8 if_First=0;
	if(res2<-2&&res3>=-2){
				back_motor(1,PWM_CONST_VAL2);//����2��PWM=50%	Counter_clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else if(res3<-2&&res2>=-2){
				back_motor(2,PWM_CONST_VAL2);////����1��PWM=50%	Clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else{	
				back_motor(0,10);//�޷���ֹͣ��10%
//				if_First=1;
//				delay_ms(30);
			}

}

void control_motor_back2(void){
//				u8 if_First=0;
	if(res2<-2&&res3>=-2){
				back_motor(2,PWM_CONST_VAL2_2);//����2��PWM=50%	Counter_clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else if(res3<-2&&res2>=-2){
				back_motor(1,PWM_CONST_VAL2);////����1��PWM=50%	Clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else{	
				back_motor(0,10);//�޷���ֹͣ��10%
//				if_First=1;
			}

}

/************************************************************
��������void send_to_pc(void);
��  �Σ�void
����ֵ����
��  �ܣ�QT��λ����ʾ���ݷ��ͣ�����ģ��
��  �ߣ�meetwit
ʱ  �䣺2018��12��1��21:25:51
*************************************************************/
void send_to_pc(void){
	if(res2>2){//��ǰ
		PcTx_Byte(0x32);
	}else if(res3>2){//��ǰ
		//for(u8 i;i<10;i++){
		PcTx_Byte(0x31);
		//}
		
	}else{
		//PcTx_Byte(0x35);
	}
	if(res2<-2){//�Һ�
		PcTx_Byte(0x34);
	}else if(res3<-2){//���
		PcTx_Byte(0x33);
	}else{
		//PcTx_Byte(0x36);
	}

	
}

/************************************************************
��������void send_to_pc(void);
��  �Σ�void
����ֵ����
��  �ܣ�QT��λ����ʾ���ݷ��ͣ���ǰ���ת��
��  �ߣ�meetwit
ʱ  �䣺2019��1��5��11:26:26
*************************************************************/
void send_to_pc2(void){
	
	double temp = 17800/2048.0,rpm1,rpm2;
	u16 adc_temp=0;
	adc_temp = Get_Adc(4);
	if(adc_temp<2048){
		//-
		adc_temp=2048-adc_temp;
		rpm1 = adc_temp*temp;
		rpm1 = - rpm1;
	}else{
		//+
		adc_temp=adc_temp-2048;
		rpm1 = adc_temp*temp;
	}
	adc_temp = Get_Adc(6);
	if(adc_temp<2048){
		//-
		adc_temp=2048-adc_temp;
		rpm2 = adc_temp*temp;
		rpm2 = - rpm2;
	}else{
		//+
		adc_temp=adc_temp-2048;
		rpm2 = adc_temp*temp;
	}
	//printf("q,%f,h,%f\r\n",rpm1/79.0,rpm2/79.0);
	printf("%lf\r\n",rpm1/79.0);
	
//	adc_temp = Get_Adc(4);
//	printf("pa4=%d\r\n",adc_temp);
//	adc_temp = Get_Adc(6);
//	printf("pa6=%d\r\n",adc_temp);
}

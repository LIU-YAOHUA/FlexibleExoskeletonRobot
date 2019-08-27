#include "main.h"
float stop_flag = 0,ctr_flag = 0,Flag_v = 0,Flag_turn = 0;
/*
��������PWM_Init_TIM1
��	�Σ�u16 arr,u16 psc Ƶ��
����ֵ����
��	�ã���ʼ����ʱ��1����·PWM���
��	�ڣ�2019��1��26��
��	�ߣ�meetwit
*/
void PWM_Init_TIM1(u16 arr,u16 psc)
{		 					 
	RCC->APB2ENR|=1<<11;       //ʹ��TIM1ʱ��    
	RCC->APB2ENR|=1<<2;        //PORTAʱ��ʹ��   
	RCC->APB2ENR|=1<<3;        //PORTBʱ��ʹ��     
	GPIOA->CRH&=0XFFFF0FF0;    //PORTA8 11�������
	GPIOA->CRH|=0X0000B00B;    //PORTA8 11�������  
	GPIOB->CRH&=0X00FFFFFF;    //PORTB14,B15�������
	GPIOB->CRH|=0XBB000000;    //PORT�������
	
	TIM1->ARR=arr;             //�趨�������Զ���װֵ 
	TIM1->PSC=psc;             //Ԥ��Ƶ������Ƶ
	TIM1->CCMR1|=6<<4;         //CH1 PWM1ģʽ	
	TIM1->CCMR1|=6<<12;        //CH2 PWM1ģʽ	
	TIM1->CCMR2|=6<<4;         //CH3 PWM1ģʽ	
	TIM1->CCMR2|=6<<12;        //CH4 PWM1ģʽ	
	TIM1->CCMR1|=1<<3;         //CH1Ԥװ��ʹ��	  
	TIM1->CCMR1|=1<<11;        //CH2Ԥװ��ʹ��	 
	TIM1->CCMR2|=1<<3;         //CH3Ԥװ��ʹ��	  
	TIM1->CCMR2|=1<<11;        //CH4Ԥװ��ʹ��	   
	TIM1->CCER|=1<<0;          //CH1���ʹ��	
	TIM1->CCER|=1<<6; //TIM1->CCER|=1<<4;         //CH2���ʹ��	 
	TIM1->CCER|=1<<10;//TIM1->CCER|=1<<8;          //CH3���ʹ��	
	TIM1->CCER|=1<<12;         //CH4���ʹ��	 
	TIM1->BDTR |= 1<<15;       //TIM1����Ҫ��仰�������PWM
	TIM1->CR1 |=1<<7;          //ARPEʹ�� 
	TIM1->CR1|=0x01;          //ʹ�ܶ�ʱ��1 											  
} 

/*
��������motor_run
��	�Σ�u8 left_right_direct ����, u8 Percentage ���ת������
����ֵ����
��	�ã������1��2�ǵ��1���������򣬷������3��4�ǵ��2���������򣬵���0ֹͣ
��	�ڣ�2019��1��26��
��	�ߣ�meetwit
*/
void motor_run(u8 left_right_direct, u8 Percentage){
	u16 temp,temp_N;
	
	if(Percentage>100){
		Percentage=100;
	}else if(Percentage>=10&&Percentage<=100){
		;
	}else if(Percentage>3&&Percentage<10){
		Percentage = 10;
	}else{
		Percentage=0;
	}
	
	temp=Percentage*PWMMAX/100;
	temp_N=PWMMAX-temp;
	
	switch (left_right_direct){
		case 0:
			PWMA1=0;
			PWMA2=0;
			PWMB1=0;
			PWMB2=0;
			break;
		case 4:
			PWMB1=PWMMAX;
			PWMB2=temp_N;
			break;
		case 1:
			PWMA1=temp_N;
			PWMA2=PWMMAX;
			break;
		case 3:
			PWMB1=temp_N;
			PWMB2=PWMMAX;
			break;
		case 2:
			PWMA1=PWMMAX;
			PWMA2=temp_N;
			break;
	}
}


/*
��������selfCorrecting
��	�Σ�u8 switchOne ѡ��һ�����,u8 type ���Ʒ�ʽ,s32 target Ŀ��ֵ
����ֵ����
��	�ã�switchOne���ڡ�l����ߵ�������ڡ�r���ұߵ����
				type����1��λ�ÿ��ƣ�
				target��Ŀ��ֵ��λ�ÿ���ʱ�Ǳ���������������6�������һȦ
��	�ڣ�2019��1��26��
��	�ߣ�meetwit
*/
void selfCorrecting(u8 switchOne,u8 type,s32 target){
	u8 temp=1;
	if(type==1){		//λ��
		if(target<0){
			target = -target;
			temp=2;
		}
		if(switchOne=='r'){
		temp=temp+2;
		}
		motor_run(temp,target/600);
	}
}

/**************************************************************************
�������ܣ�ֱ��PD����
��ڲ������Ƕȡ����ٶ�
����  ֵ��ֱ������PWM
**************************************************************************/
int balance_mw(float Angle,float Gyro)
{  
   static float Bias,kp = 3,kd = 0.2;
	 int pwm;
//   kp = m[0];
//   kd = m[2];
	 Bias=Angle-0;       //===���ƽ��ĽǶ���ֵ �ͻ�е���
	 pwm=kp*Bias+Gyro*kd;   //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� 
	 return pwm;
}


int velocity_mw(void)
{  
	static float Encoder_Integral = 0,Velocity = 0,encoder = 0;
	static float Velocity_Kp = 0.04,Velocity_Ki = 0.0002;
	int least = 0;
	
//	Velocity_Kp = m[3];
//	Velocity_Ki = m[4];
//		Flag_v = m[8];
		least = (leftEncoder+rightEncoder) - Flag_v;  
		leftEncoder = 0;
		rightEncoder = 0;
//		rt_kprintf("leftEncoder=%d,rightEncoder=%d,Encoder_Least=%d\r\n",leftEncoder,rightEncoder,least);
		encoder *= 0.8;		                                                //===һ�׵�ͨ�˲���       
		encoder += least*0.2;	                                    //===һ�׵�ͨ�˲���    
		Encoder_Integral +=encoder;                                       //===���ֳ�λ�� ����ʱ�䣺10ms
		Encoder_Integral=Encoder_Integral-0;                       //===����ң�������ݣ�����ǰ������
		if(Encoder_Integral>240000)  	Encoder_Integral=240000;             //===�����޷�
		if(Encoder_Integral<-240000)	Encoder_Integral=-240000;              //===�����޷�	
		Velocity=encoder*Velocity_Kp+Encoder_Integral*Velocity_Ki;   
		//rt_kprintf("encoder=%d,Encoder_Integral=%d,Velocity=%d\r\n",encoder,Encoder_Integral,Velocity);	   
//		printf("e=%f,EI=%f,V=%f\r\n",encoder,Encoder_Integral,Velocity);	  
		if(stop_flag||ctr_flag)   Encoder_Integral=0;      //===����رպ��������
	  return Velocity;
}


#include "main.h"
float stop_flag = 0,ctr_flag = 0,Flag_v = 0,Flag_turn = 0;
/*
函数名：PWM_Init_TIM1
传	参：u16 arr,u16 psc 频率
返回值：无
作	用：初始化定时器1的四路PWM输出
日	期：2019年1月26日
作	者：meetwit
*/
void PWM_Init_TIM1(u16 arr,u16 psc)
{		 					 
	RCC->APB2ENR|=1<<11;       //使能TIM1时钟    
	RCC->APB2ENR|=1<<2;        //PORTA时钟使能   
	RCC->APB2ENR|=1<<3;        //PORTB时钟使能     
	GPIOA->CRH&=0XFFFF0FF0;    //PORTA8 11复用输出
	GPIOA->CRH|=0X0000B00B;    //PORTA8 11复用输出  
	GPIOB->CRH&=0X00FFFFFF;    //PORTB14,B15复用输出
	GPIOB->CRH|=0XBB000000;    //PORT复用输出
	
	TIM1->ARR=arr;             //设定计数器自动重装值 
	TIM1->PSC=psc;             //预分频器不分频
	TIM1->CCMR1|=6<<4;         //CH1 PWM1模式	
	TIM1->CCMR1|=6<<12;        //CH2 PWM1模式	
	TIM1->CCMR2|=6<<4;         //CH3 PWM1模式	
	TIM1->CCMR2|=6<<12;        //CH4 PWM1模式	
	TIM1->CCMR1|=1<<3;         //CH1预装载使能	  
	TIM1->CCMR1|=1<<11;        //CH2预装载使能	 
	TIM1->CCMR2|=1<<3;         //CH3预装载使能	  
	TIM1->CCMR2|=1<<11;        //CH4预装载使能	   
	TIM1->CCER|=1<<0;          //CH1输出使能	
	TIM1->CCER|=1<<6; //TIM1->CCER|=1<<4;         //CH2输出使能	 
	TIM1->CCER|=1<<10;//TIM1->CCER|=1<<8;          //CH3输出使能	
	TIM1->CCER|=1<<12;         //CH4输出使能	 
	TIM1->BDTR |= 1<<15;       //TIM1必须要这句话才能输出PWM
	TIM1->CR1 |=1<<7;          //ARPE使能 
	TIM1->CR1|=0x01;          //使能定时器1 											  
} 

/*
函数名：motor_run
传	参：u8 left_right_direct 方向, u8 Percentage 电机转动功率
返回值：无
作	用：方向等1和2是电机1的正反方向，方向等于3和4是电机2的正反方向，等于0停止
日	期：2019年1月26日
作	者：meetwit
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
函数名：selfCorrecting
传	参：u8 switchOne 选择一个电机,u8 type 控制方式,s32 target 目标值
返回值：无
作	用：switchOne等于‘l’左边电机，等于‘r’右边电机，
				type等于1，位置控制；
				target是目标值，位置控制时是编码器的脉冲数，6万个数是一圈
日	期：2019年1月26日
作	者：meetwit
*/
void selfCorrecting(u8 switchOne,u8 type,s32 target){
	u8 temp=1;
	if(type==1){		//位置
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
函数功能：直立PD控制
入口参数：角度、角速度
返回  值：直立控制PWM
**************************************************************************/
int balance_mw(float Angle,float Gyro)
{  
   static float Bias,kp = 3,kd = 0.2;
	 int pwm;
//   kp = m[0];
//   kd = m[2];
	 Bias=Angle-0;       //===求出平衡的角度中值 和机械相关
	 pwm=kp*Bias+Gyro*kd;   //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
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
		encoder *= 0.8;		                                                //===一阶低通滤波器       
		encoder += least*0.2;	                                    //===一阶低通滤波器    
		Encoder_Integral +=encoder;                                       //===积分出位移 积分时间：10ms
		Encoder_Integral=Encoder_Integral-0;                       //===接收遥控器数据，控制前进后退
		if(Encoder_Integral>240000)  	Encoder_Integral=240000;             //===积分限幅
		if(Encoder_Integral<-240000)	Encoder_Integral=-240000;              //===积分限幅	
		Velocity=encoder*Velocity_Kp+Encoder_Integral*Velocity_Ki;   
		//rt_kprintf("encoder=%d,Encoder_Integral=%d,Velocity=%d\r\n",encoder,Encoder_Integral,Velocity);	   
//		printf("e=%f,EI=%f,V=%f\r\n",encoder,Encoder_Integral,Velocity);	  
		if(stop_flag||ctr_flag)   Encoder_Integral=0;      //===电机关闭后清除积分
	  return Velocity;
}


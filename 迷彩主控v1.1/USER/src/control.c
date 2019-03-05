#include "main.h"

#define PWM_CONST_VAL1 80			//左前
#define PWM_CONST_VAL1_1 80		//右前
#define PWM_CONST_VAL2 40			//左后
#define PWM_CONST_VAL2_2 70		//右后

u8 usmart_flag=0,urg_flag=0;

/************************************************************
函数名：void GPIO_Init(void);
形  参：void
返回值：无
功  能：初始化电机控制端口和指示灯控制端口
作  者：meetwit
时  间：2018年10月24日10:43:07
*************************************************************/
void GPIO_Init(void)
{    
	/*指示灯*/	
	RCC->AHB1ENR|=1<<7;//使能PORTH时钟 
	GPIO_Set(GPIOH,PIN2|PIN3|PIN4|PIN5|PIN6|PIN7,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); 
	
	/*电机控制端口*/	
	RCC->AHB1ENR|=1<<2;//使能PORTC时钟 
	RCC->AHB1ENR|=1<<4;//使能PORTE时钟 
	GPIO_Set(GPIOC,PIN10|PIN11,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);
	GPIO_Set(GPIOE,PIN3|PIN4,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); 

	GPIO_Initial_State();		//控制为初始状态，led关，电机不动
}

/************************************************************
函数名：void GPIO_Initial_State(void);
形  参：void
返回值：无
功  能：控制初始状态下电机停止，指示灯停止
作  者：meetwit
时  间：2018年10月24日10:36:14
*************************************************************/
void GPIO_Initial_State(void){
	LED1(1);
	LED2(1);
	LED3(1);
	LED4(1);
	LED5(1);
	LED6(1);
	
	front_motor(0,10);//无方向，停止，10%
	back_motor(0,10);//无方向，停止，10%
}

/************************************************************
函数名：void front_motor(u8 direction, u8 Percentage);
形  参：u8 direction 方向 0=停止，1=顺时针，2=逆时针, u8 Percentage %越大越快
返回值：无
功  能：控制髋前正反转，停止
作  者：meetwit
时  间：2018年10月24日10:36:14
*************************************************************/
void front_motor(u8 direction, u8 Percentage){
	u16 temp;
	temp=Percentage*PWMMAX/100;
	if(direction==1){//方向1,对着电机看 是顺时针
		M2_DI2(1);
		M2_DI3(0);
		M2_PWM_VAL=temp;
	}else if(direction==2){//方向2
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
函数名：void behind_motor(u8 direction, u8 Percentage);
形  参：u8 direction 方向 0=停止，1=顺时针，2=逆时针, u8 Percentage %越大越快
返回值：无
功  能：控制髋后正反转，停止
作  者：meetwit
时  间：2018年10月24日10:36:14
*************************************************************/
void back_motor(u8 direction, u8 Percentage){
	u16 temp;
	temp=Percentage*PWMMAX/100;
	if(direction==1){//方向1，顺时针
		M3_DI2(1);
		M3_DI3(0);
		M3_PWM_VAL=temp;
	}else if(direction==2){//方向2
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
函数名：void Emergency_stop(void);
形  参：void
返回值：无
功  能：髋前髋后电机停止，指示灯显示停止,不允许足底再控制
作  者：meetwit
时  间：2018年10月24日10:30:45
*************************************************************/
void Emergency_stop(){
	control_stop();
	urg_flag=0;
	//printf("stop");
}

/************************************************************
函数名：void control_stop(void);
形  参：void
返回值：无
功  能：髋前髋后电机停止，指示灯显示停止
作  者：meetwit
时  间：2018年10月24日10:30:45
*************************************************************/
void control_stop(void){
	LED1(0);
	LED2(0);
	LED3(1);
	LED4(1);
	LED5(1);
	LED6(1);
			
			front_motor(0,10);//无方向，停止，10%
			back_motor(0,10);//无方向，停止，10%

}

/************************************************************
函数名：void control_led2(void);
形  参：void
返回值：无
功  能：根据足底数据对指示灯进行控制
作  者：meetwit
时  间：2018年10月24日10:30:45
*************************************************************/
void control_led2(void){
			if(res2>2){
		//右脚髋前助力，电机A正转
			//right1=0;right2=1;
			LED5(0);LED6(1);
		}else if(res2<-2){
		//右脚髋后助力，电机B正转
			//right1=1;right2=0;
			LED5(1);LED6(0);
		}else{
		//stop
			//right1=0;right2=0;
			LED5(0);LED6(0);
		}

}

/************************************************************
函数名：void control_led3(void);
形  参：void
返回值：无
功  能：根据足底数据对指示灯进行控制
作  者：meetwit
时  间：2018年10月24日10:30:45
*************************************************************/
void control_led3(void){
			if(res3>2){
		//左脚髋前助力，电机A反转
			//left1=0;left2=1;
				LED3(0);LED4(1);
			
		}else if(res3	<-2){
		//左脚髋后助力，电机B反转
			//left1=1;left2=0;
			LED3(1);LED4(0);
		}else{
		//stop
			//left1=0;left2=0;
			LED3(0);LED4(0);
		}

}

/************************************************************
函数名：void control_motrol_front(void);
形  参：void
返回值：无
功  能：根据足底数据对髋前电机进行控制
作  者：meetwit
时  间：2018年10月24日10:30:05
*************************************************************/
void control_motor_front(void){
//			u8 if_First=0;
	if(res2>2&&res3<=2){
				front_motor(1,PWM_CONST_VAL1);//方向2，PWM=50%	Counter_clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else if(res3>2&&res2<=2){
				front_motor(2,PWM_CONST_VAL1_1);////方向1，PWM=50%	Clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else{	
				front_motor(0,10);//无方向，停止，10%
//				delay_ms(30);
//				if_First=1;
			}

}
void control_motor_front2(void){
//			u8 if_First=0;
	if(res2>2&&res3<=2){
				front_motor(2,PWM_CONST_VAL1);//方向2，PWM=50%	Counter_clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else if(res3>2&&res2<=2){
				front_motor(1,PWM_CONST_VAL1);////方向1，PWM=50%	Clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else{	
				front_motor(0,10);//无方向，停止，10%
//				if_First=1;
			}

}

/************************************************************
函数名：void control_motor_back(void);
形  参：void
返回值：无
功  能：根据足底数据对髋后电机进行控制
作  者：meetwit
时  间：2018年11月1日21:05:21
*************************************************************/
void control_motor_back(void){
//				u8 if_First=0;
	if(res2<-2&&res3>=-2){
				back_motor(1,PWM_CONST_VAL2);//方向2，PWM=50%	Counter_clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else if(res3<-2&&res2>=-2){
				back_motor(2,PWM_CONST_VAL2);////方向1，PWM=50%	Clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else{	
				back_motor(0,10);//无方向，停止，10%
//				if_First=1;
//				delay_ms(30);
			}

}

void control_motor_back2(void){
//				u8 if_First=0;
	if(res2<-2&&res3>=-2){
				back_motor(2,PWM_CONST_VAL2_2);//方向2，PWM=50%	Counter_clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else if(res3<-2&&res2>=-2){
				back_motor(1,PWM_CONST_VAL2);////方向1，PWM=50%	Clockwise_start2();
//				if(if_First){
//				delay_ms(100);
//					if_First=0;
//				}
			}else{	
				back_motor(0,10);//无方向，停止，10%
//				if_First=1;
			}

}

/************************************************************
函数名：void send_to_pc(void);
形  参：void
返回值：无
功  能：QT上位机显示数据发送，人体模型
作  者：meetwit
时  间：2018年12月1日21:25:51
*************************************************************/
void send_to_pc(void){
	if(res2>2){//右前
		PcTx_Byte(0x32);
	}else if(res3>2){//左前
		//for(u8 i;i<10;i++){
		PcTx_Byte(0x31);
		//}
		
	}else{
		//PcTx_Byte(0x35);
	}
	if(res2<-2){//右后
		PcTx_Byte(0x34);
	}else if(res3<-2){//左后
		PcTx_Byte(0x33);
	}else{
		//PcTx_Byte(0x36);
	}

	
}

/************************************************************
函数名：void send_to_pc(void);
形  参：void
返回值：无
功  能：QT上位机显示数据发送，当前电机转速
作  者：meetwit
时  间：2019年1月5日11:26:26
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

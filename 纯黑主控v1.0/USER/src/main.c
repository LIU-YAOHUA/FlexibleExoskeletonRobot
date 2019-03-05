#include "main.h"

int main(void)
{  
	u16 a,b;
	Stm32_Clock_Init(432,25,2,9);	//设置时钟,216Mhz
  delay_init(216);				//延时初始化  
	uart_init(108,19200);	//串口初始化为19200
	
	uart2_init(54,19200); 	//串口2初始化 
	uart3_init(54,19200); 	//串口3初始化 
	
	TIM1_PWM_Init(PWMMAX-1,216-1);
	//TIM4_Int_Init(timer_ms*10-1,10800-1);//10Khz频率,定时时间为timer_ms
	
	GPIO_Init();		 	//初始化电机控制引脚,指示灯控制引脚
	EXTIX_Init();         	//初始化按键、外部中断输入 
	
	
	
while(1)
	{
		//res2是左脚的数据，res3是右脚的数据
		a++;
		if(res2==0x79&&res3==0x79){//根据陀螺仪，左右脚没有速度，停止
					control_stop();			
					PcTx_Byte(0x30);
					delay_ms(50);
				}else{		//不是双脚站立停止状态，对系统进行控制
//					LED1(1);
//					LED2(1);
					if(res2==0x79){//左脚没有速度		
						res2=0;		//消掉imu的数据
					}
					
					if(res3==0x79){//右脚没有速度
						res3=0;		//消掉imu的数据
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




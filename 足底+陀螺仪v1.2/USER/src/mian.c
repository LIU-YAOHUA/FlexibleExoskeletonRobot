#include "stm32f10x.h"
#include "tim2.h"
#include "adc.h"
#include "delay.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "stdio.h" 

/*
陀螺仪配置
波特率 		115200
安装方式		垂直
回传速率		10HZ
超时时间设置为20ms < 100ms（10HZ）

连接串口2配置陀螺仪的时候 注意 将串口引脚设置为浮空输入
			usart2.c 第35行
*/


int main(){
	
	s8 P_value;
	u16 a3,a4,a5,a6,a7,a8;
	s32 P_Result;
	
Stm32_Clock_Init(9);	//系统时钟设置	
	
	/*定时器2初始化*/
	init_tim2();
	
	/*串口1初始化，波特率为9600*/
	usart_init(115200);			//暂时去掉串口1，串口1作为监控
	
	/*串口2初始化，波特率为9600*/
	usart2_init(115200);			//串口2作为陀螺仪
	
	/*串口3初始化，波特率为9600*/
	usart3_init(19200);			//串口3无线连接
	
	
	
	delay_init(72);					//延时函数初始化
	Adc_Init();							//PA1,开启ADC通道一
	
	while(1){
		
		/*接收到数据原样返回*/
		/*收到open close对灯进行开关*/
		
		//Task_Pc();
		Task_Pc2();
		//Task_Pc3();
		if(send_flag>=5){
		a8=Get_Adc(ADC_CH4);		//12位
		a7=Get_Adc(ADC_CH5);
		a6=Get_Adc(ADC_CH6);
		a5=Get_Adc(ADC_CH7);
		a4=Get_Adc(ADC_CH8);
		a3=Get_Adc(ADC_CH9);
		//a2=Get_Adc(ADC_CH10);
		//a1=Get_Adc(ADC_CH11);
		P_Result=(a3+a7+a8)-(a4+a5+a6);		//小于16位 65536
		//printf("\r\nR%4d\r\n",P_Result);
		P_value=P_Result/256;		//将脚尖区域减去脚跟区域的结果除以256，65536缩放在0-255之间
			if((P_value>=120)&&(P_value<=127)){		//抠出121-127这七个数作为其他标志位，例如是否有速度
			P_value=120;
			}
			if(is_xspeed){		//脚没有速度
				P_value=121;		//覆盖压力值，不给压力值输出
			}
		PcTx_Byte3(P_value);	
			printf("%d  %d  %d  %d  %d  %d\r\n",a3,a4,a5,a6,a7,a8);
		send_flag=0;
		}
	}

}








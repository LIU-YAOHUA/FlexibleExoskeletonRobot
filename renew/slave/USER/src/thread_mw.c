#include "main.h"

double usart1_m[REC_LEN1]={0};
char s1[REC_LEN1]={'q','w','e','r','t','y','u','i','o','p'};

struct IMU			stcIMU={0};												//对外调用该结构体即可
struct IMU			stcIMU_history[3]={0};						//对外调用该结构体即可

double usart3_m[REC_LEN3]={0};
char s3[REC_LEN3]={'z','x','c','v','b','n','m','j','k','l'};

int32_t hx711_num=0; 
float hx711_N=0;

/*
线	程：sendData
作	用：slave -> master
频	率：
日	期：
作	者：meetwit
*/
void sendData(void* parameter){
	rt_kprintf("hello\r\n");
	rt_thread_delay(10);
}

/*
线	程：
作	用：
频	率：
日	期：
作	者：meetwit
*/
void read_hx711(void* parameter){
	
	hx711_num=ReadCount();
	hx711_N = hx711_num*50/8388608.0*2.55*9.8-1249.5;
	rt_thread_delay(1);
}


/*
线	程：time_thread
作	用：通过串口1打印系统时间
频	率：1Hz
日	期：2019年1月26日
作	者：meetwit
*/
void time_thread(void* parameter){
	rt_tick_t tick_temp;
  rt_uint8_t h=0,m=0,s=0;
	
	while(1){
		tick_temp = rt_tick_get();
		s=tick_temp/RT_TICK_PER_SECOND%60;
		m=tick_temp/RT_TICK_PER_SECOND/60%60;
		h=tick_temp/RT_TICK_PER_SECOND/60/60%24;
		rt_kprintf("\r\nThe system runtime is %d:%d:%d.%d\r\n",h,m,s,tick_temp%RT_TICK_PER_SECOND);
		
		rt_thread_delay(RT_TICK_PER_SECOND);
	}
	
}


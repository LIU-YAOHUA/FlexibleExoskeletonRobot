#include "main.h"

/*
usart1 debug	460800
usart2 imu	115200
usart3 wifi	460800
*/


rt_thread_t tid1=RT_NULL;
rt_thread_t tid2=RT_NULL;
rt_thread_t tid3=RT_NULL;
rt_thread_t tid_time=RT_NULL;


int main(){
	rt_kprintf("\r\n\r\nmeetwit rtt systerm start init!\r\n\r\n");
	
	tid1=rt_thread_create("sendData",sendData,RT_NULL,256,5,100);
	rt_thread_startup(tid1);
	
	tid2=rt_thread_create("read_hx711",read_hx711,RT_NULL,256,6,100);
	rt_thread_startup(tid2);

//	tid3=rt_thread_create("f3",f3,RT_NULL,1024,4,100);
//	rt_thread_startup(tid3);

//	tid_time=rt_thread_create("tid_time",time_thread,RT_NULL,512,7,10);
//	rt_thread_startup(tid_time);
	
	rt_kprintf("meetwit rtt systerm started!\r\n\r\n");
	
	return 0;
}








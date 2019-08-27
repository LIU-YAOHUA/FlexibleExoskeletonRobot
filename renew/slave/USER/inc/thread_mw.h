#ifndef __THREAD_MW_H
#define __THREAD_MW_H
#include "main.h"

#define REC_LEN1 10
#define REC_LEN3 10

extern double usart1_m[REC_LEN1];
extern char s1[REC_LEN1];

extern struct IMU			stcIMU;												//对外调用该结构体即可
extern struct IMU			stcIMU_history[3];

extern double usart3_m[REC_LEN3];
extern char s3[REC_LEN3];

extern int32_t hx711_num; 
extern float hx711_N;

void sendData(void* parameter);
void read_hx711(void* parameter);
void time_thread(void* parameter);

#endif

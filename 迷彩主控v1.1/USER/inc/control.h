#ifndef __CONTROL_MT_H
#define __CONTROL_MT_H	 
#include "main.h" 

//LED端口定义
#define LED1(x)			GPIO_Pin_Set(GPIOH,PIN2,x)
#define LED2(x)			GPIO_Pin_Set(GPIOH,PIN3,x)	
#define LED3(x)			GPIO_Pin_Set(GPIOH,PIN4,x)
#define LED4(x)			GPIO_Pin_Set(GPIOH,PIN5,x)	
#define LED5(x)			GPIO_Pin_Set(GPIOH,PIN6,x)
#define LED6(x)			GPIO_Pin_Set(GPIOH,PIN7,x)	

//GPIO端口定义
#define M2_DI2(x)			GPIO_Pin_Set(GPIOC,PIN10,x)
#define M2_DI3(x)			GPIO_Pin_Set(GPIOC,PIN11,x)	

#define M3_DI2(x)			GPIO_Pin_Set(GPIOE,PIN3,x)
#define M3_DI3(x)			GPIO_Pin_Set(GPIOE,PIN4,x)	

extern 	u8 usmart_flag,urg_flag;

void GPIO_Init(void);

void GPIO_Initial_State(void);

void front_motor(u8 direction, u8 Percentage);

void back_motor(u8 direction, u8 Percentage);

void Emergency_stop(void);

void control_stop(void);

void control_led2(void);

void control_led3(void);

void control_motor_front(void);

void control_motor_back(void);

void control_motor_front2(void);

void control_motor_back2(void);

void send_to_pc(void);

void send_to_pc2(void);

#endif


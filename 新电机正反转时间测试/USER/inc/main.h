#ifndef __MAIN_MW_H
#define __MAIN_MW_H	 

#include "stdint.h"
#include "string.h"
#include "stdio.h"

#include "control.h"

#include "delay.h" 
#include "sys.h"
#include "usart.h" 

#include "exti.h"
#include "pwm.h"
#include "usart2.h"
#include "usart3.h"
#include "timer.h"

	#define PWMMAX 500	//
/*****
由于keil中将F4关于u8 s8 等定义删除，所以应该在stdint.h中添加如下定义

edit by meetwit 

typedef   signed          char s8;
typedef   signed short     int s16;
typedef   signed           int s32;
typedef   signed       __INT64 s64;

typedef unsigned          char u8;
typedef unsigned short     int u16;
typedef unsigned           int u32;
typedef unsigned       __INT64 u64;

*****/


#endif


















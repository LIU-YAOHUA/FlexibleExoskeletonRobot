#ifndef __PWM_MT_H
#define __PWM_MT_H
#include "main.h"

//通过改变TIM1->CCR1的值来改变占空比
//通过改变TIM1->CCR2的值来改变占空比
#define M2_PWM_VAL TIM1->CCR1    
#define M3_PWM_VAL TIM1->CCR2  

void TIM1_PWM_Init(u32 arr,u32 psc);

#endif
























#ifndef __PWM_MT_H
#define __PWM_MT_H
#include "main.h"

//ͨ���ı�TIM1->CCR1��ֵ���ı�ռ�ձ�
//ͨ���ı�TIM1->CCR2��ֵ���ı�ռ�ձ�
#define M2_PWM_VAL TIM1->CCR1    
#define M3_PWM_VAL TIM1->CCR2  

void TIM1_PWM_Init(u32 arr,u32 psc);

#endif
























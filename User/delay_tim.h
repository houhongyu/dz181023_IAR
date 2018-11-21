/* Define to prevent recursive inclusion -------------------------------------*/
/********************************************************
File name: Delay_Timer.h
Author:
Version:
Date:       2018-3-29
Description: 定义（声明）Delay_Timer.c文件中所用到的函数
             (延时函数)
Others: 
Function List: 
**********************************************************/

#ifndef __DELAY_TIM_H
#define __DELAY_TIM_H

void Delay_Timer_Decrement(void);
void Delay_Timer(u32 nCount); 
void Delay_Timer_Init(void);    // 定时器TIM3初始化

#endif    /* __DELAY_TIMER_H */















/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
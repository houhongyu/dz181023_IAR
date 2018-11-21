/* Private function prototypes ----------------------------------*/
/********************************************************
File name: timers.h
Author:
Date:       2018-3-29
Description: 
Function List: 
**********************************************************/

#ifndef __TIMERS_H
#define	__TIMERS_H
  

extern void SYS_config(void);     //系统时钟的配置
extern void GPIO_Config(void);
extern void TIM2_Config(void);
//extern void TDP_TIM2_Init();  
extern void Voltage_TIM2_Init(void);
extern void TIM1_Config(void);
extern void CON_TIM1_Init(void);
extern void CaptureConfig(void);
extern void pink_data();   
//extern void delay(u32 ncount);
#endif    /*  __TIMERS_H */












/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
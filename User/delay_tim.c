
#include "stm8l15x.h"
#include "stm8l15x_exti.h"
#include "delay_tim.h"

static u32 TimingDelay;

/***************************************************************
* 名称：void Delay_Timer_Decrement(void)
* 功能：获取节拍程序
* 入口参数：无
* 出口参数：无
****************************************************************/ 
void Delay_Timer_Decrement(void) 
{    
  if(TimingDelay!= 0x00)    
  {     
    TimingDelay--;    
  }    
}    


/**************************************************************
* 名 称：Delay_Timer(u32 nCount)
* 功 能：定时延时程序 1 ms为单位
* 入口参数：无
* 出口参数：无
***************************************************************/
void Delay_Timer(u32 nCount)
{    
  TimingDelay = nCount;    
    
  while(TimingDelay!= 0);    
}    


/**************************************************************
* 名 称：Delay_Timer_Init(void)
* 功 能：定时器初始化（计数周期为50us）
* 入口参数：无
* 出口参数：无
**************************************************************/
void Delay_Timer_Init(void)    
{    
  //时钟配置    
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4,ENABLE);   
  
  TIM4_DeInit();    
  TIM4_TimeBaseInit(TIM4_Prescaler_8,99);   //测得TIM4定时器时钟源频率为16MHz,经过8分频后为2MHz，只能向上计数，
                                            //计数频率为（99+1）/2MHz=50us。                          
  //TIM4_ClearFlag(TIM4_FLAG_Update);
  TIM4_ARRPreloadConfig(ENABLE);    
  TIM4_ITConfig(TIM4_IT_Update, ENABLE);    
  TIM4_Cmd(ENABLE);    
}   



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
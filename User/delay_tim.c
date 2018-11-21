
#include "stm8l15x.h"
#include "stm8l15x_exti.h"
#include "delay_tim.h"

static u32 TimingDelay;

/***************************************************************
* ���ƣ�void Delay_Timer_Decrement(void)
* ���ܣ���ȡ���ĳ���
* ��ڲ�������
* ���ڲ�������
****************************************************************/ 
void Delay_Timer_Decrement(void) 
{    
  if(TimingDelay!= 0x00)    
  {     
    TimingDelay--;    
  }    
}    


/**************************************************************
* �� �ƣ�Delay_Timer(u32 nCount)
* �� �ܣ���ʱ��ʱ���� 1 msΪ��λ
* ��ڲ�������
* ���ڲ�������
***************************************************************/
void Delay_Timer(u32 nCount)
{    
  TimingDelay = nCount;    
    
  while(TimingDelay!= 0);    
}    


/**************************************************************
* �� �ƣ�Delay_Timer_Init(void)
* �� �ܣ���ʱ����ʼ������������Ϊ50us��
* ��ڲ�������
* ���ڲ�������
**************************************************************/
void Delay_Timer_Init(void)    
{    
  //ʱ������    
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4,ENABLE);   
  
  TIM4_DeInit();    
  TIM4_TimeBaseInit(TIM4_Prescaler_8,99);   //���TIM4��ʱ��ʱ��ԴƵ��Ϊ16MHz,����8��Ƶ��Ϊ2MHz��ֻ�����ϼ�����
                                            //����Ƶ��Ϊ��99+1��/2MHz=50us��                          
  //TIM4_ClearFlag(TIM4_FLAG_Update);
  TIM4_ARRPreloadConfig(ENABLE);    
  TIM4_ITConfig(TIM4_IT_Update, ENABLE);    
  TIM4_Cmd(ENABLE);    
}   



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
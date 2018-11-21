/******************** (C) COPYRIGHT 2018 chongyou-hou *************************
* 文件名  ：mian.c
* 描述    ：实现不同脉宽
* 日期    :2018-3-29
* 作者    ：
******************************************************************************/

#include "stm8l15x.h"
#include "stm8l15x_exti.h"
#include "timers.h"
#include "delay_tim.h"

unsigned int temp;
unsigned int flag;
unsigned int _it1=0; 
//unsigned int CCR1_Val=1000;
extern float y[];
void Voltage_TIM2_Init(void);
void TIM2_Config(void);
void CON_TIM1_Init(void);
void CaptureConfig(void);
void pink_data(void); 
void delay(int);

/***********主函数*****************/
void main(void)
{
  //unsigned char a=0;
  disableInterrupts();                //中断失能
  SYS_config();                       //初始化时钟
  GPIO_Config();                  //  I/O口初始化配置
 // TIM1_Config();
  TIM2_Config(); 
  
  enableInterrupts();                //使能中断
  Voltage_TIM2_Init();        //电压控制 
  Delay_Timer_Init();
  
  Delay_Timer(5000);
 
   GPIO_SetBits(GPIOB, GPIO_Pin_0);
   GPIO_ResetBits(GPIOE, GPIO_Pin_1);
   GPIO_ResetBits(GPIOE, GPIO_Pin_2);
 
   Delay_Timer(1000);
   GPIO_ResetBits(GPIOE, GPIO_Pin_2); 
    
   while(1)
    {
      GPIO_SetBits(GPIOE, GPIO_Pin_1); 
      Delay_Timer(10);
      
      GPIO_ResetBits(GPIOE, GPIO_Pin_1); 
      GPIO_SetBits(GPIOE, GPIO_Pin_2);  
      Delay_Timer(10);
      GPIO_ResetBits(GPIOE, GPIO_Pin_2); 
      
      Delay_Timer(150);
      
    }
    //Delay_Timer(50);
   // GPIO_SetBits(GPIOE, GPIO_Pin_1);
    //Delay_Timer(10);
    //GPIO_ResetBits(GPIOE, GPIO_Pin_1);
   // Delay_Timer(50);
  //}
}




  //GPIO_SetBits(GPIOD, GPIO_Pin_7); 
  /*while(1)  
   {  
       Delay_Timer(50);
       TIM1_OC2Init(TIM1_OCMode_PWM2, 
               TIM1_OutputState_Enable,
               TIM1_OutputNState_Disable,
               CCR1_Val, 
               TIM1_OCPolarity_Low,
               TIM1_OCNPolarity_Low,
               TIM1_OCIdleState_Set,
               TIM1_OCNIdleState_Set);
   TIM1_OC2PreloadConfig(ENABLE);
  
   //CCR1_Val=(int)z[i];
  // i++;
   //if(i>=10000)
   // {
    //  i=0;
    //}
   /* if(a==0) 
	CCR1_Val=CCR1_Val+1000;										 
    else 
	CCR1_Val=CCR1_Val-1000;
	if(CCR1_Val>10000)
          {
	     CCR1_Val=10000; a=1;
          } 							  
        else if(CCR1_Val<1000)
        { 
	   CCR1_Val=1000; a=0;
	} * /
  
   // if((flag==1)&&(temp<TIM3_GetCounter()&&(temp+20)>TIM3_GetCounter()))
   // {
       //GPIO_ResetBits(GPIOD, GPIO_Pin_2);
       //flag=0;
       //temp=0;
       //TIM3_SetCounter(0);
   // }    
*/
void delay(int Count)
{
  while(--Count > 0);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
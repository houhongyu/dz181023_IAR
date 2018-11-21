/* Private function prototypes -----------------------------------------------*/

#include "stm8l15x.h"
#include "stm8l15x_it.h"
#include "timers.h"

#define TIM2_PERIOD              1600    //计数值（周期）
#define TIM1_PERIOD              40000     //计数值（周期）
#define TIM1_Prescaler               0   //分频TIM1 counter clock = TIM1CLK / TIM1_PRESCALER+0 = 2 MHz/1+0 = 2MHz
#define TIM1_ReprtitionCounter      0
unsigned int CCR2_Val=0;             //PWM0-脉宽值（Pluse）
extern unsigned int CCR1_Val=2000;          //CON_1-脉宽值（Pluse）
//unsigned int CCR1_Val=0;           //CON_2-脉宽值（Pluse）

/**********************系统时钟的配置*************************/
void SYS_config(void)
{ 
    CLK_SYSCLKSourceSwitchCmd(ENABLE);                  //时钟使能
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);       //内部高速时钟，16MHZ
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);             //1分频，系统时钟，16MHZ   
}

/**
  * @brief  Configure TIM Channels GPIO 
  * @param  None
  * @retval None
  */


/************************* I/O初始化********************************/
void GPIO_Config(void)
{
  //GPIO_Init(GPIOB,GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Fast);    //PWM1---过流控制
  GPIO_Init(GPIOB,GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Fast);    //PWM0---TIM2(chanal-2)--升压控制
  GPIO_Init(GPIOC,GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Fast);   
  GPIO_Init(GPIOE,GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Fast);   
  //GPIO_Init(GPIOD,GPIO_Pin_0, GPIO_Mode_In_FL_No_IT);     //CON_1  脉冲输入捕获（TIM3-channel 2）
  GPIO_Init(GPIOD,GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Fast);     //CON_1  脉冲控制（TIM1-channel-2）
  GPIO_Init(GPIOE,GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Fast);    //CON_2   脉冲控制
}


/********************定时器2配置*********************************/
void TIM2_Config(void)
{
   CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
   
   TIM2_TimeBaseInit(TIM2_Prescaler_1, TIM2_CounterMode_Up, TIM2_PERIOD);

   TIM2_OC2PreloadConfig(ENABLE);

   TIM2_ARRPreloadConfig(ENABLE);
   //TIM1_ITConfig(TIM1_IT_CC2, ENABLE);
   enableInterrupts();
   
  /* Enable TIM1 outputs */
   TIM2_CtrlPWMOutputs(ENABLE);
  /* TIM1 enable counter */
  //TIM1_Cmd(ENABLE);
   
}

//定时器2初始化，升压控制--PWM0
void Voltage_TIM2_Init(void)
{
  CCR2_Val=960;
  TIM2_OC2Init(TIM2_OCMode_PWM2, 
               TIM2_OutputState_Enable,       
               CCR2_Val, 
               TIM2_OCPolarity_Low,
               TIM2_OCIdleState_Set);
  //TIM1_OC1PreloadConfig(ENABLE);
  TIM2_Cmd(ENABLE);
}

/********************定时器1配置***************************/
void TIM1_Config(void)
{
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, ENABLE);
  TIM1_TimeBaseInit(TIM1_Prescaler, TIM1_CounterMode_Up, TIM1_PERIOD,TIM1_ReprtitionCounter);
  //TIM1_OC1PreloadConfig(ENABLE);
  TIM1_OC2PreloadConfig(ENABLE);
  TIM1_ARRPreloadConfig(ENABLE);
  enableInterrupts();
  TIM1_CtrlPWMOutputs(ENABLE);
  //TIM1_Cmd(ENABLE);
}

/*****脉冲控制CON_1,产生占空比可变的PWM波*****/
void CON_TIM1_Init(void)
{
  //CCR1_Val=i;
  //CCR2_Val=j;
  // TIM1-channel_1
  TIM1_OC2Init(TIM1_OCMode_PWM2, 
               TIM1_OutputState_Enable,
               TIM1_OutputNState_Disable,
               CCR1_Val, 
               TIM1_OCPolarity_Low,
               TIM1_OCNPolarity_Low,
               TIM1_OCIdleState_Set,
               TIM1_OCNIdleState_Set);
  
  // TIM1-channel_2
  //TIM1_OC2Init(TIM1_OCMode_PWM1, 
               //TIM1_OutputState_Enable,
               //TIM1_OutputNState_Disable,
               //CCR2_Val, 
               //TIM1_OCPolarity_Low,
              // TIM1_OCNPolarity_Low,
               //TIM1_OCIdleState_Set,
               //TIM1_OCNIdleState_Set);
 
  TIM1_Cmd(ENABLE);
}


//捕获--定时器3-2（TIM3-2）
void CaptureConfig(void)
{
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, ENABLE);  //时钟使能
  TIM3_DeInit();  
  //通道1（IC1单元）,通道2（IC2单元），将IC1和IC2映射到通道2，IC1上升沿捕获
  TIM3_PWMIConfig(TIM3_Channel_1,
                  TIM3_ICPolarity_Rising,
                  TIM3_ICSelection_IndirectTI,
                  TIM3_ICPSC_DIV1,
                  0);
  TIM3_SelectInputTrigger(TIM3_TRGSelection_TI2FP2);       //将IC2(通道2）作为触发源
  TIM3_SelectSlaveMode(TIM3_SlaveMode_Reset);  //从模式
  TIM3_SelectMasterSlaveMode(ENABLE);
  enableInterrupts();
  TIM3_Cmd(ENABLE);      //使能定时器3
  TIM3_ITConfig(TIM3_IT_CC1, ENABLE);   //允许捕获单元1
  TIM3_ITConfig(TIM3_IT_CC2, ENABLE);   //允许捕获单元2
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
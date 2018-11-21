/* Private function prototypes -----------------------------------------------*/
#include "stm8l15x.h"
#include "stm8l15x_it.h"
#include "timers.h"
#include <stdio.h>
#include <stdlib.h>

#define N  10000
#define P  100

float x[N];
float y[N];
int z[N];
/*void print_array_to_file(FILE *fp, const float *x, int n)
{
    int i;
    for (i = 0; i < n; i++)
        fprintf(fp, "%.15f\n", x[i]);
}*/

//  产生white_noise
void white_noise(float *x, int n)
{
    int i;
    //srand((unsigned)time(NULL));        //time()获取系统时间的函数，需要配置RTC实时时钟。
    for (i = 0; i < n; i++)
          x[i] = rand() % 801+ 200;    //产生200-1000之间的随机数(Y=1000,X=200), rand()%(Y-X+1)+X
}

//滤波系数产生
void invfreq_coeffs(float* coeffs, float alpha, int n)
{
    float a = -alpha / 2.0f;
    coeffs[0] = a;
    int i;
    for (i = 1; i < n; i++)
        coeffs[i] = coeffs[i-1] / (i+1) * (i+a);
}


float allpole_filter(float  x,                                            // Input signal
                      const float *a,                                    // Feedback coefficients
                      float *s,                                            // Delayline
                      int  p)                                               // Number of coefficients
{
    float y = x;
    int     i;
    for (i = 0; i < p; i++)
           y -= a[i] * s[i];
    for (i = p - 1; i > 0; i--)
          s[i] = s[i-1];
          s[0] = y;
    return y;
}

// 产生pink_noise
void pinknoise(const float *x,                     // Input signal
                float *y,                            // Output signal
                const float *a,                     // Feedback coefficients
                float *s,                             // Delayline
                int  n,                             // Sample points
                int  p)                            // Number of coefficients
{
    int i;
    for(i = 0; i < n; i++)
          y[i] = allpole_filter(x[i], a, s, p)/10-400;  //对相应的数据做出调整,此处x=400
      if(y[i]<0)
         z[i]=(int)(y[i]+400);     //使得到的负数转化成整数
      else
         z[i]=(int)y[i];
}

void pink_data(void)
{
     // 1. Generate white noise signal.
    white_noise(x, N);

    // 2. Generate pink noise filter coefficients.
    float coeffs[P];
    float alpha = 1.0f;
    float s[P];
    int i;
    for (i = 0; i < P; i++)
           s[i] = 0.0f;
           invfreq_coeffs(coeffs, alpha, P);

    // 3. Get pink noise signal by filtering the white noise signal.
    pinknoise(x, y, coeffs, s, N, P);    

   //return 0;
}

void PWM_CON(float *y)
{
  //float z=y;
  //int i=0;
  //int j=0;
  //while(1)
 //{
   // CON_TIM1_Init(CCR1_Val,CCR2_Val);
   // CCR1_Val=z[i];
   // CCR2_Val=z[i];
   // i++;
    
  //}
  
  
  
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
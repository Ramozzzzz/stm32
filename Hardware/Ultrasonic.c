#include "stm32f10x.h"
#include "Delay.h"

#define Trig GPIO_Pin_14
#define Echo GPIO_Pin_13

uint64_t time_now;
uint64_t time_end;


void Ultrasonic_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin=Echo;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin=Trig;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}

int32_t Ultrasonic_Measure()
{
   int32_t Distance;
    GPIO_WriteBit(GPIOB,Trig,1);
    Delay_us(15);
    GPIO_WriteBit(GPIOB,Trig,0);
    while(GPIO_ReadInputDataBit(GPIOB,Echo)==0);
    time_now=0;
    while(GPIO_ReadInputDataBit(GPIOB,Echo)==1);
    time_end=time_now;
    if(time_end/100<66){
        Distance=(time_end*343)/2;
        Distance/=100;
    }

    return Distance;
}

void TIM3_IRQHandler(void)			//更新中断函数
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)		//获取TIM3定时器的更新中断标志位
	{
		time_now++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);			//清除更新中断标志位
	}
}

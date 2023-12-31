#include "stm32f10x.h"
#include "PWM.h"

void Motor_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    PWM_Init();
}

void Motor_SpeedSet(int16_t speed, uint8_t select)
{
    if(speed<0){
       
        if(select==3){
            GPIO_SetBits(GPIOA,GPIO_Pin_4);
            GPIO_ResetBits(GPIOA,GPIO_Pin_5);
            PWM_SetCCR(-speed,3);
        }
            
        else if(select==4){
            GPIO_SetBits(GPIOA,GPIO_Pin_7);
            GPIO_ResetBits(GPIOA,GPIO_Pin_6);
            PWM_SetCCR(-speed,4);
        }
    }
    else{
        if(select==3){
            GPIO_SetBits(GPIOA,GPIO_Pin_5);
            GPIO_ResetBits(GPIOA,GPIO_Pin_4);
            PWM_SetCCR(speed,3);
        }
            
        else if(select==4){
            GPIO_SetBits(GPIOA,GPIO_Pin_6);
            GPIO_ResetBits(GPIOA,GPIO_Pin_7);
            PWM_SetCCR(speed,4);
        }
    }
}

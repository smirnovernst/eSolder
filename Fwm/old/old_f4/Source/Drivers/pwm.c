/*
*@File      pwm.c 
*@Author    EricMarina
*@Version   
*@Date      04.07.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "pwm.h"
/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* Functions
*/

void pwm_init(TIM_TypeDef *tim,uint32_t freq, uint32_t timBusFreq, uint16_t timBusPSC)
{
    tim->ARR = (timBusFreq/timBusPSC)  / freq;
    tim->PSC = timBusPSC - 1; 
    tim->CR1 |= TIM_CR1_CEN;                                
}

void pwm_channelInit(pwmChannel_t *pwmChannel, GPIO_TypeDef *port, uint8_t pin)
{
#if 0
    //@TODO: need release for stm32f4
    GPIO_Init(port, pin, GPIO_Mode_AlternateFunctionOutputPushPull);
    
    switch (pwmChannel->channel)
    {
        case 1: 
            pwmChannel->tim->CCMR1   |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;   
            pwmChannel->tim->CCER    |= TIM_CCER_CC1E;
            break;
        case 2:
            pwmChannel->tim->CCMR1   |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
            pwmChannel->tim->CCER    |= TIM_CCER_CC2E;
            break;
        case 3: 
            pwmChannel->tim->CCMR2   |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
            pwmChannel->tim->CCER    |= TIM_CCER_CC3E;
            break;
        case 4: 
            pwmChannel->tim->CCMR2   |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
            pwmChannel->tim->CCER    |= TIM_CCER_CC4E;
            break;
        break;
    }
    pwm_dutySet(pwmChannel, 0);
#endif
}

void pwm_dutySet(pwmChannel_t *pwmCh, float duty)
{
    float ccr_calc = pwmCh->tim->ARR * duty / 100;
    switch (pwmCh->channel)
    {
        case 1: 
            pwmCh->tim->CCR1 = (uint32_t)ccr_calc;
            break;
        case 2:
            pwmCh->tim->CCR2 = (uint32_t)ccr_calc;
            break;
        case 3: 
            pwmCh->tim->CCR3 = (uint32_t)ccr_calc;
            break;
        case 4: 
            pwmCh->tim->CCR4 = (uint32_t)ccr_calc;
            break;
        break;
    }
}
void pwm_channelEnable(pwmChannel_t *pwmChannel, pwmChEnable_t enable)
{
    if (enable == pwmChEnable_ON)
    {
        switch (pwmChannel->channel)
        {
            case 1: 
                pwmChannel->tim->CCER    |= TIM_CCER_CC1E;
                break;
            case 2:
                pwmChannel->tim->CCER    |= TIM_CCER_CC2E;
                break;
            case 3: 
                pwmChannel->tim->CCER    |= TIM_CCER_CC3E;
                break;
            case 4: 
                pwmChannel->tim->CCER    |= TIM_CCER_CC4E;
                break;
            break;
        }
        return;
    }
    else
    {
        switch (pwmChannel->channel)
        {
            case 1: 
                pwmChannel->tim->CCER    &= ~TIM_CCER_CC1E;
                break;
            case 2:
                pwmChannel->tim->CCER    &= ~TIM_CCER_CC2E;
                break;
            case 3: 
                pwmChannel->tim->CCER    &= ~TIM_CCER_CC3E;
                break;
            case 4: 
                pwmChannel->tim->CCER    &= ~TIM_CCER_CC4E;
                break;
            break;
        }
         
    }
    
}
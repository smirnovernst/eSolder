/*
*@File      clock.c 
*@Author    EricMarina
*@Version   
*@Date      09.05.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "clock.h"
/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* Functions
*/


uint32_t CoreClock_Init()
{
    RCC->CR |= RCC_CR_HSEON;
    while (!READ_BIT( RCC->CR, RCC_CR_HSERDY))
    {
        asm("nop");
    }
    RCC->CFGR |= RCC_CFGR_PLLSRC;
    RCC->CFGR |= RCC_CFGR_PPRE1_2;
    RCC->CFGR |= RCC_CFGR_PLLXTPRE;
    RCC->CFGR |= RCC_CFGR_PLLMULL_2; //freq x6
    
    RCC->CR |= RCC_CR_PLLON;
    while (!READ_BIT( RCC->CR, RCC_CR_PLLRDY))
    {
        asm("nop");
    }
    
    FLASH->ACR |= FLASH_ACR_LATENCY_2;
    
    RCC->CFGR |= RCC_CFGR_SW_1;

  return 0;
}

void PeriphClock_Init(void)
{
     RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN |
                      RCC_APB2ENR_IOPBEN |
                      RCC_APB2ENR_IOPCEN |
                      RCC_APB2ENR_IOPDEN |
                      RCC_APB2ENR_AFIOEN;
     
     RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
     RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
     RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
}
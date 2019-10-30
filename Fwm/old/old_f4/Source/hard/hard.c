/*
*@File          hard.c
*@Author        Ernst
*@Version       
*@Date          20.08.2018
*@Breif         
*/
/*!****************************************************************************
* Include
*/
#include "hard.h"

#include "encoders.h"
#include "GPIO.h"
#include "regulator.h"
/*!****************************************************************************
* Memory
*/
/*!****************************************************************************
* Functions
*/
void hard_init()
{
    SystemInit();
    SystemCoreClockUpdate();
    // ====== INIT RCC ====== //
    RCC->AHB1RSTR = 0xFFFFFFFF;	
    RCC->AHB1RSTR = 0;
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
    
    // ============================ //

    regulatorInit();
    
    // ====== init debug pins ====== //
    gpioInit(GPIOC, 0, gpioMode_OUT, gpioPuPd_NOPULL, gpioType_PUSHPULL, 0, 1);
  
    // ============================ //
    
    #if 0
        //@TODO: NEED RELEASE FOR STM32F4
        encoders_init();
        ili9341_Init();
        pwm_init(TIM5, 5000, APB1_TIM_FREQUENCY, 2); //PWM for lcd backlight and dry fan
        lcdBacklight_init();
        dryFan_init();
        keyboardInit();
    #endif
}

/*
*@File      regulator.c 
*@Author    EricMarina
*@Version   
*@Date      03.07.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "regulator.h"

/*!****************************************************************************
* Memory
*/
PID_GRANDO_IQ_CONTROLLER    pidPLL;     
PID_GRANDO_IQ_CONTROLLER    pidDRY;
PID_GRANDO_IQ_CONTROLLER    pidSLDR;

/*!****************************************************************************
* Interrupt Handlers
*/
__irq void TIM1_CC_IRQHandler(void)
{
    
    GPIO_PIN_SET(GPIOC, 0);
    uint32_t dPh = TIM1->CCR1;                  //Phase error
    pidPLL.term.Fbk = dPh;
    PID_GRANDO_IQ_FUNC(&pidPLL);
    TIM1->ARR = 65535 - pidPLL.term.Out;        //T
 
//    pidDRY.param.Umin = pidPLL.term.Out-1;
//    pidSLDR.param.Umin = pidPLL.term.Out-1;
    
     pidDRY.param.Umin = 0;
     pidDRY.param.Umax = TIM1->ARR+1;
     TIM1->CCR2 = pidDRY.term.Out;
    
    //---
    pidDRY.term.Fbk = stationState.dry.temperatueReal;
    pidDRY.term.Ref = stationState.dry.temperatueSet;
    
    pidSLDR.term.Fbk = stationState.solder.temperatueReal;
    pidSLDR.term.Ref = stationState.solder.temperatueSet;
    
    PID_GRANDO_IQ_FUNC(&pidDRY);
    PID_GRANDO_IQ_FUNC(&pidSLDR);
    //----
    //TIM1->CCR2 = 65535 - pidDRY.term.Out;
    TIM1->CCR3 = 65535 - pidSLDR.term.Out; 
    GPIO_PIN_RESET(GPIOC, 0);
    
    TIM1->SR = ~TIM_SR_CC1IF;                   //Clear flag 
}

/*!****************************************************************************
* Functions
*/
void regulatorInit()
{
    //TIM Configuration
    RCC->APB2ENR    |= RCC_APB2ENR_TIM1EN;      //TIM1 Enable clock
    RCC->APB2RSTR   |= RCC_APB2RSTR_TIM1RST;    //TIM1 Reset
    RCC->APB2RSTR   &= ~RCC_APB2RSTR_TIM1RST;
    
    GPIO_Init(GPIOA, 8, GPIO_Mode_InputWithPullDown); //ZC
    GPIO_Init(GPIOA, 9, GPIO_Mode_AlternateFunctionOutputPushPull); //dry
    GPIO_Init(GPIOA, 10, GPIO_Mode_AlternateFunctionOutputPushPull); //solder
    
    TIM1->PSC       = 16;                        //1 tic = 250ns for freq = 24 Mhz
    TIM1->ARR       = APB2_FREQUENCY / TIM1->PSC / 55;
    
    //Capture (CH1)
    TIM1->CCMR1     |= TIM_CCMR1_IC1F_2 |       //Input capture 1 filter - SAMPLING=fDTS/4, N=8
                       TIM_CCMR1_IC1F_1 |
                       TIM_CCMR1_IC1F_0 |
                       TIM_CCMR1_IC1F_3;
    
    TIM1->CCMR1     |= TIM_CCMR1_CC1S_0;        //CC1 channel is configured as input, IC1 is mapped on TI1
    TIM1->CCER      |= TIM_CCER_CC1P;           //Capture is done on a falling edge of IC1. When used as external trigger, IC2 is inverted
    TIM1->CCER      |= TIM_CCER_CC1E;           //Capture/Compare 1 output enable
    TIM1->DIER      |= TIM_DIER_CC1IE;	        //Capture/Compare 1 interrupt enable
    
    //Compare (CH2)
    TIM1->CCER      |= TIM_CCER_CC2E;           //Capture/Compare 2 output enable
    TIM1->CCER      |= TIM_CCER_CC2P;           //inverting polarity
    TIM1->CCMR1     |= TIM_CCMR1_OC2M;          //PWM mode 2 (INVERT PWM)                                        
    TIM1->BDTR      |= TIM_BDTR_MOE;
    TIM1->CCR2      = 1000;                     
    
    //Compare (CH3)
    TIM1->CCER      |= TIM_CCER_CC3E;           //Capture/Compare 3 output enable
    TIM1->CCER      |= TIM_CCER_CC3P;           //inverting polarity
    TIM1->CCMR2     |= TIM_CCMR2_OC3M;          //PWM mode 3 (INVERT PWM)                                        
    TIM1->BDTR      |= TIM_BDTR_MOE;
    TIM1->CCR3      = 0;   
     
    
    //PID PLL Init
    PID_GRANDO_IQ_init(&pidPLL);
    pidPLL.param.Kr   = _IQ(1.0);               //Parameter: reference set-point weighting
    pidPLL.param.Kp   = _IQ(1);                 //Parameter: proportional loop gain
    pidPLL.param.Ki   = _IQ(0.0);               //Parameter: integral gain
    pidPLL.param.Kd   = _IQ(0.000);             //Parameter: derivative gain
    pidPLL.param.Km   = _IQ(1.0);               //Parameter: derivative weighting
    pidPLL.param.Umax = 65000;
    pidPLL.param.Umin = 0;
    pidPLL.term.Ref = 25000;  

    
    //PID Dry Init
    PID_GRANDO_IQ_init(&pidDRY);
    pidDRY.param.Kr   = _IQ(1.0);                 //Parameter: reference set-point weighting
    pidDRY.param.Kp   = _IQ(100);                   //Parameter: proportional loop gain
    pidDRY.param.Ki   = _IQ(1.0);                 //Parameter: integral gain
    pidDRY.param.Kd   = _IQ(1.000);               //Parameter: derivative gain
    pidDRY.param.Km   = _IQ(1.0);                 //Parameter: derivative weighting
    pidDRY.param.Umax = 65535;
    pidDRY.param.Umin = 0;
    pidDRY.term.Ref = 300;
    
    //PID Solder Init
    PID_GRANDO_IQ_init(&pidSLDR);
    pidSLDR.param.Kr   = _IQ(1.0);                 //Parameter: reference set-point weighting
    pidSLDR.param.Kp   = _IQ(500);                   //Parameter: proportional loop gain
    pidSLDR.param.Ki   = _IQ(1.0);                 //Parameter: integral gain
    pidSLDR.param.Kd   = _IQ(1.000);               //Parameter: derivative gain
    pidSLDR.param.Km   = _IQ(1.0);                 //Parameter: derivative weighting
    pidSLDR.param.Umax = 65535;
    pidSLDR.param.Umin = 0;
    pidSLDR.term.Ref = 0;
    
    //Counter enable
    TIM1->CR1       |= TIM_CR1_CEN;              //Timer enable
    
    NVIC_SetPriority(TIM1_CC_IRQn, 1);          
    NVIC_EnableIRQ(TIM1_CC_IRQn);    
}

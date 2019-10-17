#include "main.h"
#include "pwm.h"

 
int main()
{
    for(int i=0; i<100000;i++)
    {
        __NOP();
    }
    SystemInit();
    uint32_t SysFreq = CoreClock_Init();
    PeriphClock_Init();
    GPIO_Init(GPIOC, 0, GPIO_Mode_OutPushPull); //debug led init
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
    ili9341_Init();
    pwm_init(TIM5, 5000, APB1_TIM_FREQUENCY, 2); //PWM for lcd backlight and dry fan
    lcdBacklight_init();
    dryFan_init();
    keyboardInit();
    regulatorInit();   
    UI_Init();
     
    //-----Solder encoder init-----
    encoderInit_t encSolderInit;
    
    encSolderInit.gpioA = GPIOA;
    encSolderInit.gpioB = GPIOA;
    encSolderInit.pinA = 6;
    encSolderInit.pinB = 7;
    encSolderInit.tim = TIM3;
    encoderInit(&encSolder, &encSolderInit);
    
    //-----Dry encoder init-----
    encoderInit_t encDryInit;
    
    encDryInit.gpioA = GPIOA;
    encDryInit.gpioB = GPIOA;
    encDryInit.pinA = 0;
    encDryInit.pinB = 1;
    encDryInit.tim = TIM2;
    encoderInit(&encDry, &encDryInit);
    //-----Station parametrs init-----
    stationInit();
    //-------
    
    OSInit();
 
    return 0;
}
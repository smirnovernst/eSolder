/*
*@File      GPIO.h 
*@Author    EricMarina
*@Version   1.0
*@Date      30.09.2016
*@Breif     
*/
#ifndef GPIO_h
#define GPIO_h
/*!****************************************************************************
* Include
*/
//#include "main.h"
#include <assert.h>
#include "stdint.h"
#include "stm32f1xx.h"

/*!****************************************************************************
* User define
*/
#define GPIO_FLOATIG_INPUT                      0x1
#define GPIO_INPUT_WITH_PULL_UP_PULL_DOWN       0x2
#define GPIO_OUT_PUSH_PULL                      0x0
#define GPIO_OUT_OPEN_DRAIN                     0x1
#define GPIO_AF_PUSH_PULL                       0x2
#define GPIO_AF_OPEN_DRAIN                      0x3

typedef enum
{
    GPIO_Pin_0   = 1 << 0,
    GPIO_Pin_1   = 1 << 1,
    GPIO_Pin_2   = 1 << 2,
    GPIO_Pin_3   = 1 << 3,
    GPIO_Pin_4   = 1 << 4,
    GPIO_Pin_5   = 1 << 5,
    GPIO_Pin_6   = 1 << 6,
    GPIO_Pin_7   = 1 << 7,
    GPIO_Pin_8   = 1 << 8,
    GPIO_Pin_9   = 1 << 9,
    GPIO_Pin_10  = 1 << 10,
    GPIO_Pin_11  = 1 << 11,
    GPIO_Pin_12  = 1 << 12,
    GPIO_Pin_13  = 1 << 13,
    GPIO_Pin_14  = 1 << 14,
    GPIO_Pin_15  = 1 << 15,
    GPIO_Pin_All = 0xFFFF,
}GpioPin_t;

typedef enum
{
    speed_2MHz  = 0x1,
    speed_10MHz = 0x2,
    speed_50MHz = 0x3,
}GpioSpeed_t;

typedef enum
{
    GPIO_Mode_Analog,
    GPIO_Mode_FloatingInput,
    GPIO_Mode_InputWithPullUp,
    GPIO_Mode_InputWithPullDown,
    GPIO_Mode_OutPushPull,
    GPIO_Mode_OutOpenDrain,
    GPIO_Mode_AlternateFunctionOutputPushPull,
    GPIO_Mode_AlternateFunctionOutputOpenDrain
}GpioMode_type;
/*!****************************************************************************
* User enum
*/

/*!****************************************************************************
* User typedef
*/

/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/
#define __GPIO_PIN_SET(Port, Pin_mask)       (Port->BSRR = (Pin_mask))
#define __GPIO_PIN_RESET(Port, Pin_mask)     (Port->BRR  = (Pin_mask))
#define __GPIO_PIN_TOGLE(Port, Pin_mask)     (Port->ODR  ^=(Pin_mask))
#define __GPIO_PIN_GET(Port, Pin_mask)       (Port->IDR  & (Pin_mask))


#define GPIO_PIN_SET(Port, Pin)       (Port->BSRR = (1  << Pin))
#define GPIO_PIN_RESET(Port, Pin)     (Port->BRR  = (1  << Pin))
#define GPIO_PIN_TOGLE(Port, Pin)     (Port->ODR  ^=(1  << Pin))
#define GPIO_PIN_GET(Port, Pin)       (Port->IDR  & (1  << Pin))&&1


/*!****************************************************************************
* Prototypes for the functions
*/

void GPIO_Init(GPIO_TypeDef *Port, uint8_t Pin,GpioMode_type Mode );
void __GPIO_Init(GPIO_TypeDef *Port, uint16_t pinmask,GpioMode_type Mode);
#endif //GPIO_h




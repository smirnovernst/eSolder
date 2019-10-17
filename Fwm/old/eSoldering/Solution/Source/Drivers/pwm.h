/*
*@File      pwm.h 
*@Author    EricMarina
*@Version   
*@Date      04.07.2017
*@Breif     
*/
#ifndef pwm_h
#define pwm_h
/*!****************************************************************************
* Include
*/
#include "global_inc.h"

#include "GPIO.h"
/*!****************************************************************************
* User define
*/
/*!****************************************************************************
* User enum
*/

typedef enum
{
    pwmChEnable_OFF     = 0,
    pwmChEnable_ON      = 1,
}pwmChEnable_t;
/*!****************************************************************************
* User typedef
*/

typedef struct
{
    TIM_TypeDef     *tim;
    uint8_t         channel;
}pwmChannel_t;
/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/

/*!****************************************************************************
* Prototypes for the functions
*/
void pwm_init(TIM_TypeDef *tim,uint32_t freq, uint32_t timBusFreq, uint16_t timBusPSC);
void pwm_channelInit(pwmChannel_t *pwmChannel, GPIO_TypeDef *port, uint8_t pin); 
void pwm_dutySet(pwmChannel_t *pwmCh, float duty);
void pwm_channelEnable(pwmChannel_t *pwmChannel, pwmChEnable_t enable);
//void pwm_channelEnable(pwmChannel_t *pwmCh, pwmChEnable_t
#endif //pwm_h




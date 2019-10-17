/*
*@File      PPM.h 
*@Author    EricMarina
*@Version   1.0
*@Date      10.01.2017
*@Breif     
*/
#ifndef PLL_h
#define PLL_h
/*!****************************************************************************
* Include
*/
//Device
#include "stm32f1xx.h"

//Drivers
#include "GPIO.h"

//Library
#include "IQmathLib.h"
#include "PID_GRANDO_IQ.h"
 
/*!****************************************************************************
* User define
*/
#define IQtoInt(_iqval, _mul)  (int32_t)(((int64_t)_iqval * _mul + _IQ(1)/2) / _IQ(1))
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
#define regulator_solderON      TIM1->CCER      |= TIM_CCER_CC3E
#define regulator_solderOFF     TIM1->CCER      &= ~TIM_CCER_CC3E                         
#define regulator_dryON         TIM1->CCER      |= TIM_CCER_CC2E
#define regulator_dryOFF        TIM1->CCER      &= ~TIM_CCER_CC2E
/*!****************************************************************************
* Prototypes for the functions
*/
void PPM_Init(void);

#endif //PPM_h




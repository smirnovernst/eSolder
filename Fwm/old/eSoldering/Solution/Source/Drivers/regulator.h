/*
*@File      regulator.h 
*@Author    EricMarina
*@Version   
*@Date      03.07.2017
*@Breif     
*/
#ifndef regulator_h
#define regulator_h
/*!****************************************************************************
* Include
*/
#include "global_inc.h"
#include "stationState.h"

#include "GPIO.h"

#include "IQmathLib.h"
#include "PID_GRANDO_IQ.h"
/*!****************************************************************************
* User define
*/

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

void regulatorInit();

#endif //regulator_h




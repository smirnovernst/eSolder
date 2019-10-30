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
typedef struct 
{
    int32_t *p_Ref;
    int32_t *p_Fbk;
}regulatorParam_t;
/*!****************************************************************************
* Extern viriables
*/  

/*!****************************************************************************
* Macro functions
*/
#define regulator_solderOFF()     TIM1->CCER &= ~TIM_CCER_CC3E                         
#define regulator_dryOFF()        TIM1->CCER &= ~TIM_CCER_CC2E
/*!****************************************************************************
* Prototypes for the functions
*/

void regulatorInit();

void regulatorSolderOn(regulatorParam_t params);
void regulatorDryOn(regulatorParam_t params);

#endif //regulator_h




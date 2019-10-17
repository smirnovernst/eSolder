/*
*@File      stationState.c 
*@Author    EricMarina
*@Version   
*@Date      16.06.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "stationState.h"
/*!****************************************************************************
* Memory
*/
stationState_t      stationState;
/*!****************************************************************************
* Functions
*/
void stationInit(void)
{
    stationState.setting.autoOff = enable_OFF;
    stationState.setting.beep    = enable_OFF;
    
    stationState.dry.enable  = enable_OFF;
    stationState.dry.status  = deviceStatus_Ok;
    stationState.dry.temperatueSet = 250;
    
    stationState.regulator_selected = DryRegulatorSelected_Set;
    
    stationState.solder.enable = enable_OFF;
    stationState.solder.status  = deviceStatus_Ok;
    stationState.solder.temperatueSet = 250;
}


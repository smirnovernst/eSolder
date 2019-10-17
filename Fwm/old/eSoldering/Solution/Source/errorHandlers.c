/*
*@File      errorHandlers.c 
*@Author    EricMarina
*@Version   
*@Date      22.06.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "errorHandlers.h"
/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* Functions
*/


void connectionErr(deviceParametrs_t *device)
{
    if (device->enable != enable_OFF)
    {
        device->connection = 0;
        device->status = deviceStatus_Fail;
    }
}
void tempMeasErr()
{
        __NOP();
}
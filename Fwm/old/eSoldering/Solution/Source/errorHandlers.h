/*
*@File      errorHandlers.h 
*@Author    EricMarina
*@Version   
*@Date      22.06.2017
*@Breif     
*/
#ifndef errorHandlers_h
#define errorHandlers_h
/*!****************************************************************************
* Include
*/
#include "global_inc.h"
#include "stationState.h"
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

/*!****************************************************************************
* Prototypes for the functions
*/

void connectionErr(deviceParametrs_t *device);
void tempMeasErr();
#endif //errorHandlers_h




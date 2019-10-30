/*
*@File      OSInit.h 
*@Author    EricMarina
*@Version   
*@Date      14.06.2017
*@Breif     
*/
#ifndef OSInit_h
#define OSInit_h


#include "global_inc.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"


/*!****************************************************************************
* Semaphore
*/

extern SemaphoreHandle_t max6675_solderSem;
extern SemaphoreHandle_t max6675_drySem;
extern SemaphoreHandle_t tempMeasSemStart;
extern SemaphoreHandle_t tempMeasSemEnd;


/*!****************************************************************************
*-------NAME--------------------size [2byte Word] */ 
//0 - minimal priority;  (configMAX_PRIORITIES-1) - maximal;

#define MAIN_TSK_PRIORITY           1
#define SYSTEM_TSK_PRIORITY         3
#define TEMPMEAS_TSK_PRIORITY       4

void OSInit(void);


#endif //OSInit_h




/*
*@File      OSInit.c 
*@Author    EricMarina
*@Version   
*@Date      14.06.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "OSInit.h"

#include "mainTSK.h"
#include "tempMeasTSK.h"
#include "systemTSK.h"
/*!****************************************************************************
* Memory
*/
//------semaphore------

SemaphoreHandle_t max6675_solderSem;
SemaphoreHandle_t max6675_drySem;

SemaphoreHandle_t tempMeasSemStart;
SemaphoreHandle_t tempMeasSemEnd;


/*!****************************************************************************
* Functions
*/

void OSInit(void)
{
    /************************************************
    * semaphore create
    */ 
    vSemaphoreCreateBinary(max6675_solderSem);
    vSemaphoreCreateBinary(max6675_drySem);
    vSemaphoreCreateBinary(tempMeasSemEnd);
    vSemaphoreCreateBinary(tempMeasSemStart);
      
    xSemaphoreTake(max6675_solderSem, portMAX_DELAY);
    xSemaphoreTake(max6675_drySem, portMAX_DELAY);
    xSemaphoreTake(tempMeasSemEnd, portMAX_DELAY);
    xSemaphoreTake(tempMeasSemStart, portMAX_DELAY);

    /************************************************
    * Tasks create
    */ 
    xTaskCreate((TaskFunction_t)mainTSK,    "mainTSK",    128,   NULL, 1,  NULL);
    //xTaskCreate((TaskFunction_t)tempMeasTSK,    "tempMeasTSK",    128,   NULL, TEMPMEAS_TSK_PRIORITY,  NULL);
    //xTaskCreate((TaskFunction_t)systemTSK, "systemTSK", 256, NULL, 3, NULL);
    
    vTaskStartScheduler();  
}


/*
*@File      stationState.h 
*@Author    EricMarina
*@Version   
*@Date      22.05.2017
*@Breif     
*/
#ifndef stationState_h
#define stationState_h
/*!****************************************************************************
* Include
*/
#include "global_inc.h"
/*!****************************************************************************
* User define
*/
#define SOLDER_TEMPSET_MAX  400
#define DRY_TEMPSET_MAX     400
#define DRY_FLOW_MAX        100
/*!****************************************************************************
* User enum
*/
typedef enum
{
    deviceStatus_Ok,
    deviceStatus_Fail,
    deviceStatus_Heating,
}deviceStatus;

typedef enum
{
    enable_ON,
    enable_OFF,
}enable_t;

typedef enum
{
    DryRegulatorSelected_Set  = 1,
    DryRegulatorSelected_Flow = 2,
}dryRegulatorSelected;

/*!****************************************************************************
* User typedef
*/

typedef struct
{
    enable_t        enable;
    deviceStatus    status;
    uint16_t        temperatueSet;
    uint16_t        temperatueReal;
    uint8_t         connection  :1;
}deviceParametrs_t;

typedef struct
{
    enable_t           beep;
    enable_t           autoOff;
    //enable_t           dryMotor;
}stationSetting_t;

typedef struct
{
    deviceParametrs_t       dry;
    deviceParametrs_t       solder;
    enable_t                dryReed;
    uint8_t                 dryFlow;
    int8_t                  internalTemp;
    dryRegulatorSelected    regulator_selected; 
    stationSetting_t        setting;
}stationState_t;

typedef struct
{
   uint8_t a; 
}StationErrors_t;
/*!****************************************************************************
* Extern viriables
*/
extern stationState_t      stationState;
 
/*!****************************************************************************
* Macro functions
*/

/*!****************************************************************************
* Prototypes for the functions
*/
void stationInit(void);
#endif //stationState_h




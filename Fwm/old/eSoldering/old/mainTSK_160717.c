/*
*@File      mainTSK.c 
*@Author    EricMarina
*@Version   
*@Date      22.05.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "mainTSK.h"
#include "pwr.h"
#include "lcd_backlight.h"

#include "menuTSK.h"
/*!****************************************************************************
* Memory
*/


/*!****************************************************************************
* Functions
*/
#include "max6675.h"

__task void mainTSK(void)
{
     
    /*=========== Memory ==========*/
    uint8_t     bOnOffPressCouneter = 0;    //counter for track long press button
    
    /*=========== First initialisation ==========*/  
    UI_WindowRendering();
    ili9341_displayOn;
    UI_Update(&stationState);
    lcdBacklight_bright(100);
    
    
    enSet(encSolder, 20, SOLDER_TEMPSET_MAX, TEMP_STEP, TEMP_BIGSTEP, enNONCIRC, enU16,  &stationState.solder.temperatueSet); 
    enWriteVal(&encSolder, stationState.solder.temperatueSet);  
   /*=========== Code ==========*/
    while(1)
    {
        GPIO_PIN_TOGLE(GPIOC, 0);
         /*=========== Key handlers ==========*/
        keyboardScan();
        //if(keyboard.ANY) //if pressed at least one key
        {
            //----------Dry_OnOff---------
            if (keyboard.Dry_OnOff) 
            {    
                stationState.dry.enable ^= 1;
            }
            //----------Solder_OnOff----------
            if(keyboard.Solder_OnOff)  
            {
                stationState.solder.enable ^= 1;
            } 
            //----------OnOff----------
            if(keyboard.OnOff)  
            {
                bOnOffPressCouneter++;
                if (bOnOffPressCouneter > KEY_LONG_PRESS_TRESHOLD) 
                {
                    //long press action
                    //lcdBacklight_bright(0);
                    xTaskCreate((TaskFunction_t)menuTSK,    "menuTSK",    128,   NULL, MAIN_TSK_PRIORITY,  NULL);
                    vTaskDelete(NULL);
                    bOnOffPressCouneter = 0;
                }
            } 
            else 
            {
                if (bOnOffPressCouneter > 0) //if pressed and released
                {
                    if (bOnOffPressCouneter < KEY_LONG_PRESS_TRESHOLD)
                    {
                        //short press action
                        pwr_stop();
                    }           
                    bOnOffPressCouneter = 0;
                }
            }
           //----------Enc_Dry Button----------
            if(keyboard.Enc_Dry)  
            {
                stationState.regulator_selected ^= 1;
            } 
           //----------Enc_Solder Button----------
            if(keyboard.Enc_Solder)  
            {
                if (stationState.solder.enable == enable_ON)
                {
                    stationState.solder.temperatueSet = 250; 
                }
            } 
        }// end if keyboard.ANY
        /*=========== Encoders update ==========*/
        //------ Encdry select -------
        if (stationState.regulator_selected == DryRegulatorSelected_Set)
        {
             enSet(encDry, 20, DRY_TEMPSET_MAX, TEMP_STEP, TEMP_BIGSTEP, enNONCIRC, enU16,  &stationState.dry.temperatueSet); 
             enWriteVal(&encDry, stationState.dry.temperatueSet);
        }
        else
        {
             enSet(encDry, 0, 100, FLOW_STEP, FLOW_BIGSTEP, enNONCIRC, enU8,  &stationState.dryFlow); 
             enWriteVal(&encDry, stationState.dryFlow);
        }
        
        //------ Enable/disable encoders-------
        if (stationState.solder.enable == enable_ON)  
        {
            enEnable(encSolder);
        }
        else
        {
            enDisable(encSolder);
        }
        
        if (stationState.dry.enable == enable_ON)     
        {
            enEnable(encDry);
        }
        else
        {
            enDisable(encDry);
        }
        //----- encoders update
        enGet(&encSolder);
        enGet(&encDry);
        /*=========== UI update ==========*/
        UI_Update(&stationState);
        /*===========   ==========*/
        TickType_t xLastWakeTime;
        xLastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&xLastWakeTime, (TickType_t)100/portTICK_PERIOD_MS); 
    }//end while
    
}

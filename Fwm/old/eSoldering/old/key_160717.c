/*
*@File      key.c 
*@Author    EricMarina
*@Version   0.1
*@Date      01.10.2016
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "key.h"

volatile Keyboard_t keyboard;
/*!****************************************************************************
* Functions
*/

uint8_t Key_Scan(void)
{
  keyboard.ANY = 0;
 
  keyboard.Enc_Dry       = Key_Enc_Dry;
  keyboard.Enc_Solder    = Key_Enc_Solder;
  keyboard.Dry_OnOff     = Key_Dry_OnOff;
  keyboard.Solder_OnOff  = Key_Solder_OnOff;
  keyboard.OnOff         = Key_OnOff;  
 
  return keyboard.ANY;
}

void    Key_init(void)
{
    GPIO_Init(KEY_GPIO, KEY_ENC_DRY, GPIO_Mode_InputWithPullDown);
    GPIO_Init(KEY_GPIO, KEY_ENC_SOLDER, GPIO_Mode_InputWithPullDown);
    GPIO_Init(KEY_GPIO, KEY_DRY_ONOFF, GPIO_Mode_InputWithPullDown);
    GPIO_Init(KEY_GPIO, KEY_SOLDER_ONOFF, GPIO_Mode_InputWithPullDown);
    GPIO_Init(KEY_GPIO, KEY_ONOFF, GPIO_Mode_InputWithPullDown);

}
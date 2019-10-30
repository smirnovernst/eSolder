/*
*@File      keyboard.c 
*@Author    EricMarina
*@Version   
*@Date      16.07.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "keyboard.h"
/*!****************************************************************************
* Memory
*/
 keyboard_t keyboard;
/*!****************************************************************************
* Functions
*/

void keyboardInit(void)
{
    keyboard.b_encDry.port =    KEYBOARD_GPIO;
    keyboard.b_encDry.pin =     KEYBOARD_ENC_DRY;
    buttonInit(&keyboard.b_encDry);
    
    keyboard.b_encSolder.port =    KEYBOARD_GPIO;
    keyboard.b_encSolder.pin =     KEYBOARD_ENC_SOLDER;
    buttonInit(&keyboard.b_encSolder);
    
}

uint8_t keyboardScan(void)
{
    uint8_t any_pressed = 0;
    any_pressed += buttonScan(&keyboard.b_encDry);
    any_pressed += buttonScan(&keyboard.b_encSolder);
    return any_pressed;
}
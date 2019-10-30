/*
*@File      keyboard.h 
*@Author    EricMarina
*@Version   
*@Date      16.07.2017
*@Breif     
*/
#ifndef keyboard_h
#define keyboard_h
/*!****************************************************************************
* Include
*/
#include "button.h"
/*!****************************************************************************
* User define
*/
#define KEYBOARD_GPIO         GPIOB

#define KEYBOARD_ENC_DRY         9
#define KEYBOARD_ENC_SOLDER      0

/*!****************************************************************************
* User enum
*/

/*!****************************************************************************
* User typedef
*/

typedef struct
{
    button_t    b_encDry;
    button_t    b_encSolder;
}keyboard_t;
/*!****************************************************************************
* Extern viriables
*/
extern  keyboard_t keyboard;
/*!****************************************************************************
* Macro functions
*/

/*!****************************************************************************
* Prototypes for the functions
*/
void    keyboardInit(void);
uint8_t keyboardScan(void);

#endif //keyboard_h




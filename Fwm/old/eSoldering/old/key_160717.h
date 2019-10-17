/*
*@File      key.h 
*@Author    EricMarina
*@Version   0.1
*@Date      01.10.2016
*@Breif     
*/
#ifndef key_h
#define key_h
/*!****************************************************************************
* Include
*/
//Device files
#include "stm32f1xx.h"
//Drivers 
#include "GPIO.h"
/*!****************************************************************************
* User define
*/

#define KEY_GPIO         GPIOB

#define KEY_ENC_DRY         9
#define KEY_ENC_SOLDER      0
#define KEY_DRY_ONOFF       1
#define KEY_SOLDER_ONOFF    10
#define KEY_ONOFF           2

#define KEY_LONG_PRESS_TRESHOLD     5
/*!****************************************************************************
* User enum
*/

/*!****************************************************************************
* User typedef
*/
typedef struct
{
    uint8_t Enc_Dry          :1;
    uint8_t Enc_Solder       :1;
    uint8_t Dry_OnOff        :1;
    uint8_t Solder_OnOff     :1;
    uint8_t OnOff            :1;
}Key_t;

typedef union
{
    Key_t;
    uint8_t ANY;
}Keyboard_t;
/*!****************************************************************************
* Extern viriables
*/
extern volatile Keyboard_t keyboard;
/*!****************************************************************************
* Macro functions
*/

//---Macros for each button


#define Key_Enc_Dry      GPIO_PIN_GET(KEY_GPIO, KEY_ENC_DRY)
#define Key_Enc_Solder   GPIO_PIN_GET(KEY_GPIO, KEY_ENC_SOLDER)       
#define Key_Dry_OnOff    GPIO_PIN_GET(KEY_GPIO, KEY_DRY_ONOFF)       
#define Key_Solder_OnOff GPIO_PIN_GET(KEY_GPIO, KEY_SOLDER_ONOFF)
#define Key_OnOff        GPIO_PIN_GET(KEY_GPIO, KEY_ONOFF)


/*!****************************************************************************
* Prototypes for the functions
*/
void    Key_init(void);
uint8_t Key_Scan(void);

#endif //key_h




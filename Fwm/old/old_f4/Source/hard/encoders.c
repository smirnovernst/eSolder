/*
*@File          encoders.c
*@Author        Ernst
*@Version       
*@Date          20.08.2018
*@Breif         
*/
/*!****************************************************************************
* Include
*/
#include "enco.h"
/*!****************************************************************************
* Memory
*/
/*!****************************************************************************
* Functions
*/
void encoders_init()
{
        //-----Solder encoder init-----
    encoderInit_t encSolderInit;
    
    encSolderInit.gpioA = GPIOA;
    encSolderInit.gpioB = GPIOA;
    encSolderInit.pinA = 6;
    encSolderInit.pinB = 7;
    encSolderInit.tim = TIM3;
    encoderInit(&encSolder, &encSolderInit);
    
    //-----Dry encoder init-----
    encoderInit_t encDryInit;
    
    encDryInit.gpioA = GPIOA;
    encDryInit.gpioB = GPIOA;
    encDryInit.pinA = 0;
    encDryInit.pinB = 1;
    encDryInit.tim = TIM2;
    encoderInit(&encDry, &encDryInit);
}

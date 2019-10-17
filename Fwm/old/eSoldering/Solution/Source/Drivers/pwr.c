/*
*@File      pwr.c 
*@Author    EricMarina
*@Version   
*@Date      08.07.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "pwr.h"
/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* Functions
*/


void pwr_stop()
{
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	SCB->SCR |= SCB_SCR_SLEEPDEEP; 
	PWR->CR |= PWR_CR_PDDS;
	PWR->CR |= PWR_CR_CWUF ;  
	//PWR->CSR |= PWR_CSR_EWUP; //wake-up (PA0) EN
	__WFE();
}
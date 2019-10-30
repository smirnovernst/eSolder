/*
*@File          interrupts.c
*@Author        User
*@Version       
*@Date          23.08.2018
*@Breif         
*/
/*!****************************************************************************
* Include
*/
#include "interrupts.h"

#include "spi_f4.h"
/*!****************************************************************************
* Memory
*/
/*!****************************************************************************
* Functions
*/

__irq void DMA2_Stream3_IRQHandler(void)
{
    spi_DmaTxIrqHandler(&spi1);
    DMA2->LIFCR	 = DMA_LIFCR_CTCIF3;
}

__irq void DMA2_Stream0_IRQHandler(void)
{
    spi_DmaRxIrqHandler(&spi1);
    DMA2->LIFCR	 = DMA_LIFCR_CTCIF0;
}
__irq void SPI1_IRQHandler (void)
{
    spi_IrqHandler(&spi1);
}

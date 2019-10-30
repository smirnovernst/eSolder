/*
*@File      max6675.c 
*@Author    EricMarina
*@Version   
*@Date      22.06.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "max6675.h"
/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* Functions
*/

void max6675_readData(spi_t *sensor_spi, uint16_t *buffer)
{
    uint16_t temp_matrix; //temporary matrix for taranceive
    temp_matrix = 0;
    
    spi_transaction_DMA(sensor_spi, &temp_matrix, buffer, 1);
}
void max6675_decodeData(uint16_t* buffer, max6675Data_t *data)
{
    data->temperature = (*buffer >> 3)*0.25;
    data->OC_fault = (*buffer & 0x4) >> 2;
}
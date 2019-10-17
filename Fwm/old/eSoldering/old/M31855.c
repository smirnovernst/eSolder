/*
*@File      M31855.c 
*@Author    EricMarina
*@Version   
*@Date      22.05.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "M31855.h"
/*!****************************************************************************
* Memory
*/

/*!****************************************************************************
* Functions
*/
  
void m31855_getData(spi_t *sensor_spi, m31855Data_t *data)
{

}

void m31855_readData(spi_t *sensor_spi, uint16_t *buffer)
{
    uint16_t temp_matrix[2]; //temporary matrix for taranceive
    temp_matrix[0] = 0;
    temp_matrix[1] = 0;
    
    spi_transaction_DMA(sensor_spi, temp_matrix, buffer, 2);
}
void m31855_decodeData(uint16_t* buffer, m31855Data_t *data)
{
    
    data->thermocoupleTemp = ((buffer[0] >> 2)&0x1FFF)*0.25;
    data->fault  = buffer[0] & 0x1;
    data->internalTemp = ((buffer[1] >> 4)&0x3FF)*0.0625;
    data->OC_fault = buffer[1] & 0x1;
    data->SCG_fault = buffer[1] & 0x2;
    data->SCV_fault = buffer[1] & 0x4;
}
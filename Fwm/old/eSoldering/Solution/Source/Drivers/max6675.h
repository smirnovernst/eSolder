/*
*@File      max6675.h 
*@Author    EricMarina
*@Version   
*@Date      22.06.2017
*@Breif     
*/
#ifndef max6675_h
#define max6675_h
/*!****************************************************************************
* Include
*/
#include "global_inc.h"
#include "GPIO.h"
#include "spi.h"
/*!****************************************************************************
* User define
*/

/*!****************************************************************************
* User enum
*/

/*!****************************************************************************
* User typedef
*/
typedef struct
{
    float   temperature;
    uint8_t OC_fault:1;
}max6675Data_t;
/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/

/*!****************************************************************************
* Prototypes for the functions
*/
inline void max6675_init(spi_t *sensor_spi) { spi_init(sensor_spi);}

void max6675_readData(spi_t *sensor_spi, uint16_t *buffer);
void max6675_decodeData(uint16_t* buffer, max6675Data_t *data);
#endif //max6675_h




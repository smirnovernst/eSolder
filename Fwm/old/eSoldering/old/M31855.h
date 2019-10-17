/*
*@File      M31855.h 
*@Author    EricMarina
*@Version   
*@Date      22.05.2017
*@Breif     
*/
#ifndef M31855_h
#define M31855_h
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
    float    thermocoupleTemp;
    uint8_t     fault:1;
    float    internalTemp;
    uint8_t     SCV_fault:1;
    uint8_t     SCG_fault:1;
    uint8_t     OC_fault:1;
    uint16_t h;
}m31855Data_t;

/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/

/*!****************************************************************************
* Prototypes for the functions
*/
void m31855_getData(spi_t *sensor_spi, m31855Data_t *data);
inline void m31855_init(spi_t *sensor_spi) { spi_init(sensor_spi);}

void m31855_readData(spi_t *sensor_spi, uint16_t *buffer);
void m31855_decodeData(uint16_t* buffer, m31855Data_t *data);
#endif //M31855_h




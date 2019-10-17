#ifndef i2c_h
#define i2c_h
/*!****************************************************************************
* Include
*/
//Device files
#include "stm32f1xx.h"

/*!****************************************************************************
* User define
*/
#define i2c_CCR 0x28

#ifndef i2c_CCR
    #error "I2C CCR not defined!"
#endif
/*!****************************************************************************
* User enum
*/

/*!****************************************************************************
* User typedef
*/
typedef enum
{
  i2c_OK,
  i2c_Error
}i2c_status_t;

typedef struct
{
  I2C_TypeDef  *i2c_use;
  uint8_t APB_Freq;
  
  
}i2c_type;
/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/

/*!****************************************************************************
* Prototypes for the functions
*/
i2c_status_t i2c_Init(i2c_type *i2c_init_struct);
i2c_status_t i2c_SendData(I2C_TypeDef  *i2c_use, uint8_t *data, uint16_t count);
inline void i2c_Reset(I2C_TypeDef  *i2c_use) {i2c_use->CR1 |= I2C_CR1_SWRST; }

#endif //i2c_h




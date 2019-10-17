/*!****************************************************************************
* Include
*/
#include "i2c.h"

__root uint32_t CCR;
/*!****************************************************************************
* Functions
*/

i2c_status_t i2c_Init(i2c_type *i2c_init_struct)
{
  i2c_init_struct->i2c_use->CR2 = 0;
  i2c_init_struct->i2c_use->CR2 |= i2c_init_struct->APB_Freq & 0x1F;
  
  i2c_init_struct->i2c_use->CCR = i2c_CCR;
  
  i2c_init_struct->i2c_use->CR1 = 0;
  i2c_init_struct->i2c_use->CR1 |= I2C_CR1_PE ;
  
  return i2c_OK;
}

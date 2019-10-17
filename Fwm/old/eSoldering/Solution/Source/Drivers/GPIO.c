 /*
 *@File      GPIO.c 
 *@Author    EricMarina
 *@Version   1.0
 *@Date      30.09.2016
 *@Breif     
 */
 /*!****************************************************************************
 * Include
 */
 #include "GPIO.h"
 
 /*!****************************************************************************
 * Functions
 */
 
void GPIO_Init(GPIO_TypeDef *Port, uint8_t Pin, GpioMode_type Mode)
{
    //assert
    assert((Pin >=0) && (Pin <= 15));
     
    __IO uint32_t    *ConfigurationReg;
    
    
    if (Pin <= 7) 
    {
        ConfigurationReg = &Port->CRL;
    }
    if (Pin > 7 )
    {
        ConfigurationReg = &Port->CRH;
        Pin -= 8;    
    }
    
    //Clearing bits
    uint32_t Pin_mask = 0xF << (4 * Pin);
    *ConfigurationReg &=  ~Pin_mask;
         
    //Confiuraion
    switch (Mode)
    {
    case GPIO_Mode_Analog: break;
    case GPIO_Mode_FloatingInput: 
        {
             *ConfigurationReg |= GPIO_FLOATIG_INPUT << (2 + 4 * Pin); 
            break;
        }
    case GPIO_Mode_InputWithPullUp:
        {
            *ConfigurationReg |= GPIO_INPUT_WITH_PULL_UP_PULL_DOWN << (2 + 4 * Pin); 
            __GPIO_PIN_SET(Port, (1 << Pin));
            break;
        }
    case GPIO_Mode_InputWithPullDown:
        {
            *ConfigurationReg |= GPIO_INPUT_WITH_PULL_UP_PULL_DOWN << (2 + 4 * Pin); 
            __GPIO_PIN_RESET(Port, (1 << Pin));
            break;
        }
    case GPIO_Mode_OutPushPull:
        {
             *ConfigurationReg |= GPIO_OUT_PUSH_PULL << (2 + 4 * Pin) |
                                  (speed_50MHz << (4 * Pin));
            break;
        }
    case GPIO_Mode_OutOpenDrain:
        {
            *ConfigurationReg |= GPIO_OUT_OPEN_DRAIN << (2 + 4 * Pin) |
                                 (speed_50MHz << (4 * Pin));
            break;
        }
    case GPIO_Mode_AlternateFunctionOutputPushPull:
        {
            *ConfigurationReg |= GPIO_AF_PUSH_PULL << (2 + 4 * Pin) |
                                 (speed_50MHz << (4 * Pin));
            break;
        }
    case GPIO_Mode_AlternateFunctionOutputOpenDrain:
        {
            *ConfigurationReg |= GPIO_AF_OPEN_DRAIN << (2 + 4 * Pin) |
                                 (speed_50MHz << (4 * Pin));
            break;
        }
    default: break;
    }//end switch
    
 
    
        
}//end GPIO_Init
void __GPIO_Init(GPIO_TypeDef *Port, uint16_t pinmask,GpioMode_type Mode)
{
   for (uint8_t pin = 0; pin < 16; pin++)
   {
        if (pinmask & (1<<pin))
        {
            GPIO_Init(Port, pin, Mode);
        }
   }
    
}

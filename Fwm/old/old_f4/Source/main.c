#include "main.h"
#include "pwm.h"

#include "spi_f4.h"
int main()
{
    for(int i=0; i<100000;i++)
    {
        __NOP();
    }
    hard_init();
        

     spi_init();
    //UI_Init();
      

    //-----Station parametrs init-----
    stationInit();
    //-------
    
    OSInit();
 
    while(1) {} 
    return 0;
}
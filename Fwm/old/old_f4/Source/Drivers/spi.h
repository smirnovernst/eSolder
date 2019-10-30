/*
*@File      spi.h 
*@Author    EricMarina
*@Version   
*@Date      26.05.2017
*@Breif     
*/
#ifndef spi_h
#define spi_h

#if 0
//<<TODO: need release for stm32f4
/*!****************************************************************************
* Include
*/
#include "stm32f4xx.h"
#include "GPIO.h"

#include "OSInit.h"

/*!****************************************************************************
* User define
*/
#define SPI_CS_ACT_LEVEL  (0) // CS 0- active LOW; 1 - active - HIGH
#define SPI_RTOS_USE      (1)

#define SPI1_USE        (1)
#define SPI1_RECEIVE    (0)
#define SPI1_PINREMAP   (1)
#define SPI1_16BIT      (0)
#define SPI1_HOOK       (0)
#define SPI1_DMA_USE    (0)
#define SPI1_RX_DMA_PRIOR (15)
#define SPI1_TX_DMA_PRIOR (15)



#define SPI2_USE        (1)
#define SPI2_RECEIVE    (1)
#define SPI2_PINREMAP   (0)
#define SPI2_16BIT      (1)
#define SPI2_HOOK       (1)
#define SPI2_DMA_USE    (1)
#define SPI2_RX_DMA_PRIOR (15)
#define SPI2_TX_DMA_PRIOR (15)

#define SPI3_USE        (1)
#define SPI3_RECEIVE    (1)
#define SPI3_PINREMAP   (1)
#define SPI3_16BIT      (1)
#define SPI3_HOOK       (1)
#define SPI3_DMA_USE    (1)
#define SPI3_RX_DMA_PRIOR (15)
#define SPI3_TX_DMA_PRIOR (15)





/*!****************************************************************************
* User enum
*/
typedef enum
{
    SPI_DEV_SLAVE   = 0,
    SPI_DEV_MASTER  = 1
}spi_dev_t;
    
typedef enum
{
    SPI_CLOCK_FPCLK_DIV_2    = 0,
    SPI_CLOCK_FPCLK_DIV_4    = 1,
    SPI_CLOCK_FPCLK_DIV_8    = 2,
    SPI_CLOCK_FPCLK_DIV_16   = 3,
    SPI_CLOCK_FPCLK_DIV_32   = 4,
    SPI_CLOCK_FPCLK_DIV_64   = 5,
    SPI_CLOCK_FPCLK_DIV_128  = 6,
    SPI_CLOCK_FPCLK_DIV_256  = 7
}spi_clock_t;

typedef enum
{
    SPI_MODE_0 = 0, //CPOL = 0, CPHA = 0;
    SPI_MODE_1 = 1, //CPOL = 0, CPHA = 1;
    SPI_MODE_2 = 2, //CPOL = 1, CPHA = 0;
    SPI_MODE_3 = 3, //CPOL = 1, CPHA = 1;
}spi_mode_t;
 
/*!****************************************************************************
* User typedef
*/
typedef struct
{
    GPIO_TypeDef    *port;
    uint8_t         pin;
}spi_cs_t;

typedef struct
{
    SPI_TypeDef *spi;
    spi_cs_t    cs;
    spi_dev_t   dev;
    spi_clock_t clock;
    spi_mode_t  mode;
    DMA_Channel_TypeDef *dmaChTx;
    DMA_Channel_TypeDef *dmaChRx;
}spi_t;
/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/
#if (SPI_CS_ACT_LEVEL == 0)
    #define SPI1_SEMAPHORE spi1_semaphore
    #define SPI_CS_ACT(port, pin)      GPIO_PIN_RESET(port, pin)
    #define SPI_CS_INACT(port, pin)    GPIO_PIN_SET(port, pin)
#else
    #define SPI_CS_ACT(port, pin)      GPIO_PIN_SET(port, pin)
    #define SPI_CS_INACT(port, pin)    GPIO_PIN_RESET(port, pin)
#endif

    
#if (SPI1_HOOK == (1))
    static inline void spi1_hook(void)
    {

    }
#endif
#if (SPI2_HOOK == (1))
    #define SPI2_SEMAPHORE max6675_solderSem
    static inline void spi2_hook(void)
    {
        BaseType_t  xHigherPriorityTaskWoken;
        xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(SPI2_SEMAPHORE, &xHigherPriorityTaskWoken);
        if(xHigherPriorityTaskWoken != pdFALSE)
        {
            portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
        }
    }
#endif
    
#if (SPI3_HOOK == (1))
    #define SPI3_SEMAPHORE max6675_drySem
    static inline void spi3_hook(void)
    {
        BaseType_t  xHigherPriorityTaskWoken;
        xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFrom ISR(SPI3_SEMAPHORE, &xHigherPriorityTaskWoken);
        if(xHigherPriorityTaskWoken != pdFALSE)
        {
            portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
        }
    }
#endif

    
/*!****************************************************************************
* Prototypes for the functions
*/
void spi_init(spi_t *spi);
void spi_transaction_DMA(spi_t *spi, void *send_data, void* recieve_data, uint16_t count);
void spi_transieve_DMA(spi_t *spi, void *send_data, uint16_t count);
void spi_send(spi_t *spi, uint16_t data);
#endif //if 0

#endif //spi_h




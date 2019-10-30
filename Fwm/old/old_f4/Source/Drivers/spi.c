/*
*@File      spi.c 
*@Author    EricMarina
*@Version   
*@Date      26.05.2017
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#if 0
//<<TODO: need release for stm32f4
#include "spi.h"
/*!****************************************************************************
* Memory
*/
#if (SPI1_USE == 1)
    static spi_t* spi1_active;
#endif
#if (SPI2_USE == 1)
    static spi_t* spi2_active;
#endif
#if (SPI3_USE == 1)
    static spi_t* spi3_active;
#endif

/*!****************************************************************************
* Functions
*/
static void spi_receiveHandler(spi_t *spi_active)
{
    spi_active->dmaChTx->CCR &= ~DMA_CCR_EN; // DMA channel disable
    spi_active->dmaChRx->CCR &= ~DMA_CCR_EN; // DMA channel disable

    SPI_CS_INACT(spi_active->cs.port, spi_active->cs.pin);

}

static void spi_trancieveHandler(spi_t *spi_active)
{
    spi_active->dmaChTx->CCR &= ~DMA_CCR_EN; // DMA channel disable        
    SPI_CS_INACT(spi_active->cs.port, spi_active->cs.pin);  
}    
    
#if (SPI1_USE == 1)
    #if (SPI1_RECEIVE == 1)
        __irq void DMA1_Channel2_IRQHandler(void)
        {
            spi_receiveHandler(spi1_active);
            DMA1->IFCR = DMA_IFCR_CGIF2;  
            #if (SPI1_HOOK == (1))
                spi1_hook();
            #endif
        }
    #else
        __irq void DMA1_Channel3_IRQHandler(void)
        {
            spi_trancieveHandler(spi1_active);
            DMA1->IFCR = DMA_IFCR_CGIF3;
            #if (SPI1_HOOK == (1))
                spi1_hook();
            #endif
        }
    #endif
#endif

#if (SPI2_USE == 1)
    #if (SPI2_RECEIVE == 1)
        __irq void DMA1_Channel4_IRQHandler(void)
        {
            spi_receiveHandler(spi2_active);
            DMA1->IFCR = DMA_IFCR_CGIF4;
            #if (SPI2_HOOK == (1))
                spi2_hook();
            #endif
        }
    #else
        __irq void DMA1_Channel5_IRQHandler(void)
        {
            spi_trancieveHandler(spi2_active);
            DMA1->IFCR = DMA_IFCR_CGIF5;
            #if (SPI2_HOOK == (1))
                spi2_hook();
            #endif
        }
    #endif
#endif

#if (SPI3_USE == 1)
    #if (SPI3_RECEIVE == 1)
        __irq void DMA2_Channel1_IRQHandler(void)
        {
            spi_receiveHandler(spi3_active);
            DMA2->IFCR = DMA_IFCR_CGIF1;
            #if (SPI3_HOOK == (1))
                spi3_hook();
            #endif
        }
    #else
        __irq void DMA2_Channel2_IRQHandler(void)
        {
            spi_trancieveHandler(spi3_active);
            DMA2->IFCR = DMA_IFCR_CGIF2;
            #if (SPI3_HOOK == (1))
                spi3_hook();
            #endif
        }
    #endif
#endif



void spi_init(spi_t *spi)
{
    

    if (spi->spi == SPI1)
    {
        /************************************************
        * clock
        */
        RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
        RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
        RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
        /************************************************
        * GPIO
        */    
        #if (SPI1_PINREMAP == (0))
            __GPIO_Init(GPIOA, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, GPIO_Mode_AlternateFunctionOutputPushPull);
        #else            
            AFIO->MAPR |= AFIO_MAPR_SPI1_REMAP;
            __GPIO_Init(GPIOB, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5, GPIO_Mode_AlternateFunctionOutputPushPull);
        #endif
            
        /************************************************
        * DMA
        */   
        #if (SPI1_DMA_USE == (1))
            RCC->AHBENR |= RCC_AHBENR_DMA2EN;            

            //--TX 
            spi->dmaChTx = DMA1_Channel3;
            spi->dmaChTx->CCR = 0;
            spi->dmaChTx->CCR |= DMA_CCR_PL_1; // Priority level High
            spi->dmaChTx->CCR |= DMA_CCR_MINC; //memory increment mode - enable
            spi->dmaChTx->CCR |= DMA_CCR_TCIE;
            spi->dmaChTx->CCR |= DMA_CCR_DIR; //read from memory
            spi->dmaChTx->CPAR = (uint32_t)&spi->spi->DR;       
            spi->spi->CR2 |= SPI_CR2_TXDMAEN;
            //--RX
            #if (SPI1_RECEIVE == (1))   
                spi->dmaChRx = DMA1_Channel2;
                spi->dmaChRx->CCR = 0;
                spi->dmaChRx->CCR |= DMA_CCR_PL_1; // Priority level High
                spi->dmaChRx->CCR |= DMA_CCR_MINC; //memory increment mode - enable
                spi->dmaChRx->CCR |= DMA_CCR_TCIE;
                spi->dmaChRx->CPAR = (uint32_t)&spi->spi->DR; 
                spi->spi->CR2 |= SPI_CR2_RXDMAEN;
            #endif
        #endif
        
        /************************************************
        * data frame format
        */                    
        #if (SPI1_16BIT == 1)
            spi->spi->CR1 |= SPI_CR1_DFF;
            
            spi->dmaChRx->CCR |= DMA_CCR_MSIZE_0; //Memory size - 16 bit
            spi->dmaChRx->CCR |= DMA_CCR_PSIZE_0; //Peripheral size - 16 bit
            
            spi->dmaChTx->CCR |= DMA_CCR_MSIZE_0; //Memory size - 16 bit
            spi->dmaChTx->CCR |= DMA_CCR_PSIZE_0; //Peripheral size - 16 bit
        #endif   
        /************************************************
        * NVIC
        */ 
        #if (SPI1_RECEIVE == 1)
            NVIC_SetPriority(DMA1_Channel2_IRQn, SPI1_RX_DMA_PRIOR);  
            NVIC_EnableIRQ(DMA1_Channel2_IRQn);  
        #else
            NVIC_SetPriority(DMA1_Channel3_IRQn, SPI1_TX_DMA_PRIOR);                        
            NVIC_EnableIRQ(DMA1_Channel3_IRQn); 
        #endif
    }
    if (spi->spi == SPI2)
    {
        /************************************************
        * clock
        */
        RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
        RCC->APB1RSTR |= RCC_APB1RSTR_SPI2RST;
        RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI2RST;
        /************************************************
        * GPIO
        */ 
        __GPIO_Init(GPIOB, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, GPIO_Mode_AlternateFunctionOutputPushPull);
        /************************************************
        * DMA
        */   
        #if (SPI2_DMA_USE == (1))
            RCC->AHBENR |= RCC_AHBENR_DMA1EN;            

            //--TX 
            spi->dmaChTx = DMA1_Channel5;
            spi->dmaChTx->CCR = 0;
            spi->dmaChTx->CCR |= DMA_CCR_PL_1; // Priority level High
            spi->dmaChTx->CCR |= DMA_CCR_MINC; //memory increment mode - enable
            spi->dmaChTx->CCR |= DMA_CCR_TCIE;
            spi->dmaChTx->CCR |= DMA_CCR_DIR; //read from memory
            spi->dmaChTx->CPAR = (uint32_t)&spi->spi->DR;       
            spi->spi->CR2 |= SPI_CR2_TXDMAEN;
            //--RX
            #if (SPI2_RECEIVE == (1))   
                spi->dmaChRx = DMA1_Channel4;
                spi->dmaChRx->CCR = 0;
                spi->dmaChRx->CCR |= DMA_CCR_PL_1; // Priority level High
                spi->dmaChRx->CCR |= DMA_CCR_MINC; //memory increment mode - enable
                spi->dmaChRx->CCR |= DMA_CCR_TCIE;
                spi->dmaChRx->CPAR = (uint32_t)&spi->spi->DR; 
                spi->spi->CR2 |= SPI_CR2_RXDMAEN;
            #endif
        #endif
        /************************************************
        * data frame format
        */                    
        #if (SPI2_16BIT == 1)
            spi->spi->CR1 |= SPI_CR1_DFF;
            
            spi->dmaChRx->CCR |= DMA_CCR_MSIZE_0; //Memory size - 16 bit
            spi->dmaChRx->CCR |= DMA_CCR_PSIZE_0; //Peripheral size - 16 bit
            
            spi->dmaChTx->CCR |= DMA_CCR_MSIZE_0; //Memory size - 16 bit
            spi->dmaChTx->CCR |= DMA_CCR_PSIZE_0; //Peripheral size - 16 bit
        #endif    
        /************************************************
        * NVIC
        */ 
        #if (SPI2_RECEIVE == 1)
            NVIC_SetPriority(DMA1_Channel4_IRQn, SPI2_RX_DMA_PRIOR);  
            NVIC_EnableIRQ(DMA1_Channel4_IRQn);  
        #else
            NVIC_SetPriority(DMA1_Channel5_IRQn, SPI2_TX_DMA_PRIOR);                        
            NVIC_EnableIRQ(DMA1_Channel5_IRQn); 
        #endif
    }
    
    if (spi->spi == SPI3)
    {
        /************************************************
        * clock
        */
        RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
        RCC->APB1RSTR |= RCC_APB1RSTR_SPI3RST;
        RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI3RST;
        /************************************************
        * GPIO
        */  
        #if (SPI3_PINREMAP == 0)
            __GPIO_Init(GPIOB, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5, GPIO_Mode_AlternateFunctionOutputPushPull);
        #else            
            AFIO->MAPR |= AFIO_MAPR_SPI3_REMAP;
            __GPIO_Init(GPIOC, GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12, GPIO_Mode_AlternateFunctionOutputPushPull);
        #endif
            
        /************************************************
        * DMA
        */   
        #if (SPI3_DMA_USE == (1))
            RCC->AHBENR |= RCC_AHBENR_DMA2EN;            

            //--TX 
            
            spi->dmaChTx = DMA2_Channel2;
            spi->dmaChTx->CCR = 0;
            spi->dmaChTx->CCR |= DMA_CCR_PL_1; // Priority level High
            spi->dmaChTx->CCR |= DMA_CCR_MINC; //memory increment mode - enable
            spi->dmaChTx->CCR |= DMA_CCR_TCIE;
            spi->dmaChTx->CCR |= DMA_CCR_DIR; //read from memory
            spi->dmaChTx->CPAR = (uint32_t)&spi->spi->DR;       
            spi->spi->CR2 |= SPI_CR2_TXDMAEN;
            //--RX
            #if (SPI3_RECEIVE == (1))   
                spi->dmaChRx = DMA2_Channel1;
                spi->dmaChRx->CCR = 0;
                spi->dmaChRx->CCR |= DMA_CCR_PL_1; // Priority level High
                spi->dmaChRx->CCR |= DMA_CCR_MINC; //memory increment mode - enable
                spi->dmaChRx->CCR |= DMA_CCR_TCIE;
                spi->dmaChRx->CPAR = (uint32_t)&spi->spi->DR; 
                spi->spi->CR2 |= SPI_CR2_RXDMAEN;
            #endif
        #endif
        /************************************************
        * data frame format
        */
            
        #if (SPI3_16BIT == (1))
            spi->spi->CR1 |= SPI_CR1_DFF;
            spi->dmaChRx->CCR |= DMA_CCR_MSIZE_0; //Memory size - 16 bit
            spi->dmaChRx->CCR |= DMA_CCR_PSIZE_0; //Peripheral size - 16 bit
            
            spi->dmaChTx->CCR |= DMA_CCR_MSIZE_0; //Memory size - 16 bit
            spi->dmaChTx->CCR |= DMA_CCR_PSIZE_0; //Peripheral size - 16 bit
        #endif  
        /************************************************
        * NVIC
        */ 
        #if (SPI3_RECEIVE == 1)
            NVIC_SetPriority(DMA2_Channel1_IRQn, SPI3_RX_DMA_PRIOR);  
            NVIC_EnableIRQ(DMA2_Channel1_IRQn);  
        #else
            NVIC_SetPriority(DMA2_Channel2_IRQn, SPI3_TX_DMA_PRIOR);                        
            NVIC_EnableIRQ(DMA2_Channel2_IRQn); 
        #endif
          
    }
    
    /************************************************
    * CS
    */      
    GPIO_Init(spi->cs.port, spi->cs.pin, GPIO_Mode_OutPushPull);
    SPI_CS_INACT(spi->cs.port, spi->cs.pin);
        
    /************************************************
    * DMA
    */  

    /************************************************
    * configuaration
    */          

    if (spi->dev == SPI_DEV_MASTER)
    {
        spi->spi->CR1 |= SPI_CR1_SSM | SPI_CR1_MSTR | SPI_CR1_SSI;
    }
    else
    {
        
    }
    spi->spi->CR1 |= (spi->clock << 3);
    spi->spi->CR1 |= (spi->mode); 

    spi->spi->CR1 |= SPI_CR1_SPE;
   
}

void spi_transaction_DMA(spi_t *spi, void *send_data, void* recieve_data, uint16_t count)
{
    spi->dmaChTx->CMAR = (uint32_t)send_data;
    spi->dmaChTx->CNDTR= count;
  
    spi->dmaChRx->CMAR = (uint32_t)recieve_data;
    spi->dmaChRx->CNDTR= count;
    
    #if (SPI1_USE == 1)
        if (spi->spi == SPI1) spi1_active = spi;
    #endif
    #if (SPI2_USE == 1)  
        if (spi->spi == SPI2) spi2_active = spi;
    #endif
    #if (SPI3_USE == 1)    
        if (spi->spi == SPI3) spi3_active = spi;
    #endif
    
    SPI_CS_ACT(spi->cs.port, spi->cs.pin);
    spi->dmaChTx->CCR |= DMA_CCR_EN; // DMA channel enable
    spi->dmaChRx->CCR |= DMA_CCR_EN; // DMA channel enable
}

void spi_transieve_DMA(spi_t *spi, void *send_data, uint16_t count)
{
    spi->dmaChTx->CMAR = (uint32_t)send_data;
    spi->dmaChTx->CNDTR= count;
  
    #if (SPI1_USE == 1)
        if (spi->spi == SPI1) spi1_active = spi;
    #endif
    #if (SPI2_USE == 1)  
        if (spi->spi == SPI2) spi2_active = spi;
    #endif
    #if (SPI3_USE == 1)    
        if (spi->spi == SPI3) spi3_active = spi;
    #endif
    
    SPI_CS_ACT(spi->cs.port, spi->cs.pin);
    spi->dmaChTx->CCR |= DMA_CCR_EN; // DMA channel enable
}
void spi_send(spi_t *spi, uint16_t data)
{
    SPI_CS_ACT(spi->cs.port, spi->cs.pin);
    spi->spi->DR = data;
    while(READ_BIT(spi->spi->SR, SPI_SR_BSY)) __NOP();
    SPI_CS_INACT(spi->cs.port, spi->cs.pin);
}
#endif 
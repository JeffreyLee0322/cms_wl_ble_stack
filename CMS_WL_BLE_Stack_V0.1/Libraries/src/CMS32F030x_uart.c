#include "CMS32F030x_uart.h"

/**
  * @brief  Deinitializes the UARTx peripheral registers to their default reset values.
  * @param  UARTx: where x can be from 0 or 1 to select the UART peripheral.
  * @retval None
  */
void UART_DeInit(UART_TypeDef* UARTx)
{
    if(UARTx == UART0)
        SYSCON->APBCKEN &= ~SYS_APB_UART0CE;
    else if(UARTx == UART1)
        SYSCON->APBCKEN &= ~SYS_APB_UART1CE;
}

/**
  * @brief  Initializes the UARTx peripheral according to the specified
  *         parameters in the USART_InitStruct .
  * @param  USARTx: where x can be from 0 or 1 to select the UART peripheral.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure that contains
  *         the configuration information for the specified USART peripheral.
  * @retval None
  */
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{
    uint32_t uartReg = 0;
    SystemCoreClockUpdate();
    UARTx->DLR = SystemAPBClock/(16*UART_InitStruct->UART_BaudRate);
    uartReg = UART_InitStruct->UART_Parity | UART_InitStruct->UART_ParityType + \
                UART_InitStruct->UART_StopBits + UART_InitStruct->UART_WordLength;
    UARTx->LCR = uartReg;
}

/**
  * @brief  Fills each UART_InitTypeDef member with its default value.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
    UART_InitStruct->UART_BaudRate = 9600;
    UART_InitStruct->UART_Parity     = UART_Parity_Disable;;
    UART_InitStruct->UART_WordLength = UART_WordLength_8b;
    UART_InitStruct->UART_StopBits   = UART_StopBits_1;
}

/**
  * @brief  Transmits single data through the UARTx peripheral.
  * @param  UARTx: where x can be from 0 or 1 to select the UART peripheral.
  * @param  Data: the data to transmit.
  * @retval None
  */
void UART_SendData(UART_TypeDef* UARTx, uint16_t Data)
{
    while(!((UARTx->LSR >> 6) & 0x01));
    UARTx->THR = Data & 0xFF;
}

/**
  * @brief  Returns the most recent received data by the UARTx peripheral.
  * @param  UARTx: where x can be from 0 or 1 to select the UART peripheral.
  * @retval The received data.
  */
uint8_t UART_ReceiveData(UART_TypeDef* UARTx)
{
    uint8_t data=0;
    if(UARTx->LSR & 0x01)
     data = (UARTx->RBR & 0xFF);
    return data;
}
/************************FIFO Control functions*******************/
/**
  * @brief  UART peripheral FIFO config.
  * @param  UARTx: where x can be from 0 or 1 to select the UART peripheral.
  * @param  UART_FIFOInitStruct: pointer to a UART_InitFifoTypeDef structure that contains
  *         the configuration information for the specified FIFO.
  * @retval none.
  */
void UART_FIFOControl(UART_TypeDef* UARTx,UART_InitFifoTypeDef* UART_FIFOInitStruct)
{
	UARTx->FCR |= (UART_FIFOInitStruct->UART_FCR_RXTL | UART_FIFOInitStruct->UART_FCR_TXTL);
}

/**
  * @brief  UART peripheral transmit FIFO reset.
  * @param  UARTx: where x can be from 0 or 1 to select the UART peripheral.
  * @retval none.
  */
void UART_FIFORstTx(UART_TypeDef* UARTx)
{
    UARTx->FCR |= 1<<2;
}

/**
  * @brief  UART peripheral receive FIFO reset.
  * @param  UARTx: where x can be from 0 or 1 to select the UART peripheral.
  * @retval none.
  */
void UART_FIFORstRx(UART_TypeDef* UARTx)
{
    UARTx->FCR |= 1<<1;
}

/**
  * @brief  UART peripheral FIFO reset enable/disable.
  * @param  UARTx: where x can be from 0 or 1 to select the UART peripheral.
  * @param  NewState: new state of the UARTx peripheral. 
  *          This parameter can be: ENABLE or DISABLE. 
  * @retval none.
  */
void UART_FIFOCmd(UART_TypeDef* UARTx,FunctionalState NewStatus)
{
    if(NewStatus != DISABLE)
    {
        UARTx->FCR |= 1<<0;
    }
    else
    {
        UARTx->FCR &= ~(1<<0);
    }
}

/* Interrupts and flags management functions **********************************/

/**
  * @brief  Enables or disables the specified UART interrupts.
  * @param  USARTx: where x can be from 0 or 1 to select the USART peripheral.
  * @param  UART_IT: specifies the USART interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
*            @arg UART_IER_RBRIE  :RX Buffer Register Interrupt
*            @arg UART_IER_THREIE :TX Holding Register Empty Interrupt
*            @arg UART_IER_RLSIE  :RX Line Status Interrupt
*            @arg UART_IER_MDSIE  :Modem Status Interrupt 
*            @arg UART_IER_XOFIE  :XOFF Interrupt
*            @arg UART_IER_RTSIE  :RTS Interrupt
*            @arg UART_IER_CTSIE  :CTS Interrupt
  * @param  NewState: new state of the specified UARTx interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_ITConfig(UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        UARTx->IER |= UART_IT;
    }
    else
    {
        UARTx->IER &= ~UART_IT;
    }
}

/**
  * @brief  Checks whether the specified USART interrupt has occurred or not.
  * @param  UARTx: where x can be from 0 or 1 to select the UART peripheral.
  * @retval IT_UART_StatusType :detail please check for IT_UART_StatusType enum structure.
  */
IT_UART_StatusType UART_GetITStatus(UART_TypeDef* UARTx)
{
    IT_UART_StatusType itStatus = IT_UART_No;
    if(!(UARTx->IIR & 0x01))
    {
        switch((UARTx->IIR >> 1) & 7)
        {
            case 0x00 :
            {
                itStatus = IT_UART_ModemStachange;
            }break;
            
            case 0x01 :
            {
                itStatus = IT_UART_TXEmpt;
            }break;
            
            case 0x02 :
            {
                itStatus = IT_UART_RecData;
            }break;
            
            case 0x03 :
            {
                itStatus = IT_UART_RecLine;
            }break;
            
            case 0x06 :
            {
                itStatus = IT_UART_ReceiveFifo;
            }break;
        }
    }
    return itStatus;
}

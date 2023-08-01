/***************************************************************************//**
* \file cyUart_p50_p51_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_cyUart_p50_p51_H)
#define CY_SCB_SPI_UART_PVT_cyUart_p50_p51_H

#include "cyUart_p50_p51_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (cyUart_p50_p51_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  cyUart_p50_p51_rxBufferHead;
    extern volatile uint32  cyUart_p50_p51_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   cyUart_p50_p51_rxBufferOverflow;
    /** @} globals */
#endif /* (cyUart_p50_p51_INTERNAL_RX_SW_BUFFER_CONST) */

#if (cyUart_p50_p51_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  cyUart_p50_p51_txBufferHead;
    extern volatile uint32  cyUart_p50_p51_txBufferTail;
#endif /* (cyUart_p50_p51_INTERNAL_TX_SW_BUFFER_CONST) */

#if (cyUart_p50_p51_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 cyUart_p50_p51_rxBufferInternal[cyUart_p50_p51_INTERNAL_RX_BUFFER_SIZE];
#endif /* (cyUart_p50_p51_INTERNAL_RX_SW_BUFFER) */

#if (cyUart_p50_p51_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 cyUart_p50_p51_txBufferInternal[cyUart_p50_p51_TX_BUFFER_SIZE];
#endif /* (cyUart_p50_p51_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void cyUart_p50_p51_SpiPostEnable(void);
void cyUart_p50_p51_SpiStop(void);

#if (cyUart_p50_p51_SCB_MODE_SPI_CONST_CFG)
    void cyUart_p50_p51_SpiInit(void);
#endif /* (cyUart_p50_p51_SCB_MODE_SPI_CONST_CFG) */

#if (cyUart_p50_p51_SPI_WAKE_ENABLE_CONST)
    void cyUart_p50_p51_SpiSaveConfig(void);
    void cyUart_p50_p51_SpiRestoreConfig(void);
#endif /* (cyUart_p50_p51_SPI_WAKE_ENABLE_CONST) */

void cyUart_p50_p51_UartPostEnable(void);
void cyUart_p50_p51_UartStop(void);

#if (cyUart_p50_p51_SCB_MODE_UART_CONST_CFG)
    void cyUart_p50_p51_UartInit(void);
#endif /* (cyUart_p50_p51_SCB_MODE_UART_CONST_CFG) */

#if (cyUart_p50_p51_UART_WAKE_ENABLE_CONST)
    void cyUart_p50_p51_UartSaveConfig(void);
    void cyUart_p50_p51_UartRestoreConfig(void);
#endif /* (cyUart_p50_p51_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in cyUart_p50_p51_SetPins() */
#define cyUart_p50_p51_UART_RX_PIN_ENABLE    (cyUart_p50_p51_UART_RX)
#define cyUart_p50_p51_UART_TX_PIN_ENABLE    (cyUart_p50_p51_UART_TX)

/* UART RTS and CTS position to be used in  cyUart_p50_p51_SetPins() */
#define cyUart_p50_p51_UART_RTS_PIN_ENABLE    (0x10u)
#define cyUart_p50_p51_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define cyUart_p50_p51_SpiUartEnableIntRx(intSourceMask)  cyUart_p50_p51_SetRxInterruptMode(intSourceMask)
#define cyUart_p50_p51_SpiUartEnableIntTx(intSourceMask)  cyUart_p50_p51_SetTxInterruptMode(intSourceMask)
uint32  cyUart_p50_p51_SpiUartDisableIntRx(void);
uint32  cyUart_p50_p51_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_cyUart_p50_p51_H) */


/* [] END OF FILE */

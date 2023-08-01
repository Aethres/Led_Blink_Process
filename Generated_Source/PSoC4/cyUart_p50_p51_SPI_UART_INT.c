/***************************************************************************//**
* \file cyUart_p50_p51_SPI_UART_INT.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cyUart_p50_p51_PVT.h"
#include "cyUart_p50_p51_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (cyUart_p50_p51_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: cyUart_p50_p51_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(cyUart_p50_p51_SPI_UART_ISR)
{
#if (cyUart_p50_p51_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (cyUart_p50_p51_INTERNAL_RX_SW_BUFFER_CONST) */

#if (cyUart_p50_p51_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (cyUart_p50_p51_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef cyUart_p50_p51_SPI_UART_ISR_ENTRY_CALLBACK
    cyUart_p50_p51_SPI_UART_ISR_EntryCallback();
#endif /* cyUart_p50_p51_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != cyUart_p50_p51_customIntrHandler)
    {
        cyUart_p50_p51_customIntrHandler();
    }

    #if(cyUart_p50_p51_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        cyUart_p50_p51_ClearSpiExtClkInterruptSource(cyUart_p50_p51_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (cyUart_p50_p51_CHECK_RX_SW_BUFFER)
    {
        if (cyUart_p50_p51_CHECK_INTR_RX_MASKED(cyUart_p50_p51_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (cyUart_p50_p51_rxBufferHead + 1u);

                /* Adjust local head index */
                if (cyUart_p50_p51_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == cyUart_p50_p51_rxBufferTail)
                {
                    #if (cyUart_p50_p51_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        cyUart_p50_p51_INTR_RX_MASK_REG &= ~cyUart_p50_p51_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) cyUart_p50_p51_RX_FIFO_RD_REG;
                        cyUart_p50_p51_rxBufferOverflow = (uint8) cyUart_p50_p51_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    cyUart_p50_p51_PutWordInRxBuffer(locHead, cyUart_p50_p51_RX_FIFO_RD_REG);

                    /* Move head index */
                    cyUart_p50_p51_rxBufferHead = locHead;
                }
            }
            while(0u != cyUart_p50_p51_GET_RX_FIFO_ENTRIES);

            cyUart_p50_p51_ClearRxInterruptSource(cyUart_p50_p51_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (cyUart_p50_p51_CHECK_TX_SW_BUFFER)
    {
        if (cyUart_p50_p51_CHECK_INTR_TX_MASKED(cyUart_p50_p51_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (cyUart_p50_p51_txBufferHead != cyUart_p50_p51_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (cyUart_p50_p51_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (cyUart_p50_p51_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    cyUart_p50_p51_TX_FIFO_WR_REG = cyUart_p50_p51_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    cyUart_p50_p51_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    cyUart_p50_p51_DISABLE_INTR_TX(cyUart_p50_p51_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (cyUart_p50_p51_SPI_UART_FIFO_SIZE != cyUart_p50_p51_GET_TX_FIFO_ENTRIES);

            cyUart_p50_p51_ClearTxInterruptSource(cyUart_p50_p51_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef cyUart_p50_p51_SPI_UART_ISR_EXIT_CALLBACK
    cyUart_p50_p51_SPI_UART_ISR_ExitCallback();
#endif /* cyUart_p50_p51_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (cyUart_p50_p51_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */

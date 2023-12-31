/***************************************************************************//**
* \file cyUart_p50_p51_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cyUart_p50_p51_PVT.h"
#include "cyUart_p50_p51_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (cyUart_p50_p51_UART_WAKE_ENABLE_CONST && cyUart_p50_p51_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when cyUart_p50_p51_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 cyUart_p50_p51_skipStart = 1u;
    /** \} globals */
#endif /* (cyUart_p50_p51_UART_WAKE_ENABLE_CONST && cyUart_p50_p51_UART_RX_WAKEUP_IRQ) */

#if(cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const cyUart_p50_p51_UART_INIT_STRUCT cyUart_p50_p51_configUart =
    {
        cyUart_p50_p51_UART_SUB_MODE,
        cyUart_p50_p51_UART_DIRECTION,
        cyUart_p50_p51_UART_DATA_BITS_NUM,
        cyUart_p50_p51_UART_PARITY_TYPE,
        cyUart_p50_p51_UART_STOP_BITS_NUM,
        cyUart_p50_p51_UART_OVS_FACTOR,
        cyUart_p50_p51_UART_IRDA_LOW_POWER,
        cyUart_p50_p51_UART_MEDIAN_FILTER_ENABLE,
        cyUart_p50_p51_UART_RETRY_ON_NACK,
        cyUart_p50_p51_UART_IRDA_POLARITY,
        cyUart_p50_p51_UART_DROP_ON_PARITY_ERR,
        cyUart_p50_p51_UART_DROP_ON_FRAME_ERR,
        cyUart_p50_p51_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        cyUart_p50_p51_UART_MP_MODE_ENABLE,
        cyUart_p50_p51_UART_MP_ACCEPT_ADDRESS,
        cyUart_p50_p51_UART_MP_RX_ADDRESS,
        cyUart_p50_p51_UART_MP_RX_ADDRESS_MASK,
        (uint32) cyUart_p50_p51_SCB_IRQ_INTERNAL,
        cyUart_p50_p51_UART_INTR_RX_MASK,
        cyUart_p50_p51_UART_RX_TRIGGER_LEVEL,
        cyUart_p50_p51_UART_INTR_TX_MASK,
        cyUart_p50_p51_UART_TX_TRIGGER_LEVEL,
        (uint8) cyUart_p50_p51_UART_BYTE_MODE_ENABLE,
        (uint8) cyUart_p50_p51_UART_CTS_ENABLE,
        (uint8) cyUart_p50_p51_UART_CTS_POLARITY,
        (uint8) cyUart_p50_p51_UART_RTS_POLARITY,
        (uint8) cyUart_p50_p51_UART_RTS_FIFO_LEVEL,
        (uint8) cyUart_p50_p51_UART_RX_BREAK_WIDTH
    };


    /*******************************************************************************
    * Function Name: cyUart_p50_p51_UartInit
    ****************************************************************************//**
    *
    *  Configures the cyUart_p50_p51 for UART operation.
    *
    *  This function is intended specifically to be used when the cyUart_p50_p51
    *  configuration is set to “Unconfigured cyUart_p50_p51” in the customizer.
    *  After initializing the cyUart_p50_p51 in UART mode using this function,
    *  the component can be enabled using the cyUart_p50_p51_Start() or
    * cyUart_p50_p51_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void cyUart_p50_p51_UartInit(const cyUart_p50_p51_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (cyUart_p50_p51_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (cyUart_p50_p51_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1) */

            /* Configure pins */
            cyUart_p50_p51_SetPins(cyUart_p50_p51_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            cyUart_p50_p51_scbMode       = (uint8) cyUart_p50_p51_SCB_MODE_UART;
            cyUart_p50_p51_scbEnableWake = (uint8) config->enableWake;
            cyUart_p50_p51_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            cyUart_p50_p51_rxBuffer      =         config->rxBuffer;
            cyUart_p50_p51_rxDataBits    = (uint8) config->dataBits;
            cyUart_p50_p51_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            cyUart_p50_p51_txBuffer      =         config->txBuffer;
            cyUart_p50_p51_txDataBits    = (uint8) config->dataBits;
            cyUart_p50_p51_txBufferSize  =         config->txBufferSize;

            /* Configure UART interface */
            if(cyUart_p50_p51_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                cyUart_p50_p51_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (cyUart_p50_p51_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (cyUart_p50_p51_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                cyUart_p50_p51_CTRL_REG  = cyUart_p50_p51_GET_CTRL_OVS(config->oversample);
            }

            cyUart_p50_p51_CTRL_REG     |= cyUart_p50_p51_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             cyUart_p50_p51_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             cyUart_p50_p51_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            cyUart_p50_p51_UART_CTRL_REG = cyUart_p50_p51_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            cyUart_p50_p51_UART_RX_CTRL_REG = cyUart_p50_p51_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        cyUart_p50_p51_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        cyUart_p50_p51_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        cyUart_p50_p51_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        cyUart_p50_p51_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr)   |
                                        cyUart_p50_p51_GET_UART_RX_CTRL_BREAK_WIDTH(config->breakWidth);

            if(cyUart_p50_p51_UART_PARITY_NONE != config->parity)
            {
               cyUart_p50_p51_UART_RX_CTRL_REG |= cyUart_p50_p51_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    cyUart_p50_p51_UART_RX_CTRL_PARITY_ENABLED;
            }

            cyUart_p50_p51_RX_CTRL_REG      = cyUart_p50_p51_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                cyUart_p50_p51_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                cyUart_p50_p51_GET_UART_RX_CTRL_ENABLED(config->direction);

            cyUart_p50_p51_RX_FIFO_CTRL_REG = cyUart_p50_p51_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            cyUart_p50_p51_RX_MATCH_REG     = cyUart_p50_p51_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                cyUart_p50_p51_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            cyUart_p50_p51_UART_TX_CTRL_REG = cyUart_p50_p51_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                cyUart_p50_p51_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(cyUart_p50_p51_UART_PARITY_NONE != config->parity)
            {
               cyUart_p50_p51_UART_TX_CTRL_REG |= cyUart_p50_p51_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    cyUart_p50_p51_UART_TX_CTRL_PARITY_ENABLED;
            }

            cyUart_p50_p51_TX_CTRL_REG      = cyUart_p50_p51_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                cyUart_p50_p51_GET_UART_TX_CTRL_ENABLED(config->direction);

            cyUart_p50_p51_TX_FIFO_CTRL_REG = cyUart_p50_p51_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1)
            cyUart_p50_p51_UART_FLOW_CTRL_REG = cyUart_p50_p51_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            cyUart_p50_p51_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            cyUart_p50_p51_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            cyUart_p50_p51_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (cyUart_p50_p51_ISR_NUMBER);
            CyIntSetPriority(cyUart_p50_p51_ISR_NUMBER, cyUart_p50_p51_ISR_PRIORITY);
            (void) CyIntSetVector(cyUart_p50_p51_ISR_NUMBER, &cyUart_p50_p51_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(cyUart_p50_p51_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (cyUart_p50_p51_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(cyUart_p50_p51_RX_WAKE_ISR_NUMBER, cyUart_p50_p51_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(cyUart_p50_p51_RX_WAKE_ISR_NUMBER, &cyUart_p50_p51_UART_WAKEUP_ISR);
        #endif /* (cyUart_p50_p51_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            cyUart_p50_p51_INTR_I2C_EC_MASK_REG = cyUart_p50_p51_NO_INTR_SOURCES;
            cyUart_p50_p51_INTR_SPI_EC_MASK_REG = cyUart_p50_p51_NO_INTR_SOURCES;
            cyUart_p50_p51_INTR_SLAVE_MASK_REG  = cyUart_p50_p51_NO_INTR_SOURCES;
            cyUart_p50_p51_INTR_MASTER_MASK_REG = cyUart_p50_p51_NO_INTR_SOURCES;
            cyUart_p50_p51_INTR_RX_MASK_REG     = config->rxInterruptMask;
            cyUart_p50_p51_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Configure TX interrupt sources to restore. */
            cyUart_p50_p51_IntrTxMask = LO16(cyUart_p50_p51_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            cyUart_p50_p51_rxBufferHead     = 0u;
            cyUart_p50_p51_rxBufferTail     = 0u;
            cyUart_p50_p51_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            cyUart_p50_p51_txBufferHead = 0u;
            cyUart_p50_p51_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: cyUart_p50_p51_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void cyUart_p50_p51_UartInit(void)
    {
        /* Configure UART interface */
        cyUart_p50_p51_CTRL_REG = cyUart_p50_p51_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        cyUart_p50_p51_UART_CTRL_REG = cyUart_p50_p51_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        cyUart_p50_p51_UART_RX_CTRL_REG = cyUart_p50_p51_UART_DEFAULT_UART_RX_CTRL;
        cyUart_p50_p51_RX_CTRL_REG      = cyUart_p50_p51_UART_DEFAULT_RX_CTRL;
        cyUart_p50_p51_RX_FIFO_CTRL_REG = cyUart_p50_p51_UART_DEFAULT_RX_FIFO_CTRL;
        cyUart_p50_p51_RX_MATCH_REG     = cyUart_p50_p51_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        cyUart_p50_p51_UART_TX_CTRL_REG = cyUart_p50_p51_UART_DEFAULT_UART_TX_CTRL;
        cyUart_p50_p51_TX_CTRL_REG      = cyUart_p50_p51_UART_DEFAULT_TX_CTRL;
        cyUart_p50_p51_TX_FIFO_CTRL_REG = cyUart_p50_p51_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1)
        cyUart_p50_p51_UART_FLOW_CTRL_REG = cyUart_p50_p51_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(cyUart_p50_p51_SCB_IRQ_INTERNAL)
        CyIntDisable    (cyUart_p50_p51_ISR_NUMBER);
        CyIntSetPriority(cyUart_p50_p51_ISR_NUMBER, cyUart_p50_p51_ISR_PRIORITY);
        (void) CyIntSetVector(cyUart_p50_p51_ISR_NUMBER, &cyUart_p50_p51_SPI_UART_ISR);
    #endif /* (cyUart_p50_p51_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(cyUart_p50_p51_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (cyUart_p50_p51_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(cyUart_p50_p51_RX_WAKE_ISR_NUMBER, cyUart_p50_p51_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(cyUart_p50_p51_RX_WAKE_ISR_NUMBER, &cyUart_p50_p51_UART_WAKEUP_ISR);
    #endif /* (cyUart_p50_p51_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        cyUart_p50_p51_INTR_I2C_EC_MASK_REG = cyUart_p50_p51_UART_DEFAULT_INTR_I2C_EC_MASK;
        cyUart_p50_p51_INTR_SPI_EC_MASK_REG = cyUart_p50_p51_UART_DEFAULT_INTR_SPI_EC_MASK;
        cyUart_p50_p51_INTR_SLAVE_MASK_REG  = cyUart_p50_p51_UART_DEFAULT_INTR_SLAVE_MASK;
        cyUart_p50_p51_INTR_MASTER_MASK_REG = cyUart_p50_p51_UART_DEFAULT_INTR_MASTER_MASK;
        cyUart_p50_p51_INTR_RX_MASK_REG     = cyUart_p50_p51_UART_DEFAULT_INTR_RX_MASK;
        cyUart_p50_p51_INTR_TX_MASK_REG     = cyUart_p50_p51_UART_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        cyUart_p50_p51_IntrTxMask = LO16(cyUart_p50_p51_INTR_TX_MASK_REG);

    #if(cyUart_p50_p51_INTERNAL_RX_SW_BUFFER_CONST)
        cyUart_p50_p51_rxBufferHead     = 0u;
        cyUart_p50_p51_rxBufferTail     = 0u;
        cyUart_p50_p51_rxBufferOverflow = 0u;
    #endif /* (cyUart_p50_p51_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(cyUart_p50_p51_INTERNAL_TX_SW_BUFFER_CONST)
        cyUart_p50_p51_txBufferHead = 0u;
        cyUart_p50_p51_txBufferTail = 0u;
    #endif /* (cyUart_p50_p51_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: cyUart_p50_p51_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void cyUart_p50_p51_UartPostEnable(void)
{
#if (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (cyUart_p50_p51_TX_SDA_MISO_PIN)
        if (cyUart_p50_p51_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_TX_SDA_MISO_HSIOM_REG, cyUart_p50_p51_TX_SDA_MISO_HSIOM_MASK,
                                           cyUart_p50_p51_TX_SDA_MISO_HSIOM_POS, cyUart_p50_p51_TX_SDA_MISO_HSIOM_SEL_UART);
        }
    #endif /* (cyUart_p50_p51_TX_SDA_MISO_PIN_PIN) */

    #if !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1)
        #if (cyUart_p50_p51_RTS_SS0_PIN)
            if (cyUart_p50_p51_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_RTS_SS0_HSIOM_REG, cyUart_p50_p51_RTS_SS0_HSIOM_MASK,
                                               cyUart_p50_p51_RTS_SS0_HSIOM_POS, cyUart_p50_p51_RTS_SS0_HSIOM_SEL_UART);
            }
        #endif /* (cyUart_p50_p51_RTS_SS0_PIN) */
    #endif /* !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1) */

#else
    #if (cyUart_p50_p51_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_TX_HSIOM_REG, cyUart_p50_p51_TX_HSIOM_MASK,
                                       cyUart_p50_p51_TX_HSIOM_POS, cyUart_p50_p51_TX_HSIOM_SEL_UART);
    #endif /* (cyUart_p50_p51_UART_TX_PIN) */

    #if (cyUart_p50_p51_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_RTS_HSIOM_REG, cyUart_p50_p51_RTS_HSIOM_MASK,
                                       cyUart_p50_p51_RTS_HSIOM_POS, cyUart_p50_p51_RTS_HSIOM_SEL_UART);
    #endif /* (cyUart_p50_p51_UART_RTS_PIN) */
#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    cyUart_p50_p51_SetTxInterruptMode(cyUart_p50_p51_IntrTxMask);
}


/*******************************************************************************
* Function Name: cyUart_p50_p51_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void cyUart_p50_p51_UartStop(void)
{
#if(cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (cyUart_p50_p51_TX_SDA_MISO_PIN)
        if (cyUart_p50_p51_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_TX_SDA_MISO_HSIOM_REG, cyUart_p50_p51_TX_SDA_MISO_HSIOM_MASK,
                                           cyUart_p50_p51_TX_SDA_MISO_HSIOM_POS, cyUart_p50_p51_TX_SDA_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (cyUart_p50_p51_TX_SDA_MISO_PIN_PIN) */

    #if !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1)
        #if (cyUart_p50_p51_RTS_SS0_PIN)
            if (cyUart_p50_p51_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                cyUart_p50_p51_uart_rts_spi_ss0_Write(cyUart_p50_p51_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_RTS_SS0_HSIOM_REG, cyUart_p50_p51_RTS_SS0_HSIOM_MASK,
                                               cyUart_p50_p51_RTS_SS0_HSIOM_POS, cyUart_p50_p51_RTS_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (cyUart_p50_p51_RTS_SS0_PIN) */
    #endif /* !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1) */

#else
    #if (cyUart_p50_p51_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_TX_HSIOM_REG, cyUart_p50_p51_TX_HSIOM_MASK,
                                       cyUart_p50_p51_TX_HSIOM_POS, cyUart_p50_p51_TX_HSIOM_SEL_GPIO);
    #endif /* (cyUart_p50_p51_UART_TX_PIN) */

    #if (cyUart_p50_p51_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        cyUart_p50_p51_rts_Write(cyUart_p50_p51_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_RTS_HSIOM_REG, cyUart_p50_p51_RTS_HSIOM_MASK,
                                       cyUart_p50_p51_RTS_HSIOM_POS, cyUart_p50_p51_RTS_HSIOM_SEL_GPIO);
    #endif /* (cyUart_p50_p51_UART_RTS_PIN) */

#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (cyUart_p50_p51_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    cyUart_p50_p51_UART_RX_CTRL_REG &= (uint32) ~cyUart_p50_p51_UART_RX_CTRL_SKIP_START;
#endif /* (cyUart_p50_p51_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    cyUart_p50_p51_IntrTxMask = LO16(cyUart_p50_p51_GetTxInterruptMode() & cyUart_p50_p51_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: cyUart_p50_p51_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void cyUart_p50_p51_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = cyUart_p50_p51_RX_MATCH_REG;

    matchReg &= ((uint32) ~cyUart_p50_p51_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & cyUart_p50_p51_RX_MATCH_ADDR_MASK)); /* Set address  */

    cyUart_p50_p51_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: cyUart_p50_p51_UartSetRxAddressMask
****************************************************************************//**
*
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
*  \param addressMask: Address mask.
*   - Bit value 0 – excludes bit from address comparison.
*   - Bit value 1 – the bit needs to match with the corresponding bit
*     of the address.
*
*******************************************************************************/
void cyUart_p50_p51_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = cyUart_p50_p51_RX_MATCH_REG;

    matchReg &= ((uint32) ~cyUart_p50_p51_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << cyUart_p50_p51_RX_MATCH_MASK_POS));

    cyUart_p50_p51_RX_MATCH_REG = matchReg;
}


#if(cyUart_p50_p51_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: cyUart_p50_p51_UartGetChar
    ****************************************************************************//**
    *
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char where
    *  1 to 255 are valid characters and 0 indicates an error occurred or no data
    *  is present.
    *  - RX software buffer is disabled: Returns data element retrieved from RX
    *    FIFO.
    *  - RX software buffer is enabled: Returns data element from the software
    *    receive buffer.
    *
    *  \return
    *   Next data element from the receive buffer. ASCII character values from
    *   1 to 255 are valid. A returned zero signifies an error condition or no
    *   data available.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check cyUart_p50_p51_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 cyUart_p50_p51_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != cyUart_p50_p51_SpiUartGetRxBufferSize())
        {
            rxData = cyUart_p50_p51_SpiUartReadRxData();
        }

        if (cyUart_p50_p51_CHECK_INTR_RX(cyUart_p50_p51_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            cyUart_p50_p51_ClearRxInterruptSource(cyUart_p50_p51_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: cyUart_p50_p51_UartGetByte
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    *  \return
    *   Bits 7-0 contain the next data element from the receive buffer and
    *   other bits contain the error condition.
    *   - cyUart_p50_p51_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - cyUart_p50_p51_UART_RX_UNDERFLOW    Attempt to read from an empty
    *     receiver FIFO.
    *   - cyUart_p50_p51_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - cyUart_p50_p51_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check cyUart_p50_p51_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 cyUart_p50_p51_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (cyUart_p50_p51_CHECK_RX_SW_BUFFER)
        {
            cyUart_p50_p51_DisableInt();
        }
        #endif

        if (0u != cyUart_p50_p51_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (cyUart_p50_p51_CHECK_RX_SW_BUFFER)
            {
                cyUart_p50_p51_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = cyUart_p50_p51_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = cyUart_p50_p51_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            #if (cyUart_p50_p51_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                cyUart_p50_p51_ClearRxInterruptSource(cyUart_p50_p51_INTR_RX_NOT_EMPTY);

                cyUart_p50_p51_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (cyUart_p50_p51_GetRxInterruptSource() & cyUart_p50_p51_INTR_RX_ERR);
        cyUart_p50_p51_ClearRxInterruptSource(cyUart_p50_p51_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: cyUart_p50_p51_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - cyUart_p50_p51_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - cyUart_p50_p51_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void cyUart_p50_p51_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                cyUart_p50_p51_UART_FLOW_CTRL_REG |= (uint32)  cyUart_p50_p51_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                cyUart_p50_p51_UART_FLOW_CTRL_REG &= (uint32) ~cyUart_p50_p51_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: cyUart_p50_p51_UartSetRtsFifoLevel
        ****************************************************************************//**
        *
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param level: Level in the RX FIFO for RTS signal activation.
        *   The range of valid level values is between 0 and RX FIFO depth - 1.
        *   Setting level value to 0 disables RTS signal activation.
        *
        *******************************************************************************/
        void cyUart_p50_p51_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = cyUart_p50_p51_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~cyUart_p50_p51_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (cyUart_p50_p51_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            cyUart_p50_p51_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1) */

#endif /* (cyUart_p50_p51_UART_RX_DIRECTION) */


#if(cyUart_p50_p51_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: cyUart_p50_p51_UartPutString
    ****************************************************************************//**
    *
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  requested data in transmit buffer.
    *
    *  \param string: pointer to the null terminated string array to be placed in the
    *   transmit buffer.
    *
    *******************************************************************************/
    void cyUart_p50_p51_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            cyUart_p50_p51_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: cyUart_p50_p51_UartPutCRLF
    ****************************************************************************//**
    *
    *  Places byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) in the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *
    *******************************************************************************/
    void cyUart_p50_p51_UartPutCRLF(uint32 txDataByte)
    {
        cyUart_p50_p51_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        cyUart_p50_p51_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        cyUart_p50_p51_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: cyUart_p50_p51SCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void cyUart_p50_p51_UartEnableCts(void)
        {
            cyUart_p50_p51_UART_FLOW_CTRL_REG |= (uint32)  cyUart_p50_p51_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: cyUart_p50_p51_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void cyUart_p50_p51_UartDisableCts(void)
        {
            cyUart_p50_p51_UART_FLOW_CTRL_REG &= (uint32) ~cyUart_p50_p51_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: cyUart_p50_p51_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        * \param
        * polarity: Active polarity of CTS output signal.
        *   - cyUart_p50_p51_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - cyUart_p50_p51_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void cyUart_p50_p51_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                cyUart_p50_p51_UART_FLOW_CTRL_REG |= (uint32)  cyUart_p50_p51_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                cyUart_p50_p51_UART_FLOW_CTRL_REG &= (uint32) ~cyUart_p50_p51_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1) */


    /*******************************************************************************
    * Function Name: cyUart_p50_p51_UartSendBreakBlocking
    ****************************************************************************//**
    *
    * Sends a break condition (logic low) of specified width on UART TX line.
    * Blocks until break is completed. Only call this function when UART TX FIFO
    * and shifter are empty.
    *
    * \param breakWidth
    * Width of break condition. Valid range is 4 to 16 bits.
    *
    * \note
    * Before sending break all UART TX interrupt sources are disabled. The state
    * of UART TX interrupt sources is restored before function returns.
    *
    * \sideeffect
    * If this function is called while there is data in the TX FIFO or shifter that
    * data will be shifted out in packets the size of breakWidth.
    *
    *******************************************************************************/
    void cyUart_p50_p51_UartSendBreakBlocking(uint32 breakWidth)
    {
        uint32 txCtrlReg;
        uint32 txIntrReg;

        /* Disable all UART TX interrupt source and clear UART TX Done history */
        txIntrReg = cyUart_p50_p51_GetTxInterruptMode();
        cyUart_p50_p51_SetTxInterruptMode(0u);
        cyUart_p50_p51_ClearTxInterruptSource(cyUart_p50_p51_INTR_TX_UART_DONE);

        /* Store TX CTRL configuration */
        txCtrlReg = cyUart_p50_p51_TX_CTRL_REG;

        /* Set break width */
        cyUart_p50_p51_TX_CTRL_REG = (cyUart_p50_p51_TX_CTRL_REG & (uint32) ~cyUart_p50_p51_TX_CTRL_DATA_WIDTH_MASK) |
                                        cyUart_p50_p51_GET_TX_CTRL_DATA_WIDTH(breakWidth);

        /* Generate break */
        cyUart_p50_p51_TX_FIFO_WR_REG = 0u;

        /* Wait for break completion */
        while (0u == (cyUart_p50_p51_GetTxInterruptSource() & cyUart_p50_p51_INTR_TX_UART_DONE))
        {
        }

        /* Clear all UART TX interrupt sources to  */
        cyUart_p50_p51_ClearTxInterruptSource(cyUart_p50_p51_INTR_TX_ALL);

        /* Restore TX interrupt sources and data width */
        cyUart_p50_p51_TX_CTRL_REG = txCtrlReg;
        cyUart_p50_p51_SetTxInterruptMode(txIntrReg);
    }
#endif /* (cyUart_p50_p51_UART_TX_DIRECTION) */


#if (cyUart_p50_p51_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: cyUart_p50_p51_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be
    *  cleared by this API.
    *
    *******************************************************************************/
    void cyUart_p50_p51_UartSaveConfig(void)
    {
    #if (cyUart_p50_p51_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != cyUart_p50_p51_skipStart)
        {
            cyUart_p50_p51_UART_RX_CTRL_REG |= (uint32)  cyUart_p50_p51_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            cyUart_p50_p51_UART_RX_CTRL_REG &= (uint32) ~cyUart_p50_p51_UART_RX_CTRL_SKIP_START;
        }

        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        cyUart_p50_p51_CLEAR_UART_RX_WAKE_INTR;
        cyUart_p50_p51_RxWakeClearPendingInt();
        cyUart_p50_p51_RxWakeEnableInt();
    #endif /* (cyUart_p50_p51_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: cyUart_p50_p51_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void cyUart_p50_p51_UartRestoreConfig(void)
    {
    #if (cyUart_p50_p51_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        cyUart_p50_p51_RxWakeDisableInt();
    #endif /* (cyUart_p50_p51_UART_RX_WAKEUP_IRQ) */
    }


    #if (cyUart_p50_p51_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: cyUart_p50_p51_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(cyUart_p50_p51_UART_WAKEUP_ISR)
        {
        #ifdef cyUart_p50_p51_UART_WAKEUP_ISR_ENTRY_CALLBACK
            cyUart_p50_p51_UART_WAKEUP_ISR_EntryCallback();
        #endif /* cyUart_p50_p51_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            cyUart_p50_p51_CLEAR_UART_RX_WAKE_INTR;

        #ifdef cyUart_p50_p51_UART_WAKEUP_ISR_EXIT_CALLBACK
            cyUart_p50_p51_UART_WAKEUP_ISR_ExitCallback();
        #endif /* cyUart_p50_p51_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (cyUart_p50_p51_UART_RX_WAKEUP_IRQ) */
#endif /* (cyUart_p50_p51_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */

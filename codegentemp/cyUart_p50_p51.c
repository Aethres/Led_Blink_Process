/***************************************************************************//**
* \file cyUart_p50_p51.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component.
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

#if (cyUart_p50_p51_SCB_MODE_I2C_INC)
    #include "cyUart_p50_p51_I2C_PVT.h"
#endif /* (cyUart_p50_p51_SCB_MODE_I2C_INC) */

#if (cyUart_p50_p51_SCB_MODE_EZI2C_INC)
    #include "cyUart_p50_p51_EZI2C_PVT.h"
#endif /* (cyUart_p50_p51_SCB_MODE_EZI2C_INC) */

#if (cyUart_p50_p51_SCB_MODE_SPI_INC || cyUart_p50_p51_SCB_MODE_UART_INC)
    #include "cyUart_p50_p51_SPI_UART_PVT.h"
#endif /* (cyUart_p50_p51_SCB_MODE_SPI_INC || cyUart_p50_p51_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 cyUart_p50_p51_scbMode = cyUart_p50_p51_SCB_MODE_UNCONFIG;
    uint8 cyUart_p50_p51_scbEnableWake;
    uint8 cyUart_p50_p51_scbEnableIntr;

    /* I2C configuration variables */
    uint8 cyUart_p50_p51_mode;
    uint8 cyUart_p50_p51_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * cyUart_p50_p51_rxBuffer;
    uint8  cyUart_p50_p51_rxDataBits;
    uint32 cyUart_p50_p51_rxBufferSize;

    volatile uint8 * cyUart_p50_p51_txBuffer;
    uint8  cyUart_p50_p51_txDataBits;
    uint32 cyUart_p50_p51_txBufferSize;

    /* EZI2C configuration variables */
    uint8 cyUart_p50_p51_numberOfAddr;
    uint8 cyUart_p50_p51_subAddrSize;
#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** cyUart_p50_p51_initVar indicates whether the cyUart_p50_p51 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the cyUart_p50_p51_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  cyUart_p50_p51_Init() function can be called before the 
*  cyUart_p50_p51_Start() or cyUart_p50_p51_Enable() function.
*/
uint8 cyUart_p50_p51_initVar = 0u;


#if (! (cyUart_p50_p51_SCB_MODE_I2C_CONST_CFG || \
        cyUart_p50_p51_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * cyUart_p50_p51_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent cyUart_p50_p51_Enable() call.
    */
    uint16 cyUart_p50_p51_IntrTxMask = 0u;
#endif /* (! (cyUart_p50_p51_SCB_MODE_I2C_CONST_CFG || \
              cyUart_p50_p51_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (cyUart_p50_p51_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_cyUart_p50_p51_CUSTOM_INTR_HANDLER)
    void (*cyUart_p50_p51_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_cyUart_p50_p51_CUSTOM_INTR_HANDLER) */
#endif /* (cyUart_p50_p51_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void cyUart_p50_p51_ScbEnableIntr(void);
static void cyUart_p50_p51_ScbModeStop(void);
static void cyUart_p50_p51_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: cyUart_p50_p51_Init
****************************************************************************//**
*
*  Initializes the cyUart_p50_p51 component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  cyUart_p50_p51_I2CInit, cyUart_p50_p51_SpiInit, 
*  cyUart_p50_p51_UartInit or cyUart_p50_p51_EzI2CInit.
*
*******************************************************************************/
void cyUart_p50_p51_Init(void)
{
#if (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
    if (cyUart_p50_p51_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        cyUart_p50_p51_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (cyUart_p50_p51_SCB_MODE_I2C_CONST_CFG)
    cyUart_p50_p51_I2CInit();

#elif (cyUart_p50_p51_SCB_MODE_SPI_CONST_CFG)
    cyUart_p50_p51_SpiInit();

#elif (cyUart_p50_p51_SCB_MODE_UART_CONST_CFG)
    cyUart_p50_p51_UartInit();

#elif (cyUart_p50_p51_SCB_MODE_EZI2C_CONST_CFG)
    cyUart_p50_p51_EzI2CInit();

#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: cyUart_p50_p51_Enable
****************************************************************************//**
*
*  Enables cyUart_p50_p51 component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  cyUart_p50_p51_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The cyUart_p50_p51 configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured cyUart_p50_p51”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void cyUart_p50_p51_Enable(void)
{
#if (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!cyUart_p50_p51_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        cyUart_p50_p51_CTRL_REG |= cyUart_p50_p51_CTRL_ENABLED;

        cyUart_p50_p51_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        cyUart_p50_p51_ScbModePostEnable();
    }
#else
    cyUart_p50_p51_CTRL_REG |= cyUart_p50_p51_CTRL_ENABLED;

    cyUart_p50_p51_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    cyUart_p50_p51_ScbModePostEnable();
#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: cyUart_p50_p51_Start
****************************************************************************//**
*
*  Invokes cyUart_p50_p51_Init() and cyUart_p50_p51_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  cyUart_p50_p51_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void cyUart_p50_p51_Start(void)
{
    if (0u == cyUart_p50_p51_initVar)
    {
        cyUart_p50_p51_Init();
        cyUart_p50_p51_initVar = 1u; /* Component was initialized */
    }

    cyUart_p50_p51_Enable();
}


/*******************************************************************************
* Function Name: cyUart_p50_p51_Stop
****************************************************************************//**
*
*  Disables the cyUart_p50_p51 component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function cyUart_p50_p51_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void cyUart_p50_p51_Stop(void)
{
#if (cyUart_p50_p51_SCB_IRQ_INTERNAL)
    cyUart_p50_p51_DisableInt();
#endif /* (cyUart_p50_p51_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    cyUart_p50_p51_ScbModeStop();

    /* Disable SCB IP */
    cyUart_p50_p51_CTRL_REG &= (uint32) ~cyUart_p50_p51_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    cyUart_p50_p51_SetTxInterruptMode(cyUart_p50_p51_NO_INTR_SOURCES);

#if (cyUart_p50_p51_SCB_IRQ_INTERNAL)
    cyUart_p50_p51_ClearPendingInt();
#endif /* (cyUart_p50_p51_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: cyUart_p50_p51_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void cyUart_p50_p51_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = cyUart_p50_p51_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~cyUart_p50_p51_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (cyUart_p50_p51_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    cyUart_p50_p51_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: cyUart_p50_p51_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void cyUart_p50_p51_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = cyUart_p50_p51_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~cyUart_p50_p51_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (cyUart_p50_p51_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    cyUart_p50_p51_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (cyUart_p50_p51_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: cyUart_p50_p51_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void cyUart_p50_p51_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_cyUart_p50_p51_CUSTOM_INTR_HANDLER)
        cyUart_p50_p51_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_cyUart_p50_p51_CUSTOM_INTR_HANDLER) */
    }
#endif /* (cyUart_p50_p51_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: cyUart_p50_p51_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void cyUart_p50_p51_ScbEnableIntr(void)
{
#if (cyUart_p50_p51_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != cyUart_p50_p51_scbEnableIntr)
        {
            cyUart_p50_p51_EnableInt();
        }

    #else
        cyUart_p50_p51_EnableInt();

    #endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (cyUart_p50_p51_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: cyUart_p50_p51_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void cyUart_p50_p51_ScbModePostEnable(void)
{
#if (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!cyUart_p50_p51_CY_SCBIP_V1)
    if (cyUart_p50_p51_SCB_MODE_SPI_RUNTM_CFG)
    {
        cyUart_p50_p51_SpiPostEnable();
    }
    else if (cyUart_p50_p51_SCB_MODE_UART_RUNTM_CFG)
    {
        cyUart_p50_p51_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!cyUart_p50_p51_CY_SCBIP_V1) */

#elif (cyUart_p50_p51_SCB_MODE_SPI_CONST_CFG)
    cyUart_p50_p51_SpiPostEnable();

#elif (cyUart_p50_p51_SCB_MODE_UART_CONST_CFG)
    cyUart_p50_p51_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: cyUart_p50_p51_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void cyUart_p50_p51_ScbModeStop(void)
{
#if (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
    if (cyUart_p50_p51_SCB_MODE_I2C_RUNTM_CFG)
    {
        cyUart_p50_p51_I2CStop();
    }
    else if (cyUart_p50_p51_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        cyUart_p50_p51_EzI2CStop();
    }
#if (!cyUart_p50_p51_CY_SCBIP_V1)
    else if (cyUart_p50_p51_SCB_MODE_SPI_RUNTM_CFG)
    {
        cyUart_p50_p51_SpiStop();
    }
    else if (cyUart_p50_p51_SCB_MODE_UART_RUNTM_CFG)
    {
        cyUart_p50_p51_UartStop();
    }
#endif /* (!cyUart_p50_p51_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (cyUart_p50_p51_SCB_MODE_I2C_CONST_CFG)
    cyUart_p50_p51_I2CStop();

#elif (cyUart_p50_p51_SCB_MODE_EZI2C_CONST_CFG)
    cyUart_p50_p51_EzI2CStop();

#elif (cyUart_p50_p51_SCB_MODE_SPI_CONST_CFG)
    cyUart_p50_p51_SpiStop();

#elif (cyUart_p50_p51_SCB_MODE_UART_CONST_CFG)
    cyUart_p50_p51_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: cyUart_p50_p51_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void cyUart_p50_p51_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[cyUart_p50_p51_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!cyUart_p50_p51_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!cyUart_p50_p51_CY_SCBIP_V1) */
        
        uint32 hsiomSel[cyUart_p50_p51_SCB_PINS_NUMBER] = 
        {
            cyUart_p50_p51_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            cyUart_p50_p51_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (cyUart_p50_p51_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (cyUart_p50_p51_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < cyUart_p50_p51_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = cyUart_p50_p51_PIN_DM_ALG_HIZ;
        }

        if ((cyUart_p50_p51_SCB_MODE_I2C   == mode) ||
            (cyUart_p50_p51_SCB_MODE_EZI2C == mode))
        {
        #if (cyUart_p50_p51_RX_SCL_MOSI_PIN)
            hsiomSel[cyUart_p50_p51_RX_SCL_MOSI_PIN_INDEX] = cyUart_p50_p51_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [cyUart_p50_p51_RX_SCL_MOSI_PIN_INDEX] = cyUart_p50_p51_PIN_DM_OD_LO;
        #elif (cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_INDEX] = cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_INDEX] = cyUart_p50_p51_PIN_DM_OD_LO;
        #else
        #endif /* (cyUart_p50_p51_RX_SCL_MOSI_PIN) */
        
        #if (cyUart_p50_p51_TX_SDA_MISO_PIN)
            hsiomSel[cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX] = cyUart_p50_p51_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX] = cyUart_p50_p51_PIN_DM_OD_LO;
        #endif /* (cyUart_p50_p51_TX_SDA_MISO_PIN) */
        }
    #if (!cyUart_p50_p51_CY_SCBIP_V1)
        else if (cyUart_p50_p51_SCB_MODE_SPI == mode)
        {
        #if (cyUart_p50_p51_RX_SCL_MOSI_PIN)
            hsiomSel[cyUart_p50_p51_RX_SCL_MOSI_PIN_INDEX] = cyUart_p50_p51_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_INDEX] = cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (cyUart_p50_p51_RX_SCL_MOSI_PIN) */
        
        #if (cyUart_p50_p51_TX_SDA_MISO_PIN)
            hsiomSel[cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX] = cyUart_p50_p51_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (cyUart_p50_p51_TX_SDA_MISO_PIN) */
        
        #if (cyUart_p50_p51_CTS_SCLK_PIN)
            hsiomSel[cyUart_p50_p51_CTS_SCLK_PIN_INDEX] = cyUart_p50_p51_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (cyUart_p50_p51_CTS_SCLK_PIN) */

            if (cyUart_p50_p51_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[cyUart_p50_p51_RX_SCL_MOSI_PIN_INDEX] = cyUart_p50_p51_PIN_DM_DIG_HIZ;
                pinsDm[cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX] = cyUart_p50_p51_PIN_DM_STRONG;
                pinsDm[cyUart_p50_p51_CTS_SCLK_PIN_INDEX] = cyUart_p50_p51_PIN_DM_DIG_HIZ;

            #if (cyUart_p50_p51_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[cyUart_p50_p51_RTS_SS0_PIN_INDEX] = cyUart_p50_p51_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [cyUart_p50_p51_RTS_SS0_PIN_INDEX] = cyUart_p50_p51_PIN_DM_DIG_HIZ;
            #endif /* (cyUart_p50_p51_RTS_SS0_PIN) */

            #if (cyUart_p50_p51_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= cyUart_p50_p51_TX_SDA_MISO_PIN_MASK;
            #endif /* (cyUart_p50_p51_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[cyUart_p50_p51_RX_SCL_MOSI_PIN_INDEX] = cyUart_p50_p51_PIN_DM_STRONG;
                pinsDm[cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX] = cyUart_p50_p51_PIN_DM_DIG_HIZ;
                pinsDm[cyUart_p50_p51_CTS_SCLK_PIN_INDEX] = cyUart_p50_p51_PIN_DM_STRONG;

            #if (cyUart_p50_p51_RTS_SS0_PIN)
                hsiomSel [cyUart_p50_p51_RTS_SS0_PIN_INDEX] = cyUart_p50_p51_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [cyUart_p50_p51_RTS_SS0_PIN_INDEX] = cyUart_p50_p51_PIN_DM_STRONG;
                pinsInBuf |= cyUart_p50_p51_RTS_SS0_PIN_MASK;
            #endif /* (cyUart_p50_p51_RTS_SS0_PIN) */

            #if (cyUart_p50_p51_SS1_PIN)
                hsiomSel [cyUart_p50_p51_SS1_PIN_INDEX] = cyUart_p50_p51_SS1_HSIOM_SEL_SPI;
                pinsDm   [cyUart_p50_p51_SS1_PIN_INDEX] = cyUart_p50_p51_PIN_DM_STRONG;
                pinsInBuf |= cyUart_p50_p51_SS1_PIN_MASK;
            #endif /* (cyUart_p50_p51_SS1_PIN) */

            #if (cyUart_p50_p51_SS2_PIN)
                hsiomSel [cyUart_p50_p51_SS2_PIN_INDEX] = cyUart_p50_p51_SS2_HSIOM_SEL_SPI;
                pinsDm   [cyUart_p50_p51_SS2_PIN_INDEX] = cyUart_p50_p51_PIN_DM_STRONG;
                pinsInBuf |= cyUart_p50_p51_SS2_PIN_MASK;
            #endif /* (cyUart_p50_p51_SS2_PIN) */

            #if (cyUart_p50_p51_SS3_PIN)
                hsiomSel [cyUart_p50_p51_SS3_PIN_INDEX] = cyUart_p50_p51_SS3_HSIOM_SEL_SPI;
                pinsDm   [cyUart_p50_p51_SS3_PIN_INDEX] = cyUart_p50_p51_PIN_DM_STRONG;
                pinsInBuf |= cyUart_p50_p51_SS3_PIN_MASK;
            #endif /* (cyUart_p50_p51_SS3_PIN) */

                /* Disable input buffers */
            #if (cyUart_p50_p51_RX_SCL_MOSI_PIN)
                pinsInBuf |= cyUart_p50_p51_RX_SCL_MOSI_PIN_MASK;
            #elif (cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (cyUart_p50_p51_RX_SCL_MOSI_PIN) */

            #if (cyUart_p50_p51_CTS_SCLK_PIN)
                pinsInBuf |= cyUart_p50_p51_CTS_SCLK_PIN_MASK;
            #endif /* (cyUart_p50_p51_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (cyUart_p50_p51_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (cyUart_p50_p51_TX_SDA_MISO_PIN)
                hsiomSel[cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX] = cyUart_p50_p51_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX] = cyUart_p50_p51_PIN_DM_OD_LO;
            #endif /* (cyUart_p50_p51_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (cyUart_p50_p51_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (cyUart_p50_p51_RX_SCL_MOSI_PIN)
                    hsiomSel[cyUart_p50_p51_RX_SCL_MOSI_PIN_INDEX] = cyUart_p50_p51_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [cyUart_p50_p51_RX_SCL_MOSI_PIN_INDEX] = cyUart_p50_p51_PIN_DM_DIG_HIZ;
                #elif (cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_INDEX] = cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_INDEX] = cyUart_p50_p51_PIN_DM_DIG_HIZ;
                #else
                #endif /* (cyUart_p50_p51_RX_SCL_MOSI_PIN) */
                }

                if (0u != (cyUart_p50_p51_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (cyUart_p50_p51_TX_SDA_MISO_PIN)
                    hsiomSel[cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX] = cyUart_p50_p51_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX] = cyUart_p50_p51_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= cyUart_p50_p51_TX_SDA_MISO_PIN_MASK;
                #endif /* (cyUart_p50_p51_TX_SDA_MISO_PIN) */
                }

            #if !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1)
                if (cyUart_p50_p51_UART_MODE_STD == subMode)
                {
                    if (0u != (cyUart_p50_p51_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (cyUart_p50_p51_CTS_SCLK_PIN)
                        hsiomSel[cyUart_p50_p51_CTS_SCLK_PIN_INDEX] = cyUart_p50_p51_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [cyUart_p50_p51_CTS_SCLK_PIN_INDEX] = cyUart_p50_p51_PIN_DM_DIG_HIZ;
                    #endif /* (cyUart_p50_p51_CTS_SCLK_PIN) */
                    }

                    if (0u != (cyUart_p50_p51_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (cyUart_p50_p51_RTS_SS0_PIN)
                        hsiomSel[cyUart_p50_p51_RTS_SS0_PIN_INDEX] = cyUart_p50_p51_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [cyUart_p50_p51_RTS_SS0_PIN_INDEX] = cyUart_p50_p51_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= cyUart_p50_p51_RTS_SS0_PIN_MASK;
                    #endif /* (cyUart_p50_p51_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1) */
            }
        }
    #endif /* (!cyUart_p50_p51_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (cyUart_p50_p51_RX_SCL_MOSI_PIN)
        cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_RX_SCL_MOSI_HSIOM_REG,
                                       cyUart_p50_p51_RX_SCL_MOSI_HSIOM_MASK,
                                       cyUart_p50_p51_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[cyUart_p50_p51_RX_SCL_MOSI_PIN_INDEX]);

        cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[cyUart_p50_p51_RX_SCL_MOSI_PIN_INDEX]);

        #if (!cyUart_p50_p51_CY_SCBIP_V1)
            cyUart_p50_p51_SET_INP_DIS(cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & cyUart_p50_p51_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!cyUart_p50_p51_CY_SCBIP_V1) */
    
    #elif (cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN)
        cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        cyUart_p50_p51_SET_INP_DIS(cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        cyUart_p50_p51_SET_INCFG_TYPE(cyUart_p50_p51_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        cyUart_p50_p51_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        cyUart_p50_p51_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        cyUart_p50_p51_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN) */

    #if (cyUart_p50_p51_TX_SDA_MISO_PIN)
        cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_TX_SDA_MISO_HSIOM_REG,
                                       cyUart_p50_p51_TX_SDA_MISO_HSIOM_MASK,
                                       cyUart_p50_p51_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX]);

        cyUart_p50_p51_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX]);

    #if (!cyUart_p50_p51_CY_SCBIP_V1)
        cyUart_p50_p51_SET_INP_DIS(cyUart_p50_p51_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     cyUart_p50_p51_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & cyUart_p50_p51_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!cyUart_p50_p51_CY_SCBIP_V1) */
    #endif /* (cyUart_p50_p51_RX_SCL_MOSI_PIN) */

    #if (cyUart_p50_p51_CTS_SCLK_PIN)
        cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_CTS_SCLK_HSIOM_REG,
                                       cyUart_p50_p51_CTS_SCLK_HSIOM_MASK,
                                       cyUart_p50_p51_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[cyUart_p50_p51_CTS_SCLK_PIN_INDEX]);

        cyUart_p50_p51_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[cyUart_p50_p51_CTS_SCLK_PIN_INDEX]);

        cyUart_p50_p51_SET_INP_DIS(cyUart_p50_p51_uart_cts_spi_sclk_INP_DIS,
                                     cyUart_p50_p51_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & cyUart_p50_p51_CTS_SCLK_PIN_MASK)));
    #endif /* (cyUart_p50_p51_CTS_SCLK_PIN) */

    #if (cyUart_p50_p51_RTS_SS0_PIN)
        cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_RTS_SS0_HSIOM_REG,
                                       cyUart_p50_p51_RTS_SS0_HSIOM_MASK,
                                       cyUart_p50_p51_RTS_SS0_HSIOM_POS,
                                       hsiomSel[cyUart_p50_p51_RTS_SS0_PIN_INDEX]);

        cyUart_p50_p51_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[cyUart_p50_p51_RTS_SS0_PIN_INDEX]);

        cyUart_p50_p51_SET_INP_DIS(cyUart_p50_p51_uart_rts_spi_ss0_INP_DIS,
                                     cyUart_p50_p51_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & cyUart_p50_p51_RTS_SS0_PIN_MASK)));
    #endif /* (cyUart_p50_p51_RTS_SS0_PIN) */

    #if (cyUart_p50_p51_SS1_PIN)
        cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_SS1_HSIOM_REG,
                                       cyUart_p50_p51_SS1_HSIOM_MASK,
                                       cyUart_p50_p51_SS1_HSIOM_POS,
                                       hsiomSel[cyUart_p50_p51_SS1_PIN_INDEX]);

        cyUart_p50_p51_spi_ss1_SetDriveMode((uint8) pinsDm[cyUart_p50_p51_SS1_PIN_INDEX]);

        cyUart_p50_p51_SET_INP_DIS(cyUart_p50_p51_spi_ss1_INP_DIS,
                                     cyUart_p50_p51_spi_ss1_MASK,
                                     (0u != (pinsInBuf & cyUart_p50_p51_SS1_PIN_MASK)));
    #endif /* (cyUart_p50_p51_SS1_PIN) */

    #if (cyUart_p50_p51_SS2_PIN)
        cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_SS2_HSIOM_REG,
                                       cyUart_p50_p51_SS2_HSIOM_MASK,
                                       cyUart_p50_p51_SS2_HSIOM_POS,
                                       hsiomSel[cyUart_p50_p51_SS2_PIN_INDEX]);

        cyUart_p50_p51_spi_ss2_SetDriveMode((uint8) pinsDm[cyUart_p50_p51_SS2_PIN_INDEX]);

        cyUart_p50_p51_SET_INP_DIS(cyUart_p50_p51_spi_ss2_INP_DIS,
                                     cyUart_p50_p51_spi_ss2_MASK,
                                     (0u != (pinsInBuf & cyUart_p50_p51_SS2_PIN_MASK)));
    #endif /* (cyUart_p50_p51_SS2_PIN) */

    #if (cyUart_p50_p51_SS3_PIN)
        cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_SS3_HSIOM_REG,
                                       cyUart_p50_p51_SS3_HSIOM_MASK,
                                       cyUart_p50_p51_SS3_HSIOM_POS,
                                       hsiomSel[cyUart_p50_p51_SS3_PIN_INDEX]);

        cyUart_p50_p51_spi_ss3_SetDriveMode((uint8) pinsDm[cyUart_p50_p51_SS3_PIN_INDEX]);

        cyUart_p50_p51_SET_INP_DIS(cyUart_p50_p51_spi_ss3_INP_DIS,
                                     cyUart_p50_p51_spi_ss3_MASK,
                                     (0u != (pinsInBuf & cyUart_p50_p51_SS3_PIN_MASK)));
    #endif /* (cyUart_p50_p51_SS3_PIN) */
    }

#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: cyUart_p50_p51_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void cyUart_p50_p51_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (cyUart_p50_p51_CTRL_REG & cyUart_p50_p51_CTRL_EC_AM_MODE)) &&
            (0u == (cyUart_p50_p51_I2C_CTRL_REG & cyUart_p50_p51_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            cyUart_p50_p51_CTRL_REG &= ~cyUart_p50_p51_CTRL_EC_AM_MODE;
            cyUart_p50_p51_CTRL_REG |=  cyUart_p50_p51_CTRL_EC_AM_MODE;
        }

        cyUart_p50_p51_I2C_SLAVE_CMD_REG = cyUart_p50_p51_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1) */


/* [] END OF FILE */

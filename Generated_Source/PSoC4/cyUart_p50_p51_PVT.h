/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
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

#if !defined(CY_SCB_PVT_cyUart_p50_p51_H)
#define CY_SCB_PVT_cyUart_p50_p51_H

#include "cyUart_p50_p51.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define cyUart_p50_p51_SetI2CExtClkInterruptMode(interruptMask) cyUart_p50_p51_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define cyUart_p50_p51_ClearI2CExtClkInterruptSource(interruptMask) cyUart_p50_p51_CLEAR_INTR_I2C_EC(interruptMask)
#define cyUart_p50_p51_GetI2CExtClkInterruptSource()                (cyUart_p50_p51_INTR_I2C_EC_REG)
#define cyUart_p50_p51_GetI2CExtClkInterruptMode()                  (cyUart_p50_p51_INTR_I2C_EC_MASK_REG)
#define cyUart_p50_p51_GetI2CExtClkInterruptSourceMasked()          (cyUart_p50_p51_INTR_I2C_EC_MASKED_REG)

#if (!cyUart_p50_p51_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define cyUart_p50_p51_SetSpiExtClkInterruptMode(interruptMask) \
                                                                cyUart_p50_p51_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define cyUart_p50_p51_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                cyUart_p50_p51_CLEAR_INTR_SPI_EC(interruptMask)
    #define cyUart_p50_p51_GetExtSpiClkInterruptSource()                 (cyUart_p50_p51_INTR_SPI_EC_REG)
    #define cyUart_p50_p51_GetExtSpiClkInterruptMode()                   (cyUart_p50_p51_INTR_SPI_EC_MASK_REG)
    #define cyUart_p50_p51_GetExtSpiClkInterruptSourceMasked()           (cyUart_p50_p51_INTR_SPI_EC_MASKED_REG)
#endif /* (!cyUart_p50_p51_CY_SCBIP_V1) */

#if(cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void cyUart_p50_p51_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (cyUart_p50_p51_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_cyUart_p50_p51_CUSTOM_INTR_HANDLER)
    extern cyisraddress cyUart_p50_p51_customIntrHandler;
#endif /* !defined (CY_REMOVE_cyUart_p50_p51_CUSTOM_INTR_HANDLER) */
#endif /* (cyUart_p50_p51_SCB_IRQ_INTERNAL) */

extern cyUart_p50_p51_BACKUP_STRUCT cyUart_p50_p51_backup;

#if(cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 cyUart_p50_p51_scbMode;
    extern uint8 cyUart_p50_p51_scbEnableWake;
    extern uint8 cyUart_p50_p51_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 cyUart_p50_p51_mode;
    extern uint8 cyUart_p50_p51_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * cyUart_p50_p51_rxBuffer;
    extern uint8   cyUart_p50_p51_rxDataBits;
    extern uint32  cyUart_p50_p51_rxBufferSize;

    extern volatile uint8 * cyUart_p50_p51_txBuffer;
    extern uint8   cyUart_p50_p51_txDataBits;
    extern uint32  cyUart_p50_p51_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 cyUart_p50_p51_numberOfAddr;
    extern uint8 cyUart_p50_p51_subAddrSize;
#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (cyUart_p50_p51_SCB_MODE_I2C_CONST_CFG || \
        cyUart_p50_p51_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 cyUart_p50_p51_IntrTxMask;
#endif /* (! (cyUart_p50_p51_SCB_MODE_I2C_CONST_CFG || \
              cyUart_p50_p51_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define cyUart_p50_p51_SCB_MODE_I2C_RUNTM_CFG     (cyUart_p50_p51_SCB_MODE_I2C      == cyUart_p50_p51_scbMode)
    #define cyUart_p50_p51_SCB_MODE_SPI_RUNTM_CFG     (cyUart_p50_p51_SCB_MODE_SPI      == cyUart_p50_p51_scbMode)
    #define cyUart_p50_p51_SCB_MODE_UART_RUNTM_CFG    (cyUart_p50_p51_SCB_MODE_UART     == cyUart_p50_p51_scbMode)
    #define cyUart_p50_p51_SCB_MODE_EZI2C_RUNTM_CFG   (cyUart_p50_p51_SCB_MODE_EZI2C    == cyUart_p50_p51_scbMode)
    #define cyUart_p50_p51_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (cyUart_p50_p51_SCB_MODE_UNCONFIG == cyUart_p50_p51_scbMode)

    /* Defines wakeup enable */
    #define cyUart_p50_p51_SCB_WAKE_ENABLE_CHECK       (0u != cyUart_p50_p51_scbEnableWake)
#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!cyUart_p50_p51_CY_SCBIP_V1)
    #define cyUart_p50_p51_SCB_PINS_NUMBER    (7u)
#else
    #define cyUart_p50_p51_SCB_PINS_NUMBER    (2u)
#endif /* (!cyUart_p50_p51_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_cyUart_p50_p51_H) */


/* [] END OF FILE */

/***************************************************************************//**
* \file cyUart_p50_p51_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
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

#include "cyUart_p50_p51.h"
#include "cyUart_p50_p51_PVT.h"

#if(cyUart_p50_p51_SCB_MODE_I2C_INC)
    #include "cyUart_p50_p51_I2C_PVT.h"
#endif /* (cyUart_p50_p51_SCB_MODE_I2C_INC) */

#if(cyUart_p50_p51_SCB_MODE_EZI2C_INC)
    #include "cyUart_p50_p51_EZI2C_PVT.h"
#endif /* (cyUart_p50_p51_SCB_MODE_EZI2C_INC) */

#if(cyUart_p50_p51_SCB_MODE_SPI_INC || cyUart_p50_p51_SCB_MODE_UART_INC)
    #include "cyUart_p50_p51_SPI_UART_PVT.h"
#endif /* (cyUart_p50_p51_SCB_MODE_SPI_INC || cyUart_p50_p51_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG || \
   (cyUart_p50_p51_SCB_MODE_I2C_CONST_CFG   && (!cyUart_p50_p51_I2C_WAKE_ENABLE_CONST))   || \
   (cyUart_p50_p51_SCB_MODE_EZI2C_CONST_CFG && (!cyUart_p50_p51_EZI2C_WAKE_ENABLE_CONST)) || \
   (cyUart_p50_p51_SCB_MODE_SPI_CONST_CFG   && (!cyUart_p50_p51_SPI_WAKE_ENABLE_CONST))   || \
   (cyUart_p50_p51_SCB_MODE_UART_CONST_CFG  && (!cyUart_p50_p51_UART_WAKE_ENABLE_CONST)))

    cyUart_p50_p51_BACKUP_STRUCT cyUart_p50_p51_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: cyUart_p50_p51_Sleep
****************************************************************************//**
*
*  Prepares the cyUart_p50_p51 component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the cyUart_p50_p51_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void cyUart_p50_p51_Sleep(void)
{
#if(cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)

    if(cyUart_p50_p51_SCB_WAKE_ENABLE_CHECK)
    {
        if(cyUart_p50_p51_SCB_MODE_I2C_RUNTM_CFG)
        {
            cyUart_p50_p51_I2CSaveConfig();
        }
        else if(cyUart_p50_p51_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            cyUart_p50_p51_EzI2CSaveConfig();
        }
    #if(!cyUart_p50_p51_CY_SCBIP_V1)
        else if(cyUart_p50_p51_SCB_MODE_SPI_RUNTM_CFG)
        {
            cyUart_p50_p51_SpiSaveConfig();
        }
        else if(cyUart_p50_p51_SCB_MODE_UART_RUNTM_CFG)
        {
            cyUart_p50_p51_UartSaveConfig();
        }
    #endif /* (!cyUart_p50_p51_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        cyUart_p50_p51_backup.enableState = (uint8) cyUart_p50_p51_GET_CTRL_ENABLED;

        if(0u != cyUart_p50_p51_backup.enableState)
        {
            cyUart_p50_p51_Stop();
        }
    }

#else

    #if (cyUart_p50_p51_SCB_MODE_I2C_CONST_CFG && cyUart_p50_p51_I2C_WAKE_ENABLE_CONST)
        cyUart_p50_p51_I2CSaveConfig();

    #elif (cyUart_p50_p51_SCB_MODE_EZI2C_CONST_CFG && cyUart_p50_p51_EZI2C_WAKE_ENABLE_CONST)
        cyUart_p50_p51_EzI2CSaveConfig();

    #elif (cyUart_p50_p51_SCB_MODE_SPI_CONST_CFG && cyUart_p50_p51_SPI_WAKE_ENABLE_CONST)
        cyUart_p50_p51_SpiSaveConfig();

    #elif (cyUart_p50_p51_SCB_MODE_UART_CONST_CFG && cyUart_p50_p51_UART_WAKE_ENABLE_CONST)
        cyUart_p50_p51_UartSaveConfig();

    #else

        cyUart_p50_p51_backup.enableState = (uint8) cyUart_p50_p51_GET_CTRL_ENABLED;

        if(0u != cyUart_p50_p51_backup.enableState)
        {
            cyUart_p50_p51_Stop();
        }

    #endif /* defined (cyUart_p50_p51_SCB_MODE_I2C_CONST_CFG) && (cyUart_p50_p51_I2C_WAKE_ENABLE_CONST) */

#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: cyUart_p50_p51_Wakeup
****************************************************************************//**
*
*  Prepares the cyUart_p50_p51 component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the cyUart_p50_p51_Wakeup() function without first calling the 
*   cyUart_p50_p51_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void cyUart_p50_p51_Wakeup(void)
{
#if(cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)

    if(cyUart_p50_p51_SCB_WAKE_ENABLE_CHECK)
    {
        if(cyUart_p50_p51_SCB_MODE_I2C_RUNTM_CFG)
        {
            cyUart_p50_p51_I2CRestoreConfig();
        }
        else if(cyUart_p50_p51_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            cyUart_p50_p51_EzI2CRestoreConfig();
        }
    #if(!cyUart_p50_p51_CY_SCBIP_V1)
        else if(cyUart_p50_p51_SCB_MODE_SPI_RUNTM_CFG)
        {
            cyUart_p50_p51_SpiRestoreConfig();
        }
        else if(cyUart_p50_p51_SCB_MODE_UART_RUNTM_CFG)
        {
            cyUart_p50_p51_UartRestoreConfig();
        }
    #endif /* (!cyUart_p50_p51_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != cyUart_p50_p51_backup.enableState)
        {
            cyUart_p50_p51_Enable();
        }
    }

#else

    #if (cyUart_p50_p51_SCB_MODE_I2C_CONST_CFG  && cyUart_p50_p51_I2C_WAKE_ENABLE_CONST)
        cyUart_p50_p51_I2CRestoreConfig();

    #elif (cyUart_p50_p51_SCB_MODE_EZI2C_CONST_CFG && cyUart_p50_p51_EZI2C_WAKE_ENABLE_CONST)
        cyUart_p50_p51_EzI2CRestoreConfig();

    #elif (cyUart_p50_p51_SCB_MODE_SPI_CONST_CFG && cyUart_p50_p51_SPI_WAKE_ENABLE_CONST)
        cyUart_p50_p51_SpiRestoreConfig();

    #elif (cyUart_p50_p51_SCB_MODE_UART_CONST_CFG && cyUart_p50_p51_UART_WAKE_ENABLE_CONST)
        cyUart_p50_p51_UartRestoreConfig();

    #else

        if(0u != cyUart_p50_p51_backup.enableState)
        {
            cyUart_p50_p51_Enable();
        }

    #endif /* (cyUart_p50_p51_I2C_WAKE_ENABLE_CONST) */

#endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */

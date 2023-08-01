/*******************************************************************************
* File Name: cyUart_p50_p51_rx.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "cyUart_p50_p51_rx.h"

static cyUart_p50_p51_rx_BACKUP_STRUCT  cyUart_p50_p51_rx_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: cyUart_p50_p51_rx_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet cyUart_p50_p51_rx_SUT.c usage_cyUart_p50_p51_rx_Sleep_Wakeup
*******************************************************************************/
void cyUart_p50_p51_rx_Sleep(void)
{
    #if defined(cyUart_p50_p51_rx__PC)
        cyUart_p50_p51_rx_backup.pcState = cyUart_p50_p51_rx_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            cyUart_p50_p51_rx_backup.usbState = cyUart_p50_p51_rx_CR1_REG;
            cyUart_p50_p51_rx_USB_POWER_REG |= cyUart_p50_p51_rx_USBIO_ENTER_SLEEP;
            cyUart_p50_p51_rx_CR1_REG &= cyUart_p50_p51_rx_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cyUart_p50_p51_rx__SIO)
        cyUart_p50_p51_rx_backup.sioState = cyUart_p50_p51_rx_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        cyUart_p50_p51_rx_SIO_REG &= (uint32)(~cyUart_p50_p51_rx_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: cyUart_p50_p51_rx_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to cyUart_p50_p51_rx_Sleep() for an example usage.
*******************************************************************************/
void cyUart_p50_p51_rx_Wakeup(void)
{
    #if defined(cyUart_p50_p51_rx__PC)
        cyUart_p50_p51_rx_PC = cyUart_p50_p51_rx_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            cyUart_p50_p51_rx_USB_POWER_REG &= cyUart_p50_p51_rx_USBIO_EXIT_SLEEP_PH1;
            cyUart_p50_p51_rx_CR1_REG = cyUart_p50_p51_rx_backup.usbState;
            cyUart_p50_p51_rx_USB_POWER_REG &= cyUart_p50_p51_rx_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cyUart_p50_p51_rx__SIO)
        cyUart_p50_p51_rx_SIO_REG = cyUart_p50_p51_rx_backup.sioState;
    #endif
}


/* [] END OF FILE */

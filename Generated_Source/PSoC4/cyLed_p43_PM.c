/*******************************************************************************
* File Name: cyLed_p43.c  
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
#include "cyLed_p43.h"

static cyLed_p43_BACKUP_STRUCT  cyLed_p43_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: cyLed_p43_Sleep
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
*  \snippet cyLed_p43_SUT.c usage_cyLed_p43_Sleep_Wakeup
*******************************************************************************/
void cyLed_p43_Sleep(void)
{
    #if defined(cyLed_p43__PC)
        cyLed_p43_backup.pcState = cyLed_p43_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            cyLed_p43_backup.usbState = cyLed_p43_CR1_REG;
            cyLed_p43_USB_POWER_REG |= cyLed_p43_USBIO_ENTER_SLEEP;
            cyLed_p43_CR1_REG &= cyLed_p43_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cyLed_p43__SIO)
        cyLed_p43_backup.sioState = cyLed_p43_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        cyLed_p43_SIO_REG &= (uint32)(~cyLed_p43_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: cyLed_p43_Wakeup
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
*  Refer to cyLed_p43_Sleep() for an example usage.
*******************************************************************************/
void cyLed_p43_Wakeup(void)
{
    #if defined(cyLed_p43__PC)
        cyLed_p43_PC = cyLed_p43_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            cyLed_p43_USB_POWER_REG &= cyLed_p43_USBIO_EXIT_SLEEP_PH1;
            cyLed_p43_CR1_REG = cyLed_p43_backup.usbState;
            cyLed_p43_USB_POWER_REG &= cyLed_p43_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cyLed_p43__SIO)
        cyLed_p43_SIO_REG = cyLed_p43_backup.sioState;
    #endif
}


/* [] END OF FILE */

/*******************************************************************************
* File Name: cySegC_p22.c  
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
#include "cySegC_p22.h"

static cySegC_p22_BACKUP_STRUCT  cySegC_p22_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: cySegC_p22_Sleep
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
*  \snippet cySegC_p22_SUT.c usage_cySegC_p22_Sleep_Wakeup
*******************************************************************************/
void cySegC_p22_Sleep(void)
{
    #if defined(cySegC_p22__PC)
        cySegC_p22_backup.pcState = cySegC_p22_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            cySegC_p22_backup.usbState = cySegC_p22_CR1_REG;
            cySegC_p22_USB_POWER_REG |= cySegC_p22_USBIO_ENTER_SLEEP;
            cySegC_p22_CR1_REG &= cySegC_p22_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cySegC_p22__SIO)
        cySegC_p22_backup.sioState = cySegC_p22_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        cySegC_p22_SIO_REG &= (uint32)(~cySegC_p22_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: cySegC_p22_Wakeup
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
*  Refer to cySegC_p22_Sleep() for an example usage.
*******************************************************************************/
void cySegC_p22_Wakeup(void)
{
    #if defined(cySegC_p22__PC)
        cySegC_p22_PC = cySegC_p22_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            cySegC_p22_USB_POWER_REG &= cySegC_p22_USBIO_EXIT_SLEEP_PH1;
            cySegC_p22_CR1_REG = cySegC_p22_backup.usbState;
            cySegC_p22_USB_POWER_REG &= cySegC_p22_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cySegC_p22__SIO)
        cySegC_p22_SIO_REG = cySegC_p22_backup.sioState;
    #endif
}


/* [] END OF FILE */

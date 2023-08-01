/*******************************************************************************
* File Name: cyDigit2_p35.c  
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
#include "cyDigit2_p35.h"

static cyDigit2_p35_BACKUP_STRUCT  cyDigit2_p35_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: cyDigit2_p35_Sleep
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
*  \snippet cyDigit2_p35_SUT.c usage_cyDigit2_p35_Sleep_Wakeup
*******************************************************************************/
void cyDigit2_p35_Sleep(void)
{
    #if defined(cyDigit2_p35__PC)
        cyDigit2_p35_backup.pcState = cyDigit2_p35_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            cyDigit2_p35_backup.usbState = cyDigit2_p35_CR1_REG;
            cyDigit2_p35_USB_POWER_REG |= cyDigit2_p35_USBIO_ENTER_SLEEP;
            cyDigit2_p35_CR1_REG &= cyDigit2_p35_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cyDigit2_p35__SIO)
        cyDigit2_p35_backup.sioState = cyDigit2_p35_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        cyDigit2_p35_SIO_REG &= (uint32)(~cyDigit2_p35_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: cyDigit2_p35_Wakeup
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
*  Refer to cyDigit2_p35_Sleep() for an example usage.
*******************************************************************************/
void cyDigit2_p35_Wakeup(void)
{
    #if defined(cyDigit2_p35__PC)
        cyDigit2_p35_PC = cyDigit2_p35_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            cyDigit2_p35_USB_POWER_REG &= cyDigit2_p35_USBIO_EXIT_SLEEP_PH1;
            cyDigit2_p35_CR1_REG = cyDigit2_p35_backup.usbState;
            cyDigit2_p35_USB_POWER_REG &= cyDigit2_p35_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cyDigit2_p35__SIO)
        cyDigit2_p35_SIO_REG = cyDigit2_p35_backup.sioState;
    #endif
}


/* [] END OF FILE */

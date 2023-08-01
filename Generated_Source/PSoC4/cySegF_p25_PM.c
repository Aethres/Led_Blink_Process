/*******************************************************************************
* File Name: cySegF_p25.c  
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
#include "cySegF_p25.h"

static cySegF_p25_BACKUP_STRUCT  cySegF_p25_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: cySegF_p25_Sleep
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
*  \snippet cySegF_p25_SUT.c usage_cySegF_p25_Sleep_Wakeup
*******************************************************************************/
void cySegF_p25_Sleep(void)
{
    #if defined(cySegF_p25__PC)
        cySegF_p25_backup.pcState = cySegF_p25_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            cySegF_p25_backup.usbState = cySegF_p25_CR1_REG;
            cySegF_p25_USB_POWER_REG |= cySegF_p25_USBIO_ENTER_SLEEP;
            cySegF_p25_CR1_REG &= cySegF_p25_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cySegF_p25__SIO)
        cySegF_p25_backup.sioState = cySegF_p25_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        cySegF_p25_SIO_REG &= (uint32)(~cySegF_p25_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: cySegF_p25_Wakeup
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
*  Refer to cySegF_p25_Sleep() for an example usage.
*******************************************************************************/
void cySegF_p25_Wakeup(void)
{
    #if defined(cySegF_p25__PC)
        cySegF_p25_PC = cySegF_p25_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            cySegF_p25_USB_POWER_REG &= cySegF_p25_USBIO_EXIT_SLEEP_PH1;
            cySegF_p25_CR1_REG = cySegF_p25_backup.usbState;
            cySegF_p25_USB_POWER_REG &= cySegF_p25_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cySegF_p25__SIO)
        cySegF_p25_SIO_REG = cySegF_p25_backup.sioState;
    #endif
}


/* [] END OF FILE */

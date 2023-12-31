/*******************************************************************************
* File Name: cySegB_p21.c  
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
#include "cySegB_p21.h"

static cySegB_p21_BACKUP_STRUCT  cySegB_p21_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: cySegB_p21_Sleep
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
*  \snippet cySegB_p21_SUT.c usage_cySegB_p21_Sleep_Wakeup
*******************************************************************************/
void cySegB_p21_Sleep(void)
{
    #if defined(cySegB_p21__PC)
        cySegB_p21_backup.pcState = cySegB_p21_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            cySegB_p21_backup.usbState = cySegB_p21_CR1_REG;
            cySegB_p21_USB_POWER_REG |= cySegB_p21_USBIO_ENTER_SLEEP;
            cySegB_p21_CR1_REG &= cySegB_p21_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cySegB_p21__SIO)
        cySegB_p21_backup.sioState = cySegB_p21_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        cySegB_p21_SIO_REG &= (uint32)(~cySegB_p21_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: cySegB_p21_Wakeup
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
*  Refer to cySegB_p21_Sleep() for an example usage.
*******************************************************************************/
void cySegB_p21_Wakeup(void)
{
    #if defined(cySegB_p21__PC)
        cySegB_p21_PC = cySegB_p21_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            cySegB_p21_USB_POWER_REG &= cySegB_p21_USBIO_EXIT_SLEEP_PH1;
            cySegB_p21_CR1_REG = cySegB_p21_backup.usbState;
            cySegB_p21_USB_POWER_REG &= cySegB_p21_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cySegB_p21__SIO)
        cySegB_p21_SIO_REG = cySegB_p21_backup.sioState;
    #endif
}


/* [] END OF FILE */

/*******************************************************************************
* File Name: cyDigit1_p34.c  
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
#include "cyDigit1_p34.h"

static cyDigit1_p34_BACKUP_STRUCT  cyDigit1_p34_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: cyDigit1_p34_Sleep
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
*  \snippet cyDigit1_p34_SUT.c usage_cyDigit1_p34_Sleep_Wakeup
*******************************************************************************/
void cyDigit1_p34_Sleep(void)
{
    #if defined(cyDigit1_p34__PC)
        cyDigit1_p34_backup.pcState = cyDigit1_p34_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            cyDigit1_p34_backup.usbState = cyDigit1_p34_CR1_REG;
            cyDigit1_p34_USB_POWER_REG |= cyDigit1_p34_USBIO_ENTER_SLEEP;
            cyDigit1_p34_CR1_REG &= cyDigit1_p34_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cyDigit1_p34__SIO)
        cyDigit1_p34_backup.sioState = cyDigit1_p34_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        cyDigit1_p34_SIO_REG &= (uint32)(~cyDigit1_p34_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: cyDigit1_p34_Wakeup
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
*  Refer to cyDigit1_p34_Sleep() for an example usage.
*******************************************************************************/
void cyDigit1_p34_Wakeup(void)
{
    #if defined(cyDigit1_p34__PC)
        cyDigit1_p34_PC = cyDigit1_p34_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            cyDigit1_p34_USB_POWER_REG &= cyDigit1_p34_USBIO_EXIT_SLEEP_PH1;
            cyDigit1_p34_CR1_REG = cyDigit1_p34_backup.usbState;
            cyDigit1_p34_USB_POWER_REG &= cyDigit1_p34_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cyDigit1_p34__SIO)
        cyDigit1_p34_SIO_REG = cyDigit1_p34_backup.sioState;
    #endif
}


/* [] END OF FILE */

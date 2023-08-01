/*******************************************************************************
* File Name: cyCol1_p03.c  
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
#include "cyCol1_p03.h"

static cyCol1_p03_BACKUP_STRUCT  cyCol1_p03_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: cyCol1_p03_Sleep
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
*  \snippet cyCol1_p03_SUT.c usage_cyCol1_p03_Sleep_Wakeup
*******************************************************************************/
void cyCol1_p03_Sleep(void)
{
    #if defined(cyCol1_p03__PC)
        cyCol1_p03_backup.pcState = cyCol1_p03_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            cyCol1_p03_backup.usbState = cyCol1_p03_CR1_REG;
            cyCol1_p03_USB_POWER_REG |= cyCol1_p03_USBIO_ENTER_SLEEP;
            cyCol1_p03_CR1_REG &= cyCol1_p03_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cyCol1_p03__SIO)
        cyCol1_p03_backup.sioState = cyCol1_p03_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        cyCol1_p03_SIO_REG &= (uint32)(~cyCol1_p03_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: cyCol1_p03_Wakeup
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
*  Refer to cyCol1_p03_Sleep() for an example usage.
*******************************************************************************/
void cyCol1_p03_Wakeup(void)
{
    #if defined(cyCol1_p03__PC)
        cyCol1_p03_PC = cyCol1_p03_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            cyCol1_p03_USB_POWER_REG &= cyCol1_p03_USBIO_EXIT_SLEEP_PH1;
            cyCol1_p03_CR1_REG = cyCol1_p03_backup.usbState;
            cyCol1_p03_USB_POWER_REG &= cyCol1_p03_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cyCol1_p03__SIO)
        cyCol1_p03_SIO_REG = cyCol1_p03_backup.sioState;
    #endif
}


/* [] END OF FILE */

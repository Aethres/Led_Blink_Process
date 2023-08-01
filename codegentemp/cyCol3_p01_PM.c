/*******************************************************************************
* File Name: cyCol3_p01.c  
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
#include "cyCol3_p01.h"

static cyCol3_p01_BACKUP_STRUCT  cyCol3_p01_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: cyCol3_p01_Sleep
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
*  \snippet cyCol3_p01_SUT.c usage_cyCol3_p01_Sleep_Wakeup
*******************************************************************************/
void cyCol3_p01_Sleep(void)
{
    #if defined(cyCol3_p01__PC)
        cyCol3_p01_backup.pcState = cyCol3_p01_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            cyCol3_p01_backup.usbState = cyCol3_p01_CR1_REG;
            cyCol3_p01_USB_POWER_REG |= cyCol3_p01_USBIO_ENTER_SLEEP;
            cyCol3_p01_CR1_REG &= cyCol3_p01_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cyCol3_p01__SIO)
        cyCol3_p01_backup.sioState = cyCol3_p01_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        cyCol3_p01_SIO_REG &= (uint32)(~cyCol3_p01_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: cyCol3_p01_Wakeup
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
*  Refer to cyCol3_p01_Sleep() for an example usage.
*******************************************************************************/
void cyCol3_p01_Wakeup(void)
{
    #if defined(cyCol3_p01__PC)
        cyCol3_p01_PC = cyCol3_p01_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            cyCol3_p01_USB_POWER_REG &= cyCol3_p01_USBIO_EXIT_SLEEP_PH1;
            cyCol3_p01_CR1_REG = cyCol3_p01_backup.usbState;
            cyCol3_p01_USB_POWER_REG &= cyCol3_p01_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(cyCol3_p01__SIO)
        cyCol3_p01_SIO_REG = cyCol3_p01_backup.sioState;
    #endif
}


/* [] END OF FILE */

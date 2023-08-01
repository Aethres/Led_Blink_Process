/*******************************************************************************
* File Name: cyBuzzerPWM_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cyBuzzerPWM.h"

static cyBuzzerPWM_BACKUP_STRUCT cyBuzzerPWM_backup;


/*******************************************************************************
* Function Name: cyBuzzerPWM_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: cyBuzzerPWM_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_Sleep(void)
{
    if(0u != (cyBuzzerPWM_BLOCK_CONTROL_REG & cyBuzzerPWM_MASK))
    {
        cyBuzzerPWM_backup.enableState = 1u;
    }
    else
    {
        cyBuzzerPWM_backup.enableState = 0u;
    }

    cyBuzzerPWM_Stop();
    cyBuzzerPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: cyBuzzerPWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_Wakeup(void)
{
    cyBuzzerPWM_RestoreConfig();

    if(0u != cyBuzzerPWM_backup.enableState)
    {
        cyBuzzerPWM_Enable();
    }
}


/* [] END OF FILE */

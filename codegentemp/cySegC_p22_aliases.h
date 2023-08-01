/*******************************************************************************
* File Name: cySegC_p22.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_cySegC_p22_ALIASES_H) /* Pins cySegC_p22_ALIASES_H */
#define CY_PINS_cySegC_p22_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cySegC_p22_0			(cySegC_p22__0__PC)
#define cySegC_p22_0_PS		(cySegC_p22__0__PS)
#define cySegC_p22_0_PC		(cySegC_p22__0__PC)
#define cySegC_p22_0_DR		(cySegC_p22__0__DR)
#define cySegC_p22_0_SHIFT	(cySegC_p22__0__SHIFT)
#define cySegC_p22_0_INTR	((uint16)((uint16)0x0003u << (cySegC_p22__0__SHIFT*2u)))

#define cySegC_p22_INTR_ALL	 ((uint16)(cySegC_p22_0_INTR))


#endif /* End Pins cySegC_p22_ALIASES_H */


/* [] END OF FILE */

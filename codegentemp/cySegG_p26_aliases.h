/*******************************************************************************
* File Name: cySegG_p26.h  
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

#if !defined(CY_PINS_cySegG_p26_ALIASES_H) /* Pins cySegG_p26_ALIASES_H */
#define CY_PINS_cySegG_p26_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cySegG_p26_0			(cySegG_p26__0__PC)
#define cySegG_p26_0_PS		(cySegG_p26__0__PS)
#define cySegG_p26_0_PC		(cySegG_p26__0__PC)
#define cySegG_p26_0_DR		(cySegG_p26__0__DR)
#define cySegG_p26_0_SHIFT	(cySegG_p26__0__SHIFT)
#define cySegG_p26_0_INTR	((uint16)((uint16)0x0003u << (cySegG_p26__0__SHIFT*2u)))

#define cySegG_p26_INTR_ALL	 ((uint16)(cySegG_p26_0_INTR))


#endif /* End Pins cySegG_p26_ALIASES_H */


/* [] END OF FILE */

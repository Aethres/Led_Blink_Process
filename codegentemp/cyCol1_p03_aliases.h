/*******************************************************************************
* File Name: cyCol1_p03.h  
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

#if !defined(CY_PINS_cyCol1_p03_ALIASES_H) /* Pins cyCol1_p03_ALIASES_H */
#define CY_PINS_cyCol1_p03_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cyCol1_p03_0			(cyCol1_p03__0__PC)
#define cyCol1_p03_0_PS		(cyCol1_p03__0__PS)
#define cyCol1_p03_0_PC		(cyCol1_p03__0__PC)
#define cyCol1_p03_0_DR		(cyCol1_p03__0__DR)
#define cyCol1_p03_0_SHIFT	(cyCol1_p03__0__SHIFT)
#define cyCol1_p03_0_INTR	((uint16)((uint16)0x0003u << (cyCol1_p03__0__SHIFT*2u)))

#define cyCol1_p03_INTR_ALL	 ((uint16)(cyCol1_p03_0_INTR))


#endif /* End Pins cyCol1_p03_ALIASES_H */


/* [] END OF FILE */

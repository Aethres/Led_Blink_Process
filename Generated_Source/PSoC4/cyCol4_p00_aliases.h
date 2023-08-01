/*******************************************************************************
* File Name: cyCol4_p00.h  
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

#if !defined(CY_PINS_cyCol4_p00_ALIASES_H) /* Pins cyCol4_p00_ALIASES_H */
#define CY_PINS_cyCol4_p00_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cyCol4_p00_0			(cyCol4_p00__0__PC)
#define cyCol4_p00_0_PS		(cyCol4_p00__0__PS)
#define cyCol4_p00_0_PC		(cyCol4_p00__0__PC)
#define cyCol4_p00_0_DR		(cyCol4_p00__0__DR)
#define cyCol4_p00_0_SHIFT	(cyCol4_p00__0__SHIFT)
#define cyCol4_p00_0_INTR	((uint16)((uint16)0x0003u << (cyCol4_p00__0__SHIFT*2u)))

#define cyCol4_p00_INTR_ALL	 ((uint16)(cyCol4_p00_0_INTR))


#endif /* End Pins cyCol4_p00_ALIASES_H */


/* [] END OF FILE */

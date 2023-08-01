/*******************************************************************************
* File Name: cyDigit2_p35.h  
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

#if !defined(CY_PINS_cyDigit2_p35_ALIASES_H) /* Pins cyDigit2_p35_ALIASES_H */
#define CY_PINS_cyDigit2_p35_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cyDigit2_p35_0			(cyDigit2_p35__0__PC)
#define cyDigit2_p35_0_PS		(cyDigit2_p35__0__PS)
#define cyDigit2_p35_0_PC		(cyDigit2_p35__0__PC)
#define cyDigit2_p35_0_DR		(cyDigit2_p35__0__DR)
#define cyDigit2_p35_0_SHIFT	(cyDigit2_p35__0__SHIFT)
#define cyDigit2_p35_0_INTR	((uint16)((uint16)0x0003u << (cyDigit2_p35__0__SHIFT*2u)))

#define cyDigit2_p35_INTR_ALL	 ((uint16)(cyDigit2_p35_0_INTR))


#endif /* End Pins cyDigit2_p35_ALIASES_H */


/* [] END OF FILE */

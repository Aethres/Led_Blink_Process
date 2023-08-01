/*******************************************************************************
* File Name: cyDigit1_p34.h  
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

#if !defined(CY_PINS_cyDigit1_p34_ALIASES_H) /* Pins cyDigit1_p34_ALIASES_H */
#define CY_PINS_cyDigit1_p34_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cyDigit1_p34_0			(cyDigit1_p34__0__PC)
#define cyDigit1_p34_0_PS		(cyDigit1_p34__0__PS)
#define cyDigit1_p34_0_PC		(cyDigit1_p34__0__PC)
#define cyDigit1_p34_0_DR		(cyDigit1_p34__0__DR)
#define cyDigit1_p34_0_SHIFT	(cyDigit1_p34__0__SHIFT)
#define cyDigit1_p34_0_INTR	((uint16)((uint16)0x0003u << (cyDigit1_p34__0__SHIFT*2u)))

#define cyDigit1_p34_INTR_ALL	 ((uint16)(cyDigit1_p34_0_INTR))


#endif /* End Pins cyDigit1_p34_ALIASES_H */


/* [] END OF FILE */

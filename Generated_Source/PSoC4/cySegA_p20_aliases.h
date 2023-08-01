/*******************************************************************************
* File Name: cySegA_p20.h  
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

#if !defined(CY_PINS_cySegA_p20_ALIASES_H) /* Pins cySegA_p20_ALIASES_H */
#define CY_PINS_cySegA_p20_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cySegA_p20_0			(cySegA_p20__0__PC)
#define cySegA_p20_0_PS		(cySegA_p20__0__PS)
#define cySegA_p20_0_PC		(cySegA_p20__0__PC)
#define cySegA_p20_0_DR		(cySegA_p20__0__DR)
#define cySegA_p20_0_SHIFT	(cySegA_p20__0__SHIFT)
#define cySegA_p20_0_INTR	((uint16)((uint16)0x0003u << (cySegA_p20__0__SHIFT*2u)))

#define cySegA_p20_INTR_ALL	 ((uint16)(cySegA_p20_0_INTR))


#endif /* End Pins cySegA_p20_ALIASES_H */


/* [] END OF FILE */

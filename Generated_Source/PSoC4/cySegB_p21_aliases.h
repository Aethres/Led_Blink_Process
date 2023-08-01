/*******************************************************************************
* File Name: cySegB_p21.h  
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

#if !defined(CY_PINS_cySegB_p21_ALIASES_H) /* Pins cySegB_p21_ALIASES_H */
#define CY_PINS_cySegB_p21_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cySegB_p21_0			(cySegB_p21__0__PC)
#define cySegB_p21_0_PS		(cySegB_p21__0__PS)
#define cySegB_p21_0_PC		(cySegB_p21__0__PC)
#define cySegB_p21_0_DR		(cySegB_p21__0__DR)
#define cySegB_p21_0_SHIFT	(cySegB_p21__0__SHIFT)
#define cySegB_p21_0_INTR	((uint16)((uint16)0x0003u << (cySegB_p21__0__SHIFT*2u)))

#define cySegB_p21_INTR_ALL	 ((uint16)(cySegB_p21_0_INTR))


#endif /* End Pins cySegB_p21_ALIASES_H */


/* [] END OF FILE */

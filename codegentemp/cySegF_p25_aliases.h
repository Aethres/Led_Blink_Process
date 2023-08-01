/*******************************************************************************
* File Name: cySegF_p25.h  
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

#if !defined(CY_PINS_cySegF_p25_ALIASES_H) /* Pins cySegF_p25_ALIASES_H */
#define CY_PINS_cySegF_p25_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cySegF_p25_0			(cySegF_p25__0__PC)
#define cySegF_p25_0_PS		(cySegF_p25__0__PS)
#define cySegF_p25_0_PC		(cySegF_p25__0__PC)
#define cySegF_p25_0_DR		(cySegF_p25__0__DR)
#define cySegF_p25_0_SHIFT	(cySegF_p25__0__SHIFT)
#define cySegF_p25_0_INTR	((uint16)((uint16)0x0003u << (cySegF_p25__0__SHIFT*2u)))

#define cySegF_p25_INTR_ALL	 ((uint16)(cySegF_p25_0_INTR))


#endif /* End Pins cySegF_p25_ALIASES_H */


/* [] END OF FILE */

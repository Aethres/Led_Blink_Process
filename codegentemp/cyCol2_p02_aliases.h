/*******************************************************************************
* File Name: cyCol2_p02.h  
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

#if !defined(CY_PINS_cyCol2_p02_ALIASES_H) /* Pins cyCol2_p02_ALIASES_H */
#define CY_PINS_cyCol2_p02_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cyCol2_p02_0			(cyCol2_p02__0__PC)
#define cyCol2_p02_0_PS		(cyCol2_p02__0__PS)
#define cyCol2_p02_0_PC		(cyCol2_p02__0__PC)
#define cyCol2_p02_0_DR		(cyCol2_p02__0__DR)
#define cyCol2_p02_0_SHIFT	(cyCol2_p02__0__SHIFT)
#define cyCol2_p02_0_INTR	((uint16)((uint16)0x0003u << (cyCol2_p02__0__SHIFT*2u)))

#define cyCol2_p02_INTR_ALL	 ((uint16)(cyCol2_p02_0_INTR))


#endif /* End Pins cyCol2_p02_ALIASES_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: cyCol3_p01.h  
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

#if !defined(CY_PINS_cyCol3_p01_ALIASES_H) /* Pins cyCol3_p01_ALIASES_H */
#define CY_PINS_cyCol3_p01_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cyCol3_p01_0			(cyCol3_p01__0__PC)
#define cyCol3_p01_0_PS		(cyCol3_p01__0__PS)
#define cyCol3_p01_0_PC		(cyCol3_p01__0__PC)
#define cyCol3_p01_0_DR		(cyCol3_p01__0__DR)
#define cyCol3_p01_0_SHIFT	(cyCol3_p01__0__SHIFT)
#define cyCol3_p01_0_INTR	((uint16)((uint16)0x0003u << (cyCol3_p01__0__SHIFT*2u)))

#define cyCol3_p01_INTR_ALL	 ((uint16)(cyCol3_p01_0_INTR))


#endif /* End Pins cyCol3_p01_ALIASES_H */


/* [] END OF FILE */

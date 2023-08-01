/*******************************************************************************
* File Name: cySegD_p23.h  
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

#if !defined(CY_PINS_cySegD_p23_ALIASES_H) /* Pins cySegD_p23_ALIASES_H */
#define CY_PINS_cySegD_p23_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cySegD_p23_0			(cySegD_p23__0__PC)
#define cySegD_p23_0_PS		(cySegD_p23__0__PS)
#define cySegD_p23_0_PC		(cySegD_p23__0__PC)
#define cySegD_p23_0_DR		(cySegD_p23__0__DR)
#define cySegD_p23_0_SHIFT	(cySegD_p23__0__SHIFT)
#define cySegD_p23_0_INTR	((uint16)((uint16)0x0003u << (cySegD_p23__0__SHIFT*2u)))

#define cySegD_p23_INTR_ALL	 ((uint16)(cySegD_p23_0_INTR))


#endif /* End Pins cySegD_p23_ALIASES_H */


/* [] END OF FILE */

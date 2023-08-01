/*******************************************************************************
* File Name: cyLed_p44.h  
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

#if !defined(CY_PINS_cyLed_p44_ALIASES_H) /* Pins cyLed_p44_ALIASES_H */
#define CY_PINS_cyLed_p44_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cyLed_p44_0			(cyLed_p44__0__PC)
#define cyLed_p44_0_PS		(cyLed_p44__0__PS)
#define cyLed_p44_0_PC		(cyLed_p44__0__PC)
#define cyLed_p44_0_DR		(cyLed_p44__0__DR)
#define cyLed_p44_0_SHIFT	(cyLed_p44__0__SHIFT)
#define cyLed_p44_0_INTR	((uint16)((uint16)0x0003u << (cyLed_p44__0__SHIFT*2u)))

#define cyLed_p44_INTR_ALL	 ((uint16)(cyLed_p44_0_INTR))


#endif /* End Pins cyLed_p44_ALIASES_H */


/* [] END OF FILE */

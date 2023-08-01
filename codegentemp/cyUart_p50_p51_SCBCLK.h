/*******************************************************************************
* File Name: cyUart_p50_p51_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_cyUart_p50_p51_SCBCLK_H)
#define CY_CLOCK_cyUart_p50_p51_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void cyUart_p50_p51_SCBCLK_StartEx(uint32 alignClkDiv);
#define cyUart_p50_p51_SCBCLK_Start() \
    cyUart_p50_p51_SCBCLK_StartEx(cyUart_p50_p51_SCBCLK__PA_DIV_ID)

#else

void cyUart_p50_p51_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void cyUart_p50_p51_SCBCLK_Stop(void);

void cyUart_p50_p51_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 cyUart_p50_p51_SCBCLK_GetDividerRegister(void);
uint8  cyUart_p50_p51_SCBCLK_GetFractionalDividerRegister(void);

#define cyUart_p50_p51_SCBCLK_Enable()                         cyUart_p50_p51_SCBCLK_Start()
#define cyUart_p50_p51_SCBCLK_Disable()                        cyUart_p50_p51_SCBCLK_Stop()
#define cyUart_p50_p51_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    cyUart_p50_p51_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define cyUart_p50_p51_SCBCLK_SetDivider(clkDivider)           cyUart_p50_p51_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define cyUart_p50_p51_SCBCLK_SetDividerValue(clkDivider)      cyUart_p50_p51_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define cyUart_p50_p51_SCBCLK_DIV_ID     cyUart_p50_p51_SCBCLK__DIV_ID

#define cyUart_p50_p51_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define cyUart_p50_p51_SCBCLK_CTRL_REG   (*(reg32 *)cyUart_p50_p51_SCBCLK__CTRL_REGISTER)
#define cyUart_p50_p51_SCBCLK_DIV_REG    (*(reg32 *)cyUart_p50_p51_SCBCLK__DIV_REGISTER)

#define cyUart_p50_p51_SCBCLK_CMD_DIV_SHIFT          (0u)
#define cyUart_p50_p51_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define cyUart_p50_p51_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define cyUart_p50_p51_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define cyUart_p50_p51_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << cyUart_p50_p51_SCBCLK_CMD_DISABLE_SHIFT))
#define cyUart_p50_p51_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << cyUart_p50_p51_SCBCLK_CMD_ENABLE_SHIFT))

#define cyUart_p50_p51_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define cyUart_p50_p51_SCBCLK_DIV_FRAC_SHIFT (3u)
#define cyUart_p50_p51_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define cyUart_p50_p51_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define cyUart_p50_p51_SCBCLK_DIV_REG        (*(reg32 *)cyUart_p50_p51_SCBCLK__REGISTER)
#define cyUart_p50_p51_SCBCLK_ENABLE_REG     cyUart_p50_p51_SCBCLK_DIV_REG
#define cyUart_p50_p51_SCBCLK_DIV_FRAC_MASK  cyUart_p50_p51_SCBCLK__FRAC_MASK
#define cyUart_p50_p51_SCBCLK_DIV_FRAC_SHIFT (16u)
#define cyUart_p50_p51_SCBCLK_DIV_INT_MASK   cyUart_p50_p51_SCBCLK__DIVIDER_MASK
#define cyUart_p50_p51_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_cyUart_p50_p51_SCBCLK_H) */

/* [] END OF FILE */

/*******************************************************************************
* File Name: cyCol4_p00.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_cyCol4_p00_H) /* Pins cyCol4_p00_H */
#define CY_PINS_cyCol4_p00_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyCol4_p00_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} cyCol4_p00_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cyCol4_p00_Read(void);
void    cyCol4_p00_Write(uint8 value);
uint8   cyCol4_p00_ReadDataReg(void);
#if defined(cyCol4_p00__PC) || (CY_PSOC4_4200L) 
    void    cyCol4_p00_SetDriveMode(uint8 mode);
#endif
void    cyCol4_p00_SetInterruptMode(uint16 position, uint16 mode);
uint8   cyCol4_p00_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cyCol4_p00_Sleep(void); 
void cyCol4_p00_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cyCol4_p00__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cyCol4_p00_DRIVE_MODE_BITS        (3)
    #define cyCol4_p00_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cyCol4_p00_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cyCol4_p00_SetDriveMode() function.
         *  @{
         */
        #define cyCol4_p00_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cyCol4_p00_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cyCol4_p00_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cyCol4_p00_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cyCol4_p00_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cyCol4_p00_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cyCol4_p00_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cyCol4_p00_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cyCol4_p00_MASK               cyCol4_p00__MASK
#define cyCol4_p00_SHIFT              cyCol4_p00__SHIFT
#define cyCol4_p00_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cyCol4_p00_SetInterruptMode() function.
     *  @{
     */
        #define cyCol4_p00_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cyCol4_p00_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cyCol4_p00_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cyCol4_p00_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cyCol4_p00__SIO)
    #define cyCol4_p00_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cyCol4_p00__PC) && (CY_PSOC4_4200L)
    #define cyCol4_p00_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cyCol4_p00_USBIO_DISABLE              ((uint32)(~cyCol4_p00_USBIO_ENABLE))
    #define cyCol4_p00_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cyCol4_p00_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cyCol4_p00_USBIO_ENTER_SLEEP          ((uint32)((1u << cyCol4_p00_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cyCol4_p00_USBIO_SUSPEND_DEL_SHIFT)))
    #define cyCol4_p00_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cyCol4_p00_USBIO_SUSPEND_SHIFT)))
    #define cyCol4_p00_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cyCol4_p00_USBIO_SUSPEND_DEL_SHIFT)))
    #define cyCol4_p00_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cyCol4_p00__PC)
    /* Port Configuration */
    #define cyCol4_p00_PC                 (* (reg32 *) cyCol4_p00__PC)
#endif
/* Pin State */
#define cyCol4_p00_PS                     (* (reg32 *) cyCol4_p00__PS)
/* Data Register */
#define cyCol4_p00_DR                     (* (reg32 *) cyCol4_p00__DR)
/* Input Buffer Disable Override */
#define cyCol4_p00_INP_DIS                (* (reg32 *) cyCol4_p00__PC2)

/* Interrupt configuration Registers */
#define cyCol4_p00_INTCFG                 (* (reg32 *) cyCol4_p00__INTCFG)
#define cyCol4_p00_INTSTAT                (* (reg32 *) cyCol4_p00__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cyCol4_p00_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cyCol4_p00__SIO)
    #define cyCol4_p00_SIO_REG            (* (reg32 *) cyCol4_p00__SIO)
#endif /* (cyCol4_p00__SIO_CFG) */

/* USBIO registers */
#if !defined(cyCol4_p00__PC) && (CY_PSOC4_4200L)
    #define cyCol4_p00_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cyCol4_p00_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cyCol4_p00_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cyCol4_p00_DRIVE_MODE_SHIFT       (0x00u)
#define cyCol4_p00_DRIVE_MODE_MASK        (0x07u << cyCol4_p00_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cyCol4_p00_H */


/* [] END OF FILE */

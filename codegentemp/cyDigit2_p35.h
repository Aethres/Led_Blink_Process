/*******************************************************************************
* File Name: cyDigit2_p35.h  
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

#if !defined(CY_PINS_cyDigit2_p35_H) /* Pins cyDigit2_p35_H */
#define CY_PINS_cyDigit2_p35_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyDigit2_p35_aliases.h"


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
} cyDigit2_p35_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cyDigit2_p35_Read(void);
void    cyDigit2_p35_Write(uint8 value);
uint8   cyDigit2_p35_ReadDataReg(void);
#if defined(cyDigit2_p35__PC) || (CY_PSOC4_4200L) 
    void    cyDigit2_p35_SetDriveMode(uint8 mode);
#endif
void    cyDigit2_p35_SetInterruptMode(uint16 position, uint16 mode);
uint8   cyDigit2_p35_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cyDigit2_p35_Sleep(void); 
void cyDigit2_p35_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cyDigit2_p35__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cyDigit2_p35_DRIVE_MODE_BITS        (3)
    #define cyDigit2_p35_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cyDigit2_p35_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cyDigit2_p35_SetDriveMode() function.
         *  @{
         */
        #define cyDigit2_p35_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cyDigit2_p35_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cyDigit2_p35_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cyDigit2_p35_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cyDigit2_p35_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cyDigit2_p35_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cyDigit2_p35_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cyDigit2_p35_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cyDigit2_p35_MASK               cyDigit2_p35__MASK
#define cyDigit2_p35_SHIFT              cyDigit2_p35__SHIFT
#define cyDigit2_p35_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cyDigit2_p35_SetInterruptMode() function.
     *  @{
     */
        #define cyDigit2_p35_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cyDigit2_p35_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cyDigit2_p35_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cyDigit2_p35_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cyDigit2_p35__SIO)
    #define cyDigit2_p35_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cyDigit2_p35__PC) && (CY_PSOC4_4200L)
    #define cyDigit2_p35_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cyDigit2_p35_USBIO_DISABLE              ((uint32)(~cyDigit2_p35_USBIO_ENABLE))
    #define cyDigit2_p35_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cyDigit2_p35_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cyDigit2_p35_USBIO_ENTER_SLEEP          ((uint32)((1u << cyDigit2_p35_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cyDigit2_p35_USBIO_SUSPEND_DEL_SHIFT)))
    #define cyDigit2_p35_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cyDigit2_p35_USBIO_SUSPEND_SHIFT)))
    #define cyDigit2_p35_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cyDigit2_p35_USBIO_SUSPEND_DEL_SHIFT)))
    #define cyDigit2_p35_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cyDigit2_p35__PC)
    /* Port Configuration */
    #define cyDigit2_p35_PC                 (* (reg32 *) cyDigit2_p35__PC)
#endif
/* Pin State */
#define cyDigit2_p35_PS                     (* (reg32 *) cyDigit2_p35__PS)
/* Data Register */
#define cyDigit2_p35_DR                     (* (reg32 *) cyDigit2_p35__DR)
/* Input Buffer Disable Override */
#define cyDigit2_p35_INP_DIS                (* (reg32 *) cyDigit2_p35__PC2)

/* Interrupt configuration Registers */
#define cyDigit2_p35_INTCFG                 (* (reg32 *) cyDigit2_p35__INTCFG)
#define cyDigit2_p35_INTSTAT                (* (reg32 *) cyDigit2_p35__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cyDigit2_p35_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cyDigit2_p35__SIO)
    #define cyDigit2_p35_SIO_REG            (* (reg32 *) cyDigit2_p35__SIO)
#endif /* (cyDigit2_p35__SIO_CFG) */

/* USBIO registers */
#if !defined(cyDigit2_p35__PC) && (CY_PSOC4_4200L)
    #define cyDigit2_p35_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cyDigit2_p35_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cyDigit2_p35_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cyDigit2_p35_DRIVE_MODE_SHIFT       (0x00u)
#define cyDigit2_p35_DRIVE_MODE_MASK        (0x07u << cyDigit2_p35_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cyDigit2_p35_H */


/* [] END OF FILE */

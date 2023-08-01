/*******************************************************************************
* File Name: cySegC_p22.h  
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

#if !defined(CY_PINS_cySegC_p22_H) /* Pins cySegC_p22_H */
#define CY_PINS_cySegC_p22_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cySegC_p22_aliases.h"


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
} cySegC_p22_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cySegC_p22_Read(void);
void    cySegC_p22_Write(uint8 value);
uint8   cySegC_p22_ReadDataReg(void);
#if defined(cySegC_p22__PC) || (CY_PSOC4_4200L) 
    void    cySegC_p22_SetDriveMode(uint8 mode);
#endif
void    cySegC_p22_SetInterruptMode(uint16 position, uint16 mode);
uint8   cySegC_p22_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cySegC_p22_Sleep(void); 
void cySegC_p22_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cySegC_p22__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cySegC_p22_DRIVE_MODE_BITS        (3)
    #define cySegC_p22_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cySegC_p22_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cySegC_p22_SetDriveMode() function.
         *  @{
         */
        #define cySegC_p22_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cySegC_p22_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cySegC_p22_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cySegC_p22_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cySegC_p22_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cySegC_p22_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cySegC_p22_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cySegC_p22_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cySegC_p22_MASK               cySegC_p22__MASK
#define cySegC_p22_SHIFT              cySegC_p22__SHIFT
#define cySegC_p22_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cySegC_p22_SetInterruptMode() function.
     *  @{
     */
        #define cySegC_p22_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cySegC_p22_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cySegC_p22_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cySegC_p22_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cySegC_p22__SIO)
    #define cySegC_p22_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cySegC_p22__PC) && (CY_PSOC4_4200L)
    #define cySegC_p22_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cySegC_p22_USBIO_DISABLE              ((uint32)(~cySegC_p22_USBIO_ENABLE))
    #define cySegC_p22_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cySegC_p22_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cySegC_p22_USBIO_ENTER_SLEEP          ((uint32)((1u << cySegC_p22_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cySegC_p22_USBIO_SUSPEND_DEL_SHIFT)))
    #define cySegC_p22_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cySegC_p22_USBIO_SUSPEND_SHIFT)))
    #define cySegC_p22_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cySegC_p22_USBIO_SUSPEND_DEL_SHIFT)))
    #define cySegC_p22_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cySegC_p22__PC)
    /* Port Configuration */
    #define cySegC_p22_PC                 (* (reg32 *) cySegC_p22__PC)
#endif
/* Pin State */
#define cySegC_p22_PS                     (* (reg32 *) cySegC_p22__PS)
/* Data Register */
#define cySegC_p22_DR                     (* (reg32 *) cySegC_p22__DR)
/* Input Buffer Disable Override */
#define cySegC_p22_INP_DIS                (* (reg32 *) cySegC_p22__PC2)

/* Interrupt configuration Registers */
#define cySegC_p22_INTCFG                 (* (reg32 *) cySegC_p22__INTCFG)
#define cySegC_p22_INTSTAT                (* (reg32 *) cySegC_p22__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cySegC_p22_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cySegC_p22__SIO)
    #define cySegC_p22_SIO_REG            (* (reg32 *) cySegC_p22__SIO)
#endif /* (cySegC_p22__SIO_CFG) */

/* USBIO registers */
#if !defined(cySegC_p22__PC) && (CY_PSOC4_4200L)
    #define cySegC_p22_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cySegC_p22_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cySegC_p22_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cySegC_p22_DRIVE_MODE_SHIFT       (0x00u)
#define cySegC_p22_DRIVE_MODE_MASK        (0x07u << cySegC_p22_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cySegC_p22_H */


/* [] END OF FILE */

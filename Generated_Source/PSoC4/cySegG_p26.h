/*******************************************************************************
* File Name: cySegG_p26.h  
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

#if !defined(CY_PINS_cySegG_p26_H) /* Pins cySegG_p26_H */
#define CY_PINS_cySegG_p26_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cySegG_p26_aliases.h"


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
} cySegG_p26_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cySegG_p26_Read(void);
void    cySegG_p26_Write(uint8 value);
uint8   cySegG_p26_ReadDataReg(void);
#if defined(cySegG_p26__PC) || (CY_PSOC4_4200L) 
    void    cySegG_p26_SetDriveMode(uint8 mode);
#endif
void    cySegG_p26_SetInterruptMode(uint16 position, uint16 mode);
uint8   cySegG_p26_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cySegG_p26_Sleep(void); 
void cySegG_p26_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cySegG_p26__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cySegG_p26_DRIVE_MODE_BITS        (3)
    #define cySegG_p26_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cySegG_p26_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cySegG_p26_SetDriveMode() function.
         *  @{
         */
        #define cySegG_p26_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cySegG_p26_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cySegG_p26_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cySegG_p26_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cySegG_p26_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cySegG_p26_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cySegG_p26_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cySegG_p26_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cySegG_p26_MASK               cySegG_p26__MASK
#define cySegG_p26_SHIFT              cySegG_p26__SHIFT
#define cySegG_p26_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cySegG_p26_SetInterruptMode() function.
     *  @{
     */
        #define cySegG_p26_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cySegG_p26_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cySegG_p26_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cySegG_p26_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cySegG_p26__SIO)
    #define cySegG_p26_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cySegG_p26__PC) && (CY_PSOC4_4200L)
    #define cySegG_p26_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cySegG_p26_USBIO_DISABLE              ((uint32)(~cySegG_p26_USBIO_ENABLE))
    #define cySegG_p26_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cySegG_p26_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cySegG_p26_USBIO_ENTER_SLEEP          ((uint32)((1u << cySegG_p26_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cySegG_p26_USBIO_SUSPEND_DEL_SHIFT)))
    #define cySegG_p26_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cySegG_p26_USBIO_SUSPEND_SHIFT)))
    #define cySegG_p26_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cySegG_p26_USBIO_SUSPEND_DEL_SHIFT)))
    #define cySegG_p26_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cySegG_p26__PC)
    /* Port Configuration */
    #define cySegG_p26_PC                 (* (reg32 *) cySegG_p26__PC)
#endif
/* Pin State */
#define cySegG_p26_PS                     (* (reg32 *) cySegG_p26__PS)
/* Data Register */
#define cySegG_p26_DR                     (* (reg32 *) cySegG_p26__DR)
/* Input Buffer Disable Override */
#define cySegG_p26_INP_DIS                (* (reg32 *) cySegG_p26__PC2)

/* Interrupt configuration Registers */
#define cySegG_p26_INTCFG                 (* (reg32 *) cySegG_p26__INTCFG)
#define cySegG_p26_INTSTAT                (* (reg32 *) cySegG_p26__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cySegG_p26_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cySegG_p26__SIO)
    #define cySegG_p26_SIO_REG            (* (reg32 *) cySegG_p26__SIO)
#endif /* (cySegG_p26__SIO_CFG) */

/* USBIO registers */
#if !defined(cySegG_p26__PC) && (CY_PSOC4_4200L)
    #define cySegG_p26_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cySegG_p26_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cySegG_p26_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cySegG_p26_DRIVE_MODE_SHIFT       (0x00u)
#define cySegG_p26_DRIVE_MODE_MASK        (0x07u << cySegG_p26_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cySegG_p26_H */


/* [] END OF FILE */

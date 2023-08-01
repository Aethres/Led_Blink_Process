/*******************************************************************************
* File Name: cySegB_p21.h  
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

#if !defined(CY_PINS_cySegB_p21_H) /* Pins cySegB_p21_H */
#define CY_PINS_cySegB_p21_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cySegB_p21_aliases.h"


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
} cySegB_p21_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cySegB_p21_Read(void);
void    cySegB_p21_Write(uint8 value);
uint8   cySegB_p21_ReadDataReg(void);
#if defined(cySegB_p21__PC) || (CY_PSOC4_4200L) 
    void    cySegB_p21_SetDriveMode(uint8 mode);
#endif
void    cySegB_p21_SetInterruptMode(uint16 position, uint16 mode);
uint8   cySegB_p21_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cySegB_p21_Sleep(void); 
void cySegB_p21_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cySegB_p21__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cySegB_p21_DRIVE_MODE_BITS        (3)
    #define cySegB_p21_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cySegB_p21_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cySegB_p21_SetDriveMode() function.
         *  @{
         */
        #define cySegB_p21_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cySegB_p21_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cySegB_p21_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cySegB_p21_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cySegB_p21_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cySegB_p21_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cySegB_p21_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cySegB_p21_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cySegB_p21_MASK               cySegB_p21__MASK
#define cySegB_p21_SHIFT              cySegB_p21__SHIFT
#define cySegB_p21_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cySegB_p21_SetInterruptMode() function.
     *  @{
     */
        #define cySegB_p21_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cySegB_p21_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cySegB_p21_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cySegB_p21_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cySegB_p21__SIO)
    #define cySegB_p21_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cySegB_p21__PC) && (CY_PSOC4_4200L)
    #define cySegB_p21_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cySegB_p21_USBIO_DISABLE              ((uint32)(~cySegB_p21_USBIO_ENABLE))
    #define cySegB_p21_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cySegB_p21_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cySegB_p21_USBIO_ENTER_SLEEP          ((uint32)((1u << cySegB_p21_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cySegB_p21_USBIO_SUSPEND_DEL_SHIFT)))
    #define cySegB_p21_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cySegB_p21_USBIO_SUSPEND_SHIFT)))
    #define cySegB_p21_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cySegB_p21_USBIO_SUSPEND_DEL_SHIFT)))
    #define cySegB_p21_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cySegB_p21__PC)
    /* Port Configuration */
    #define cySegB_p21_PC                 (* (reg32 *) cySegB_p21__PC)
#endif
/* Pin State */
#define cySegB_p21_PS                     (* (reg32 *) cySegB_p21__PS)
/* Data Register */
#define cySegB_p21_DR                     (* (reg32 *) cySegB_p21__DR)
/* Input Buffer Disable Override */
#define cySegB_p21_INP_DIS                (* (reg32 *) cySegB_p21__PC2)

/* Interrupt configuration Registers */
#define cySegB_p21_INTCFG                 (* (reg32 *) cySegB_p21__INTCFG)
#define cySegB_p21_INTSTAT                (* (reg32 *) cySegB_p21__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cySegB_p21_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cySegB_p21__SIO)
    #define cySegB_p21_SIO_REG            (* (reg32 *) cySegB_p21__SIO)
#endif /* (cySegB_p21__SIO_CFG) */

/* USBIO registers */
#if !defined(cySegB_p21__PC) && (CY_PSOC4_4200L)
    #define cySegB_p21_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cySegB_p21_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cySegB_p21_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cySegB_p21_DRIVE_MODE_SHIFT       (0x00u)
#define cySegB_p21_DRIVE_MODE_MASK        (0x07u << cySegB_p21_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cySegB_p21_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: cyDigit1_p34.h  
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

#if !defined(CY_PINS_cyDigit1_p34_H) /* Pins cyDigit1_p34_H */
#define CY_PINS_cyDigit1_p34_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyDigit1_p34_aliases.h"


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
} cyDigit1_p34_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cyDigit1_p34_Read(void);
void    cyDigit1_p34_Write(uint8 value);
uint8   cyDigit1_p34_ReadDataReg(void);
#if defined(cyDigit1_p34__PC) || (CY_PSOC4_4200L) 
    void    cyDigit1_p34_SetDriveMode(uint8 mode);
#endif
void    cyDigit1_p34_SetInterruptMode(uint16 position, uint16 mode);
uint8   cyDigit1_p34_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cyDigit1_p34_Sleep(void); 
void cyDigit1_p34_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cyDigit1_p34__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cyDigit1_p34_DRIVE_MODE_BITS        (3)
    #define cyDigit1_p34_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cyDigit1_p34_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cyDigit1_p34_SetDriveMode() function.
         *  @{
         */
        #define cyDigit1_p34_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cyDigit1_p34_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cyDigit1_p34_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cyDigit1_p34_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cyDigit1_p34_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cyDigit1_p34_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cyDigit1_p34_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cyDigit1_p34_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cyDigit1_p34_MASK               cyDigit1_p34__MASK
#define cyDigit1_p34_SHIFT              cyDigit1_p34__SHIFT
#define cyDigit1_p34_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cyDigit1_p34_SetInterruptMode() function.
     *  @{
     */
        #define cyDigit1_p34_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cyDigit1_p34_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cyDigit1_p34_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cyDigit1_p34_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cyDigit1_p34__SIO)
    #define cyDigit1_p34_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cyDigit1_p34__PC) && (CY_PSOC4_4200L)
    #define cyDigit1_p34_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cyDigit1_p34_USBIO_DISABLE              ((uint32)(~cyDigit1_p34_USBIO_ENABLE))
    #define cyDigit1_p34_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cyDigit1_p34_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cyDigit1_p34_USBIO_ENTER_SLEEP          ((uint32)((1u << cyDigit1_p34_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cyDigit1_p34_USBIO_SUSPEND_DEL_SHIFT)))
    #define cyDigit1_p34_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cyDigit1_p34_USBIO_SUSPEND_SHIFT)))
    #define cyDigit1_p34_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cyDigit1_p34_USBIO_SUSPEND_DEL_SHIFT)))
    #define cyDigit1_p34_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cyDigit1_p34__PC)
    /* Port Configuration */
    #define cyDigit1_p34_PC                 (* (reg32 *) cyDigit1_p34__PC)
#endif
/* Pin State */
#define cyDigit1_p34_PS                     (* (reg32 *) cyDigit1_p34__PS)
/* Data Register */
#define cyDigit1_p34_DR                     (* (reg32 *) cyDigit1_p34__DR)
/* Input Buffer Disable Override */
#define cyDigit1_p34_INP_DIS                (* (reg32 *) cyDigit1_p34__PC2)

/* Interrupt configuration Registers */
#define cyDigit1_p34_INTCFG                 (* (reg32 *) cyDigit1_p34__INTCFG)
#define cyDigit1_p34_INTSTAT                (* (reg32 *) cyDigit1_p34__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cyDigit1_p34_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cyDigit1_p34__SIO)
    #define cyDigit1_p34_SIO_REG            (* (reg32 *) cyDigit1_p34__SIO)
#endif /* (cyDigit1_p34__SIO_CFG) */

/* USBIO registers */
#if !defined(cyDigit1_p34__PC) && (CY_PSOC4_4200L)
    #define cyDigit1_p34_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cyDigit1_p34_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cyDigit1_p34_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cyDigit1_p34_DRIVE_MODE_SHIFT       (0x00u)
#define cyDigit1_p34_DRIVE_MODE_MASK        (0x07u << cyDigit1_p34_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cyDigit1_p34_H */


/* [] END OF FILE */

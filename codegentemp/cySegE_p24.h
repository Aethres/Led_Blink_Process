/*******************************************************************************
* File Name: cySegE_p24.h  
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

#if !defined(CY_PINS_cySegE_p24_H) /* Pins cySegE_p24_H */
#define CY_PINS_cySegE_p24_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cySegE_p24_aliases.h"


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
} cySegE_p24_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cySegE_p24_Read(void);
void    cySegE_p24_Write(uint8 value);
uint8   cySegE_p24_ReadDataReg(void);
#if defined(cySegE_p24__PC) || (CY_PSOC4_4200L) 
    void    cySegE_p24_SetDriveMode(uint8 mode);
#endif
void    cySegE_p24_SetInterruptMode(uint16 position, uint16 mode);
uint8   cySegE_p24_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cySegE_p24_Sleep(void); 
void cySegE_p24_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cySegE_p24__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cySegE_p24_DRIVE_MODE_BITS        (3)
    #define cySegE_p24_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cySegE_p24_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cySegE_p24_SetDriveMode() function.
         *  @{
         */
        #define cySegE_p24_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cySegE_p24_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cySegE_p24_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cySegE_p24_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cySegE_p24_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cySegE_p24_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cySegE_p24_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cySegE_p24_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cySegE_p24_MASK               cySegE_p24__MASK
#define cySegE_p24_SHIFT              cySegE_p24__SHIFT
#define cySegE_p24_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cySegE_p24_SetInterruptMode() function.
     *  @{
     */
        #define cySegE_p24_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cySegE_p24_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cySegE_p24_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cySegE_p24_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cySegE_p24__SIO)
    #define cySegE_p24_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cySegE_p24__PC) && (CY_PSOC4_4200L)
    #define cySegE_p24_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cySegE_p24_USBIO_DISABLE              ((uint32)(~cySegE_p24_USBIO_ENABLE))
    #define cySegE_p24_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cySegE_p24_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cySegE_p24_USBIO_ENTER_SLEEP          ((uint32)((1u << cySegE_p24_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cySegE_p24_USBIO_SUSPEND_DEL_SHIFT)))
    #define cySegE_p24_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cySegE_p24_USBIO_SUSPEND_SHIFT)))
    #define cySegE_p24_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cySegE_p24_USBIO_SUSPEND_DEL_SHIFT)))
    #define cySegE_p24_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cySegE_p24__PC)
    /* Port Configuration */
    #define cySegE_p24_PC                 (* (reg32 *) cySegE_p24__PC)
#endif
/* Pin State */
#define cySegE_p24_PS                     (* (reg32 *) cySegE_p24__PS)
/* Data Register */
#define cySegE_p24_DR                     (* (reg32 *) cySegE_p24__DR)
/* Input Buffer Disable Override */
#define cySegE_p24_INP_DIS                (* (reg32 *) cySegE_p24__PC2)

/* Interrupt configuration Registers */
#define cySegE_p24_INTCFG                 (* (reg32 *) cySegE_p24__INTCFG)
#define cySegE_p24_INTSTAT                (* (reg32 *) cySegE_p24__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cySegE_p24_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cySegE_p24__SIO)
    #define cySegE_p24_SIO_REG            (* (reg32 *) cySegE_p24__SIO)
#endif /* (cySegE_p24__SIO_CFG) */

/* USBIO registers */
#if !defined(cySegE_p24__PC) && (CY_PSOC4_4200L)
    #define cySegE_p24_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cySegE_p24_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cySegE_p24_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cySegE_p24_DRIVE_MODE_SHIFT       (0x00u)
#define cySegE_p24_DRIVE_MODE_MASK        (0x07u << cySegE_p24_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cySegE_p24_H */


/* [] END OF FILE */

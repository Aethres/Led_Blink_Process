/*******************************************************************************
* File Name: cySegD_p23.h  
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

#if !defined(CY_PINS_cySegD_p23_H) /* Pins cySegD_p23_H */
#define CY_PINS_cySegD_p23_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cySegD_p23_aliases.h"


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
} cySegD_p23_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cySegD_p23_Read(void);
void    cySegD_p23_Write(uint8 value);
uint8   cySegD_p23_ReadDataReg(void);
#if defined(cySegD_p23__PC) || (CY_PSOC4_4200L) 
    void    cySegD_p23_SetDriveMode(uint8 mode);
#endif
void    cySegD_p23_SetInterruptMode(uint16 position, uint16 mode);
uint8   cySegD_p23_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cySegD_p23_Sleep(void); 
void cySegD_p23_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cySegD_p23__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cySegD_p23_DRIVE_MODE_BITS        (3)
    #define cySegD_p23_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cySegD_p23_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cySegD_p23_SetDriveMode() function.
         *  @{
         */
        #define cySegD_p23_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cySegD_p23_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cySegD_p23_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cySegD_p23_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cySegD_p23_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cySegD_p23_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cySegD_p23_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cySegD_p23_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cySegD_p23_MASK               cySegD_p23__MASK
#define cySegD_p23_SHIFT              cySegD_p23__SHIFT
#define cySegD_p23_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cySegD_p23_SetInterruptMode() function.
     *  @{
     */
        #define cySegD_p23_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cySegD_p23_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cySegD_p23_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cySegD_p23_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cySegD_p23__SIO)
    #define cySegD_p23_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cySegD_p23__PC) && (CY_PSOC4_4200L)
    #define cySegD_p23_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cySegD_p23_USBIO_DISABLE              ((uint32)(~cySegD_p23_USBIO_ENABLE))
    #define cySegD_p23_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cySegD_p23_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cySegD_p23_USBIO_ENTER_SLEEP          ((uint32)((1u << cySegD_p23_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cySegD_p23_USBIO_SUSPEND_DEL_SHIFT)))
    #define cySegD_p23_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cySegD_p23_USBIO_SUSPEND_SHIFT)))
    #define cySegD_p23_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cySegD_p23_USBIO_SUSPEND_DEL_SHIFT)))
    #define cySegD_p23_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cySegD_p23__PC)
    /* Port Configuration */
    #define cySegD_p23_PC                 (* (reg32 *) cySegD_p23__PC)
#endif
/* Pin State */
#define cySegD_p23_PS                     (* (reg32 *) cySegD_p23__PS)
/* Data Register */
#define cySegD_p23_DR                     (* (reg32 *) cySegD_p23__DR)
/* Input Buffer Disable Override */
#define cySegD_p23_INP_DIS                (* (reg32 *) cySegD_p23__PC2)

/* Interrupt configuration Registers */
#define cySegD_p23_INTCFG                 (* (reg32 *) cySegD_p23__INTCFG)
#define cySegD_p23_INTSTAT                (* (reg32 *) cySegD_p23__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cySegD_p23_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cySegD_p23__SIO)
    #define cySegD_p23_SIO_REG            (* (reg32 *) cySegD_p23__SIO)
#endif /* (cySegD_p23__SIO_CFG) */

/* USBIO registers */
#if !defined(cySegD_p23__PC) && (CY_PSOC4_4200L)
    #define cySegD_p23_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cySegD_p23_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cySegD_p23_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cySegD_p23_DRIVE_MODE_SHIFT       (0x00u)
#define cySegD_p23_DRIVE_MODE_MASK        (0x07u << cySegD_p23_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cySegD_p23_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: cySegA_p20.h  
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

#if !defined(CY_PINS_cySegA_p20_H) /* Pins cySegA_p20_H */
#define CY_PINS_cySegA_p20_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cySegA_p20_aliases.h"


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
} cySegA_p20_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cySegA_p20_Read(void);
void    cySegA_p20_Write(uint8 value);
uint8   cySegA_p20_ReadDataReg(void);
#if defined(cySegA_p20__PC) || (CY_PSOC4_4200L) 
    void    cySegA_p20_SetDriveMode(uint8 mode);
#endif
void    cySegA_p20_SetInterruptMode(uint16 position, uint16 mode);
uint8   cySegA_p20_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cySegA_p20_Sleep(void); 
void cySegA_p20_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cySegA_p20__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cySegA_p20_DRIVE_MODE_BITS        (3)
    #define cySegA_p20_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cySegA_p20_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cySegA_p20_SetDriveMode() function.
         *  @{
         */
        #define cySegA_p20_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cySegA_p20_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cySegA_p20_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cySegA_p20_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cySegA_p20_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cySegA_p20_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cySegA_p20_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cySegA_p20_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cySegA_p20_MASK               cySegA_p20__MASK
#define cySegA_p20_SHIFT              cySegA_p20__SHIFT
#define cySegA_p20_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cySegA_p20_SetInterruptMode() function.
     *  @{
     */
        #define cySegA_p20_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cySegA_p20_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cySegA_p20_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cySegA_p20_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cySegA_p20__SIO)
    #define cySegA_p20_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cySegA_p20__PC) && (CY_PSOC4_4200L)
    #define cySegA_p20_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cySegA_p20_USBIO_DISABLE              ((uint32)(~cySegA_p20_USBIO_ENABLE))
    #define cySegA_p20_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cySegA_p20_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cySegA_p20_USBIO_ENTER_SLEEP          ((uint32)((1u << cySegA_p20_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cySegA_p20_USBIO_SUSPEND_DEL_SHIFT)))
    #define cySegA_p20_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cySegA_p20_USBIO_SUSPEND_SHIFT)))
    #define cySegA_p20_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cySegA_p20_USBIO_SUSPEND_DEL_SHIFT)))
    #define cySegA_p20_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cySegA_p20__PC)
    /* Port Configuration */
    #define cySegA_p20_PC                 (* (reg32 *) cySegA_p20__PC)
#endif
/* Pin State */
#define cySegA_p20_PS                     (* (reg32 *) cySegA_p20__PS)
/* Data Register */
#define cySegA_p20_DR                     (* (reg32 *) cySegA_p20__DR)
/* Input Buffer Disable Override */
#define cySegA_p20_INP_DIS                (* (reg32 *) cySegA_p20__PC2)

/* Interrupt configuration Registers */
#define cySegA_p20_INTCFG                 (* (reg32 *) cySegA_p20__INTCFG)
#define cySegA_p20_INTSTAT                (* (reg32 *) cySegA_p20__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cySegA_p20_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cySegA_p20__SIO)
    #define cySegA_p20_SIO_REG            (* (reg32 *) cySegA_p20__SIO)
#endif /* (cySegA_p20__SIO_CFG) */

/* USBIO registers */
#if !defined(cySegA_p20__PC) && (CY_PSOC4_4200L)
    #define cySegA_p20_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cySegA_p20_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cySegA_p20_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cySegA_p20_DRIVE_MODE_SHIFT       (0x00u)
#define cySegA_p20_DRIVE_MODE_MASK        (0x07u << cySegA_p20_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cySegA_p20_H */


/* [] END OF FILE */

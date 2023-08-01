/*******************************************************************************
* File Name: cyLed_p44.h  
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

#if !defined(CY_PINS_cyLed_p44_H) /* Pins cyLed_p44_H */
#define CY_PINS_cyLed_p44_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyLed_p44_aliases.h"


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
} cyLed_p44_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cyLed_p44_Read(void);
void    cyLed_p44_Write(uint8 value);
uint8   cyLed_p44_ReadDataReg(void);
#if defined(cyLed_p44__PC) || (CY_PSOC4_4200L) 
    void    cyLed_p44_SetDriveMode(uint8 mode);
#endif
void    cyLed_p44_SetInterruptMode(uint16 position, uint16 mode);
uint8   cyLed_p44_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cyLed_p44_Sleep(void); 
void cyLed_p44_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cyLed_p44__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cyLed_p44_DRIVE_MODE_BITS        (3)
    #define cyLed_p44_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cyLed_p44_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cyLed_p44_SetDriveMode() function.
         *  @{
         */
        #define cyLed_p44_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cyLed_p44_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cyLed_p44_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cyLed_p44_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cyLed_p44_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cyLed_p44_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cyLed_p44_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cyLed_p44_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cyLed_p44_MASK               cyLed_p44__MASK
#define cyLed_p44_SHIFT              cyLed_p44__SHIFT
#define cyLed_p44_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cyLed_p44_SetInterruptMode() function.
     *  @{
     */
        #define cyLed_p44_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cyLed_p44_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cyLed_p44_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cyLed_p44_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cyLed_p44__SIO)
    #define cyLed_p44_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cyLed_p44__PC) && (CY_PSOC4_4200L)
    #define cyLed_p44_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cyLed_p44_USBIO_DISABLE              ((uint32)(~cyLed_p44_USBIO_ENABLE))
    #define cyLed_p44_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cyLed_p44_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cyLed_p44_USBIO_ENTER_SLEEP          ((uint32)((1u << cyLed_p44_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cyLed_p44_USBIO_SUSPEND_DEL_SHIFT)))
    #define cyLed_p44_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cyLed_p44_USBIO_SUSPEND_SHIFT)))
    #define cyLed_p44_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cyLed_p44_USBIO_SUSPEND_DEL_SHIFT)))
    #define cyLed_p44_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cyLed_p44__PC)
    /* Port Configuration */
    #define cyLed_p44_PC                 (* (reg32 *) cyLed_p44__PC)
#endif
/* Pin State */
#define cyLed_p44_PS                     (* (reg32 *) cyLed_p44__PS)
/* Data Register */
#define cyLed_p44_DR                     (* (reg32 *) cyLed_p44__DR)
/* Input Buffer Disable Override */
#define cyLed_p44_INP_DIS                (* (reg32 *) cyLed_p44__PC2)

/* Interrupt configuration Registers */
#define cyLed_p44_INTCFG                 (* (reg32 *) cyLed_p44__INTCFG)
#define cyLed_p44_INTSTAT                (* (reg32 *) cyLed_p44__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cyLed_p44_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cyLed_p44__SIO)
    #define cyLed_p44_SIO_REG            (* (reg32 *) cyLed_p44__SIO)
#endif /* (cyLed_p44__SIO_CFG) */

/* USBIO registers */
#if !defined(cyLed_p44__PC) && (CY_PSOC4_4200L)
    #define cyLed_p44_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cyLed_p44_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cyLed_p44_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cyLed_p44_DRIVE_MODE_SHIFT       (0x00u)
#define cyLed_p44_DRIVE_MODE_MASK        (0x07u << cyLed_p44_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cyLed_p44_H */


/* [] END OF FILE */

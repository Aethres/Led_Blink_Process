/*******************************************************************************
* File Name: cyBuzzer_p55.h  
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

#if !defined(CY_PINS_cyBuzzer_p55_H) /* Pins cyBuzzer_p55_H */
#define CY_PINS_cyBuzzer_p55_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyBuzzer_p55_aliases.h"


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
} cyBuzzer_p55_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cyBuzzer_p55_Read(void);
void    cyBuzzer_p55_Write(uint8 value);
uint8   cyBuzzer_p55_ReadDataReg(void);
#if defined(cyBuzzer_p55__PC) || (CY_PSOC4_4200L) 
    void    cyBuzzer_p55_SetDriveMode(uint8 mode);
#endif
void    cyBuzzer_p55_SetInterruptMode(uint16 position, uint16 mode);
uint8   cyBuzzer_p55_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cyBuzzer_p55_Sleep(void); 
void cyBuzzer_p55_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cyBuzzer_p55__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cyBuzzer_p55_DRIVE_MODE_BITS        (3)
    #define cyBuzzer_p55_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cyBuzzer_p55_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cyBuzzer_p55_SetDriveMode() function.
         *  @{
         */
        #define cyBuzzer_p55_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cyBuzzer_p55_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cyBuzzer_p55_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cyBuzzer_p55_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cyBuzzer_p55_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cyBuzzer_p55_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cyBuzzer_p55_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cyBuzzer_p55_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cyBuzzer_p55_MASK               cyBuzzer_p55__MASK
#define cyBuzzer_p55_SHIFT              cyBuzzer_p55__SHIFT
#define cyBuzzer_p55_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cyBuzzer_p55_SetInterruptMode() function.
     *  @{
     */
        #define cyBuzzer_p55_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cyBuzzer_p55_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cyBuzzer_p55_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cyBuzzer_p55_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cyBuzzer_p55__SIO)
    #define cyBuzzer_p55_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cyBuzzer_p55__PC) && (CY_PSOC4_4200L)
    #define cyBuzzer_p55_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cyBuzzer_p55_USBIO_DISABLE              ((uint32)(~cyBuzzer_p55_USBIO_ENABLE))
    #define cyBuzzer_p55_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cyBuzzer_p55_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cyBuzzer_p55_USBIO_ENTER_SLEEP          ((uint32)((1u << cyBuzzer_p55_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cyBuzzer_p55_USBIO_SUSPEND_DEL_SHIFT)))
    #define cyBuzzer_p55_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cyBuzzer_p55_USBIO_SUSPEND_SHIFT)))
    #define cyBuzzer_p55_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cyBuzzer_p55_USBIO_SUSPEND_DEL_SHIFT)))
    #define cyBuzzer_p55_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cyBuzzer_p55__PC)
    /* Port Configuration */
    #define cyBuzzer_p55_PC                 (* (reg32 *) cyBuzzer_p55__PC)
#endif
/* Pin State */
#define cyBuzzer_p55_PS                     (* (reg32 *) cyBuzzer_p55__PS)
/* Data Register */
#define cyBuzzer_p55_DR                     (* (reg32 *) cyBuzzer_p55__DR)
/* Input Buffer Disable Override */
#define cyBuzzer_p55_INP_DIS                (* (reg32 *) cyBuzzer_p55__PC2)

/* Interrupt configuration Registers */
#define cyBuzzer_p55_INTCFG                 (* (reg32 *) cyBuzzer_p55__INTCFG)
#define cyBuzzer_p55_INTSTAT                (* (reg32 *) cyBuzzer_p55__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cyBuzzer_p55_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cyBuzzer_p55__SIO)
    #define cyBuzzer_p55_SIO_REG            (* (reg32 *) cyBuzzer_p55__SIO)
#endif /* (cyBuzzer_p55__SIO_CFG) */

/* USBIO registers */
#if !defined(cyBuzzer_p55__PC) && (CY_PSOC4_4200L)
    #define cyBuzzer_p55_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cyBuzzer_p55_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cyBuzzer_p55_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cyBuzzer_p55_DRIVE_MODE_SHIFT       (0x00u)
#define cyBuzzer_p55_DRIVE_MODE_MASK        (0x07u << cyBuzzer_p55_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cyBuzzer_p55_H */


/* [] END OF FILE */

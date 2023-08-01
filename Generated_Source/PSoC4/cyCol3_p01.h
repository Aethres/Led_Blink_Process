/*******************************************************************************
* File Name: cyCol3_p01.h  
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

#if !defined(CY_PINS_cyCol3_p01_H) /* Pins cyCol3_p01_H */
#define CY_PINS_cyCol3_p01_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyCol3_p01_aliases.h"


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
} cyCol3_p01_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cyCol3_p01_Read(void);
void    cyCol3_p01_Write(uint8 value);
uint8   cyCol3_p01_ReadDataReg(void);
#if defined(cyCol3_p01__PC) || (CY_PSOC4_4200L) 
    void    cyCol3_p01_SetDriveMode(uint8 mode);
#endif
void    cyCol3_p01_SetInterruptMode(uint16 position, uint16 mode);
uint8   cyCol3_p01_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cyCol3_p01_Sleep(void); 
void cyCol3_p01_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cyCol3_p01__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cyCol3_p01_DRIVE_MODE_BITS        (3)
    #define cyCol3_p01_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cyCol3_p01_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cyCol3_p01_SetDriveMode() function.
         *  @{
         */
        #define cyCol3_p01_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cyCol3_p01_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cyCol3_p01_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cyCol3_p01_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cyCol3_p01_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cyCol3_p01_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cyCol3_p01_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cyCol3_p01_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cyCol3_p01_MASK               cyCol3_p01__MASK
#define cyCol3_p01_SHIFT              cyCol3_p01__SHIFT
#define cyCol3_p01_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cyCol3_p01_SetInterruptMode() function.
     *  @{
     */
        #define cyCol3_p01_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cyCol3_p01_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cyCol3_p01_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cyCol3_p01_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cyCol3_p01__SIO)
    #define cyCol3_p01_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cyCol3_p01__PC) && (CY_PSOC4_4200L)
    #define cyCol3_p01_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cyCol3_p01_USBIO_DISABLE              ((uint32)(~cyCol3_p01_USBIO_ENABLE))
    #define cyCol3_p01_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cyCol3_p01_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cyCol3_p01_USBIO_ENTER_SLEEP          ((uint32)((1u << cyCol3_p01_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cyCol3_p01_USBIO_SUSPEND_DEL_SHIFT)))
    #define cyCol3_p01_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cyCol3_p01_USBIO_SUSPEND_SHIFT)))
    #define cyCol3_p01_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cyCol3_p01_USBIO_SUSPEND_DEL_SHIFT)))
    #define cyCol3_p01_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cyCol3_p01__PC)
    /* Port Configuration */
    #define cyCol3_p01_PC                 (* (reg32 *) cyCol3_p01__PC)
#endif
/* Pin State */
#define cyCol3_p01_PS                     (* (reg32 *) cyCol3_p01__PS)
/* Data Register */
#define cyCol3_p01_DR                     (* (reg32 *) cyCol3_p01__DR)
/* Input Buffer Disable Override */
#define cyCol3_p01_INP_DIS                (* (reg32 *) cyCol3_p01__PC2)

/* Interrupt configuration Registers */
#define cyCol3_p01_INTCFG                 (* (reg32 *) cyCol3_p01__INTCFG)
#define cyCol3_p01_INTSTAT                (* (reg32 *) cyCol3_p01__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cyCol3_p01_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cyCol3_p01__SIO)
    #define cyCol3_p01_SIO_REG            (* (reg32 *) cyCol3_p01__SIO)
#endif /* (cyCol3_p01__SIO_CFG) */

/* USBIO registers */
#if !defined(cyCol3_p01__PC) && (CY_PSOC4_4200L)
    #define cyCol3_p01_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cyCol3_p01_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cyCol3_p01_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cyCol3_p01_DRIVE_MODE_SHIFT       (0x00u)
#define cyCol3_p01_DRIVE_MODE_MASK        (0x07u << cyCol3_p01_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cyCol3_p01_H */


/* [] END OF FILE */

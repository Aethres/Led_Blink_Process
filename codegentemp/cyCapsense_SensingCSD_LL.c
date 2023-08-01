/***************************************************************************//**
* \file cyCapsense_SensingCSD_LL.c
* \version 6.0
*
* \brief
*   This file defines the data structure global variables and provides
*   implementation for the low-level APIs of the CSD part of
*   the Sensing module. The file contains the APIs used for the CSD block
*   initialization, calibration, and scanning.
*
* \see cyCapsense v6.0 Datasheet
*
*//*****************************************************************************
* Copyright (2016-2018), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/
#include "cyCapsense_Structure.h"
#include "cyCapsense_Configuration.h"
#include "cyCapsense_SensingCSD_LL.h"
#include "cyapicallbacks.h"

#if (cyCapsense_ENABLE == cyCapsense_CSD_EN)

/***************************************
* API Constants
***************************************/

#if (cyCapsense_ENABLE == cyCapsense_CSDV2)

#if (cyCapsense_ENABLE == cyCapsense_CSD_AUTO_ZERO_EN)
    #define cyCapsense_CSD_AZ_ENABLE_CFG                  (cyCapsense_CSD_AZ_EN_MASK)
#else
    #define cyCapsense_CSD_AZ_ENABLE_CFG                  (0uL)
#endif /* (cyCapsense_ENABLE == cyCapsense_CSD_AUTO_ZERO_EN) */

#if (cyCapsense_IDAC_SINKING == cyCapsense_CSD_IDAC_CONFIG)
    #define cyCapsense_HSCMP_SCAN_MASK                    (cyCapsense_HSCMP_EN_MASK | cyCapsense_CSD_AZ_ENABLE_CFG |\
                                                                 cyCapsense_HSCMP_INVERT_MASK)
#else
    #define cyCapsense_HSCMP_SCAN_MASK                    (cyCapsense_HSCMP_EN_MASK | cyCapsense_CSD_AZ_ENABLE_CFG)
#endif /* (cyCapsense_IDAC_SINKING == cyCapsense_CSD_IDAC_CONFIG) */

#define cyCapsense_HSCMP_INIT_MASK                        (cyCapsense_HSCMP_EN_MASK | cyCapsense_CSD_AZ_ENABLE_CFG)

#define cyCapsense_DEFAULT_SW_SHIELD_SEL                  (0x00000000uL)
#define cyCapsense_DEFAULT_CSD_SW_DSI_SEL                 (cyCapsense_SW_DSI_SEL_CMODPAD | cyCapsense_SW_DSI_SEL_TANKPAD)
#define cyCapsense_DEFAULT_CSD_INTR_SET                   (0x00000000uL)
#define cyCapsense_DEFAULT_SW_HS_P_SEL                    (0x00000000uL)
#define cyCapsense_DEFAULT_SW_HS_N_SEL                    (0x00000000uL)
#define cyCapsense_DEFAULT_CSD_SW_FW_TANK_SEL             (0x00000000uL)
#define cyCapsense_DEFAULT_CSD_ADC_CTL                    (0x00000000uL)
#define cyCapsense_DEFAULT_HSCMP_CFG                      (0x00000000uL)

#else

    /* Set IDAC ranges */
    #if (cyCapsense_IDAC_GAIN_8X == cyCapsense_CSD_IDAC_GAIN)
        #define cyCapsense_DEFAULT_IDAC_MOD_RANGE         (cyCapsense_IDAC_MOD_RANGE_MASK)
        #define cyCapsense_DEFAULT_IDAC_COMP_RANGE        (cyCapsense_IDAC_COMP_RANGE_MASK)
    #else
        #define cyCapsense_DEFAULT_IDAC_MOD_RANGE         (0u)
        #define cyCapsense_DEFAULT_IDAC_COMP_RANGE        (0u)
    #endif /* (cyCapsense_IDAC_GAIN_8X == cyCapsense_CSD_IDAC_GAIN) */

    /* Defining default IDACs configuration according to settings in customizer. */
    #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
        #define cyCapsense_DEFAULT_CSD_IDAC_CONFIG        (cyCapsense_IDAC_MOD_MODE_VARIABLE |\
                                                                 cyCapsense_IDAC_COMP_MODE_FIXED |\
                                                                 cyCapsense_DEFAULT_IDAC_MOD_RANGE |\
                                                                 cyCapsense_DEFAULT_IDAC_COMP_RANGE)
    #else
        #define cyCapsense_DEFAULT_CSD_IDAC_CONFIG        (cyCapsense_IDAC_MOD_MODE_VARIABLE |\
                                                                 cyCapsense_DEFAULT_IDAC_MOD_RANGE)
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */

#endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */

/***************************************
* Variables
***************************************/

#if (cyCapsense_ENABLE == cyCapsense_CSDV2)
    uint32 cyCapsense_configCsd = cyCapsense_DEFAULT_CSD_CONFIG;
#else
    uint32 cyCapsense_configCsd = cyCapsense_DEFAULT_CSD_CONFIG | cyCapsense_DEFAULT_MODULATION_MODE;
    static uint32 cyCapsense_counterResolution = cyCapsense_CNT_RESOLUTION_12_BITS;
#endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */

/* Flag to indicate electrodes that were connected previously */
static uint8 cyCapsense_eleCsdDisconnectFlag = 0u;
#if ((cyCapsense_ENABLE == cyCapsense_CSDV2) && (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN))
    /* Number of re-samplings when the bad conversion occurs */
    uint8 cyCapsense_badConversionsNum = cyCapsense_BAD_CONVERSIONS_NUM;
#endif /* ((cyCapsense_ENABLE == cyCapsense_CSDV2) && (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN)) */

#if (cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE)
    /* Stores IDAC and raw count that corresponds to a sensor with maximum Cp within a widget */
    uint8 cyCapsense_calibratedIdac = 1u;
    uint16 cyCapsense_calibratedRawcount = 1u;
    #if (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN)
        uint8 cyCapsense_calibratedIdacRow = 1u;
        uint16 cyCapsense_calibratedRawcountRow = 1u;
    #endif /*(cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN) */
#endif /* (cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE) */


/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

#if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN)
    static void cyCapsense_SsSetShieldDelay(uint32 delay);
    #if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN)
        static void cyCapsense_SsCSDEnableShieldTank(void);
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN) */
    #if (0u != cyCapsense_CSD_TOTAL_SHIELD_COUNT)
        static void cyCapsense_SsCSDEnableShieldElectrodes(void);
    #endif /* (0u != cyCapsense_CSD_TOTAL_SHIELD_COUNT) */
#endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) */

#if ((cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE) || \
     (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_AUTOCAL_EN))
    static cystatus cyCapsense_SsCSDCalibrateCheck(cyCapsense_RAM_WD_BASE_STRUCT const *ptrWdgt, uint32 rawLevel, uint32 rawData);
    #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
        static void cyCapsense_SsCSDSetSingleIdacMode(void);
        static void cyCapsense_SsCSDRestoreIdacMode(void);
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */
    static cystatus cyCapsense_SsCSDCalibrateOneSensor(uint32 rawLevel,
                                                             uint8 *ptrIdac,
                                                             uint8 *iDAC8Max);
#endif /* ((cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE) || \
           (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_AUTOCAL_EN))  */
#if (cyCapsense_ENABLE == cyCapsense_CSDV2)
    static void cyCapsense_SsCSDSetFilterDelay(void);
#else
    CY_INLINE static void cyCapsense_SsCSDClockRestart(void);
#endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
CY_INLINE static void cyCapsense_SsCSDCmodPrecharge(void);
CY_INLINE static void cyCapsense_SsCSDTriggerScan(void);
static void cyCapsense_SsCSDConfigIDACs(void);
static void cyCapsense_SsCSDSetModeSnsClockDivider(uint32 snsClkSource, uint32 snsClkDivider);

/** \}
* \endcond */


#if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN)
    /*******************************************************************************
    * Function Name: cyCapsense_SsSetShieldDelay
    ****************************************************************************//**
    *
    * \brief
    *   This is an internal function that sets a shield delay.
    *
    * \details
    *   The function updates the CSD configuration register bits that define the shield
    *   signal delay relatively to the sense signal.
    *
    * \param delay
    *   Specifies the shield delay value:
    *    PSoC 4100/4200 value interpretation:
    *         0 - no delay
    *         1 - 1 cycle of HFCLK
    *         2 - 2 cycles of HFCLK
    *    Third-generation HW block (except 4100/4200 devices):
    *         0 - no delay
    *         3 - 10ns delay
    *         2 - 50ns delay
    *    Fourth-generation HW block:
    *         0 - no delay
    *         1 - 5ns delay
    *         2 - 10ns delay
    *         3 - 20ns delay
    *
    *******************************************************************************/
    static void cyCapsense_SsSetShieldDelay(uint32 delay)
    {
        /* Update CSD config register shield delay bits with shield delay value */
        cyCapsense_configCsd &= (uint32)(~cyCapsense_CONFIG_SHIELD_DELAY_MASK);
        cyCapsense_configCsd |= (delay << cyCapsense_SHIELD_DELAY_SHIFT);
    }

    #if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN)
        /*******************************************************************************
        * Function Name: cyCapsense_SsCSDEnableShieldTank
        ****************************************************************************//**
        *
        * \brief
        *   This function configures Csh pin
        *
        * \details
        *   The function updates the CSH_HSIOM register to connect Csh to AMUXBUS-B.
        *   For Third-generation HW block it additionally sets Strong drive mode for Csh
        *   and applies High level to Csh pin when precharge is set to IO buffer.
        *
        *******************************************************************************/
        static void cyCapsense_SsCSDEnableShieldTank(void)
        {
            uint32 newRegValue;

            /* Update the CSH_HSIOM register to connect Csh to AMUXBUS-B */
            newRegValue = CY_GET_REG32(cyCapsense_CSH_HSIOM_PTR);
            newRegValue &= (uint32)(~(uint32)cyCapsense_CSH_HSIOM_MASK);
            newRegValue |= (cyCapsense_CSH_TO_AMUXBUS_B_MASK << cyCapsense_CSH_HSIOM_SHIFT);
            CY_SET_REG32(cyCapsense_CSH_HSIOM_PTR, newRegValue);

            #if ((cyCapsense_CSH_PRECHARGE_IO_BUF == cyCapsense_CSD_CSH_PRECHARGE_SRC) &&\
                 (cyCapsense_DISABLE == cyCapsense_CSDV2))
                /* Set Strong drive mode for Csh */
                newRegValue = CY_GET_REG32(cyCapsense_CSH_PC_PTR);
                newRegValue &= (uint32)(~(cyCapsense_CSH_PC_MASK << cyCapsense_CSH_PC_SHIFT));
                newRegValue |= (cyCapsense_CSH_PC_STRONG_MODE << cyCapsense_CSH_PC_SHIFT);
                CY_SET_REG32(cyCapsense_CSH_PC_PTR, newRegValue);

                /* Appliy High level to Csh pin for Csh */
                newRegValue = CY_GET_REG32(cyCapsense_CSH_DR_PTR);
                newRegValue &= (uint32)(~(cyCapsense_DR_MASK << cyCapsense_CSH_SHIFT));
                newRegValue |= (uint32)cyCapsense_CSH_DR_CONFIG;
                CY_SET_REG32(cyCapsense_CSH_DR_PTR, newRegValue);
            #endif /* ((cyCapsense_CSH_PRECHARGE_IO_BUF == cyCapsense_CSD_CSH_PRECHARGE_SRC) &&\
                       (cyCapsense_DISABLE == cyCapsense_CSDV2)) */
        }
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN) */

    #if (0u != cyCapsense_CSD_TOTAL_SHIELD_COUNT)
        /*******************************************************************************
        * Function Name: cyCapsense_SsCSDEnableShieldElectrodes
        ****************************************************************************//**
        *
        * \brief
        *   This internal function initializes Shield Electrodes.
        *
        * \details
        *   The function sets the bit in the HSIOM register which enables the shield electrode
        *   functionality on the pin. The port and pin configurations are stored in
        *   the cyCapsense_shieldIoList structure.
        *
        *******************************************************************************/
        static void cyCapsense_SsCSDEnableShieldElectrodes(void)
        {
            uint32 newRegValue;
            uint32 shieldIndex;

            for (shieldIndex = 0u; shieldIndex < cyCapsense_CSD_TOTAL_SHIELD_COUNT; shieldIndex++)
            {
                /* Set drive mode to Analog */
                CY_SET_REG32(cyCapsense_shieldIoList[shieldIndex].pcPtr, CY_GET_REG32(cyCapsense_shieldIoList[shieldIndex].pcPtr) &
                           ~(cyCapsense_GPIO_PC_MASK <<(cyCapsense_shieldIoList[shieldIndex].shift)));

                /* Set HSIOM register mode to CSD_SHIELD or AMUXBUS B connection */
                newRegValue = CY_GET_REG32(cyCapsense_shieldIoList[shieldIndex].hsiomPtr);
                newRegValue &= ~(cyCapsense_HSIOM_SEL_MASK << (cyCapsense_shieldIoList[shieldIndex].hsiomShift));

                /* Set HSIOM register mode to CSD_SHIELD */
                newRegValue |= (cyCapsense_HSIOM_SEL_CSD_SHIELD << (cyCapsense_shieldIoList[shieldIndex].hsiomShift));

                CY_SET_REG32(cyCapsense_shieldIoList[shieldIndex].hsiomPtr, newRegValue);
            }
        }


        /*******************************************************************************
        * Function Name: cyCapsense_SsCSDDisableShieldElectrodes
        ****************************************************************************//**
        *
        * \brief
        *   This internal function disables Shield Electrodes.
        *
        * \details
        *   The function resets the bit in the HSIOM register which disables the shield
        *   electrode functionality on the pin. The port and pin configurations are
        *   stored in  the cyCapsense_shieldIoList structure.
        *
        *******************************************************************************/
        void cyCapsense_SsCSDDisableShieldElectrodes(void)
        {
            uint32 newRegValue;
            uint32 shieldIndex;

            for (shieldIndex = 0u; shieldIndex < cyCapsense_CSD_TOTAL_SHIELD_COUNT; shieldIndex++)
            {
                /* Reset HSIOM register (to GPIO state) */
                CY_SET_REG32(cyCapsense_shieldIoList[shieldIndex].hsiomPtr, CY_GET_REG32(cyCapsense_shieldIoList[shieldIndex].hsiomPtr) &
                             (uint32)~(uint32)(cyCapsense_HSIOM_SEL_MASK << cyCapsense_shieldIoList[shieldIndex].hsiomShift));

                /* Update port configuration register (drive mode to ground)  */
                newRegValue = CY_GET_REG32(cyCapsense_shieldIoList[shieldIndex].pcPtr);
                newRegValue &= ~(cyCapsense_GPIO_PC_MASK << cyCapsense_shieldIoList[shieldIndex].shift);
                newRegValue |= (cyCapsense_SNS_GROUND_CONNECT << cyCapsense_shieldIoList[shieldIndex].shift);
                CY_SET_REG32(cyCapsense_shieldIoList[shieldIndex].pcPtr, newRegValue);

                /* Set logic 0 to port data register */
                CY_SET_REG32(cyCapsense_shieldIoList[shieldIndex].drPtr, CY_GET_REG32(cyCapsense_shieldIoList[shieldIndex].drPtr) &
                           (uint32)~(uint32)((uint32)1u << cyCapsense_shieldIoList[shieldIndex].drShift));
            }
        }
    #endif /* (0u != cyCapsense_CSD_TOTAL_SHIELD_COUNT) */
#endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) */


/*******************************************************************************
* Function Name: cyCapsense_SsCSDSetModeSnsClockDivider
****************************************************************************//**
*
* \brief
*   Sets sense source and Sense Clock Divider
*
* \details
*   For Fourth-generation HW block: Updates cyCapsense_SENSE_PERIOD register with
*   sense source and Sense Clock Divider.
*   For Third-generation HW block: Updates cyCapsense_configCsd variable with
*   sense source and sets sense clock divider.
*
* \param
*   snsClkSource The sense source for the sense clock.
* \param
*   snsClkDivider The divider value for the sense clock.
*
*******************************************************************************/
static void cyCapsense_SsCSDSetModeSnsClockDivider(uint32 snsClkSource, uint32 snsClkDivider)
{
    #if (cyCapsense_ENABLE == cyCapsense_CSDV2)
        /* Update reg value with divider and configuration */
        CY_SET_REG32(cyCapsense_SENSE_PERIOD_PTR, snsClkSource | (snsClkDivider - 1u));
    #else
        /* Set configuration */
        cyCapsense_configCsd &= ~(cyCapsense_CONFIG_PRS_SELECT_MASK | cyCapsense_CSD_PRS_12_BIT);
        cyCapsense_configCsd |= snsClkSource;

        /* Set sense clock divider */
        cyCapsense_SsSetSnsClockDivider(snsClkDivider);
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
}


#if (cyCapsense_ENABLE == cyCapsense_CSDV2)
    /*******************************************************************************
    * Function Name: cyCapsense_SsCSDSetFilterDelay
    ****************************************************************************//**
    *
    * \brief
    *   Sets the filter delay for Fourth-generation HW block.
    *
    * \details
    *   This function updates Fourth-generation HW block configuration
    *   variable cyCapsense_configCsd
    *   with the filter delay which depends on the sample clock frequency.
    *   This variable is written into register during enabling
    *   Fourth-generation HW block .
    *
    *******************************************************************************/
    static void cyCapsense_SsCSDSetFilterDelay(void)
    {
        #if (cyCapsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ)
            uint32 sampleClkFreqHz;
        #endif /* (cyCapsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) */

        cyCapsense_configCsd &= ~cyCapsense_CONFIG_FILTER_DELAY_MASK;

        #if (cyCapsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ)
            sampleClkFreqHz = CYDEV_BCLK__HFCLK__HZ / (uint32)cyCapsense_dsRam.modCsdClk;
            if(sampleClkFreqHz <= cyCapsense_MOD_CSD_CLK_12MHZ)
            {
                cyCapsense_configCsd |= cyCapsense_CONFIG_FILTER_DELAY_12MHZ;
            }
            else if(sampleClkFreqHz <= cyCapsense_MOD_CSD_CLK_24MHZ)
            {
                cyCapsense_configCsd |= cyCapsense_CONFIG_FILTER_DELAY_24MHZ;
            }
            else
            {
                cyCapsense_configCsd |= cyCapsense_CONFIG_FILTER_DELAY_48MHZ;
            }
        #else
            cyCapsense_configCsd |= cyCapsense_CONFIG_FILTER_DELAY_12MHZ;
        #endif /* (cyCapsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) */
    }
#endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)  */


/*******************************************************************************
* Function Name: cyCapsense_SsCSDConfigIDACs
****************************************************************************//**
*
* \brief
*   Configures the mode for IDAC registers
*
* \details
*   This function configures the IDAC modes depend on Compensation IDAC
*   enabled or disabled.
*
*******************************************************************************/
static void cyCapsense_SsCSDConfigIDACs(void)
{
    #if (cyCapsense_ENABLE == cyCapsense_CSDV2)
    CY_SET_REG32(cyCapsense_IDAC_MOD_PTR, cyCapsense_IDAC_MOD_DEFAULT_CFG);
        #if ((cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) && \
             (cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN))
        CY_SET_REG32(cyCapsense_IDACB_PTR, cyCapsense_IDAC_COMP_DEFAULT_CFG);
        #endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) && \
                   (cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN)) */
    #else
        #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
            CY_SET_REG32(cyCapsense_IDAC_PTR, cyCapsense_DEFAULT_CSD_IDAC_CONFIG);
        #else
            CY_SET_REG32(cyCapsense_IDAC_PTR, CY_GET_REG32(cyCapsense_IDAC_PTR) &
                                                                ~(cyCapsense_IDAC_MOD_MODE_MASK |
                                                                  cyCapsense_IDAC_MOD_MASK));
            CY_SET_REG32(cyCapsense_IDAC_PTR, CY_GET_REG32(cyCapsense_IDAC_PTR) |
                                                                 cyCapsense_DEFAULT_CSD_IDAC_CONFIG);
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
}


/*******************************************************************************
* Function Name: cyCapsense_SsCSDInitialize
****************************************************************************//**
*
* \brief
*   This API initializes the CSD module.
*
* \details
*   The function performs the following steps for Fourth-generation HW block:
*   1) Sets GPIO output to "0" for all sensor pins;
*   2) Connects CMOD to AMUXBUS-A and to CSDBUS-A;
*   3) Connects CMOD to (sense path) to CSDCOMP;
*   4) Connects Csh_tank to AMUXBUS-B and to CSDBUS-B;
*   5) Connects VREF to REFGEN;
*   6) Configures REFGEN and sets the reference voltage;
*   7) Connects VREF to CSDCOMP and HSCOMP;
*   8) Configures IDAC and connect to CSDBUS-A (to drive CMOD);
*   9) Configures ModClk;
*   10) Configure SnsClk source;
*   11) Sets other CSD configurations (Csd Auto Zero time,
*       Sample Init period, interrupts,
*       CMOD and Csh_tank/shield initialization switch resistance).
*
*   The function performs the following steps for Third-generation HW block:
*   1) Sets all the sensors to the inactive state;
*   2) Enables Shield Electrodes;
*   3) Configures the CSD block and IDACs;
*   4) Connects Cmod to AMUXBUS-A;
*   5) Enables the clocks;
*   6) Sets the shield delay;
*   7) Enables the CSD block; connects Vref Buffer to the AMUX bus.
*
*******************************************************************************/
void cyCapsense_SsCSDInitialize(void)
{
    uint32 newRegValue;

    /* Set all the sensors to inactive state */
    cyCapsense_SsClearCSDSensors();

    #if (cyCapsense_ENABLE == cyCapsense_CSDV2)
        cyCapsense_BistDischargeExtCapacitors();
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
    
    #if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN)
        /* Connect shields to AMUX-B bus (config HSIOM regs) */
        #if (0u != cyCapsense_CSD_TOTAL_SHIELD_COUNT)
            cyCapsense_SsCSDEnableShieldElectrodes();
        #endif /* (0u != cyCapsense_CSD_TOTAL_SHIELD_COUNT) */

        #if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN)
            /* Configure Csh */
            cyCapsense_SsCSDEnableShieldTank();
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN) */
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) */

    #if (cyCapsense_ENABLE == cyCapsense_CSDV2)

        /* Initialize the unused CSD registers to defaut state */
        CY_SET_REG32(cyCapsense_SENSE_DUTY_PTR,       cyCapsense_DEFAULT_SENSE_DUTY_SEL);

        /* Configure VREF */
        newRegValue = CY_GET_REG32(cyCapsense_SW_REFGEN_SEL_PTR);
        newRegValue |= cyCapsense_DEFAULT_SW_REFGEN_SEL;

        CY_SET_REG32(cyCapsense_SW_REFGEN_SEL_PTR, newRegValue);
        CY_SET_REG32(cyCapsense_INTR_SET_PTR,         cyCapsense_DEFAULT_CSD_INTR_SET);
        CY_SET_REG32(cyCapsense_SW_FW_TANK_SEL_PTR,   cyCapsense_DEFAULT_CSD_SW_FW_TANK_SEL);
        CY_SET_REG32(cyCapsense_SW_DSI_SEL_PTR,       cyCapsense_DEFAULT_CSD_SW_DSI_SEL);
        CY_SET_REG32(cyCapsense_ADC_CTL_PTR,          cyCapsense_DEFAULT_CSD_ADC_CTL);
        CY_SET_REG32(cyCapsense_AMBUF_PTR,            cyCapsense_AMBUF_PWR_MODE_OFF);
        CY_SET_REG32(cyCapsense_SW_SHIELD_SEL_PTR,    cyCapsense_DEFAULT_SW_SHIELD_SEL);
        CY_SET_REG32(cyCapsense_SW_HS_P_SEL_PTR,      cyCapsense_DEFAULT_SW_HS_P_SEL);
        CY_SET_REG32(cyCapsense_SW_HS_N_SEL_PTR,      cyCapsense_DEFAULT_SW_HS_N_SEL);
        CY_SET_REG32(cyCapsense_HSCMP_PTR,            cyCapsense_DEFAULT_HSCMP_CFG);

        /* Connect CMOD to AMUXBUS-A */
        newRegValue = CY_GET_REG32(cyCapsense_CMOD_HSIOM_PTR);
        newRegValue &= (uint32)(~(uint32)cyCapsense_CMOD_HSIOM_MASK);
        newRegValue |= (cyCapsense_HSIOM_SEL_AMUXA << cyCapsense_CMOD_HSIOM_SHIFT);
        CY_SET_REG32(cyCapsense_CMOD_HSIOM_PTR, newRegValue);

        /* Connect AMUXBUS-A to CSDBUS-A */
        newRegValue = CY_GET_REG32(cyCapsense_SW_BYP_SEL_PTR);
        newRegValue |= cyCapsense_SW_BYP_SEL_SW_BYA_MASK;
        CY_SET_REG32(cyCapsense_SW_BYP_SEL_PTR, newRegValue);

        /* Connect CMOD to (sense path) to CSDCOMP */
        #if (cyCapsense_CSD__CMOD_PAD == cyCapsense_CMOD_CONNECTION)
            CY_SET_REG32(cyCapsense_SW_CMP_P_SEL_PTR, cyCapsense_SW_CMP_P_SEL_SW_SFPM_STATIC_CLOSE);
        #elif (cyCapsense_CSD__CSHIELD_PAD == cyCapsense_CMOD_CONNECTION)
            CY_SET_REG32(cyCapsense_SW_CMP_P_SEL_PTR, cyCapsense_SW_CMP_P_SEL_SW_SFPS_STATIC_CLOSE);
        #else
            CY_SET_REG32(cyCapsense_SW_CMP_P_SEL_PTR, cyCapsense_SW_CMP_P_SEL_SW_SFPT_STATIC_CLOSE);
        #endif /* (cyCapsense_CSD__CMOD_PAD == cyCapsense_CMOD_CONNECTION) */

        /* Configure shield driving path */
        #if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN)
            /* Connect AMUXBUS-B to CSDBUS-B (and AMUXBUS-A to CSDBUS-A ) */
            CY_SET_REG32(cyCapsense_SW_BYP_SEL_PTR, cyCapsense_SW_BYP_SEL_SW_BYA_MASK | cyCapsense_SW_BYP_SEL_SW_BYB_MASK);

        /* Connect AMUXBUS-B to HSCMP positive input */
        CY_SET_REG32(cyCapsense_SW_HS_P_SEL_PTR, 0x00000000uL);
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) */

        /* Configure VREF */
        #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) && (cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN)
            /* Connect VREF to REFGEN. Connect IDACB to CSDBUSA */
            newRegValue = CY_GET_REG32(cyCapsense_SW_REFGEN_SEL_PTR);
            newRegValue |= cyCapsense_SW_REFGEN_SEL_SW_SGR_MASK | cyCapsense_SW_REFGEN_SEL_SW_IAIB_MASK;
            CY_SET_REG32(cyCapsense_SW_REFGEN_SEL_PTR, newRegValue);
        #else
            /* Connect VREF to REFGEN (IAIB switch is open) */
            newRegValue = CY_GET_REG32(cyCapsense_SW_REFGEN_SEL_PTR);
            newRegValue |= cyCapsense_SW_REFGEN_SEL_SW_SGR_MASK;
            CY_SET_REG32(cyCapsense_SW_REFGEN_SEL_PTR, newRegValue);
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) && (cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN */

    #if (cyCapsense_2000_MV > cyCapsense_CYDEV_VDDA_MV)

        /* Connect VREFLOW (from AMBUF and RefGen is in bypass mode) to CSDCOMP when Vdda < 2 V */
        CY_SET_REG32(cyCapsense_SW_CMP_N_SEL_PTR, cyCapsense_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE);

        /* Configure REFGEN. Set reference voltage when Vdda < 2 V */
        CY_SET_REG32(cyCapsense_REFGEN_PTR, cyCapsense_REFGEN_LV);

        /* Connect Vrefhi to AMUBUF positive input when Vdaa < 2V
         *  Connect AMUBUF to SCDCMP negative input when Vdaa < 2V
         */
        #if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN)
            #if (cyCapsense_IDAC_SINKING == cyCapsense_CSD_IDAC_CONFIG)
                CY_SET_REG32(cyCapsense_SW_AMUXBUF_SEL_PTR, cyCapsense_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE |
                                                                      cyCapsense_SW_AMUXBUF_SEL_SW_ICB_PHI2);
            #else
                CY_SET_REG32(cyCapsense_SW_AMUXBUF_SEL_PTR, cyCapsense_SW_AMUXBUF_SEL_SW_DEFAULT);
            #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) */
            CY_SET_REG32(cyCapsense_AMBUF_PTR, cyCapsense_AMBUF_PWR_MODE_NORM);
        #else
            CY_SET_REG32(cyCapsense_AMBUF_PTR, cyCapsense_AMBUF_PWR_MODE_OFF);
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) */

        /* Connect VREFHI to HSCOMP */
        CY_SET_REG32(cyCapsense_SW_HS_N_SEL_PTR, cyCapsense_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE);
    #else

        /* Connect VREFHI (from RefGen) to CSDCOMP when Vdda >= 2 V */
        CY_SET_REG32(cyCapsense_SW_CMP_N_SEL_PTR, cyCapsense_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE);

        /* Configure REFGEN. Set reference voltage when Vdda >= 2 V */
        CY_SET_REG32(cyCapsense_REFGEN_PTR, cyCapsense_REFGEN_HV);

        #if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN)
            /* Turn on CSD_AMBUF high power level when Vdaa >= 2V */
            CY_SET_REG32(cyCapsense_AMBUF_PTR, cyCapsense_AMBUF_PWR_MODE_HI);

            #if (cyCapsense_IDAC_SINKING != cyCapsense_CSD_IDAC_CONFIG)
                CY_SET_REG32(cyCapsense_SW_AMUXBUF_SEL_PTR, cyCapsense_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE |
                                                                      cyCapsense_SW_AMUXBUF_SEL_SW_ICB_PHI2);
            #else
                CY_SET_REG32(cyCapsense_SW_AMUXBUF_SEL_PTR, cyCapsense_SW_AMUXBUF_SEL_SW_DEFAULT);
            #endif /* (cyCapsense_IDAC_SINKING == cyCapsense_CSD_IDAC_CONFIG) */
        #else
            CY_SET_REG32(cyCapsense_SW_AMUXBUF_SEL_PTR, cyCapsense_SW_AMUXBUF_SEL_SW_DEFAULT);
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) */

        /* Connect VREFHI to HSCOMP */
        CY_SET_REG32(cyCapsense_SW_HS_N_SEL_PTR, cyCapsense_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE);
    #endif /* (cyCapsense_2000_MV > cyCapsense_CYDEV_VDDA_MV) */

    /* Configure IDACs mode */
    cyCapsense_SsCSDConfigIDACs();

        /* Configure ModClk */
        cyCapsense_SsSetModClkClockDivider((uint32)cyCapsense_dsRam.modCsdClk);

    /* Set other CSD configurations */
    #if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN)
        cyCapsense_SsSetShieldDelay(cyCapsense_CSD_SHIELD_DELAY);
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) */

    /* Configure HW block filter delay */
    cyCapsense_SsCSDSetFilterDelay();

    #if (cyCapsense_DISABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN)
        /* Enable power to sub-blocks */
        CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd |
                                                  cyCapsense_CONFIG_SENSE_EN_MASK |
                                                  cyCapsense_CONFIG_ENABLE_MASK);
    #endif /* (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN) */

        /* Set Csd Auto Zero time (set AZ_TIME bitmask) */
        CY_SET_REG32(cyCapsense_SEQ_TIME_PTR, cyCapsense_CSD_AUTO_ZERO_TIME);

        /* Select CMOD and Csh_tank/shield initialization switch resistance */
        CY_SET_REG32(cyCapsense_SW_RES_PTR, 0x00000000);

        /* Set the number of dummy fine initialization cycles */
        CY_SET_REG32(cyCapsense_SEQ_INIT_CNT_PTR, cyCapsense_CSD_FINE_INIT_TIME);
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */

    #if (cyCapsense_DISABLE == cyCapsense_CSDV2)

        /* Configure IDACs mode */
        cyCapsense_SsCSDConfigIDACs();

        /* Connect Cmod to AMUXBUS-A using HSIOM registers */
        newRegValue = CY_GET_REG32(cyCapsense_CMOD_HSIOM_PTR);
        newRegValue &= (uint32)(~(uint32)cyCapsense_CMOD_HSIOM_MASK);
        newRegValue |= (cyCapsense_HSIOM_SEL_AMUXA << cyCapsense_CMOD_HSIOM_SHIFT);
        CY_SET_REG32(cyCapsense_CMOD_HSIOM_PTR, newRegValue);

        #if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN)
            cyCapsense_SsSetShieldDelay(cyCapsense_CSD_SHIELD_DELAY);
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) */

        /* Enable CSD block. Connect Vref Buffer to AMUX bus to make sure that Cmod is charged before scanning in active mode */
        #if (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN)
            CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd);
        #else
            CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CTANK_PRECHARGE_CONFIG_CSD_EN);
        #endif /* (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN) */
    #endif /* (cyCapsense_DISABLE == cyCapsense_CSDV2) */

    #if ((cyCapsense_ENABLE == cyCapsense_CSD_COMMON_SNS_CLK_EN) &&\
         (cyCapsense_CLK_SOURCE_DIRECT == cyCapsense_CSD_SNS_CLK_SOURCE))
         /* Set clock dividers and clock source mode */
        cyCapsense_SsCSDConfigClock();
    #endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_COMMON_SNS_CLK_EN) &&\
               (cyCapsense_CLK_SOURCE_DIRECT == cyCapsense_CSD_SNS_CLK_SOURCE)) */
}


/*******************************************************************************
* Function Name: cyCapsense_SsCSDElectrodeCheck
****************************************************************************//**
*
* \brief
*   Checks if electrodes were previously connected using
 * cyCapsense_CSDSetupWidgetExt() API and if yes disconnects them.
*
* \details
*   This function checks if cyCapsense_eleCsdDisconnectFlag is set.
*   If it set, the function disconnects the previously connected electrode.
*   The previous IO is contained in cyCapsense_curSnsIOPtr and
*   cyCapsense_curFlashSnsPtr contains the previous data for Ganged
*   sensors.
*
*******************************************************************************/
void cyCapsense_SsCSDElectrodeCheck(void)
{
    #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
        uint32 tempVal;
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN) */

    if (cyCapsense_ENABLE == cyCapsense_eleCsdDisconnectFlag)
    {
        /* Disconnect if electrodes were previous connected by CSDSetupWidgetExt() API */
        #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
            /* Check ganged sns flag  */
            if (cyCapsense_GANGED_SNS_MASK == (cyCapsense_curFlashWdgtPtr->staticConfig & cyCapsense_GANGED_SNS_MASK))
            {
                /* Get number of ganged pins */
                tempVal = cyCapsense_curFlashSnsPtr->numPins;

                /* Get IO pointer  */
                cyCapsense_curSnsIOPtr = &cyCapsense_ioList[cyCapsense_curFlashSnsPtr->firstPinId];

                /* Disconnect all ganged sensors */
                do
                {
                    cyCapsense_CSDDisconnectSns(cyCapsense_curSnsIOPtr);
                    cyCapsense_curSnsIOPtr++;
                    tempVal--;
                } while (0u != tempVal);
            }
            else
            {
                /* Disconnect ganged sensor */
                cyCapsense_CSDDisconnectSns(cyCapsense_curSnsIOPtr);
            }
        #else
            /* Disable sensor */
            cyCapsense_CSDDisconnectSns(cyCapsense_curSnsIOPtr);
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)  */

        cyCapsense_eleCsdDisconnectFlag = 0u;
    }
}


/*******************************************************************************
* Function Name: cyCapsense_SsCSDSetUpIdacs
****************************************************************************//**
*
* \brief
*  This internal function changes the IDACs values.
*
* \details
*  If Compensation IDAC is enabled, it updates two IDACs.
*  The Modulator IDAC is common for all the sensors of the widget.
*  The Compensation IDAC is updated for the sensor of the widget which
*  is available in the RAM_SNS_STRUCT structure.
*  If the Compensation IDAC is disabled, the function updates the Modulator IDAC
*  value only in the RAM_WD_BASE_STRUCT structure.
*
* \param
*  ptrWdgt The pointer to the RAM_WD_BASE_STRUCT structure.
*
*******************************************************************************/
void cyCapsense_SsCSDSetUpIdacs(cyCapsense_RAM_WD_BASE_STRUCT const *ptrWdgt)
{

    uint8 interruptState;

#if (cyCapsense_ENABLE == cyCapsense_CSDV2)
    uint32 idacARegValue;
    #if ((cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) && \
         (cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN))
        uint32 idacBRegValue;
    #endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) && \
               (cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN)) */

    interruptState = CyEnterCriticalSection();

    /* Get IDACA Value */
    idacARegValue = CY_GET_REG32(cyCapsense_IDAC_MOD_PTR);

    /* Set IDACA Value mask */
    idacARegValue &= ~(cyCapsense_IDAC_MOD_VAL_MASK);

    /* Set IDACA value */
    #if (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN)
        if (cyCapsense_dsFlash.wdgtArray[(cyCapsense_widgetIndex)].numCols <= cyCapsense_sensorIndex)
        {
            idacARegValue |= (uint32)ptrWdgt->rowIdacMod[cyCapsense_scanFreqIndex];
        }
        else
        {
            idacARegValue |= (uint32)ptrWdgt->idacMod[cyCapsense_scanFreqIndex];
        }
    #else
        idacARegValue |= (uint32)ptrWdgt->idacMod[cyCapsense_scanFreqIndex];
    #endif /* (cyCapsense_CSD_MATRIX_WIDGET_EN | cyCapsense_CSD_TOUCHPAD_WIDGET_EN) */

    /* Update IDACA register with new value */
    CY_SET_REG32(cyCapsense_IDAC_MOD_PTR, idacARegValue);
    CyExitCriticalSection(interruptState);

    #if ((cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) && \
         (cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN))
        interruptState = CyEnterCriticalSection();
        /* Get IDACB Value */
        idacBRegValue = CY_GET_REG32(cyCapsense_IDAC_COMP_PTR);

        /* Set IDACB Value mask */
        idacBRegValue &= ~(cyCapsense_IDAC_COMP_VAL_MASK);

        /* Set IDACB value */
        idacBRegValue |= (uint32)cyCapsense_curRamSnsPtr->idacComp[cyCapsense_scanFreqIndex];

        /* Update IDACA register with new value */
        CY_SET_REG32(cyCapsense_IDAC_COMP_PTR, idacBRegValue);
        CyExitCriticalSection(interruptState);
    #endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) && \
               (cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN)) */

#else

    uint32 newRegValue;
    uint8 const *ptrIdacMod = ptrWdgt->idacMod;

    #if (cyCapsense_CSD_MATRIX_WIDGET_EN  | cyCapsense_CSD_TOUCHPAD_WIDGET_EN)
        if (cyCapsense_dsFlash.wdgtArray[(cyCapsense_widgetIndex)].numCols <= cyCapsense_sensorIndex)
        {
            ptrIdacMod = &ptrWdgt->rowIdacMod[0u];
        }
    #endif /* (cyCapsense_CSD_MATRIX_WIDGET_EN  | cyCapsense_CSD_TOUCHPAD_WIDGET_EN) */

    interruptState = CyEnterCriticalSection();

    /* Get Idac Value */
    newRegValue = CY_GET_REG32(cyCapsense_IDAC_PTR);

    /* Set Idac Value mask */
    #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
        newRegValue &= ~(cyCapsense_IDAC_MOD_MASK | cyCapsense_IDAC_COMP_MASK);
    #else
        newRegValue &= ~(cyCapsense_IDAC_MOD_MASK);
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */

    /* Set Idac value */
    #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
        newRegValue |= (ptrIdacMod[cyCapsense_scanFreqIndex] |
                       (uint32)((uint32)cyCapsense_curRamSnsPtr->idacComp[cyCapsense_scanFreqIndex] <<
                       cyCapsense_IDAC_COMP_DATA_OFFSET));
    #else
        newRegValue |= ptrIdacMod[cyCapsense_scanFreqIndex];
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */
    CY_SET_REG32(cyCapsense_IDAC_PTR, newRegValue);

    CyExitCriticalSection(interruptState);

#endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
}


#if (cyCapsense_ENABLE == cyCapsense_CSDV2)
    /*******************************************************************************
    * Function Name: cyCapsense_SsCSDGetNumberOfConversions
    ****************************************************************************//**
    *
    * \brief
    *  This function gets Number of conversions.
    *
    * \details
    *  This function gets Number of conversions using foll.owing equation:
    *   conversionsNum = (2^resolution - 1) / snsClkDivider.
    *
    * \param
    *  snsClkDivider The divider value for the sense clock.
    *  resolution The widget resolution.
    *  snsClkSrc The current Sense Clock Source.
    *
    * \return Returns the Number of conversions.
    *
    *******************************************************************************/
    uint32 cyCapsense_SsCSDGetNumberOfConversions(uint32 snsClkDivider, uint32 resolution, uint32 snsClkSrc)
    {
        uint32 conversionsNum;
        #if ((cyCapsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) && (cyCapsense_ENABLE != cyCapsense_CSDV2_REF9P6UA_EN))
            uint32 sampleClkFreqHz;
        #endif /* ((cyCapsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) && (cyCapsense_ENABLE != cyCapsense_CSDV2_REF9P6UA_EN)) */

        /* Calculate scanning resolution value in register */
        conversionsNum = (uint32)((1uL << resolution) - 1uL);

        #if(cyCapsense_ENABLE != cyCapsense_CSDV2_REF9P6UA_EN)
            /* Apply correction to oveflow for 16 bit resolution */
            if (cyCapsense_RES16BIT == resolution)
            {
                conversionsNum -= ((snsClkDivider + 1u) >> 1u);

                #if (cyCapsense_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ)
                    sampleClkFreqHz = CYDEV_BCLK__HFCLK__HZ / (uint32)cyCapsense_dsRam.modCsdClk;

                    if (sampleClkFreqHz <= cyCapsense_MOD_CSD_CLK_12MHZ)
                    {
                        conversionsNum -= cyCapsense_CONFIG_FILTER_DELAY_2_CYCLES;
                    }
                    else if (sampleClkFreqHz <= cyCapsense_MOD_CSD_CLK_24MHZ)
                    {
                        conversionsNum -= cyCapsense_CONFIG_FILTER_DELAY_3_CYCLES;
                    }
                    else
                    {
                        conversionsNum -= cyCapsense_CONFIG_FILTER_DELAY_4_CYCLES;
                    }
                #else
                    conversionsNum -= cyCapsense_CONFIG_FILTER_DELAY_2_CYCLES;
                #endif /* (INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) */
            }
        #endif /* (cyCapsense_ENABLE != cyCapsense_CSDV2_REF9P6UA_EN) */

        if (0u < snsClkDivider)
        {
            conversionsNum /= snsClkDivider;
        }

    #if((cyCapsense_CLK_SOURCE_PRS8  == cyCapsense_CSD_SNS_CLK_SOURCE) ||\
        (cyCapsense_CLK_SOURCE_PRS12 == cyCapsense_CSD_SNS_CLK_SOURCE) ||\
        (cyCapsense_CLK_SOURCE_PRSAUTO == cyCapsense_CSD_SNS_CLK_SOURCE))
        switch (snsClkSrc)
        {
            case cyCapsense_CLK_SOURCE_PRS8:
            case cyCapsense_CLK_SOURCE_PRS12:
                /* Divide by 2 for PRS8/PRS12 mode */
                conversionsNum >>= 1u;
                break;

            default:
                break;
        }
    #endif /* ((cyCapsense_CLK_SOURCE_PRS8  == cyCapsense_CSD_SNS_CLK_SOURCE) ||\
               (cyCapsense_CLK_SOURCE_PRS12 == cyCapsense_CSD_SNS_CLK_SOURCE) ||\
               (cyCapsense_CLK_SOURCE_PRSAUTO == cyCapsense_CSD_SNS_CLK_SOURCE)) */

    return((conversionsNum > 0uL) ? (conversionsNum) : 1uL);
    }
#endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */


/*******************************************************************************
* Function Name: cyCapsense_SsCSDConfigClock
****************************************************************************//**
*
* \brief
*  This function configure sense clock for different modes.
*
* \details
*  Function sets the clock divider and configures the mode based on configuration.
*
*******************************************************************************/
void cyCapsense_SsCSDConfigClock(void)
{
    uint32 snsClkDivider;
    uint32 snsClkSrc;
    uint32 newRegValue;

    cyCapsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (cyCapsense_RAM_WD_BASE_STRUCT *)
             cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2WdgtRam;

    /* Get sense divider based on configuration */
    #if (cyCapsense_ENABLE == cyCapsense_CSD_COMMON_SNS_CLK_EN)
        snsClkDivider = (uint32)cyCapsense_dsRam.snsCsdClk;
    #else
        #if (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN)
            /* Get SnsClck divider for rows or columns */
            if (cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].numCols <= cyCapsense_sensorIndex)
            {
                snsClkDivider = (uint32)(ptrWdgt->rowSnsClk);
            }
            else
            {
                snsClkDivider = (uint32)(ptrWdgt->snsClk);
            }
        #else
            snsClkDivider = (uint32)(ptrWdgt->snsClk);
        #endif /* (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN) */
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_COMMON_SNS_CLK_EN) */

    /* Get sense clk source calculated in cyCapsense_SsCSDInitialize() before */
    #if (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN)
        /* Get SnsClc Source for rows or columns */
        if (cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].numCols <= cyCapsense_sensorIndex)
        {
            snsClkSrc = (uint32)ptrWdgt->rowSnsClkSource;
        }
        else
        {
            snsClkSrc = (uint32)ptrWdgt->snsClkSource;
        }
    #else
        snsClkSrc = (uint32)ptrWdgt->snsClkSource;
    #endif /* (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN) */

    #if (cyCapsense_ENABLE == cyCapsense_CSDV2)
        newRegValue = (snsClkSrc << CYFLD_CSD_LFSR_SIZE__OFFSET);

        /* Configuring PRS SEL_BIT */
        if ((cyCapsense_CLK_SOURCE_PRS8 == snsClkSrc) ||
            (cyCapsense_CLK_SOURCE_PRS12 == snsClkSrc))
        {
            newRegValue |= cyCapsense_SENSE_PERIOD_SEL_LFSR_MSB_MASK;
        }
    #else
        newRegValue = snsClkSrc;
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */

    #if((cyCapsense_CLK_SOURCE_PRS8  == cyCapsense_CSD_SNS_CLK_SOURCE) ||\
        (cyCapsense_CLK_SOURCE_PRS12 == cyCapsense_CSD_SNS_CLK_SOURCE) ||\
        (cyCapsense_CLK_SOURCE_PRSAUTO == cyCapsense_CSD_SNS_CLK_SOURCE))
        switch (snsClkSrc)
        {
        case cyCapsense_CLK_SOURCE_PRS8:
        case cyCapsense_CLK_SOURCE_PRS12:
            /* Divide by 2 for PRS8/PRS12 mode */
            snsClkDivider >>= 1;
            if (snsClkDivider == 0u)
            {
                snsClkDivider = 1u;
            }
            break;

        default:
            break;
        }
    #endif /* ((cyCapsense_CLK_SOURCE_PRS8  == cyCapsense_CSD_SNS_CLK_SOURCE) ||\
               (cyCapsense_CLK_SOURCE_PRS12 == cyCapsense_CSD_SNS_CLK_SOURCE) ||\
               (cyCapsense_CLK_SOURCE_PRSAUTO == cyCapsense_CSD_SNS_CLK_SOURCE)) */
    cyCapsense_SsCSDSetModeSnsClockDivider(newRegValue, snsClkDivider);
}


/*******************************************************************************
* Function Name: cyCapsense_SsCSDCalculateScanDuration
****************************************************************************//**
*
* \brief
*   Calculates Scan Duration which is defined by scan resolution
*
* \details
*   For Fourth-generation HW block: The function calculates the number of conversions and updates
*   SEQ_NORM_CNT register. The number of conversions depends on resolution and
*   snsClk divider.
*   For Third-generation HW block: The function recalculate the resolution using following equation:
*   2^resolution - 1. The calculated value is contained in
*   cyCapsense_counterResolution global variable and used in
*   cyCapsense_SsCSDStartSample() function to trigger the scan process.
*
* \param wdgtIndex
*  ptrWdgt The pointer to the RAM_WD_BASE_STRUCT structure.
*
*******************************************************************************/
void cyCapsense_SsCSDCalculateScanDuration(cyCapsense_RAM_WD_BASE_STRUCT const *ptrWdgt)
{
    #if (cyCapsense_ENABLE == cyCapsense_CSDV2)
        uint32 conversionsNum;
        uint32 snsClkDivider;

    /* Get Number Of Conversions */
    #if (cyCapsense_ENABLE == cyCapsense_CSD_COMMON_SNS_CLK_EN)
        snsClkDivider = cyCapsense_dsRam.snsCsdClk;
    #else
        #if (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN)
            /* Get SnsClck divider for rows or columns */
            if (cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].numCols <= cyCapsense_sensorIndex)
            {
                snsClkDivider = (uint32)(ptrWdgt->rowSnsClk);
            }
            else
            {
                snsClkDivider = (uint32)(ptrWdgt->snsClk);
            }
        #else
            snsClkDivider = (uint32)(ptrWdgt->snsClk);
        #endif /* (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN) */
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_COMMON_SNS_CLK_EN) */

    conversionsNum = cyCapsense_SsCSDGetNumberOfConversions(snsClkDivider, (uint32)ptrWdgt->resolution, (uint32)ptrWdgt->snsClkSource);

        /* Set Number Of Conversions based on scanning resolution */
        CY_SET_REG32(cyCapsense_SEQ_NORM_CNT_PTR, (conversionsNum & cyCapsense_SEQ_NORM_CNT_CONV_CNT_MASK));
    #else
        /* Set up scanning resolution  */
        cyCapsense_counterResolution = (uint32)((0x00000001Lu << ptrWdgt->resolution) - 1u) << cyCapsense_RESOLUTION_OFFSET;
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
}


/*******************************************************************************
* Function Name: cyCapsense_CSDSetupWidget
****************************************************************************//**
*
* \brief
*  Performs hardware and firmware initialization required for scanning sensors
*  in a specific widget using the CSD sensing method. This function requires using
*  the cyCapsense_CSDScan() function to start scanning.
*
* \details
*  This function initializes the specific widget common parameters to perform
*  the CSD scanning. The initialization includes setting up a Modulator and
*  Sense clock frequency and scanning resolution.
*
*  This function does not connect any specific sensors to the scanning hardware,
*  neither does it start a scanning process. The cyCapsense_CSDScan()
*  API must be called after initializing the widget to start scanning.
*
*  This function is called when no scanning is in progress. I.e.
*  cyCapsense_IsBusy() returns a non-busy status.
*
*  This function is called by the cyCapsense_SetupWidget() API if the
*  given widget uses the CSD sensing method.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*
* \param  widgetId
*  Specifies the ID number of the widget to perform hardware and firmware
*  initialization required for scanning sensors in the specific widget.
*  A macro for the widget ID can be found in the cyCapsense Configuration header
*  file defined as cyCapsense_<WidgetName>_WDGT_ID.
*
*******************************************************************************/
void cyCapsense_CSDSetupWidget(uint32 widgetId)
{

    cyCapsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (cyCapsense_RAM_WD_BASE_STRUCT *)
                                                    cyCapsense_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

    /* Save widget Id to have assess to it after scanning  */
    cyCapsense_widgetIndex = (uint8)widgetId;

    cyCapsense_SsSwitchSensingMode(cyCapsense_SENSE_METHOD_CSD_E);

    #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
        /* Reset the frequency scan channel if enabled */
        cyCapsense_scanFreqIndex = cyCapsense_FREQ_CHANNEL_0;
    #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

    /* Disconnect previous electrode if it has been connected */
    cyCapsense_SsCSDElectrodeCheck();

    /* Initialize IO Sns electrode structure pointer to current widget */
    cyCapsense_curSnsIOPtr = (cyCapsense_FLASH_IO_STRUCT const *)
                                    cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2SnsFlash;

    /* Update status register in Data structure */
    cyCapsense_dsRam.status &= ~cyCapsense_STATUS_WDGT0_MASK;
    cyCapsense_dsRam.status |= cyCapsense_widgetIndex;

    /* Set up scanning resolution (Number ofconversion for CSDv2) */
    cyCapsense_SsCSDCalculateScanDuration(ptrWdgt);

    #if ((cyCapsense_DISABLE == cyCapsense_CSD_COMMON_SNS_CLK_EN) ||\
         (cyCapsense_CLK_SOURCE_DIRECT != cyCapsense_CSD_SNS_CLK_SOURCE))
        cyCapsense_SsCSDConfigClock();
    #endif /* ((cyCapsense_DISABLE == cyCapsense_CSD_COMMON_SNS_CLK_EN) ||\
               (cyCapsense_CLK_SOURCE_DIRECT != cyCapsense_CSD_SNS_CLK_SOURCE)) */
}


/*******************************************************************************
* Function Name: cyCapsense_CSDSetupWidgetExt
****************************************************************************//**
*
* \brief
*  Performs extended initialization for the CSD widget and also performs
*  initialization required for a specific sensor in the widget. This function
*  requires using the cyCapsense_CSDScanExt() function to initiate a scan.
*
* \details
*  This function does the same as cyCapsense_CSDSetupWidget() and also
*  does the following tasks:
*    1. Connects the first sensor of the widget.
*    2. Configures the IDAC value.
*    3. Initializes an interrupt callback function to initialize a scan of the
*  next sensors in a widget.
*
*  Once this function is called to initialize a widget and a sensor, the
*  cyCapsense_CSDScanExt() function is called to scan the sensor.
*
*  This function is called when no scanning is in progress. I.e.
*  cyCapsense_IsBusy() returns a non-busy status.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*
* \param widgetId
*  Specifies the ID number of the widget to perform hardware and firmware
*  initialization required for scanning the specific sensor in the specific
*  widget.
*  A macro for the widget ID can be found in the cyCapsense Configuration header
*  file defined as cyCapsense_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specifies the ID number of the sensor within the widget to perform hardware
*  and firmware initialization required for scanning a specific sensor in a
*  specific widget.
*  A macro for the sensor ID within a specified widget can be found in the
*  cyCapsense Configuration header file defined as
*  cyCapsense_<WidgetName>_SNS<SensorNumber>_ID
*
*******************************************************************************/
void cyCapsense_CSDSetupWidgetExt(uint32 widgetId, uint32 sensorId)
{
    cyCapsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (cyCapsense_RAM_WD_BASE_STRUCT *)
                                                    cyCapsense_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

    /* Save widget and sensor Ids to have access to it after scanning  */
    cyCapsense_sensorIndex = (uint8)sensorId;

    /* Update global pointer to cyCapsense_RAM_SNS_STRUCT to current sensor  */
    cyCapsense_curRamSnsPtr = (cyCapsense_RAM_SNS_STRUCT *)
                                              cyCapsense_dsFlash.wdgtArray[widgetId].ptr2SnsRam
                                              + cyCapsense_sensorIndex;

    cyCapsense_CSDSetupWidget(widgetId);

     /* Setup Idac Value */
    cyCapsense_SsCSDSetUpIdacs(ptrWdgt);

    #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
        /* initialize access pointers for current pointer to widget configuration in Flash */
        cyCapsense_curFlashWdgtPtr = &cyCapsense_dsFlash.wdgtArray[widgetId];
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)  */

    #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
        cyCapsense_SsCSDConnectSensorExt(widgetId, sensorId);
    #else
        /* Enable sensor */
        cyCapsense_curSnsIOPtr += cyCapsense_sensorIndex;
        cyCapsense_CSDConnectSns(cyCapsense_curSnsIOPtr);
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)  */

    #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
        /* Save sns pointer */
        cyCapsense_curFlashSnsPtr = (cyCapsense_FLASH_SNS_STRUCT const *)
                                           cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2SnsFlash +
                                           cyCapsense_sensorIndex;
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN) */

    cyCapsense_eleCsdDisconnectFlag = cyCapsense_DISCONNECT_IO_FLAG;

    /* Setup ISR handler to single-sensor scan function */
    cyCapsense_ISR_StartEx(&cyCapsense_CSDPostSingleScan);
}

/*******************************************************************************
* Function Name: cyCapsense_SsCSDStartSample
****************************************************************************//**
*
* \brief
*   Starts the CSD conversion.
*
* \details
*   This function assumes that the CSD block is already set up using
*   the cyCapsense_CSDSetupWidget API and the sensor port-pin is connected to the CSD
*   block using cyCapsense_CSDConnectSns.
*   For Third-generation HW block the function performs the following tasks:
*   1. Disconnects the Vref buffer from AMUX;
*   2. Precharges Cmod;
*   3. Makes the PreSettling delay to have a stable Vref voltage;
*   4. Sets the resolution to the Counter register to start scanning.
*
*******************************************************************************/
void cyCapsense_SsCSDStartSample(void)
{
    #if (cyCapsense_ENABLE != cyCapsense_CSDV2)
        uint8 interruptState;
    #endif

    #ifdef cyCapsense_START_SAMPLE_CALLBACK
        cyCapsense_StartSampleCallback(cyCapsense_widgetIndex, cyCapsense_sensorIndex);
    #endif /* cyCapsense_START_SAMPLE_CALLBACK */

    #if (cyCapsense_ENABLE == cyCapsense_CSDV2)
        /* Fourth-generation HW block section */

        /* Disable CSD interrupt to prevent it during coarse initialization */
        CyIntDisable(cyCapsense_ISR_NUMBER);

        /* Enable power to sub-blocks */
        CY_SET_REG32(cyCapsense_HSCMP_PTR, cyCapsense_HSCMP_INIT_MASK);

        #if (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN)
            CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd |
                                                      cyCapsense_CONFIG_SENSE_EN_MASK |
                                                      cyCapsense_CONFIG_ENABLE_MASK);
            #if(cyCapsense_CSD_ANALOG_STARTUP_DELAY_US > 0uL)
                CyDelayUs(cyCapsense_CSD_ANALOG_STARTUP_DELAY_US);
            #endif /* (cyCapsense_CSD_ANALOG_STARTUP_DELAY_US > 0uL) */
        #endif /* (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN) */

        /* Precharging Cmod and Csh */
        cyCapsense_SsCSDCmodPrecharge();

        /* Trigger Scan */
        cyCapsense_SsCSDTriggerScan();

    #else
        /* Third-generation HW block section */
        interruptState = CyEnterCriticalSection();

        /* Enable CSD block. Disconnect Vref Buffer from AMUX */
        #if ((cyCapsense_CSH_PRECHARGE_IO_BUF == cyCapsense_CSD_CSH_PRECHARGE_SRC) &&\
             (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN))
            CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CMOD_PRECHARGE_CONFIG_CSD_EN);
        #else
            CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CTANK_PRECHARGE_CONFIG_CSD_EN);
        #endif /* ((cyCapsense_CSH_PRECHARGE_IO_BUF == cyCapsense_CSD_CSH_PRECHARGE_SRC) &&\
                   (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN)) */

        /* Restart the clocks. Scan one cycle to reset the flip-flop for Direct clock mode */
        cyCapsense_SsCSDClockRestart();

        /* Precharging Cmod to Vref */
        cyCapsense_SsCSDCmodPrecharge();

        #if (cyCapsense_CLK_SOURCE_DIRECT != cyCapsense_CSD_SNS_CLK_SOURCE)
            /* Set PreSettling delay to skip IDAC glitch before scanning */
            CyDelayCycles(cyCapsense_GLITCH_ELIMINATION_CYCLES);
        #endif /* (cyCapsense_CSD_SNS_CLK_SOURCE != cyCapsense_CLK_SOURCE_DIRECT) */

        /* Trigger Scan */
        cyCapsense_SsCSDTriggerScan();

        CyExitCriticalSection(interruptState);
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
}


/*******************************************************************************
* Function Name: cyCapsense_CSDScanExt
****************************************************************************//**
*
* \brief
*  Starts the CSD conversion on the preconfigured sensor. This function requires
*  using the cyCapsense_CSDSetupWidgetExt() function to set up the a
*  widget.
*
* \details
*  This function performs single scanning of one sensor in the widget configured
*  by the cyCapsense_CSDSetupWidgetExt() function. It does the following
*  tasks:
*    1. Sets the busy flag in the cyCapsense_dsRam structure.
*    2. Performs the clock-phase alignment of the sense and modulator clocks.
*    3. Performs the Cmod pre-charging.
*    4. Starts single scanning.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*  This function is called when no scanning is in progress. I.e.
*  cyCapsense_IsBusy() returns a non-busy status.
*
*  The sensor must be preconfigured by using the
*  cyCapsense_CSDSetupWidgetExt() API prior to calling this function.
*  The sensor remains ready for a next scan if a previous scan was triggered
*  by using the cyCapsense_CSDScanExt() function. In this case, calling
*  cyCapsense_CSDSetupWidgetExt() is not required every time before the
*  cyCapsense_CSDScanExt() function. If a previous scan was triggered in
*  any other way - cyCapsense_Scan(), cyCapsense_ScanAllWidgets() or
*  cyCapsense_RunTuner() - (see the cyCapsense_RunTuner() function
*  description for more details), the sensor must be preconfigured again by
*  using the cyCapsense_CSDSetupWidgetExt() API prior to calling the
*  cyCapsense_CSDScanExt() function.
*
*  If disconnection of the sensors is required after calling
*  cyCapsense_CSDScanExt(), the cyCapsense_CSDDisconnectSns()
*  function can be used.
*
*******************************************************************************/
void cyCapsense_CSDScanExt(void)
{
    /* Set Start of sensor scan flag */
    cyCapsense_dsRam.status |= (cyCapsense_SW_STS_BUSY | cyCapsense_WDGT_SW_STS_BUSY);

    #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
        /* Reset the frequency scan channel if enabled */
        cyCapsense_scanFreqIndex = cyCapsense_FREQ_CHANNEL_0;
    #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

    #if (cyCapsense_ENABLE != cyCapsense_BLOCK_OFF_AFTER_SCAN_EN) &&\
        (cyCapsense_ENABLE == cyCapsense_CSDV2)
        #if(cyCapsense_CSD_ANALOG_STARTUP_DELAY_US > 0uL)
            CyDelayUs(cyCapsense_CSD_ANALOG_STARTUP_DELAY_US);
        #endif /* (cyCapsense_CSD_ANALOG_STARTUP_DELAY_US > 0uL) */
    #endif /* (cyCapsense_ENABLE != cyCapsense_BLOCK_OFF_AFTER_SCAN_EN) &&\
              (cyCapsense_ENABLE == cyCapsense_CSDV2)*/

    cyCapsense_SsCSDStartSample();
}


/*******************************************************************************
* Function Name: cyCapsense_CSDScan
****************************************************************************//**
*
* \brief
*  This function initiates a scan for the sensors of the widget initialized by the
*  cyCapsense_CSDSetupWidget() function.
*
* \details
*  This function performs scanning of all the sensors in the widget configured by
*  the cyCapsense_CSDSetupWidget() function. It does the following tasks:
*    1. Connects the first sensor of the widget.
*    2. Configures the IDAC value.
*    3. Initializes the interrupt callback function to initialize a scan of
*       the next sensors in a widget.
*    4. Starts scanning for the first sensor in the widget.
*
*  This function is called by the cyCapsense_Scan() API if the given
*  widget uses the CSD sensing method.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*
*  This function is called when no scanning is in progress. I.e.
*  cyCapsense_IsBusy() returns a non-busy status. The widget must be
*  preconfigured by the cyCapsense_CSDSetupWidget() function if any other
*  widget was previously scanned or any other type of the scan functions was used.
*
*******************************************************************************/
void cyCapsense_CSDScan(void)
{
    cyCapsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (cyCapsense_RAM_WD_BASE_STRUCT *)
                                                    cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2WdgtRam;

     /*
      * Update cyCapsense_sensorIndex with the first sensor in
      * widget to use it in ISR handler to configure the next sensor
      */
    cyCapsense_sensorIndex = 0u;

    /* Update global pointer to cyCapsense_RAM_SNS_STRUCT to current sensor  */
    cyCapsense_curRamSnsPtr = (cyCapsense_RAM_SNS_STRUCT *)
                                              cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2SnsRam
                                              + cyCapsense_sensorIndex;

    #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
        /* Reset the frequency scan channel if enabled */
        cyCapsense_scanFreqIndex = cyCapsense_FREQ_CHANNEL_0;
    #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

    /* Setup Idac Value */
   cyCapsense_SsCSDSetUpIdacs(ptrWdgt);

    #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
        /* Check ganged sns flag  */
        if (cyCapsense_GANGED_SNS_MASK == (cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].staticConfig &
            cyCapsense_GANGED_SNS_MASK))
        {
            /* Setup ISR handler to multiple-sensor scan function with ganged sensors */
            cyCapsense_ISR_StartEx(&cyCapsense_CSDPostMultiScanGanged);
        }
        else
        {
            /* Set up ISR handler to multiple-sensor scan function without ganged sensors */
            cyCapsense_ISR_StartEx(&cyCapsense_CSDPostMultiScan);
        }

        cyCapsense_SsCSDConnectSensorExt((uint32)cyCapsense_widgetIndex, (uint32)cyCapsense_sensorIndex);
    #else
        /* initialize ptr to sensor IO structure to appropriate address */
        cyCapsense_curSnsIOPtr = (cyCapsense_FLASH_IO_STRUCT const *)
                                        cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2SnsFlash
                                        + cyCapsense_sensorIndex;

        /* Enable sensor */
        cyCapsense_CSDConnectSns(cyCapsense_curSnsIOPtr);

        /* Set-up ISR handler to multiple-sensor scan function without ganged sensors */
        cyCapsense_ISR_StartEx(&cyCapsense_CSDPostMultiScan);
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)  */

    /* Start scanning */
    cyCapsense_CSDScanExt();
}


/*******************************************************************************
* Function Name: cyCapsense_SsCSDConnectSensorExt
****************************************************************************//**
*
* \brief
*  Connects a ganged sensor port-pin to the sensing HW block via the AMUX bus.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and
*   masks from the FLASH_IO_STRUCT object. Basing on this data, it updates the HSIOM and
*   PC registers.
*
* \param widgetId
*  Specifies ID of the widget.
*
* \param sensorId
*  Specifies ID of the sensor in the widget.
*
*******************************************************************************/
void cyCapsense_SsCSDConnectSensorExt(uint32 widgetId, uint32 sensorId)
{
    #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
        uint32 tempVal;
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN) */

    /* initialize ptr to sensor IO structure to appropriate address */
    cyCapsense_curSnsIOPtr = (cyCapsense_FLASH_IO_STRUCT const *)
                                                      cyCapsense_dsFlash.wdgtArray[widgetId].ptr2SnsFlash
                                                      + sensorId;

    #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
        /* Check ganged sns flag  */
        if (cyCapsense_GANGED_SNS_MASK ==
           (cyCapsense_dsFlash.wdgtArray[widgetId].staticConfig &
            cyCapsense_GANGED_SNS_MASK))
        {
            /* Get sns pointer */
            cyCapsense_curFlashSnsPtr = (cyCapsense_FLASH_SNS_STRUCT const *)
                                               cyCapsense_dsFlash.wdgtArray[widgetId].ptr2SnsFlash +
                                               sensorId;

            /* Get number of ganged pins */
            tempVal = cyCapsense_curFlashSnsPtr->numPins;

            /* Get IO pointer  */
            cyCapsense_curSnsIOPtr = &cyCapsense_ioList[cyCapsense_curFlashSnsPtr->firstPinId];

            /* Connect all ganged sensors  */
            do
            {
                cyCapsense_CSDConnectSns(cyCapsense_curSnsIOPtr);
                cyCapsense_curSnsIOPtr++;
                tempVal--;
            } while (0u != tempVal);
        }
        else
        {
            /* Connect sensor */
            cyCapsense_CSDConnectSns(cyCapsense_curSnsIOPtr);
        }
    #else
        /* Connect sensor */
        cyCapsense_CSDConnectSns(cyCapsense_curSnsIOPtr);
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN) */
}


/*******************************************************************************
* Function Name: cyCapsense_SsCSDDisconnectSnsExt
****************************************************************************//**
*
* \brief
*  Disconnects a ganged sensor port-pin from the sensing HW block and AMUX bus.
*  Sets the default state of the un-scanned sensor.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and
*   masks from the FLASH_IO_STRUCT object. Basing on this data and Inactive sensor
*   connection parameter, it updates the HSIOM, PC and DR registers.
*   The HSIOM register is updated only when the Inactive sensor connection parameter
*   is set to Shield.
*
* \param widgetId
*  Specifies ID of the widget.
*
* \param sensorId
*  Specifies ID of the sensor in the widget.
*
*******************************************************************************/
void cyCapsense_SsCSDDisconnectSnsExt(uint32 widgetId, uint32 sensorId)
{
    #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
        uint32 tempVal;
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN) */

    /* initialize ptr to sensor IO structure to appropriate address        */
    cyCapsense_curSnsIOPtr = (cyCapsense_FLASH_IO_STRUCT const *)
                                                      cyCapsense_dsFlash.wdgtArray[widgetId].ptr2SnsFlash
                                                      + sensorId;

    #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
        /* Check ganged sns flag  */
        if ((cyCapsense_dsFlash.wdgtArray[widgetId].staticConfig &
            cyCapsense_GANGED_SNS_MASK) == cyCapsense_GANGED_SNS_MASK)
        {
            /* Get sns pointer */
            cyCapsense_curFlashSnsPtr = (cyCapsense_FLASH_SNS_STRUCT const *)
                                               cyCapsense_dsFlash.wdgtArray[widgetId].ptr2SnsFlash +
                                               sensorId;

            /* Get number of ganged pins */
            tempVal = cyCapsense_curFlashSnsPtr->numPins;

            /* Get IO pointer  */
            cyCapsense_curSnsIOPtr = &cyCapsense_ioList[cyCapsense_curFlashSnsPtr->firstPinId];

            /* Disconnect all ganged sensors */
            do
            {
                cyCapsense_CSDDisconnectSns(cyCapsense_curSnsIOPtr);
                cyCapsense_curSnsIOPtr++;
                tempVal--;
            } while (0u != tempVal);
        }
        else
        {
            /* Disconnect ganged sensor */
            cyCapsense_CSDDisconnectSns(cyCapsense_curSnsIOPtr);
        }
    #else
        /* Disconnect ganged sensor */
        cyCapsense_CSDDisconnectSns(cyCapsense_curSnsIOPtr);
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN) */
}


/*******************************************************************************
* Function Name: cyCapsense_CSDConnectSns
****************************************************************************//**
*
* \brief
*  Connects a port pin used by the sensor to the AMUX bus of the sensing HW block.
*
* \details
*  Connects a port pin used by the sensor to the AMUX bus of the sensing HW block
*  while a sensor is being scanned. The function ignores the fact if
*  the sensor is a ganged sensor and connects only a specified pin.
*
*  Scanning should be completed before calling this API.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases. Functions that perform a setup and scan of a sensor/widget,
*  automatically set the required pin states and perform the sensor connection.
*  They do not take into account changes in the design made by the
*  cyCapsense_CSDConnectSns() function.
*
* \param  snsAddrPtr
*  Specifies the pointer to the FLASH_IO_STRUCT object belonging to a sensor
*  which to be connected to the sensing HW block.
*
*******************************************************************************/
void cyCapsense_CSDConnectSns(cyCapsense_FLASH_IO_STRUCT const *snsAddrPtr)
{
    uint32 newRegisterValue;
    uint8  interruptState;
    uint32 pinModeShift;
    uint32 pinHSIOMShift;

    /* Get offsets for sensor */
    pinModeShift = (uint32)snsAddrPtr->shift;
    pinHSIOMShift = (uint32)snsAddrPtr->hsiomShift;

    interruptState = CyEnterCriticalSection();

    /* Use temporary variable to update registers without multiple writings to them */
    newRegisterValue = CY_GET_REG32(snsAddrPtr->hsiomPtr);
    newRegisterValue &= ~(cyCapsense_HSIOM_SEL_MASK << pinHSIOMShift);
    newRegisterValue |= (uint32)((uint32)cyCapsense_HSIOM_SEL_CSD_SENSE << pinHSIOMShift);

    /* Update port configuration register (drive mode) for sensor */
    CY_SET_REG32(snsAddrPtr->pcPtr, CY_GET_REG32(snsAddrPtr->pcPtr) & (uint32)~((uint32)cyCapsense_GPIO_PC_MASK << pinModeShift));

    /* Update HSIOM register for sensor */
    CY_SET_REG32(snsAddrPtr->hsiomPtr, newRegisterValue);

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: cyCapsense_CSDDisconnectSns
****************************************************************************//**
*
* \brief
*  Disconnects a sensor port pin from the sensing HW block and the AMUX bus. Sets
*  the default state of the un-scanned sensor.
*
* \details
*  This function works identically to cyCapsense_CSDConnectSns() except
*  it disconnects the specified port-pin used by the sensor.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases. Functions that perform a setup and scan of sensor/widget
*  automatically set the required pin states and perform the sensor connection.
*  They ignore changes in the design made by the
*  cyCapsense_CSDDisconnectSns() function.
*
* \param  snsAddrPtr
*  Specifies the pointer to the FLASH_IO_STRUCT object belonging to a sensor
*  which should be disconnected from the sensing HW block.
*
*******************************************************************************/
void cyCapsense_CSDDisconnectSns(cyCapsense_FLASH_IO_STRUCT const *snsAddrPtr)
{
    uint32 pinHSIOMShift;
    uint32 newRegisterValue;
    uint32 pinModeShift;

    #if ((cyCapsense_DISABLE == cyCapsense_CSD_SHIELD_EN) || \
        (cyCapsense_SNS_CONNECTION_SHIELD != cyCapsense_CSD_INACTIVE_SNS_CONNECTION))
        uint8  interruptState;
    #endif /* ((cyCapsense_DISABLE == cyCapsense_CSD_SHIELD_EN) && \
                (cyCapsense_SNS_CONNECTION_SHIELD != cyCapsense_CSD_INACTIVE_SNS_CONNECTION))) */

    pinHSIOMShift = (uint32)snsAddrPtr->hsiomShift;
    pinModeShift = (uint32)snsAddrPtr->shift;

    #if ((cyCapsense_DISABLE == cyCapsense_CSD_SHIELD_EN) ||  \
        (cyCapsense_SNS_CONNECTION_SHIELD != cyCapsense_CSD_INACTIVE_SNS_CONNECTION))
        /* Update HSIOM register to disconnect sensor */
        CY_SET_REG32(snsAddrPtr->hsiomPtr, CY_GET_REG32(snsAddrPtr->hsiomPtr) & ~(cyCapsense_HSIOM_SEL_MASK << pinHSIOMShift));

        interruptState = CyEnterCriticalSection();

        /* Update port configuration register (drive mode) for sensor */
        newRegisterValue = CY_GET_REG32(snsAddrPtr->pcPtr);
        newRegisterValue &= ~(cyCapsense_GPIO_PC_MASK << pinModeShift);
        newRegisterValue |= cyCapsense_CSD_INACTIVE_SNS_CONNECTION << pinModeShift;
        CY_SET_REG32(snsAddrPtr->pcPtr, newRegisterValue);

        CyExitCriticalSection(interruptState);

        /* Set logic 0 to port data register */
        CY_SET_REG32(snsAddrPtr->drPtr, CY_GET_REG32(snsAddrPtr->drPtr) & (uint32)~(uint32)((uint32)1u << snsAddrPtr->drShift));
    #else
        /* Update port configuration register (drive mode to HiZ Analog) for sensor */
        CY_SET_REG32(snsAddrPtr->pcPtr, CY_GET_REG32(snsAddrPtr->pcPtr) & (uint32)~((uint32)cyCapsense_GPIO_PC_MASK << pinModeShift));

        /* Connect to Shield */
        newRegisterValue = CY_GET_REG32(snsAddrPtr->hsiomPtr) & ~(cyCapsense_HSIOM_SEL_MASK << pinHSIOMShift);
        newRegisterValue |= (cyCapsense_HSIOM_SEL_CSD_SHIELD << pinHSIOMShift);
        CY_SET_REG32(snsAddrPtr->hsiomPtr, newRegisterValue);
    #endif /* ((cyCapsense_DISABLE == cyCapsense_CSD_SHIELD_EN) && \
                (cyCapsense_SNS_CONNECTION_SHIELD != cyCapsense_CSD_INACTIVE_SNS_CONNECTION)) */
}

#if ((cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE) || \
     (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_AUTOCAL_EN))
    #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
        /*******************************************************************************
        * Function Name: cyCapsense_SsCSDSetSingleIdacMode
        ****************************************************************************//**
        *
        * \brief
        *  This function set single IDAC mode.
        *
        * \details
        *   For Third-generation HW block: The function enables Modulator IDAC only in variable mode.
        *   For Fourth-generation HW block: The function enables IDACA LEG1 in CSD mode, IDACA LEG2 in GP mode.
        *
        *******************************************************************************/
        static void cyCapsense_SsCSDSetSingleIdacMode(void)
        {
            uint32 newRegValue;

            #if (cyCapsense_ENABLE == cyCapsense_CSDV2)
                /* Enable IDACA LEG1 in CSD mode, IDACA LEG2 in GP mode */
                newRegValue = CY_GET_REG32(cyCapsense_IDAC_MOD_PTR) &
                              cyCapsense_IDAC_MOD_VAL_MASK;
                newRegValue |= cyCapsense_IDAC_MOD_CALIBRATION_CFG;
                CY_SET_REG32(cyCapsense_IDAC_MOD_PTR, newRegValue);
                #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) && \
                    (cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN)
                    newRegValue = CY_GET_REG32(cyCapsense_IDAC_COMP_PTR) & cyCapsense_IDAC_COMP_VAL_MASK;
                    newRegValue |= cyCapsense_IDAC_COMP_CALIBRATION_CFG;
                    CY_SET_REG32(cyCapsense_IDAC_COMP_PTR, newRegValue);
                #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) && \
                          (cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN */
            #else
                /* Enable Modulator IDAC only in variable mode */
                newRegValue = CY_GET_REG32(cyCapsense_IDAC_PTR) &
                              ~(cyCapsense_IDAC_MOD_MODE_MASK | cyCapsense_IDAC_COMP_MODE_MASK);
                newRegValue |= cyCapsense_IDAC_MOD_MODE_VARIABLE;
                CY_SET_REG32(cyCapsense_IDAC_PTR, newRegValue);
            #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
        }
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */
#endif /* ((cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE) || \
           (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_AUTOCAL_EN)) */

#if ((cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE) || \
     (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_AUTOCAL_EN))
    #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
        /*******************************************************************************
        * Function Name: cyCapsense_SsCSDRestoreIdacMode
        ****************************************************************************//**
        *
        * \brief
        *  This function restores IDAC configuration.
        *
        * \details
        *   The function restores Compensation IDAC if it is enabled.
        *
        *******************************************************************************/
        static void cyCapsense_SsCSDRestoreIdacMode(void)
        {
            /* Restore IDAC configuration */
            #if (cyCapsense_ENABLE == cyCapsense_CSDV2)
                uint32 newRegValue;

                newRegValue = CY_GET_REG32(cyCapsense_SW_REFGEN_SEL_PTR);
                newRegValue |= cyCapsense_DEFAULT_SW_REFGEN_SEL;
                CY_SET_REG32(cyCapsense_SW_REFGEN_SEL_PTR, newRegValue);
                CY_SET_REG32(cyCapsense_IDAC_MOD_PTR, cyCapsense_IDAC_MOD_DEFAULT_CFG);
                #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) && \
                    (cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN)
                CY_SET_REG32(cyCapsense_IDAC_COMP_PTR, cyCapsense_IDAC_COMP_DEFAULT_CFG);
                #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) && \
                          (cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN */
            #else
                #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
                    CY_SET_REG32(cyCapsense_IDAC_PTR, cyCapsense_DEFAULT_CSD_IDAC_CONFIG);
                #else
                    CY_SET_REG32(cyCapsense_IDAC_PTR, CY_GET_REG32(cyCapsense_IDAC_PTR) &
                                                                        ~(cyCapsense_IDAC_MOD_MODE_MASK | cyCapsense_IDAC_MOD_MASK));
                    CY_SET_REG32(cyCapsense_IDAC_PTR, CY_GET_REG32(cyCapsense_IDAC_PTR) | cyCapsense_DEFAULT_CSD_IDAC_CONFIG);
                #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */
            #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
        }
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */

    /*******************************************************************************
    * Function Name: cyCapsense_SsCSDCalibrateCheck
    ****************************************************************************//**
    *
    * \brief
    *  This internal function checks if the calibration is performed successfully.
    *
    * \details
    *   The function verifies calibration error based on maximum raw count level.
    *
    * \param rawLevel The raw data level which should be reached during the
    *   calibration procedure.
    * \param rawData  Calibrated raw counts.
    *
    * \return Returns the status of the operation:
    *   - Zero     - All the sensors in the widget are calibrated successfully.
    *   - Non-Zero - Calibration failed for any sensor in the widget.
    *
    *******************************************************************************/
    static cystatus cyCapsense_SsCSDCalibrateCheck(cyCapsense_RAM_WD_BASE_STRUCT const *ptrWdgt, uint32 rawLevel, uint32 rawData)
    {
        cystatus calibrateStatus;
        uint32 rawCountsError;
        uint32 minRawLevel = 0u;
        uint32 maxRawLevel = (0x00000001Lu << ptrWdgt->resolution) - 1u;

        /* Calculate the error in rawcounts for given resolution (round to floor) */
        rawCountsError = ((maxRawLevel * cyCapsense_IDAC_MOD_MAX_CALIB_ERROR) /
                          cyCapsense_PERCENTAGE_100) + 1u;

        /* Get minimum and maximum range values */
        if ((rawLevel + rawCountsError) <= maxRawLevel)
        {
            maxRawLevel = rawLevel + rawCountsError;
        }
        if (rawLevel >= rawCountsError)
        {
            minRawLevel = rawLevel - rawCountsError;
        }

        /* Check if calibration is in valid range */
        if ((rawData < minRawLevel) || (rawData > maxRawLevel))
        {
            calibrateStatus = CYRET_BAD_DATA;
        }
        else
        {
            calibrateStatus = CYRET_SUCCESS;
        }

        return (calibrateStatus);
    }

    /*******************************************************************************
    * Function Name: cyCapsense_SsCSDCalibrateOneSensor
    ****************************************************************************//**
    *
    * \brief
    *  Computes the Modulator IDAC value for one sensor that provides raw signal at
    *  the specified level.
    *
    * \details
    *   The function performs the following tasks:
    *   1. initializes The Compensation IDAC to zero
    *   2. Enables the calibrated sensor
    *   3. Performs eight iteration steps to get the target = rawLevel
    *      setting and resetting the IDAC value bits beginning from the
    *      MSB bit to an MSB bit.
    *   4. Disables the calibrated sensor
    *   5. Checks if the IDAC is in the correct range
    *   6. Updates the maximum IDAC value in the widget
    *   7. Stores the temporary ModIDAC8 value (in the single-IDAC mode).
    *
    *  The CSD block should be initialized with the cyCapsense_SsCSDInitialize()
    *  API before using this function.
    *
    * \param  rawLevel
    *   The raw data level which should be reached during the calibration procedure.
    * \param  ptrIdac  The pointer to IDAC.
    * \param  iDAC8Max The pointer to the maximum IDAC value in the widget.
    *
    * \return Returns the status of the operation:
    *  - Zero     - All the sensors in the widget are calibrated successfully.
    *  - Non-Zero - Calibration failed for any sensor in the widget.
    *
    *******************************************************************************/
    static cystatus cyCapsense_SsCSDCalibrateOneSensor(uint32 rawLevel,
                                                           uint8 *ptrIdac,
                                                           uint8 *iDAC8Max)
    {
        cystatus calibrateStatus;
        uint32 calMask = ((uint32)cyCapsense_CAL_MIDDLE_BIT << 1uL);
        uint32 watchdogCounter;

        uint16 rawData0 = 0u;
        #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
            uint16 rawData1 = 0u;
            uint16 rawData2 = 0u;
        #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

        /* Declare and initialize ptr to widget and sensor structures to appropriate address */
        cyCapsense_RAM_WD_BASE_STRUCT *ptrWdgt = (cyCapsense_RAM_WD_BASE_STRUCT *)
                                                        cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2WdgtRam;

        ptrIdac[0u] = 0u;
        #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
            ptrIdac[cyCapsense_FREQ_CHANNEL_1] = 0u;
            ptrIdac[cyCapsense_FREQ_CHANNEL_2] = 0u;
        #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

        /* Setup the calibrated sensor of the widget (Set IDAC = calMask and connect the sensor) */
        cyCapsense_CSDSetupWidgetExt((uint32)cyCapsense_widgetIndex, (uint32)cyCapsense_sensorIndex);

        #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
            /* Set single IDAC mode */
            cyCapsense_SsCSDSetSingleIdacMode();
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */

        /*
         * Perform the iteration steps to get target = rawLevel.
         * The number of iteration steps is defined by calMask and depend on IDAC resolution.
         */
        do
        {
            /* Decrease IDAC until rawData reaches rawLevel */
            if (rawData0 < rawLevel)
            {
                /* Reset bit for null channel (decrease IDAC -> will increase rawData) */
                ptrIdac[0u] &= (uint8)(~calMask);
            }
            #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                if (rawData1 < rawLevel)
                {
                    ptrIdac[cyCapsense_FREQ_CHANNEL_1] &= (uint8)(~calMask);
                }
                if (rawData2 < rawLevel)
                {
                    ptrIdac[cyCapsense_FREQ_CHANNEL_2] &= (uint8)(~calMask);
                }
            #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

            /*
            * Shift calMask to set or reset next bit.
            * Perform scan even if callibration mask is equal to zero.
            * It gives raw counts for the last changed IDAC.
            */
            calMask >>= 1u;

            /* Set bit for null channel */
            ptrIdac[0u] |= (uint8)calMask;
            #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                ptrIdac[cyCapsense_FREQ_CHANNEL_1] |= (uint8)calMask;
                ptrIdac[cyCapsense_FREQ_CHANNEL_2] |= (uint8)calMask;
            #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

            /* Update IDAC */
            cyCapsense_SsCSDSetUpIdacs(ptrWdgt);

            /* Scan sensor */
            cyCapsense_CSDScanExt();

            /* Initialize Watchdog Counter with time interval which is enough to charge 100 nF capacitor */
            watchdogCounter = cyCapsense_CSD_CALIBR_WATCHDOG_CYCLES_NUM;
            while (((cyCapsense_dsRam.status & cyCapsense_SW_STS_BUSY) != 0u) &&
                   (0u != watchdogCounter))
            {
                /* Wait until scan complete and decrement Watchdog Counter to prevent unending loop */
                watchdogCounter--;
            }

            /* Read rawData */
            rawData0 = cyCapsense_curRamSnsPtr->raw[0u];
            #if(cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                rawData1 = cyCapsense_curRamSnsPtr->raw[cyCapsense_FREQ_CHANNEL_1];
                rawData2 = cyCapsense_curRamSnsPtr->raw[cyCapsense_FREQ_CHANNEL_2];
            #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */
        }
        while (calMask > 0u);

        #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
            cyCapsense_SsCSDDisconnectSnsExt((uint32)cyCapsense_widgetIndex, (uint32)cyCapsense_sensorIndex);
        #else
            /* initialize pointer to sensor IO structure */
            cyCapsense_curSnsIOPtr = (cyCapsense_FLASH_IO_STRUCT const *)
                                            cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2SnsFlash
                                            + cyCapsense_sensorIndex;

            /* Disable sensor */
            cyCapsense_CSDDisconnectSns(cyCapsense_curSnsIOPtr);
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN) */

        /* Set flag about disconnecting the electrode */
        cyCapsense_eleCsdDisconnectFlag = 0u;

        #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
            /* Restore IDAC configuration to default state */
            cyCapsense_SsCSDRestoreIdacMode();
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */

        /* Check if IDAC is in correct range */
        calibrateStatus = cyCapsense_SsCSDCalibrateCheck(ptrWdgt, rawLevel, (uint32)rawData0);
        #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
            calibrateStatus |= cyCapsense_SsCSDCalibrateCheck(ptrWdgt, rawLevel, (uint32)rawData1);
            calibrateStatus |= cyCapsense_SsCSDCalibrateCheck(ptrWdgt, rawLevel, (uint32)rawData2);
        #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

        /*
         * Update maximum IDAC value in widget. iDAC8Max variable will contain
         * maximum IDAC value after all the sensors in a widget have been scanned.
         */
        if (*iDAC8Max < ptrIdac[0u])
        {
            *iDAC8Max = ptrIdac[0u];
            #if (cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE)
                /* Stores IDAC and raw count that corresponds to a sensor with maximum Cp within a widget */
                cyCapsense_calibratedIdac = *iDAC8Max;
                cyCapsense_calibratedRawcount = rawData0;
            #endif /* (cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE) */
        }
        #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
            if (iDAC8Max[cyCapsense_FREQ_CHANNEL_1] < ptrIdac[cyCapsense_FREQ_CHANNEL_1])
            {
                iDAC8Max[cyCapsense_FREQ_CHANNEL_1] = ptrIdac[cyCapsense_FREQ_CHANNEL_1];
            }
            if (iDAC8Max[cyCapsense_FREQ_CHANNEL_2] < ptrIdac[cyCapsense_FREQ_CHANNEL_2])
            {
                iDAC8Max[cyCapsense_FREQ_CHANNEL_2] = ptrIdac[cyCapsense_FREQ_CHANNEL_2];
            }
        #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

        #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
            /*
             * Store temporary ModIDAC8 value (in single-IDAC mode) in idacComp variable.
             * We need this value to calculate idacMod value the in the dual-IDAC mode.
             */
            cyCapsense_curRamSnsPtr->idacComp[0u] = ptrIdac[0u];
            #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_1] = ptrIdac[cyCapsense_FREQ_CHANNEL_1];
                cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_2] = ptrIdac[cyCapsense_FREQ_CHANNEL_2];
            #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */

        return (calibrateStatus);
    }


    /*******************************************************************************
    * Function Name: cyCapsense_CSDCalibrateWidget
    ****************************************************************************//**
    *
    * \brief
    *  Executes the IDAC calibration for all the sensors in the widget specified in
    *  the input.
    *
    * \details
    *  Performs a successive approximation search algorithm to find appropriate
    *  IDAC values for sensors in the specified widget that provides the raw
    *  count to the level specified by the target parameter.
    *
    *  Calibration is always performed in the single IDAC mode and if the dual
    *  IDAC mode (Enable compensation IDAC is enabled) is configured, the IDAC
    *  values are re-calculated to match the raw count target. If a widget
    *  consists of two or more elements (buttons, slider segments, etc.), then
    *  calibration is performed by the element with the highest sensor
    *  capacitance.
    *
    *  Calibration fails if the achieved raw count is outside of the +/-10%
    *  range of the target.
    *
    *  This function is available when the CSD Enable IDAC auto-calibration
    *  parameter is enabled or the  SmartSense auto-tuning mode is configured.
    *
    * \param widgetId
    *  Specifies the ID number of the CSD widget to calibrate its raw count.
    *  A macro for the widget ID can be found in the
    *  cyCapsense Configuration header file defined as
    *  cyCapsense_<WidgetName>_WDGT_ID.
    *
    * \param target
    *  Specifies the calibration target in percentages of the maximum raw count.
    *
    * \return
    *  Returns the status of the specified widget calibration:
    *    - CYRET_SUCCESS - The operation is successfully completed.
    *    - CYRET_BAD_PARAM - The input parameter is invalid.
    *    - CYRET_BAD_DATA - The calibration failed and the Component may not operate as expected.
    *
    *******************************************************************************/
    cystatus cyCapsense_CSDCalibrateWidget(uint32 widgetId, uint32 target)
    {
        uint32 rawLevel;
        cystatus calibrateStatus = CYRET_SUCCESS;

        #if (cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE)
            #if (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN)
                uint8 maxIdac = 1u;
                uint16 maxRaw = 1u;
            #endif /*(cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN) */
        #endif /* (cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE) */

        /* Declare and initialize ptr to widget and sensor structures to appropriate address */
        cyCapsense_RAM_WD_BASE_STRUCT *ptrWdgt = (cyCapsense_RAM_WD_BASE_STRUCT *)
                                              cyCapsense_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

        #if (1u == cyCapsense_NUM_SCAN_FREQS)
            uint8 iDAC8Max[cyCapsense_NUM_SCAN_FREQS] = {1u};
        #else
            uint8 iDAC8Max[cyCapsense_NUM_SCAN_FREQS] = {1u, 1u, 1u};
        #endif /* (1u == cyCapsense_NUM_SCAN_FREQS) */

        uint8 *ptrIdac;

        /* Calibrate maximum level for given resolution */
        rawLevel = (0x00000001Lu << ptrWdgt->resolution) - 1u;

        /* Calculate percentage of maximum value */
        rawLevel = (rawLevel * target) / cyCapsense_PERCENTAGE_100;

        /* Update cyCapsense_widgetIndex */
        cyCapsense_widgetIndex = (uint8)widgetId;

        /* Setup ISR handler to single-sensor scan function */
        cyCapsense_ISR_StartEx(&cyCapsense_CSDPostSingleScan);

        /* Init pointer to Modulator IDAC */
        ptrIdac = &ptrWdgt->idacMod[0u];

        #if (cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE)
            cyCapsense_calibratedIdac = 1u;
            cyCapsense_calibratedRawcount = 1u;
        #endif /* (cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE) */

        /* Go through all the sensors (or columns of touchpad) of widget to calibrate them */
        for (cyCapsense_sensorIndex = 0u;
             cyCapsense_sensorIndex < cyCapsense_dsFlash.wdgtArray[widgetId].numCols;
             cyCapsense_sensorIndex++)
        {
            /* Calibrate current sensor in widget */
            calibrateStatus |= cyCapsense_SsCSDCalibrateOneSensor(rawLevel, ptrIdac, iDAC8Max);
        }

        /* Normalize idacMod and idacComp values */
        #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
            /* Calculate Modulator value: idacMod = (iDAC8Max + 1)/2 */
            ptrIdac[0u] = (iDAC8Max[0u] + 1u) >> 1u;
            #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                ptrIdac[cyCapsense_FREQ_CHANNEL_1] =  (iDAC8Max[cyCapsense_FREQ_CHANNEL_1] + 1u) >> 1u;
                ptrIdac[cyCapsense_FREQ_CHANNEL_2] = (iDAC8Max[cyCapsense_FREQ_CHANNEL_2] + 1u) >> 1u;
            #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

            /* Go through all columns of touchpad (or all the sensors in button) to normalize them */
            for (cyCapsense_sensorIndex = 0u;
                 cyCapsense_sensorIndex < cyCapsense_dsFlash.wdgtArray[widgetId].numCols;
                 cyCapsense_sensorIndex++)
            {
                cyCapsense_curRamSnsPtr = (cyCapsense_RAM_SNS_STRUCT *)
                         cyCapsense_dsFlash.wdgtArray[widgetId].ptr2SnsRam + cyCapsense_sensorIndex;
                /* Calculate Compensation IDAC value: idacComp(i) = (iDAC8(i) - idacMod) * Target */
                if (cyCapsense_curRamSnsPtr->idacComp[0u] >= ptrIdac[0u])
                {
                    cyCapsense_curRamSnsPtr->idacComp[0u] -= ptrIdac[0u];
                    #if ((cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN) ||\
                         (cyCapsense_DISABLE == cyCapsense_CSDV2))
                        cyCapsense_curRamSnsPtr->idacComp[0u] =
                            (uint8)((((target * cyCapsense_curRamSnsPtr->idacComp[0u]) + cyCapsense_PERCENTAGE_100) - 1u) /
                            cyCapsense_PERCENTAGE_100);
                    #endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN) ||\
                               (cyCapsense_DISABLE == cyCapsense_CSDV2)) */
                }
                else
                {
                    cyCapsense_curRamSnsPtr->idacComp[0u] = 0u;
                }
                #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                    /* Do same for first frequency channel */
                    if (cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_1] >= ptrIdac[cyCapsense_FREQ_CHANNEL_1])
                    {
                        cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_1] -= ptrIdac[cyCapsense_FREQ_CHANNEL_1];
                        #if ((cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN) ||\
                             (cyCapsense_DISABLE == cyCapsense_CSDV2))
                            cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_1] =
                                (uint8)((((target * cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_1]) +
                                cyCapsense_PERCENTAGE_100) - 1u) / cyCapsense_PERCENTAGE_100);
                        #endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                   (cyCapsense_DISABLE == cyCapsense_CSDV2)) */
                    }
                    else
                    {
                       cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_1] = 0u;
                    }
                    /* Do same for second frequency channel */
                    if (cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_2] >= ptrIdac[cyCapsense_FREQ_CHANNEL_2])
                    {
                        cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_2] -= ptrIdac[cyCapsense_FREQ_CHANNEL_2];
                        #if ((cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN) ||\
                             (cyCapsense_DISABLE == cyCapsense_CSDV2))
                            cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_2] =
                                (uint8)((((target * cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_2]) +
                                cyCapsense_PERCENTAGE_100) - 1u) / cyCapsense_PERCENTAGE_100);
                        #endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                   (cyCapsense_DISABLE == cyCapsense_CSDV2)) */
                    }
                    else
                    {
                        cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_2] = 0u;
                    }
                #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */
            }
        #else
            /* Normalize widget for single-IDAC mode*/
            ptrIdac[0u] = iDAC8Max[0u];
            #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                ptrIdac[cyCapsense_FREQ_CHANNEL_1] = iDAC8Max[cyCapsense_FREQ_CHANNEL_1];
                ptrIdac[cyCapsense_FREQ_CHANNEL_2] = iDAC8Max[cyCapsense_FREQ_CHANNEL_2];
            #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */

        #if (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN)
            if ((cyCapsense_WD_TOUCHPAD_E == (cyCapsense_WD_TYPE_ENUM)cyCapsense_dsFlash.wdgtArray[widgetId].wdgtType) ||
                (cyCapsense_WD_MATRIX_BUTTON_E == (cyCapsense_WD_TYPE_ENUM)cyCapsense_dsFlash.wdgtArray[widgetId].wdgtType))
            {
                /* Init pointer to Modulator IDAC for columns */
                ptrIdac = &ptrWdgt->rowIdacMod[0u];

                /* Reset the maximum value for columns */
                iDAC8Max[0u] = 1u;
                #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                    iDAC8Max[cyCapsense_FREQ_CHANNEL_1] = 1u;
                    iDAC8Max[cyCapsense_FREQ_CHANNEL_2] = 1u;
                #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

                #if (cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE)
                    maxIdac = cyCapsense_calibratedIdac;
                    maxRaw = cyCapsense_calibratedRawcount;
                    cyCapsense_calibratedIdac = 1u;
                    cyCapsense_calibratedRawcount = 1u;
                #endif /* (cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE) */

                /* Go through all columns of touchpad to calibrate them */
                for (cyCapsense_sensorIndex = cyCapsense_dsFlash.wdgtArray[widgetId].numCols;
                     cyCapsense_sensorIndex < (uint8)cyCapsense_dsFlash.wdgtArray[widgetId].totalNumSns;
                     cyCapsense_sensorIndex++)
                {
                    /* Calibrate current sensor in widget */
                    calibrateStatus |= cyCapsense_SsCSDCalibrateOneSensor(rawLevel, ptrIdac, iDAC8Max);
                }

                #if (cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE)
                    cyCapsense_calibratedIdacRow = cyCapsense_calibratedIdac;
                    cyCapsense_calibratedRawcountRow = cyCapsense_calibratedRawcount;
                    cyCapsense_calibratedIdac = maxIdac;
                    cyCapsense_calibratedRawcount = maxRaw;
                #endif /* (cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE) */

                /* Normalize idacMod and idacComp values */
                #if (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN)
                    /* Calculate Modulator value: idacMod = (iDAC8Max + 1)/2 */
                    ptrIdac[0u] = (iDAC8Max[0u] + 1u) >> 1u;
                    #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                        ptrIdac[cyCapsense_FREQ_CHANNEL_1] =  (iDAC8Max[cyCapsense_FREQ_CHANNEL_1] + 1u) >> 1u;
                        ptrIdac[cyCapsense_FREQ_CHANNEL_2] = (iDAC8Max[cyCapsense_FREQ_CHANNEL_2] + 1u) >> 1u;
                    #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

                    /* Go through all columns of touchpad to normalize them */
                    for (cyCapsense_sensorIndex = cyCapsense_dsFlash.wdgtArray[widgetId].numCols;
                         cyCapsense_sensorIndex < (uint8)cyCapsense_dsFlash.wdgtArray[widgetId].totalNumSns;
                         cyCapsense_sensorIndex++)
                    {
                        cyCapsense_curRamSnsPtr = (cyCapsense_RAM_SNS_STRUCT *)
                                 cyCapsense_dsFlash.wdgtArray[widgetId].ptr2SnsRam + cyCapsense_sensorIndex;

                        /* Calculate Compensation IDAC value: idacComp(i) = (iDAC8(i) - idacMod) * Target */
                        if (cyCapsense_curRamSnsPtr->idacComp[0u] >= ptrIdac[0u])
                        {
                            cyCapsense_curRamSnsPtr->idacComp[0u] -= ptrIdac[0u];
                            #if ((cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                 (cyCapsense_DISABLE == cyCapsense_CSDV2))
                                cyCapsense_curRamSnsPtr->idacComp[0u] =
                                    (uint8)((((target * cyCapsense_curRamSnsPtr->idacComp[0u]) +
                                        cyCapsense_PERCENTAGE_100) - 1u) / cyCapsense_PERCENTAGE_100);
                            #endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                       (cyCapsense_DISABLE == cyCapsense_CSDV2)) */
                        }
                        #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                            /* Do same for first frequency channel */
                            if (cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_1] >= ptrIdac[cyCapsense_FREQ_CHANNEL_1])
                            {
                                cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_1] -= ptrIdac[cyCapsense_FREQ_CHANNEL_1];
                                #if ((cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                     (cyCapsense_DISABLE == cyCapsense_CSDV2))
                                    cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_1] =
                                        (uint8)((((target * cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_1]) +
                                        cyCapsense_PERCENTAGE_100) - 1u) / cyCapsense_PERCENTAGE_100);
                                #endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                           (cyCapsense_DISABLE == cyCapsense_CSDV2)) */
                            }
                            /* Do same for second frequency channel */
                            if (cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_2] >= ptrIdac[cyCapsense_FREQ_CHANNEL_2])
                            {
                                cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_2] -= ptrIdac[cyCapsense_FREQ_CHANNEL_2];
                                #if ((cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                     (cyCapsense_DISABLE == cyCapsense_CSDV2))
                                    cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_2] =
                                        (uint8)((((target * cyCapsense_curRamSnsPtr->idacComp[cyCapsense_FREQ_CHANNEL_2]) +
                                        cyCapsense_PERCENTAGE_100) - 1u) / cyCapsense_PERCENTAGE_100);
                                #endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                           (cyCapsense_DISABLE == cyCapsense_CSDV2)) */
                            }
                        #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */
                    }
                #else
                    /* Normalize widget for single-IDAC mode*/
                    ptrIdac[0u] = iDAC8Max[0u];
                    #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                        ptrIdac[cyCapsense_FREQ_CHANNEL_1] = iDAC8Max[cyCapsense_FREQ_CHANNEL_1];
                        ptrIdac[cyCapsense_FREQ_CHANNEL_2] = iDAC8Max[cyCapsense_FREQ_CHANNEL_2];
                    #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */
                #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) */
            }
        #endif /* (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN) */

        cyCapsense_sensorIndex = 0u;

        return calibrateStatus;
    }
#endif /* ((cyCapsense_CSD_SS_DIS != cyCapsense_CSD_AUTOTUNE)) || \
            (cyCapsense_ENABLE == cyCapsense_CSD_IDAC_AUTOCAL_EN)) */


#if (cyCapsense_DISABLE == cyCapsense_CSDV2)
    /*******************************************************************************
    * Function Name: cyCapsense_SsCSDClockRestart
    ****************************************************************************//**
    *
    * \brief
    *  This function restarts the clocks.
    *
    * \details
    *  The function performs following:
    *  1) Stops, sets dividers and starts ModClk clock;
    *  2) Stops and starts SnsClk clock;
    *  3) Scan one cycle to reset the flip-flop for Direct clock mode.
    *
    *******************************************************************************/
    CY_INLINE static void cyCapsense_SsCSDClockRestart(void)
    {
        /* Stop clocks, set dividers, and start clock to align clock phase */
        cyCapsense_SsSetModClkClockDivider((uint32)cyCapsense_dsRam.modCsdClk);

        #if (cyCapsense_ENABLE == cyCapsense_IS_M0S8PERI_BLOCK)
            /* Stop sense clock clock   */
            CY_SET_REG32(cyCapsense_SNSCLK_CMD_PTR,
                         ((uint32)cyCapsense_SnsClk__DIV_ID <<
                         cyCapsense_SNSCLK_CMD_DIV_SHIFT)|
                         ((uint32)cyCapsense_SNSCLK_CMD_DISABLE_MASK));

            /* Check whether previous sense clock start command has finished. */
            while(0u != (CY_GET_REG32(cyCapsense_SNSCLK_CMD_PTR) & cyCapsense_SNSCLK_CMD_ENABLE_MASK))
            {
                /* Wait until previous sense clock start command has finished. */
            }

            /* Start sense clock aligned to previously started modulator clock. */
            CY_SET_REG32(cyCapsense_SNSCLK_CMD_PTR,
                         (uint32)(((uint32)cyCapsense_SnsClk__DIV_ID << cyCapsense_SNSCLK_CMD_DIV_SHIFT) |
                          ((uint32)cyCapsense_ModClk__PA_DIV_ID << cyCapsense_SNSCLK_CMD_PA_DIV_SHIFT) |
                          cyCapsense_SNSCLK_CMD_ENABLE_MASK));
        #else
            /* Clear bit to disable SnsClk clock. */
            CY_SET_REG32(cyCapsense_SNSCLK_CMD_PTR,
                         CY_GET_REG32(cyCapsense_SNSCLK_CMD_PTR) &
                         (uint32)(~(uint32)cyCapsense_SnsClk__ENABLE_MASK));

            /* Set bit to enable SnsClk clock. */
            CY_SET_REG32(cyCapsense_SNSCLK_CMD_PTR,
                         CY_GET_REG32(cyCapsense_SNSCLK_CMD_PTR) |
                        cyCapsense_SnsClk__ENABLE_MASK);
        #endif /* (cyCapsense_ENABLE == cyCapsense_IS_M0S8PERI_BLOCK) */

        #if (cyCapsense_CLK_SOURCE_DIRECT == cyCapsense_CSD_SNS_CLK_SOURCE)
            /* Scan one cycle to reset the flip-flop for Direct clock mode */
            CyIntDisable(cyCapsense_ISR_NUMBER);
            CY_SET_REG32(cyCapsense_COUNTER_PTR, cyCapsense_ONE_CYCLE);

            while(0u != (CY_GET_REG32(cyCapsense_COUNTER_PTR) & cyCapsense_RESOLUTION_16_BITS))
            {
                /* Wait until scanning is complete */
            }
            CY_SET_REG32(cyCapsense_INTR_PTR, cyCapsense_INTR_SET_MASK);
            CyIntClearPending(cyCapsense_ISR_NUMBER);
        #endif /* (cyCapsense_CLK_SOURCE_DIRECT == cyCapsense_CSD_SNS_CLK_SOURCE) */
    }
#endif /* (cyCapsense_DISABLE == cyCapsense_CSDV2) */


/*******************************************************************************
* Function Name: cyCapsense_SsCSDCmodPrecharge
****************************************************************************//**
*
* \brief
*  This function initializes the Cmod charging to Vref.
*
* \details
*  For Third-generation HW block:
*  The function initializes the Cmod charging to Vref.
*  Then it waits the even when Cmod is completely charged
*  to Vref to have stable raw counts. Software Watchdog Counter is implemented to
*  prevent the project hanging.
*
*  For Fourth-generation HW block:
*  Coarse initialization for CMOD and Cch.
*  The coarse initialization is performed by HSCOMP.
*  The HSCOMP monitors the Cmod voltage via Cmod sense path
*  and charges the Cmod using HCAV switch via CSDBUS-A, AMUXBUS-A
*  and static connection of Cmod to AMUXBUS-A.
*
*******************************************************************************/
CY_INLINE static void cyCapsense_SsCSDCmodPrecharge(void)
{
    #if (cyCapsense_ENABLE == cyCapsense_CSDV2)

        /* Fourth-generation HW block section */

        uint32 watchdogCounter;
        #if((cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) &&\
            (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN))
            uint32 tmpRegValue;
        #endif

        CY_SET_REG32(cyCapsense_CSDCMP_PTR, cyCapsense_CSD_CSDCMP_INIT);
        CY_SET_REG32(cyCapsense_SW_FW_MOD_SEL_PTR,  cyCapsense_CSD_SW_FW_MOD_SEL_INIT);
        CY_SET_REG32(cyCapsense_SW_FW_TANK_SEL_PTR, cyCapsense_CSD_SW_FW_TANK_SEL_INIT);
        CY_SET_REG32(cyCapsense_SW_SHIELD_SEL_PTR,  cyCapsense_CSD_SW_SHIELD_SEL_INIT);
        #if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN)
            /*
             * Connect CMOD to (sense path) to HSCOMP: HMPM or HMPS or HMPT switches depend on Cmod connects to certain pad
             * Connect AMUXBUS-B to HSCMP positive input
             */
            CY_SET_REG32(cyCapsense_SW_HS_P_SEL_PTR, cyCapsense_SW_HS_P_SEL_COARSE);

            #if(0u != cyCapsense_CSD_SHIELD_TANK_EN)
                /* Connect CTANK to AMUXBUS-A */
                tmpRegValue = CY_GET_REG32(cyCapsense_CSH_HSIOM_PTR);
                tmpRegValue &= (uint32)(~(uint32)cyCapsense_CSH_HSIOM_MASK);
                tmpRegValue |= (cyCapsense_HSIOM_SEL_AMUXA << cyCapsense_CSH_HSIOM_SHIFT);
                CY_SET_REG32(cyCapsense_CSH_HSIOM_PTR, tmpRegValue);
            #endif /* (0u != cyCapsense_CSD_SHIELD_TANK_EN) */
        #else
            /* Connect CMOD to (sense path) to HSCOMP: HMPM or HMPS or HMPT switches depend on Cmod connects to certain pad */
            CY_SET_REG32(cyCapsense_SW_HS_P_SEL_PTR, cyCapsense_SW_HS_P_SEL_COARSE);
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) */

        CY_SET_REG32(cyCapsense_SW_RES_PTR, cyCapsense_CSD_SW_RES_INIT);

        /* Clear all interrupt pending requests */
        CY_SET_REG32(cyCapsense_INTR_PTR, cyCapsense_INTR_ALL_MASK);

        CY_SET_REG32(cyCapsense_INTR_MASK_PTR, cyCapsense_CLEAR_MASK);

        /* Start SEQUENCER for coarse initialization for Cmod */
        CY_SET_REG32(cyCapsense_SEQ_START_PTR, cyCapsense_SEQ_START_SEQ_MODE_MASK |
                                                         cyCapsense_SEQ_START_START_MASK);

        /* Init Watchdog Counter to prevent a hang */
        watchdogCounter = cyCapsense_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM;

        /* Wait for INTR.INIT goes high */
        while((0u == (CY_GET_REG32(cyCapsense_INTR_PTR) & cyCapsense_INTR_INIT_MASK)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        if (0u == watchdogCounter)
        {
            /* Set sequencer to idle state if coarse initialization fails */
            CY_SET_REG32(cyCapsense_SEQ_START_PTR, cyCapsense_SEQ_START_ABORT_MASK);
        }

    #else

        uint32 tmpRegValue;
        uint32 newRegValue;
        uint32 watchdogCounter;

        /* Save the current IDAC configuration */
        tmpRegValue = CY_GET_REG32(cyCapsense_IDAC_PTR);

        /* Wait until Cmod discharges below Vref */
        CyDelayCycles(cyCapsense_CMOD_DISCHARGE_CYCLES);

        newRegValue = cyCapsense_CSD_IDAC_PRECHARGE_CONFIG | (tmpRegValue & ~cyCapsense_IDAC_MOD_CFG_MASK);

        /* Set the IDAC configuration for fast Cmod precharge to Vref */
        CY_SET_REG32(cyCapsense_IDAC_PTR, newRegValue);

        #if (cyCapsense_IDAC_SINKING == cyCapsense_CSD_IDAC_CONFIG)
            CY_SET_REG32(cyCapsense_CONFIG_PTR, CY_GET_REG32(cyCapsense_CONFIG_PTR) & ~cyCapsense_CONFIG_POLARITY_MASK);
        #endif /* (cyCapsense_IDAC_SINKING == cyCapsense_CSD_IDAC_CONFIG) */

        /* Init Watchdog Counter to prevent a hang */
        watchdogCounter = cyCapsense_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM;

        /* Wait until Cmod reaches to Vref */
        while((0u == (CY_GET_REG32(cyCapsense_STATUS_PTR) & cyCapsense_STATUS_SAMPLE)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        #if (cyCapsense_IDAC_SINKING == cyCapsense_CSD_IDAC_CONFIG)
            CY_SET_REG32(cyCapsense_CONFIG_PTR, CY_GET_REG32(cyCapsense_CONFIG_PTR) | cyCapsense_CONFIG_POLARITY_MASK);
        #endif /* (cyCapsense_IDAC_SINKING == cyCapsense_CSD_IDAC_CONFIG) */

        /* Restore the current IDAC configuration */
        CY_SET_REG32(cyCapsense_IDAC_PTR, tmpRegValue);

        /* Enable the sense modulator output */
        CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CTANK_PRECHARGE_CONFIG_CSD_EN | cyCapsense_CONFIG_SENSE_EN_MASK);

        CyIntEnable(cyCapsense_ISR_NUMBER);

    #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
}


/*******************************************************************************
* Function Name: cyCapsense_SsCSDTriggerScan
****************************************************************************//**
*
* \brief
*  This function triggers the scanning.
*
* \details
*  For Third-generation HW block:
*  Writes resolution to start the scanning.
*
*  For Fourth-generation HW block:
*  Trigger the fine initialization (scan some dummy cycles) and start sampling.
*  Fine initialization for CMOD and Start scan.
*  For the fine initialization and sampling, Cmod is static connected to AMUXBUS-A
*  and in every conversion (one cycle of SnsClk), the sensor capacitance is charged
*  from Cmod and discharged to ground using the switches in GPIO cell.
*  The CSDCOMP monitors voltage on Cmod using the sense path and charges Cmod back
*  to Vref using IDACs by connecting IDAC to CSDBUS-A and then the AMUXBUS-A.
*
*******************************************************************************/
CY_INLINE static void cyCapsense_SsCSDTriggerScan(void)
{
    #if (cyCapsense_ENABLE == cyCapsense_CSDV2)

        /* Fourth-generation HW block section */

        uint32 watchdogCounter;

        /* Clear previous interrupts */
        CY_SET_REG32(cyCapsense_INTR_PTR, cyCapsense_INTR_ALL_MASK);

        /* Clear pending interrupts  */
        CyIntClearPending(cyCapsense_ISR_NUMBER);

        /* Enable CSD interrupt */
        CyIntEnable(cyCapsense_ISR_NUMBER);


        CY_SET_REG32(cyCapsense_SW_HS_P_SEL_PTR, cyCapsense_CSD_SW_HS_P_SEL_SCAN);

        /* Set scanning configuration for switches */
        CY_SET_REG32(cyCapsense_SW_FW_MOD_SEL_PTR, cyCapsense_CSD_SW_FW_MOD_SEL_SCAN);
        CY_SET_REG32(cyCapsense_SW_FW_TANK_SEL_PTR,cyCapsense_CSD_SW_FW_TANK_SEL_SCAN);

        CY_SET_REG32(cyCapsense_SW_SHIELD_SEL_PTR,  cyCapsense_CSD_SW_SHIELD_SEL_SCAN);

        #if((cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) && (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN))
            /* Connect CTANK to AMUXBUS-B */
            cyCapsense_SsCSDEnableShieldTank();
        #endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) && (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN)) */

        CY_SET_REG32(cyCapsense_SW_RES_PTR, cyCapsense_CSD_SW_RES_SCAN);
        CY_SET_REG32(cyCapsense_CSDCMP_PTR, cyCapsense_CSD_CSDCMP_SCAN);

        #if (cyCapsense_DISABLE == cyCapsense_CSD_SHIELD_EN)
            /* Disable HSCOMP during the sampling phase when shield is disabled */
            CY_SET_REG32(cyCapsense_HSCMP_PTR, 0u);
        #else
            CY_SET_REG32(cyCapsense_HSCMP_PTR, cyCapsense_HSCMP_SCAN_MASK);
        #endif /* (cyCapsense_DISABLE == cyCapsense_CSD_SHIELD_EN) */

        #if (cyCapsense_CLK_SOURCE_DIRECT != cyCapsense_CSD_SNS_CLK_SOURCE)
            /* Force the LFSR to it's initial state (all ones) */
            CY_SET_REG32(cyCapsense_SENSE_PERIOD_PTR, CY_GET_REG32(cyCapsense_SENSE_PERIOD_PTR) |
                                                           cyCapsense_SENSE_PERIOD_LFSR_CLEAR_MASK);
        #endif /* (cyCapsense_CLK_SOURCE_DIRECT != cyCapsense_CSD_SNS_CLK_SOURCE) */

        /* Enable SAMPLE interrupt */
        CY_SET_REG32(cyCapsense_INTR_MASK_PTR, cyCapsense_INTR_MASK_SAMPLE_MASK);

        /* Init Watchdog Counter to prevent a hang */
        watchdogCounter = cyCapsense_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM;

        /* Wait for IDLE state of the HW sequencer */
        while((0u != (cyCapsense_STAT_SEQ_REG & cyCapsense_STAT_SEQ_SEQ_STATE_MASK)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        /* Start SEQUENCER for fine initialization scan for Cmod and then for normal scan */
        CY_SET_REG32(cyCapsense_SEQ_START_PTR, cyCapsense_SEQ_START_AZ0_SKIP_MASK |
                                                     cyCapsense_SEQ_START_AZ1_SKIP_MASK |
                                                     cyCapsense_SEQ_START_START_MASK);

    #else

        /* Third-generation HW block section */

        /* Set resolution to Counter register to start scanning */
        CY_SET_REG32(cyCapsense_COUNTER_PTR, cyCapsense_counterResolution);

    #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
}

#endif  /* (cyCapsense_ENABLE == cyCapsense_CSD_EN) */


/* [] END OF FILE */

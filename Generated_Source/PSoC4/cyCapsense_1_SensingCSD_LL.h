/***************************************************************************//**
* \file cyCapsense_1_SensingCSD_LL.h
* \version 6.0
*
* \brief
*   This file provides the headers of APIs specific to CSD sensing implementation.
*
* \see cyCapsense_1 v6.0 Datasheet
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

#if !defined(CY_SENSE_cyCapsense_1_SENSINGCSD_LL_H)
#define CY_SENSE_cyCapsense_1_SENSINGCSD_LL_H

#include <CyLib.h>
#include <cyfitter.h>
#include <cytypes.h>
#include <cypins.h>
#include "cyCapsense_1_Structure.h"
#include "cyCapsense_1_Configuration.h"
#include "cyCapsense_1_Sensing.h"

/****************************************************************************
* Register and mode mask definition
****************************************************************************/

#if (cyCapsense_1_ENABLE == cyCapsense_1_CSDV2)
    #define cyCapsense_1_CSD_CSDCMP_INIT                                (cyCapsense_1_CSDCMP_CSDCMP_DISABLED)

    /* SW_HS_P_SEL switches state for Coarse initialization of CMOD (sense path) */
    #if (cyCapsense_1_ENABLE == cyCapsense_1_CSD_EN)
        #if (cyCapsense_1_CSD__CMOD_PAD == cyCapsense_1_CMOD_CONNECTION)
            #define cyCapsense_1_CSD_HS_P_SEL_COARSE_CMOD               (cyCapsense_1_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #elif (cyCapsense_1_CSD__CSHIELD_PAD == cyCapsense_1_CMOD_CONNECTION)
            #define cyCapsense_1_CSD_HS_P_SEL_COARSE_CMOD               (cyCapsense_1_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #else
            #define cyCapsense_1_CSD_HS_P_SEL_COARSE_CMOD               (cyCapsense_1_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #endif /* (cyCapsense_1_CSD__CMOD_PAD == cyCapsense_1_CMOD_CONNECTION) */
    #else
        #define cyCapsense_1_CSD_HS_P_SEL_COARSE_CMOD                   (0x00000000uL)
    #endif /* ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_CSX_EN) && (cyCapsense_1_ENABLE == cyCapsense_1_CSD_EN)) */

    #if ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_TANK_EN) && \
        (cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN))
        /* SW_HS_P_SEL switches state for Coarse initialization of CTANK (sense path) */
        #if (cyCapsense_1_CSD__CSH_TANK_PAD == cyCapsense_1_CTANK_CONNECTION)
            #define cyCapsense_1_CSD_HS_P_SEL_COARSE_TANK               (cyCapsense_1_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #elif (cyCapsense_1_CSD__CSHIELD_PAD == cyCapsense_1_CTANK_CONNECTION)
            #define cyCapsense_1_CSD_HS_P_SEL_COARSE_TANK               (cyCapsense_1_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #elif (cyCapsense_1_CSD__CMOD_PAD == cyCapsense_1_CTANK_CONNECTION)
            #define cyCapsense_1_CSD_HS_P_SEL_COARSE_TANK               (cyCapsense_1_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #else
            #define cyCapsense_1_CSD_HS_P_SEL_COARSE_TANK               (cyCapsense_1_SW_HS_P_SEL_SW_HMMA_STATIC_CLOSE)
        #endif /* (cyCapsense_1_CSD__CSH_TANK_PAD == cyCapsense_1_CTANK_CONNECTION) */
    #else
        #define cyCapsense_1_CSD_HS_P_SEL_COARSE_TANK                   (0x00000000uL)
    #endif /* ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_TANK_EN) && \
               (cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN)) */

    #define cyCapsense_1_CSD_SW_HS_P_SEL_COARSE                         (cyCapsense_1_HS_P_SEL_COARSE_CMOD | cyCapsense_1_CSD_HS_P_SEL_COARSE_TANK)

    /* C_mod config */
    #if ((cyCapsense_1_CSD__CMOD_PAD == cyCapsense_1_CMOD_CONNECTION) || (cyCapsense_1_CSD__CMOD_PAD == cyCapsense_1_CTANK_CONNECTION))
        #define cyCapsense_1_CSD_SW_FW_MOD_SEL_INIT             (cyCapsense_1_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE |\
                                                                     cyCapsense_1_SW_FW_MOD_SEL_SW_F1MA_STATIC_CLOSE |\
                                                                     cyCapsense_1_SW_FW_MOD_SEL_SW_F1CA_STATIC_CLOSE)
        #define cyCapsense_1_SW_DSI_SEL_CMODPAD                 (cyCapsense_1_SW_DSI_CMOD)
    #else
        #define cyCapsense_1_CSD_SW_FW_MOD_SEL_INIT             (0x00000000uL)
        #define cyCapsense_1_SW_DSI_SEL_CMODPAD                 (0x00000000uL)
    #endif /* (cyCapsense_1_CSD__CMOD_PAD == cyCapsense_1_CMOD_CONNECTION) */

    /* C_tank config */
    #if ((cyCapsense_1_CSD__CSH_TANK_PAD == cyCapsense_1_CMOD_CONNECTION) || (cyCapsense_1_CSD__CSH_TANK_PAD == cyCapsense_1_CTANK_CONNECTION))
        #define cyCapsense_1_CSD_SW_FW_TANK_SEL_INIT            (cyCapsense_1_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE |\
                                                                     cyCapsense_1_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE |\
                                                                     cyCapsense_1_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE)
        #define cyCapsense_1_SW_DSI_SEL_TANKPAD                 (cyCapsense_1_SW_DSI_CTANK)
    #else
        #define cyCapsense_1_CSD_SW_FW_TANK_SEL_INIT            (0x00000000uL)
        #define cyCapsense_1_SW_DSI_SEL_TANKPAD                 (0x00000000uL)
    #endif /* (cyCapsense_1_CSD__CSH_TANK_PAD == cyCapsense_1_CTANK_CONNECTION) */

    #define cyCapsense_1_CSD_SW_SHIELD_SEL_INIT                 (cyCapsense_1_SW_SHIELD_SEL_SW_HCAV_HSCMP)

    /* Defining default HW configuration according to settings in customizer. */
    #define cyCapsense_1_DEFAULT_CSD_CONFIG                 (cyCapsense_1_CONFIG_FILTER_DELAY_12MHZ |\
                                                                 cyCapsense_1_CONFIG_SAMPLE_SYNC_MASK)
    #if (cyCapsense_1_ENABLE == cyCapsense_1_CSD_AUTO_ZERO_EN)
        /* Enable CSDCMP */
        #define cyCapsense_1_CSD_CSDCMP_SCAN                (cyCapsense_1_CSDCMP_CSDCMP_EN_MASK |\
                                                                 cyCapsense_1_CSDCMP_AZ_EN_MASK)
    #else
        /* Enable CSDCMP */
        #define cyCapsense_1_CSD_CSDCMP_SCAN                (cyCapsense_1_CSDCMP_CSDCMP_EN_MASK)
    #endif /* (cyCapsense_1_ENABLE == cyCapsense_1_CSD_AUTO_ZERO_EN) */

    #if ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_TANK_EN) && \
        (cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN))
        /* SW_HS_P_SEL switches state for Coarse initialization of CTANK (sense path) */
        #if (cyCapsense_1_CSD__CSH_TANK_PAD == cyCapsense_1_CTANK_CONNECTION)
            #define cyCapsense_1_CSD_HS_P_SEL_SCAN_TANK                 (cyCapsense_1_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #elif (cyCapsense_1_CSD__CSHIELD_PAD == cyCapsense_1_CTANK_CONNECTION)
            #define cyCapsense_1_CSD_HS_P_SEL_SCAN_TANK                 (cyCapsense_1_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #elif (cyCapsense_1_CSD__CMOD_PAD == cyCapsense_1_CTANK_CONNECTION)
            #define cyCapsense_1_CSD_HS_P_SEL_SCAN_TANK                 (cyCapsense_1_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #else
            #define cyCapsense_1_CSD_HS_P_SEL_SCAN_TANK                 (cyCapsense_1_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
        #endif /* (cyCapsense_1_CSD__CSH_TANK_PAD == cyCapsense_1_CTANK_CONNECTION) */
        #define cyCapsense_1_CSD_SW_HS_P_SEL_SCAN                       (cyCapsense_1_HS_P_SEL_SCAN_TANK)
    #elif(cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN)
        #define cyCapsense_1_CSD_SW_HS_P_SEL_SCAN                       (cyCapsense_1_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
    #else
        #define cyCapsense_1_CSD_SW_HS_P_SEL_SCAN                       (cyCapsense_1_STATIC_OPEN)
    #endif /* ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_TANK_EN) && \
               (cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN)) */

    /* SW_FW_MOD_SEL switches state for Coarse initialization of CMOD (sense path) */
    #define cyCapsense_1_CSD_SW_FW_MOD_SEL_SCAN                 (0x00000000uL)

    #if((cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN) && \
        (cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_TANK_EN) && \
        (cyCapsense_1_CSD__CSH_TANK_PAD == cyCapsense_1_CTANK_CONNECTION))
        #define cyCapsense_1_CSD_SW_FW_TANK_SEL_SCAN            (cyCapsense_1_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE | \
                                                                 cyCapsense_1_SW_FW_TANK_SEL_SW_F2CB_STATIC_CLOSE)
    #else
        #define cyCapsense_1_CSD_SW_FW_TANK_SEL_SCAN            (0x00000000uL)
    #endif /* ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN) && \
               (cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_TANK_EN) && \
               (cyCapsense_1_CSD__CSH_TANK_PAD == cyCapsense_1_CTANK_CONNECTION)) */

    /* Shield switch default config */
    #if ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN) && \
         (cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_TANK_EN))
        #if (cyCapsense_1_IDAC_SINKING == cyCapsense_1_CSD_IDAC_CONFIG)
            #define cyCapsense_1_CSD_SW_SHIELD_SEL_SCAN          (cyCapsense_1_SW_SHIELD_SEL_SW_HCBG_HSCMP)
        #else
            #define cyCapsense_1_CSD_SW_SHIELD_SEL_SCAN          (cyCapsense_1_SW_SHIELD_SEL_SW_HCBV_HSCMP)
        #endif /* (cyCapsense_1_IDAC_SINKING == cyCapsense_1_CSD_IDAC_CONFIG) */
    #elif(cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN)
        #if (cyCapsense_1_IDAC_SINKING == cyCapsense_1_CSD_IDAC_CONFIG)
            #define cyCapsense_1_CSD_SW_SHIELD_SEL_SCAN          (cyCapsense_1_SW_SHIELD_SEL_SW_HCBV_PHI1 | \
                                                                     cyCapsense_1_SW_SHIELD_SEL_SW_HCBG_PHI2_HSCMP)
        #else
            #define cyCapsense_1_CSD_SW_SHIELD_SEL_SCAN          (cyCapsense_1_SW_SHIELD_SEL_SW_HCBG_PHI1 | \
                                                                     cyCapsense_1_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP)
        #endif /* (cyCapsense_1_IDAC_SINKING == cyCapsense_1_CSD_IDAC_CONFIG) */
    #else
        #define cyCapsense_1_CSD_SW_SHIELD_SEL_SCAN              (0x00000000uL)
    #endif /* ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN) && \
               (cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_TANK_EN)) */

    #define cyCapsense_1_CSD_SW_RES_INIT                        (cyCapsense_1_CSD_INIT_SWITCH_RES << CYFLD_CSD_RES_HCAV__OFFSET)
    #define cyCapsense_1_CSD_SW_RES_SCAN                        ((cyCapsense_1_CSD_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBV__OFFSET) |\
                                                                     (cyCapsense_1_CSD_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBG__OFFSET))

    #define cyCapsense_1_CSD_SHIELD_GPIO_DM                 (cyCapsense_1_GPIO_STRGDRV)
    #define cyCapsense_1_CSD_SENSOR_HSIOM_SEL               (cyCapsense_1_HSIOM_SEL_CSD_SENSE)
    #define cyCapsense_1_CSD_SHIELD_HSIOM_SEL               (cyCapsense_1_HSIOM_SEL_CSD_SHIELD)
    #define cyCapsense_1_CSD_CMOD_HSIOM_SEL                 (cyCapsense_1_HSIOM_SEL_AMUXA)

    #define cyCapsense_1_DEFAULT_IDAC_MOD_BALL_MODE         ((uint32)cyCapsense_1_IDAC_MOD_BALL_MODE_FULL <<\
                                                                 CYFLD_CSD_BAL_MODE__OFFSET)
    #define cyCapsense_1_DEFAULT_IDAC_COMP_BALL_MODE        ((uint32)cyCapsense_1_IDAC_COMP_BALL_MODE_FULL <<\
                                                                 CYFLD_CSD_BAL_MODE__OFFSET)

    #define cyCapsense_1_DEFAULT_SENSE_DUTY_SEL             (cyCapsense_1_SENSE_DUTY_OVERLAP_PHI1_MASK |\
                                                                 cyCapsense_1_SENSE_DUTY_OVERLAP_PHI2_MASK)

    #define cyCapsense_1_CSD_IDAC_MOD_BITS_USED                     (7u)
    #define cyCapsense_1_CAL_MIDDLE_BIT                             (1uL << (cyCapsense_1_CSD_IDAC_MOD_BITS_USED - 1u))

    #define cyCapsense_1_DELAY_EXTRACYCLES_NUM                      (9u)

    #if (cyCapsense_1_IDAC_GAIN_HIGH == cyCapsense_1_CSD_IDAC_GAIN)
        #define cyCapsense_1_CSD_IDAC_GAIN_VALUE_NA                 (2400u)
    #elif (cyCapsense_1_IDAC_GAIN_MEDIUM == cyCapsense_1_CSD_IDAC_GAIN)
        #define cyCapsense_1_CSD_IDAC_GAIN_VALUE_NA                 (300u)
    #else
        #define cyCapsense_1_CSD_IDAC_GAIN_VALUE_NA                 (37u)
    #endif /* (cyCapsense_1_IDAC_GAIN_HIGH == cyCapsense_1_CSD_IDAC_GAIN) */

    /* Defining the drive mode of pins depending on the Inactive sensor connection setting in the Component customizer. */
    #if(cyCapsense_1_SNS_CONNECTION_GROUND == cyCapsense_1_CSD_INACTIVE_SNS_CONNECTION)
        #define cyCapsense_1_CSD_INACTIVE_SNS_GPIO_DM               (CY_SYS_PINS_DM_STRONG)
    #elif(cyCapsense_1_SNS_CONNECTION_HIGHZ == cyCapsense_1_CSD_INACTIVE_SNS_CONNECTION)
        #define cyCapsense_1_CSD_INACTIVE_SNS_GPIO_DM               (CY_SYS_PINS_DM_ALG_HIZ)
    #elif(cyCapsense_1_SNS_CONNECTION_SHIELD == cyCapsense_1_CSD_INACTIVE_SNS_CONNECTION)
        #define cyCapsense_1_CSD_INACTIVE_SNS_GPIO_DM               (CY_SYS_PINS_DM_ALG_HIZ)
    #else
        #error "Unsupported inactive connection for the inactive sensors."
    #endif /* (cyCapsense_1_SNS_CONNECTION_GROUND == cyCapsense_1_CSD_INACTIVE_SNS_CONNECTION) */


    /* Clock Source Mode */
    #if (cyCapsense_1_CLK_SOURCE_DIRECT == cyCapsense_1_CSD_SNS_CLK_SOURCE)
        #define cyCapsense_1_DEFAULT_MODULATION_MODE                (cyCapsense_1_CLK_SOURCE_DIRECT)
    #elif (cyCapsense_1_CLK_SOURCE_PRSAUTO == cyCapsense_1_CSD_SNS_CLK_SOURCE)
        #define cyCapsense_1_DEFAULT_MODULATION_MODE                (cyCapsense_1_CLK_SOURCE_SSC2)
    #elif ((cyCapsense_1_CLK_SOURCE_PRS8) == cyCapsense_1_CSD_SNS_CLK_SOURCE)
        #define cyCapsense_1_DEFAULT_MODULATION_MODE                (cyCapsense_1_CSD_SNS_CLK_SOURCE)
    #elif ((cyCapsense_1_CLK_SOURCE_PRS12) == cyCapsense_1_CSD_SNS_CLK_SOURCE)
        #define cyCapsense_1_DEFAULT_MODULATION_MODE                (cyCapsense_1_CSD_SNS_CLK_SOURCE)
    #else
        #define cyCapsense_1_DEFAULT_MODULATION_MODE                (cyCapsense_1_CSD_SNS_CLK_SOURCE)
    #endif /* (cyCapsense_1_CLK_SOURCE_DIRECT != cyCapsense_1_CSD_SNS_CLK_SOURCE) */

    /* IDACs Ranges */
    #if (cyCapsense_1_IDAC_GAIN_LOW == cyCapsense_1_CSD_IDAC_GAIN)
        #define cyCapsense_1_DEFAULT_IDAC_MOD_RANGE                 ((uint32)cyCapsense_1_IDAC_MOD_RANGE_IDAC_LO << CYFLD_CSD_RANGE__OFFSET)
        #define cyCapsense_1_DEFAULT_IDAC_COMP_RANGE                ((uint32)cyCapsense_1_IDAC_COMP_RANGE_IDAC_LO << CYFLD_CSD_RANGE__OFFSET)
    #elif (cyCapsense_1_IDAC_GAIN_MEDIUM == cyCapsense_1_CSD_IDAC_GAIN)
        #define cyCapsense_1_DEFAULT_IDAC_MOD_RANGE                 ((uint32)cyCapsense_1_IDAC_MOD_RANGE_IDAC_MED << CYFLD_CSD_RANGE__OFFSET)
        #define cyCapsense_1_DEFAULT_IDAC_COMP_RANGE                ((uint32)cyCapsense_1_IDAC_COMP_RANGE_IDAC_MED << CYFLD_CSD_RANGE__OFFSET)
    #else
        #define cyCapsense_1_DEFAULT_IDAC_MOD_RANGE                 ((uint32)cyCapsense_1_IDAC_MOD_RANGE_IDAC_HI << CYFLD_CSD_RANGE__OFFSET)
        #define cyCapsense_1_DEFAULT_IDAC_COMP_RANGE                ((uint32)cyCapsense_1_IDAC_COMP_RANGE_IDAC_HI << CYFLD_CSD_RANGE__OFFSET)
    #endif

    /* IDACs Polarities */
    #if (cyCapsense_1_IDAC_SINKING == cyCapsense_1_CSD_IDAC_CONFIG)
        #define cyCapsense_1_DEFAULT_IDAC_MOD_POLARITY              ((uint32)cyCapsense_1_IDAC_MOD_POLARITY_VDDA_SNK << CYFLD_CSD_POLARITY__OFFSET)
        #define cyCapsense_1_DEFAULT_IDAC_COMP_POLARITY             ((uint32)cyCapsense_1_IDAC_COMP_POLARITY_VDDA_SNK << CYFLD_CSD_POLARITY__OFFSET)
    #else
        #define cyCapsense_1_DEFAULT_IDAC_MOD_POLARITY              ((uint32)cyCapsense_1_IDAC_MOD_POLARITY_VSSA_SRC << CYFLD_CSD_POLARITY__OFFSET)
        #define cyCapsense_1_DEFAULT_IDAC_COMP_POLARITY             ((uint32)cyCapsense_1_IDAC_COMP_POLARITY_VSSA_SRC << CYFLD_CSD_POLARITY__OFFSET)
    #endif /* (cyCapsense_1_IDAC_SINKING == cyCapsense_1_CSD_IDAC_CONFIG) */

    #define cyCapsense_1_SW_REFGEN_VREF_SRC                         (cyCapsense_1_SW_REFGEN_SEL_SW_SGR_MASK)

    /* IDAC legs configuration */
    #if ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_IDAC_COMP_EN) && \
         (cyCapsense_1_ENABLE == cyCapsense_1_CSD_DEDICATED_IDAC_COMP_EN))
            #define cyCapsense_1_DEFAULT_SW_REFGEN_SEL              (cyCapsense_1_SW_REFGEN_VREF_SRC | cyCapsense_1_SW_REFGEN_SEL_SW_IAIB_MASK)
            #define cyCapsense_1_DEFAULT_IDAC_COMP_LEG1_MODE        (cyCapsense_1_IDAC_COMP_LEG1_EN_MASK |\
                                                                        ((uint32)cyCapsense_1_IDAC_COMP_LEG1_MODE_CSD_STATIC << CYFLD_CSD_LEG1_MODE__OFFSET))
    #else
            #define cyCapsense_1_DEFAULT_SW_REFGEN_SEL              (cyCapsense_1_SW_REFGEN_VREF_SRC)
            #define cyCapsense_1_DEFAULT_IDAC_COMP_LEG1_MODE        ((uint32)cyCapsense_1_IDAC_COMP_LEG1_MODE_CSD_STATIC << CYFLD_CSD_LEG1_MODE__OFFSET)
    #endif /* ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_IDAC_COMP_EN) && \
               (cyCapsense_1_ENABLE == cyCapsense_1_CSD_DEDICATED_IDAC_COMP_EN)) */


    #if ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_IDAC_COMP_EN) && \
         (cyCapsense_1_DISABLE == cyCapsense_1_CSD_DEDICATED_IDAC_COMP_EN))
            #define cyCapsense_1_DEFAULT_IDAC_COMP_LEG2_MODE        (cyCapsense_1_IDAC_COMP_LEG2_EN_MASK |\
                                                                        ((uint32)cyCapsense_1_IDAC_COMP_LEG2_MODE_CSD_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET))
    #else
            #define cyCapsense_1_DEFAULT_IDAC_COMP_LEG2_MODE        ((uint32)cyCapsense_1_IDAC_COMP_LEG2_MODE_GP_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET)
    #endif /* ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_IDAC_COMP_EN) && \
            (cyCapsense_1_DISABLE == cyCapsense_1_CSD_DEDICATED_IDAC_COMP_EN)) */

    /* IDACs register configuration is based on the Component configuration */
    #define cyCapsense_1_IDAC_MOD_DEFAULT_CFG                       (cyCapsense_1_DEFAULT_IDAC_MOD_RANGE | \
                                                                         cyCapsense_1_DEFAULT_IDAC_MOD_POLARITY | \
                                                                         cyCapsense_1_DEFAULT_IDAC_MOD_BALL_MODE | \
                                                                        ((uint32)(cyCapsense_1_IDAC_MOD_LEG1_MODE_CSD << CYFLD_CSD_LEG1_MODE__OFFSET)) | \
                                                                         cyCapsense_1_IDAC_MOD_LEG1_EN_MASK | \
                                                                         cyCapsense_1_DEFAULT_IDAC_COMP_LEG2_MODE)

    #define cyCapsense_1_IDAC_COMP_DEFAULT_CFG                      (cyCapsense_1_DEFAULT_IDAC_COMP_RANGE | \
                                                                         cyCapsense_1_DEFAULT_IDAC_COMP_POLARITY | \
                                                                         cyCapsense_1_DEFAULT_IDAC_COMP_BALL_MODE | \
                                                                         cyCapsense_1_DEFAULT_IDAC_COMP_LEG1_MODE | \
                                                                        ((uint32)(cyCapsense_1_IDAC_COMP_LEG2_MODE_GP_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET)))

    #define cyCapsense_1_IDAC_MOD_CALIBRATION_CFG                   ((uint32)(cyCapsense_1_DEFAULT_IDAC_MOD_RANGE | \
                                                                         cyCapsense_1_DEFAULT_IDAC_MOD_POLARITY | \
                                                                         cyCapsense_1_DEFAULT_IDAC_MOD_BALL_MODE | \
                                                                        ((uint32)(cyCapsense_1_IDAC_MOD_LEG1_MODE_CSD << CYFLD_CSD_LEG1_MODE__OFFSET)) | \
                                                                         cyCapsense_1_IDAC_MOD_LEG1_EN_MASK | \
                                                                        ((uint32)((uint32)cyCapsense_1_IDAC_MOD_LEG2_MODE_GP_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET))))

    #define cyCapsense_1_IDAC_COMP_CALIBRATION_CFG                  ((uint32)(cyCapsense_1_DEFAULT_IDAC_COMP_RANGE | \
                                                                         cyCapsense_1_DEFAULT_IDAC_COMP_POLARITY | \
                                                                         cyCapsense_1_DEFAULT_IDAC_COMP_BALL_MODE | \
                                                                        ((uint32)((uint32)cyCapsense_1_IDAC_COMP_LEG1_MODE_GP_STATIC << CYFLD_CSD_LEG1_MODE__OFFSET)) | \
                                                                        ((uint32)((uint32)cyCapsense_1_IDAC_COMP_LEG2_MODE_GP_STATIC << CYFLD_CSD_LEG2_MODE__OFFSET))))
#else
    #define cyCapsense_1_CSD_IDAC_MOD_BITS_USED                     (8u)

    #define cyCapsense_1_IDAC_MOD_CFG_MASK                  (cyCapsense_1_IDAC_POLARITY1_MIR_MASK |\
                                                                cyCapsense_1_IDAC_MOD_RANGE_MASK |\
                                                                cyCapsense_1_IDAC_MOD_MODE_MASK |\
                                                                cyCapsense_1_IDAC_MOD_MASK)

    #define cyCapsense_1_IDAC_COMP_CFG_MASK                 (cyCapsense_1_IDAC_POLARITY2_MIR_MASK |\
                                                                cyCapsense_1_IDAC_COMP_RANGE_MASK |\
                                                                cyCapsense_1_IDAC_COMP_MODE_MASK |\
                                                                cyCapsense_1_IDAC_COMP_MASK)

        #define cyCapsense_1_PRS_8_CONFIG                       cyCapsense_1_CONFIG_PRS_SELECT_MASK
    #define cyCapsense_1_PRS_12_CONFIG                      (cyCapsense_1_CONFIG_PRS_12_8_MASK |\
                                                                cyCapsense_1_CONFIG_PRS_SELECT_MASK)

    /* Third-generation HW block Initial PRS mode */
    #if (cyCapsense_1_CLK_SOURCE_PRS8 == cyCapsense_1_CSD_SNS_CLK_SOURCE)
        #define cyCapsense_1_DEFAULT_MODULATION_MODE        cyCapsense_1_CONFIG_PRS_SELECT_MASK

    #elif (cyCapsense_1_CLK_SOURCE_PRS12 == cyCapsense_1_CSD_SNS_CLK_SOURCE)
        #define cyCapsense_1_DEFAULT_MODULATION_MODE        (cyCapsense_1_CONFIG_PRS_12_8_MASK |\
                                                                cyCapsense_1_CONFIG_PRS_SELECT_MASK)
    #else
        #define cyCapsense_1_DEFAULT_MODULATION_MODE        (0u)
    #endif /* (cyCapsense_1_CSD_SNS_CLK_SOURCE == cyCapsense_1_PRS_8BITS) */

    /* Third-generation HW block Set IDAC polarity */
    #if (cyCapsense_1_CSD_IDAC_CONFIG == cyCapsense_1_IDAC_SINKING)
        #define cyCapsense_1_DEFAULT_IDAC_POLARITY          cyCapsense_1_CONFIG_POLARITY_MASK
        #define cyCapsense_1_CSH_DR_CONFIG                  cyCapsense_1_CTANK_DR_VDDIO
    #else
        #define cyCapsense_1_DEFAULT_IDAC_POLARITY          (0u)
        #define cyCapsense_1_CSH_DR_CONFIG                  cyCapsense_1_CTANK_DR_VSSIO
    #endif /* (cyCapsense_1_CSD_IDAC_CONFIG == cyCapsense_1_IDAC_SINKING) */

    /* Defining default CSD configuration according to settings in customizer. */
    #define cyCapsense_1_DEFAULT_CSD_CONFIG                 (cyCapsense_1_CONFIG_SENSE_COMP_BW_MASK |\
                                                                cyCapsense_1_DEFAULT_IDAC_POLARITY |\
                                                                cyCapsense_1_CONFIG_SENSE_INSEL_MASK |\
                                                                cyCapsense_1_CONFIG_REFBUF_DRV_MASK)

    #define cyCapsense_1_CSD_ENABLE_MASK                    (cyCapsense_1_CONFIG_ENABLE_MASK |\
                                                                cyCapsense_1_CONFIG_SENSE_EN_MASK |\
                                                                cyCapsense_1_CONFIG_SENSE_COMP_EN_MASK)

    /* Third-generation HW block Defining mask intended for clearing bits related to pre-charging options. */
    #define cyCapsense_1_PRECHARGE_CONFIG_MASK              (cyCapsense_1_CONFIG_REFBUF_EN_MASK |\
                                                                cyCapsense_1_CONFIG_COMP_MODE_MASK |\
                                                                cyCapsense_1_CONFIG_COMP_PIN_MASK  |\
                                                                cyCapsense_1_CONFIG_REFBUF_OUTSEL_MASK)

    #define cyCapsense_1_CMOD_PRECHARGE_CONFIG              (cyCapsense_1_DEFAULT_CSD_CONFIG |\
                                                                cyCapsense_1_CONFIG_REFBUF_EN_MASK |\
                                                                cyCapsense_1_CONFIG_COMP_PIN_MASK)

    #define cyCapsense_1_CMOD_PRECHARGE_CONFIG_CSD_EN       (cyCapsense_1_DEFAULT_CSD_CONFIG |\
                                                                cyCapsense_1_CSD_ENABLE_MASK |\
                                                                cyCapsense_1_CONFIG_REFBUF_EN_MASK |\
                                                                cyCapsense_1_CONFIG_COMP_PIN_MASK)


    /* Third-generation HW block Ctank pre-charge mode configuration */
    #if(cyCapsense_1_CSD_CSH_PRECHARGE_SRC == cyCapsense_1_CSH_PRECHARGE_VREF)
        #if (cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN)
            #define  cyCapsense_1_CTANK_PRECHARGE_CONFIG    (cyCapsense_1_DEFAULT_CSD_CONFIG |\
                                                                 cyCapsense_1_CONFIG_REFBUF_EN_MASK |\
                                                                 cyCapsense_1_CONFIG_PRS_CLEAR_MASK |\
                                                                 cyCapsense_1_CONFIG_REFBUF_OUTSEL_MASK)
        #else
            #define  cyCapsense_1_CTANK_PRECHARGE_CONFIG    (cyCapsense_1_DEFAULT_CSD_CONFIG |\
                                                                 cyCapsense_1_CONFIG_REFBUF_OUTSEL_MASK |\
                                                                 cyCapsense_1_CONFIG_PRS_CLEAR_MASK)
        #endif /* (cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN) */
    #else
        #define  cyCapsense_1_CTANK_PRECHARGE_CONFIG        (cyCapsense_1_DEFAULT_CSD_CONFIG |\
                                                                cyCapsense_1_CONFIG_REFBUF_OUTSEL_MASK |\
                                                                cyCapsense_1_CONFIG_REFBUF_EN_MASK |\
                                                                cyCapsense_1_CONFIG_COMP_MODE_MASK |\
                                                                cyCapsense_1_CONFIG_PRS_CLEAR_MASK |\
                                                                cyCapsense_1_CONFIG_COMP_PIN_MASK)
    #endif /* (cyCapsense_1_CSD_CSH_PRECHARGE_SRC == cyCapsense_1__CSH_PRECHARGE_IO_BUF) */

    #define  cyCapsense_1_CTANK_PRECHARGE_CONFIG_CSD_EN     (cyCapsense_1_CTANK_PRECHARGE_CONFIG |\
                                                                 cyCapsense_1_CONFIG_ENABLE_MASK |\
                                                                 cyCapsense_1_CONFIG_SENSE_COMP_EN_MASK)

#endif /* (cyCapsense_1_ENABLE == cyCapsense_1_CSDV2) */

/* Calibration constants */
#define cyCapsense_1_IDAC_MOD_MAX_CALIB_ERROR                       (10u)
#define cyCapsense_1_CAL_MIDDLE_BIT                                 (1uL << (cyCapsense_1_CSD_IDAC_MOD_BITS_USED - 1u))

#define cyCapsense_1_CSD_AVG_CYCLES_PER_LOOP                   (5u)
#define cyCapsense_1_CSD_MEASURE_MAX_TIME_US                   (6000u)
#define cyCapsense_1_CSD_PRECHARGE_MAX_TIME_US                 (250u)

#define cyCapsense_1_CSD_CALIBR_WATCHDOG_CYCLES_NUM            (((CYDEV_BCLK__SYSCLK__MHZ) * (cyCapsense_1_CSD_MEASURE_MAX_TIME_US)) /\
                                                                    (cyCapsense_1_CSD_AVG_CYCLES_PER_LOOP))
#define cyCapsense_1_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM         (((CYDEV_BCLK__SYSCLK__MHZ) * (cyCapsense_1_CSD_MEASURE_MAX_TIME_US)) /\
                                                                    (cyCapsense_1_CSD_AVG_CYCLES_PER_LOOP))

/***************************************
* Global software variables
***************************************/

extern uint32 cyCapsense_1_configCsd;

#if (cyCapsense_1_ENABLE == cyCapsense_1_CSD_NOISE_METRIC_EN)
    extern uint8 cyCapsense_1_badConversionsNum;
#endif /* (cyCapsense_1_ENABLE == cyCapsense_1_CSD_NOISE_METRIC_EN) */

#if (cyCapsense_1_CSD_SS_DIS != cyCapsense_1_CSD_AUTOTUNE)
    /* Stores IDAC and raw count that corresponds to a sensor with maximum Cp within a widget */
    extern uint8 cyCapsense_1_calibratedIdac;
    extern uint16 cyCapsense_1_calibratedRawcount;
    #if (cyCapsense_1_CSD_MATRIX_WIDGET_EN || cyCapsense_1_CSD_TOUCHPAD_WIDGET_EN)
        extern uint8 cyCapsense_1_calibratedIdacRow;
        extern uint16 cyCapsense_1_calibratedRawcountRow;
    #endif /*(cyCapsense_1_CSD_MATRIX_WIDGET_EN || cyCapsense_1_CSD_TOUCHPAD_WIDGET_EN) */
#endif /* (cyCapsense_1_CSD_SS_DIS != cyCapsense_1_CSD_AUTOTUNE) */

/***************************************
* Function Prototypes
**************************************/

/**
* \cond SECTION_C_LOW_LEVEL
* \addtogroup group_c_low_level
* \{
*/

void cyCapsense_1_CSDSetupWidget(uint32 widgetId);
void cyCapsense_1_CSDSetupWidgetExt(uint32 widgetId, uint32 sensorId);
void cyCapsense_1_CSDScan(void);
void cyCapsense_1_CSDScanExt(void);
#if ((cyCapsense_1_CSD_SS_DIS != cyCapsense_1_CSD_AUTOTUNE) || \
     (cyCapsense_1_ENABLE == cyCapsense_1_CSD_IDAC_AUTOCAL_EN))
    cystatus cyCapsense_1_CSDCalibrateWidget(uint32 widgetId, uint32 target);
#endif /* ((cyCapsense_1_CSD_SS_DIS != cyCapsense_1_CSD_AUTOTUNE) || \
           (cyCapsense_1_ENABLE == cyCapsense_1_CSD_IDAC_AUTOCAL_EN))  */
void cyCapsense_1_CSDConnectSns(cyCapsense_1_FLASH_IO_STRUCT const *snsAddrPtr);
void cyCapsense_1_CSDDisconnectSns(cyCapsense_1_FLASH_IO_STRUCT const *snsAddrPtr);

/** \}
* \endcond */

/*****************************************************
* Function Prototypes - internal Low Level functions
*****************************************************/

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

void cyCapsense_1_SsCSDInitialize(void);
void cyCapsense_1_SsCSDStartSample(void);
void cyCapsense_1_SsCSDSetUpIdacs(cyCapsense_1_RAM_WD_BASE_STRUCT const *ptrWdgt);
void cyCapsense_1_SsCSDConfigClock(void);
void cyCapsense_1_SsCSDElectrodeCheck(void);
#if ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN) && \
     (0u != cyCapsense_1_CSD_TOTAL_SHIELD_COUNT))
    void cyCapsense_1_SsCSDDisableShieldElectrodes(void);
#endif /* ((cyCapsense_1_ENABLE == cyCapsense_1_CSD_SHIELD_EN) && \
           (0u != cyCapsense_1_CSD_TOTAL_SHIELD_COUNT)) */
#if (cyCapsense_1_ENABLE == cyCapsense_1_CSDV2)
    uint32 cyCapsense_1_SsCSDGetNumberOfConversions(uint32 snsClkDivider, uint32 resolution, uint32 snsClkSrc);
#endif /* (cyCapsense_1_ENABLE == cyCapsense_1_CSDV2) */
void cyCapsense_1_SsCSDCalculateScanDuration(cyCapsense_1_RAM_WD_BASE_STRUCT const *ptrWdgt);
void cyCapsense_1_SsCSDConnectSensorExt(uint32 widgetId, uint32 sensorId);
void cyCapsense_1_SsCSDDisconnectSnsExt(uint32 widgetId, uint32 sensorId);

#if ((cyCapsense_1_CSD_SS_DIS != cyCapsense_1_CSD_AUTOTUNE) || \
     (cyCapsense_1_ENABLE == cyCapsense_1_SELF_TEST_EN) || \
     (cyCapsense_1_ENABLE == cyCapsense_1_CSD_IDAC_AUTOCAL_EN))
#endif /* ((cyCapsense_1_CSD_SS_DIS != cyCapsense_1_CSD_AUTOTUNE) || \
           (cyCapsense_1_ENABLE == cyCapsense_1_SELF_TEST_EN) || \
           (cyCapsense_1_ENABLE == cyCapsense_1_CSD_IDAC_AUTOCAL_EN)) */

/** \}
* \endcond */

/***************************************
* Global software variables
***************************************/
extern uint32 cyCapsense_1_configCsd;

/* Interrupt handler */
extern CY_ISR_PROTO(cyCapsense_1_CSDPostSingleScan);
extern CY_ISR_PROTO(cyCapsense_1_CSDPostMultiScan);
#if (cyCapsense_1_ENABLE == cyCapsense_1_CSD_GANGED_SNS_EN)
extern CY_ISR_PROTO(cyCapsense_1_CSDPostMultiScanGanged);
#endif /* (cyCapsense_1_ENABLE == cyCapsense_1_CSD_GANGED_SNS_EN) */
#if (cyCapsense_1_ENABLE == cyCapsense_1_CSD_NOISE_METRIC_EN)
    extern uint8 cyCapsense_1_badConversionsNum;
#endif /* (cyCapsense_1_ENABLE == cyCapsense_1_CSD_NOISE_METRIC_EN) */

#endif /* End CY_SENSE_cyCapsense_1_SENSINGCSD_LL_H */


/* [] END OF FILE */

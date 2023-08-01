/***************************************************************************//**
* \file cyCapsense_1_Filter.h
* \version 6.0
*
* \brief 
*   This file contains the definitions for all firmware filters
*   implementation.
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

#if !defined(CY_SENSE_cyCapsense_1_FILTER_H)
#define CY_SENSE_cyCapsense_1_FILTER_H

#include "cytypes.h"
#include "CyLib.h"
#include "cyfitter.h"

#include "cyCapsense_1_Structure.h"
#include "cyCapsense_1_Configuration.h"

/***************************************
* Function Prototypes
***************************************/

/*******************************************************************************
* LOW LEVEL API
*******************************************************************************/
/**
* \cond (SECTION_C_LOW_LEVEL || SECTION_I_LOW_LEVEL)
* \addtogroup group_c_low_level
* \{
*/

cystatus cyCapsense_1_UpdateAllBaselines(void);
cystatus cyCapsense_1_UpdateWidgetBaseline(uint32 widgetId);
cystatus cyCapsense_1_UpdateSensorBaseline(uint32 widgetId, uint32 sensorId);

void cyCapsense_1_InitializeAllBaselines(void);
void cyCapsense_1_InitializeWidgetBaseline(uint32 widgetId);
void cyCapsense_1_InitializeSensorBaseline(uint32 widgetId, uint32 sensorId);

#if ((cyCapsense_1_ENABLE == cyCapsense_1_RC_FILTER_EN) || \
     (0u != (cyCapsense_1_CSD_AUTOTUNE & cyCapsense_1_CSD_SS_TH_EN)))
    void cyCapsense_1_InitializeAllFilters(void);
    void cyCapsense_1_InitializeWidgetFilter(uint32 widgetId);
#endif /* ((cyCapsense_1_ENABLE == cyCapsense_1_RC_FILTER_EN) || \
           (0u != (cyCapsense_1_CSD_AUTOTUNE & cyCapsense_1_CSD_SS_TH_EN))) */

/** \}
* \endcond */


/*******************************************************************************
* Function Prototypes - internal functions
*******************************************************************************/
/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

void cyCapsense_1_FtInitialize(void);

#if (0u != (cyCapsense_1_CSD_AUTOTUNE & cyCapsense_1_CSD_SS_TH_EN))
    void cyCapsense_1_RunNoiseEnvelope(uint32 widgetId, uint32 sensorId);
    void cyCapsense_1_InitializeNoiseEnvelope(uint32 widgetId, uint32 sensorId);
#endif /* (0u != (cyCapsense_1_CSD_AUTOTUNE & cyCapsense_1_CSD_SS_TH_EN)) */

#if (cyCapsense_1_REGULAR_RC_IIR_FILTER_EN || cyCapsense_1_PROX_RC_IIR_FILTER_EN)
    void cyCapsense_1_InitializeIIR(uint32 widgetId, uint32 sensorId);
    void cyCapsense_1_RunIIR(uint32 widgetId, uint32 sensorId);
#endif /* (cyCapsense_1_REGULAR_RC_IIR_FILTER_EN || cyCapsense_1_PROX_RC_IIR_FILTER_EN) */

#if (cyCapsense_1_REGULAR_RC_MEDIAN_FILTER_EN || cyCapsense_1_PROX_RC_MEDIAN_FILTER_EN)
    void cyCapsense_1_InitializeMedian(uint32 widgetId, uint32 sensorId);
    void cyCapsense_1_RunMedian(uint32 widgetId, uint32 sensorId);
#endif /* (cyCapsense_1_REGULAR_RC_MEDIAN_FILTER_EN || cyCapsense_1_PROX_RC_MEDIAN_FILTER_EN) */

#if (cyCapsense_1_REGULAR_RC_AVERAGE_FILTER_EN || cyCapsense_1_PROX_RC_AVERAGE_FILTER_EN)
    void cyCapsense_1_InitializeAverage(uint32 widgetId, uint32 sensorId);
    void cyCapsense_1_RunAverage(uint32 widgetId, uint32 sensorId);
#endif /* (cyCapsense_1_REGULAR_RC_AVERAGE_FILTER_EN || cyCapsense_1_PROX_RC_AVERAGE_FILTER_EN) */

void cyCapsense_1_FtInitializeBaseline(cyCapsense_1_RAM_SNS_STRUCT *ptrSensor, uint32 wdType);
uint32 cyCapsense_1_FtUpdateBaseline(
                            cyCapsense_1_RAM_WD_BASE_STRUCT *ptrWidgetRam,
                            cyCapsense_1_RAM_SNS_STRUCT *ptrSensor,
                            uint32 wdType);

#if (cyCapsense_1_POS_MEDIAN_FILTER_EN || cyCapsense_1_REGULAR_RC_MEDIAN_FILTER_EN || cyCapsense_1_PROX_RC_MEDIAN_FILTER_EN)
uint32 cyCapsense_1_FtMedian(uint32 x1, uint32 x2, uint32 x3);
#endif /*cyCapsense_1_POS_MEDIAN_FILTER_EN || cyCapsense_1_REGULAR_RC_MEDIAN_FILTER_EN || cyCapsense_1_PROX_RC_MEDIAN_FILTER_EN*/

uint32 cyCapsense_1_FtIIR1stOrder(uint32 input, uint32 prevOutput, uint32 n, uint32 shift);

#if (cyCapsense_1_POS_JITTER_FILTER_EN)
    uint32 cyCapsense_1_FtJitter(uint32 input, uint32 prevOutput);
#endif /* cyCapsense_1_POS_JITTER_FILTER_EN */

void cyCapsense_1_FtInitializeBaselineChannel(cyCapsense_1_RAM_SNS_STRUCT *ptrSensor, uint32 wdType, uint32 channel);

#if (cyCapsense_1_ENABLE == cyCapsense_1_RC_FILTER_EN)
    void cyCapsense_1_FtRunEnabledFilters(uint32 widgetId, uint32 sensorId);
    void cyCapsense_1_FtRunEnabledFiltersInternal(cyCapsense_1_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                      cyCapsense_1_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
#endif /* (cyCapsense_1_ENABLE == cyCapsense_1_RC_FILTER_EN) */


#if (cyCapsense_1_REGULAR_RC_IIR_FILTER_EN || cyCapsense_1_PROX_RC_IIR_FILTER_EN)
    void cyCapsense_1_InitializeIIRInternal(cyCapsense_1_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                  cyCapsense_1_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
    void cyCapsense_1_RunIIRInternal(cyCapsense_1_PTR_FILTER_VARIANT ptrFilterHistObj,
                                           cyCapsense_1_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
#endif /* (cyCapsense_1_REGULAR_RC_IIR_FILTER_EN || cyCapsense_1_PROX_RC_IIR_FILTER_EN) */

#if (cyCapsense_1_REGULAR_RC_MEDIAN_FILTER_EN || cyCapsense_1_PROX_RC_MEDIAN_FILTER_EN)
    void cyCapsense_1_InitializeMedianInternal(cyCapsense_1_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                     cyCapsense_1_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
    void cyCapsense_1_RunMedianInternal(cyCapsense_1_PTR_FILTER_VARIANT ptrFilterHistObj,
                                              cyCapsense_1_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
#endif /* (cyCapsense_1_REGULAR_RC_MEDIAN_FILTER_EN || cyCapsense_1_PROX_RC_MEDIAN_FILTER_EN) */

#if (cyCapsense_1_REGULAR_RC_AVERAGE_FILTER_EN || cyCapsense_1_PROX_RC_AVERAGE_FILTER_EN)
    void cyCapsense_1_InitializeAverageInternal(cyCapsense_1_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                      cyCapsense_1_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
    void cyCapsense_1_RunAverageInternal(cyCapsense_1_PTR_FILTER_VARIANT ptrFilterHistObj,
                                               cyCapsense_1_RAM_SNS_STRUCT *ptrSensorObj, uint32 wdType);
#endif /* (cyCapsense_1_REGULAR_RC_AVERAGE_FILTER_EN || cyCapsense_1_PROX_RC_AVERAGE_FILTER_EN) */

#if (cyCapsense_1_ENABLE == cyCapsense_1_ALP_FILTER_EN)
    void cyCapsense_1_InitializeALP(uint32 widgetId, uint32 sensorId);
    void cyCapsense_1_RunALP(uint32 widgetId, uint32 sensorId);
    void cyCapsense_1_InitializeALPInternal(cyCapsense_1_PTR_FILTER_VARIANT ptrFilterHistObj,
                                                cyCapsense_1_RAM_SNS_STRUCT *ptrSensorObj,
                                                uint32 wdType);
    void cyCapsense_1_ConfigRunALPInternal(cyCapsense_1_PTR_FILTER_VARIANT ptrFilterHistObj,
                                        cyCapsense_1_RAM_WD_BASE_STRUCT *ptrRamWdgt,
                                        cyCapsense_1_RAM_SNS_STRUCT *ptrSensorObj,
                                        uint32 wdType);
    void cyCapsense_1_RunALPInternal(cyCapsense_1_PTR_FILTER_VARIANT ptrFilterHistObj,
                                        ALP_FLTR_CONFIG_STRUCT *ptrAlpFilterConfig,
                                        cyCapsense_1_RAM_SNS_STRUCT *ptrSensorObj,
                                        uint32 wdType);
#endif /* (cyCapsense_1_ENABLE == cyCapsense_1_ALP_FILTER_EN) */

/** \}
* \endcond */

/***************************************
* Initial Parameter Constants
***************************************/
#define NOISE_ENVELOPE_SHIFT                        (0x02u)
#define NOISE_ENVELOPE_RUN_DIFF_SHIFT               (0x03u)
#define NOISE_ENVELOPE_SIGN_REG                     (0x0Fu)
#define NOISE_ENVELOPE_SIGN_REG_SHIFT               (0x01u)
#define NOISE_ENVELOPE_RESET_COUNTER                (0x0Au)
#define NOISE_ENVELOPE_4_TIMES                      (0x02u)

#endif /* End CY_SENSE_cyCapsense_1_FILTER_H */


/* [] END OF FILE */

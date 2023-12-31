/***************************************************************************//**
* \file cyCapsense_1_RegisterMap.h
* \version 6.0
*
* \brief
*   This file provides the definitions for the Component data structure register.
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

#if !defined(CY_SENSE_cyCapsense_1_REGISTER_MAP_H)
#define CY_SENSE_cyCapsense_1_REGISTER_MAP_H

#include <cytypes.h>
#include "cyCapsense_1_Configuration.h"
#include "cyCapsense_1_Structure.h"

/*****************************************************************************/
/* RAM Data structure register definitions                                   */
/*****************************************************************************/
#define cyCapsense_1_CONFIG_ID_VALUE                        (cyCapsense_1_dsRam.configId)
#define cyCapsense_1_CONFIG_ID_OFFSET                       (0u)
#define cyCapsense_1_CONFIG_ID_SIZE                         (2u)
#define cyCapsense_1_CONFIG_ID_PARAM_ID                     (0x87000000u)

#define cyCapsense_1_DEVICE_ID_VALUE                        (cyCapsense_1_dsRam.deviceId)
#define cyCapsense_1_DEVICE_ID_OFFSET                       (2u)
#define cyCapsense_1_DEVICE_ID_SIZE                         (2u)
#define cyCapsense_1_DEVICE_ID_PARAM_ID                     (0x8B000002u)

#define cyCapsense_1_HW_CLOCK_VALUE                         (cyCapsense_1_dsRam.hwClock)
#define cyCapsense_1_HW_CLOCK_OFFSET                        (4u)
#define cyCapsense_1_HW_CLOCK_SIZE                          (2u)
#define cyCapsense_1_HW_CLOCK_PARAM_ID                      (0x86000004u)

#define cyCapsense_1_TUNER_CMD_VALUE                        (cyCapsense_1_dsRam.tunerCmd)
#define cyCapsense_1_TUNER_CMD_OFFSET                       (6u)
#define cyCapsense_1_TUNER_CMD_SIZE                         (2u)
#define cyCapsense_1_TUNER_CMD_PARAM_ID                     (0xA1000006u)

#define cyCapsense_1_SCAN_COUNTER_VALUE                     (cyCapsense_1_dsRam.scanCounter)
#define cyCapsense_1_SCAN_COUNTER_OFFSET                    (8u)
#define cyCapsense_1_SCAN_COUNTER_SIZE                      (2u)
#define cyCapsense_1_SCAN_COUNTER_PARAM_ID                  (0x85000008u)

#define cyCapsense_1_STATUS_VALUE                           (cyCapsense_1_dsRam.status)
#define cyCapsense_1_STATUS_OFFSET                          (12u)
#define cyCapsense_1_STATUS_SIZE                            (4u)
#define cyCapsense_1_STATUS_PARAM_ID                        (0xCB00000Cu)

#define cyCapsense_1_WDGT_ENABLE0_VALUE                     (cyCapsense_1_dsRam.wdgtEnable[0u])
#define cyCapsense_1_WDGT_ENABLE0_OFFSET                    (16u)
#define cyCapsense_1_WDGT_ENABLE0_SIZE                      (4u)
#define cyCapsense_1_WDGT_ENABLE0_PARAM_ID                  (0xE6000010u)

#define cyCapsense_1_WDGT_STATUS0_VALUE                     (cyCapsense_1_dsRam.wdgtStatus[0u])
#define cyCapsense_1_WDGT_STATUS0_OFFSET                    (20u)
#define cyCapsense_1_WDGT_STATUS0_SIZE                      (4u)
#define cyCapsense_1_WDGT_STATUS0_PARAM_ID                  (0xCC000014u)

#define cyCapsense_1_SNS_STATUS0_VALUE                      (cyCapsense_1_dsRam.snsStatus[0u])
#define cyCapsense_1_SNS_STATUS0_OFFSET                     (24u)
#define cyCapsense_1_SNS_STATUS0_SIZE                       (1u)
#define cyCapsense_1_SNS_STATUS0_PARAM_ID                   (0x48000018u)

#define cyCapsense_1_CSD0_CONFIG_VALUE                      (cyCapsense_1_dsRam.csd0Config)
#define cyCapsense_1_CSD0_CONFIG_OFFSET                     (26u)
#define cyCapsense_1_CSD0_CONFIG_SIZE                       (2u)
#define cyCapsense_1_CSD0_CONFIG_PARAM_ID                   (0xAA80001Au)

#define cyCapsense_1_MOD_CSD_CLK_VALUE                      (cyCapsense_1_dsRam.modCsdClk)
#define cyCapsense_1_MOD_CSD_CLK_OFFSET                     (28u)
#define cyCapsense_1_MOD_CSD_CLK_SIZE                       (1u)
#define cyCapsense_1_MOD_CSD_CLK_PARAM_ID                   (0x6F80001Cu)

#define cyCapsense_1_BUTTON0_RESOLUTION_VALUE               (cyCapsense_1_dsRam.wdgtList.button0.resolution)
#define cyCapsense_1_BUTTON0_RESOLUTION_OFFSET              (30u)
#define cyCapsense_1_BUTTON0_RESOLUTION_SIZE                (2u)
#define cyCapsense_1_BUTTON0_RESOLUTION_PARAM_ID            (0x8080001Eu)

#define cyCapsense_1_BUTTON0_FINGER_TH_VALUE                (cyCapsense_1_dsRam.wdgtList.button0.fingerTh)
#define cyCapsense_1_BUTTON0_FINGER_TH_OFFSET               (32u)
#define cyCapsense_1_BUTTON0_FINGER_TH_SIZE                 (2u)
#define cyCapsense_1_BUTTON0_FINGER_TH_PARAM_ID             (0x80800020u)

#define cyCapsense_1_BUTTON0_NOISE_TH_VALUE                 (cyCapsense_1_dsRam.wdgtList.button0.noiseTh)
#define cyCapsense_1_BUTTON0_NOISE_TH_OFFSET                (34u)
#define cyCapsense_1_BUTTON0_NOISE_TH_SIZE                  (1u)
#define cyCapsense_1_BUTTON0_NOISE_TH_PARAM_ID              (0x44800022u)

#define cyCapsense_1_BUTTON0_NNOISE_TH_VALUE                (cyCapsense_1_dsRam.wdgtList.button0.nNoiseTh)
#define cyCapsense_1_BUTTON0_NNOISE_TH_OFFSET               (35u)
#define cyCapsense_1_BUTTON0_NNOISE_TH_SIZE                 (1u)
#define cyCapsense_1_BUTTON0_NNOISE_TH_PARAM_ID             (0x42800023u)

#define cyCapsense_1_BUTTON0_HYSTERESIS_VALUE               (cyCapsense_1_dsRam.wdgtList.button0.hysteresis)
#define cyCapsense_1_BUTTON0_HYSTERESIS_OFFSET              (36u)
#define cyCapsense_1_BUTTON0_HYSTERESIS_SIZE                (1u)
#define cyCapsense_1_BUTTON0_HYSTERESIS_PARAM_ID            (0x49800024u)

#define cyCapsense_1_BUTTON0_ON_DEBOUNCE_VALUE              (cyCapsense_1_dsRam.wdgtList.button0.onDebounce)
#define cyCapsense_1_BUTTON0_ON_DEBOUNCE_OFFSET             (37u)
#define cyCapsense_1_BUTTON0_ON_DEBOUNCE_SIZE               (1u)
#define cyCapsense_1_BUTTON0_ON_DEBOUNCE_PARAM_ID           (0x4F800025u)

#define cyCapsense_1_BUTTON0_LOW_BSLN_RST_VALUE             (cyCapsense_1_dsRam.wdgtList.button0.lowBslnRst)
#define cyCapsense_1_BUTTON0_LOW_BSLN_RST_OFFSET            (38u)
#define cyCapsense_1_BUTTON0_LOW_BSLN_RST_SIZE              (1u)
#define cyCapsense_1_BUTTON0_LOW_BSLN_RST_PARAM_ID          (0x45800026u)

#define cyCapsense_1_BUTTON0_IDAC_MOD0_VALUE                (cyCapsense_1_dsRam.wdgtList.button0.idacMod[0u])
#define cyCapsense_1_BUTTON0_IDAC_MOD0_OFFSET               (39u)
#define cyCapsense_1_BUTTON0_IDAC_MOD0_SIZE                 (1u)
#define cyCapsense_1_BUTTON0_IDAC_MOD0_PARAM_ID             (0x4E000027u)

#define cyCapsense_1_BUTTON0_SNS_CLK_VALUE                  (cyCapsense_1_dsRam.wdgtList.button0.snsClk)
#define cyCapsense_1_BUTTON0_SNS_CLK_OFFSET                 (40u)
#define cyCapsense_1_BUTTON0_SNS_CLK_SIZE                   (2u)
#define cyCapsense_1_BUTTON0_SNS_CLK_PARAM_ID               (0x82800028u)

#define cyCapsense_1_BUTTON0_SNS_CLK_SOURCE_VALUE           (cyCapsense_1_dsRam.wdgtList.button0.snsClkSource)
#define cyCapsense_1_BUTTON0_SNS_CLK_SOURCE_OFFSET          (42u)
#define cyCapsense_1_BUTTON0_SNS_CLK_SOURCE_SIZE            (1u)
#define cyCapsense_1_BUTTON0_SNS_CLK_SOURCE_PARAM_ID        (0x4680002Au)

#define cyCapsense_1_BUTTON0_FINGER_CAP_VALUE               (cyCapsense_1_dsRam.wdgtList.button0.fingerCap)
#define cyCapsense_1_BUTTON0_FINGER_CAP_OFFSET              (44u)
#define cyCapsense_1_BUTTON0_FINGER_CAP_SIZE                (2u)
#define cyCapsense_1_BUTTON0_FINGER_CAP_PARAM_ID            (0xA500002Cu)

#define cyCapsense_1_BUTTON0_SIGPFC_VALUE                   (cyCapsense_1_dsRam.wdgtList.button0.sigPFC)
#define cyCapsense_1_BUTTON0_SIGPFC_OFFSET                  (46u)
#define cyCapsense_1_BUTTON0_SIGPFC_SIZE                    (2u)
#define cyCapsense_1_BUTTON0_SIGPFC_PARAM_ID                (0xA900002Eu)

#define cyCapsense_1_BUTTON0_SNS0_RAW0_VALUE                (cyCapsense_1_dsRam.snsList.button0[0u].raw[0u])
#define cyCapsense_1_BUTTON0_SNS0_RAW0_OFFSET               (48u)
#define cyCapsense_1_BUTTON0_SNS0_RAW0_SIZE                 (2u)
#define cyCapsense_1_BUTTON0_SNS0_RAW0_PARAM_ID             (0x88000030u)

#define cyCapsense_1_BUTTON0_SNS0_BSLN0_VALUE               (cyCapsense_1_dsRam.snsList.button0[0u].bsln[0u])
#define cyCapsense_1_BUTTON0_SNS0_BSLN0_OFFSET              (50u)
#define cyCapsense_1_BUTTON0_SNS0_BSLN0_SIZE                (2u)
#define cyCapsense_1_BUTTON0_SNS0_BSLN0_PARAM_ID            (0x84000032u)

#define cyCapsense_1_BUTTON0_SNS0_BSLN_EXT0_VALUE           (cyCapsense_1_dsRam.snsList.button0[0u].bslnExt[0u])
#define cyCapsense_1_BUTTON0_SNS0_BSLN_EXT0_OFFSET          (52u)
#define cyCapsense_1_BUTTON0_SNS0_BSLN_EXT0_SIZE            (1u)
#define cyCapsense_1_BUTTON0_SNS0_BSLN_EXT0_PARAM_ID        (0x41000034u)

#define cyCapsense_1_BUTTON0_SNS0_DIFF_VALUE                (cyCapsense_1_dsRam.snsList.button0[0u].diff)
#define cyCapsense_1_BUTTON0_SNS0_DIFF_OFFSET               (54u)
#define cyCapsense_1_BUTTON0_SNS0_DIFF_SIZE                 (2u)
#define cyCapsense_1_BUTTON0_SNS0_DIFF_PARAM_ID             (0x85000036u)

#define cyCapsense_1_BUTTON0_SNS0_NEG_BSLN_RST_CNT0_VALUE   (cyCapsense_1_dsRam.snsList.button0[0u].negBslnRstCnt[0u])
#define cyCapsense_1_BUTTON0_SNS0_NEG_BSLN_RST_CNT0_OFFSET  (56u)
#define cyCapsense_1_BUTTON0_SNS0_NEG_BSLN_RST_CNT0_SIZE    (1u)
#define cyCapsense_1_BUTTON0_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x42000038u)

#define cyCapsense_1_SNR_TEST_WIDGET_ID_VALUE               (cyCapsense_1_dsRam.snrTestWidgetId)
#define cyCapsense_1_SNR_TEST_WIDGET_ID_OFFSET              (58u)
#define cyCapsense_1_SNR_TEST_WIDGET_ID_SIZE                (1u)
#define cyCapsense_1_SNR_TEST_WIDGET_ID_PARAM_ID            (0x6500003Au)

#define cyCapsense_1_SNR_TEST_SENSOR_ID_VALUE               (cyCapsense_1_dsRam.snrTestSensorId)
#define cyCapsense_1_SNR_TEST_SENSOR_ID_OFFSET              (59u)
#define cyCapsense_1_SNR_TEST_SENSOR_ID_SIZE                (1u)
#define cyCapsense_1_SNR_TEST_SENSOR_ID_PARAM_ID            (0x6300003Bu)

#define cyCapsense_1_SNR_TEST_SCAN_COUNTER_VALUE            (cyCapsense_1_dsRam.snrTestScanCounter)
#define cyCapsense_1_SNR_TEST_SCAN_COUNTER_OFFSET           (60u)
#define cyCapsense_1_SNR_TEST_SCAN_COUNTER_SIZE             (2u)
#define cyCapsense_1_SNR_TEST_SCAN_COUNTER_PARAM_ID         (0x8B00003Cu)

#define cyCapsense_1_SNR_TEST_RAW_COUNT0_VALUE              (cyCapsense_1_dsRam.snrTestRawCount[0u])
#define cyCapsense_1_SNR_TEST_RAW_COUNT0_OFFSET             (62u)
#define cyCapsense_1_SNR_TEST_RAW_COUNT0_SIZE               (2u)
#define cyCapsense_1_SNR_TEST_RAW_COUNT0_PARAM_ID           (0x8700003Eu)


/*****************************************************************************/
/* Flash Data structure register definitions                                 */
/*****************************************************************************/
#define cyCapsense_1_BUTTON0_PTR2SNS_FLASH_VALUE            (cyCapsense_1_dsFlash.wdgtArray[0].ptr2SnsFlash)
#define cyCapsense_1_BUTTON0_PTR2SNS_FLASH_OFFSET           (0u)
#define cyCapsense_1_BUTTON0_PTR2SNS_FLASH_SIZE             (4u)
#define cyCapsense_1_BUTTON0_PTR2SNS_FLASH_PARAM_ID         (0xD1000000u)

#define cyCapsense_1_BUTTON0_PTR2WD_RAM_VALUE               (cyCapsense_1_dsFlash.wdgtArray[0].ptr2WdgtRam)
#define cyCapsense_1_BUTTON0_PTR2WD_RAM_OFFSET              (4u)
#define cyCapsense_1_BUTTON0_PTR2WD_RAM_SIZE                (4u)
#define cyCapsense_1_BUTTON0_PTR2WD_RAM_PARAM_ID            (0xD0000004u)

#define cyCapsense_1_BUTTON0_PTR2SNS_RAM_VALUE              (cyCapsense_1_dsFlash.wdgtArray[0].ptr2SnsRam)
#define cyCapsense_1_BUTTON0_PTR2SNS_RAM_OFFSET             (8u)
#define cyCapsense_1_BUTTON0_PTR2SNS_RAM_SIZE               (4u)
#define cyCapsense_1_BUTTON0_PTR2SNS_RAM_PARAM_ID           (0xD3000008u)

#define cyCapsense_1_BUTTON0_PTR2FLTR_HISTORY_VALUE         (cyCapsense_1_dsFlash.wdgtArray[0].ptr2FltrHistory)
#define cyCapsense_1_BUTTON0_PTR2FLTR_HISTORY_OFFSET        (12u)
#define cyCapsense_1_BUTTON0_PTR2FLTR_HISTORY_SIZE          (4u)
#define cyCapsense_1_BUTTON0_PTR2FLTR_HISTORY_PARAM_ID      (0xD200000Cu)

#define cyCapsense_1_BUTTON0_PTR2DEBOUNCE_VALUE             (cyCapsense_1_dsFlash.wdgtArray[0].ptr2DebounceArr)
#define cyCapsense_1_BUTTON0_PTR2DEBOUNCE_OFFSET            (16u)
#define cyCapsense_1_BUTTON0_PTR2DEBOUNCE_SIZE              (4u)
#define cyCapsense_1_BUTTON0_PTR2DEBOUNCE_PARAM_ID          (0xD4000010u)

#define cyCapsense_1_BUTTON0_STATIC_CONFIG_VALUE            (cyCapsense_1_dsFlash.wdgtArray[0].staticConfig)
#define cyCapsense_1_BUTTON0_STATIC_CONFIG_OFFSET           (20u)
#define cyCapsense_1_BUTTON0_STATIC_CONFIG_SIZE             (4u)
#define cyCapsense_1_BUTTON0_STATIC_CONFIG_PARAM_ID         (0xD5000014u)

#define cyCapsense_1_BUTTON0_TOTAL_NUM_SNS_VALUE            (cyCapsense_1_dsFlash.wdgtArray[0].totalNumSns)
#define cyCapsense_1_BUTTON0_TOTAL_NUM_SNS_OFFSET           (24u)
#define cyCapsense_1_BUTTON0_TOTAL_NUM_SNS_SIZE             (2u)
#define cyCapsense_1_BUTTON0_TOTAL_NUM_SNS_PARAM_ID         (0x99000018u)

#define cyCapsense_1_BUTTON0_TYPE_VALUE                     (cyCapsense_1_dsFlash.wdgtArray[0].wdgtType)
#define cyCapsense_1_BUTTON0_TYPE_OFFSET                    (26u)
#define cyCapsense_1_BUTTON0_TYPE_SIZE                      (1u)
#define cyCapsense_1_BUTTON0_TYPE_PARAM_ID                  (0x5D00001Au)

#define cyCapsense_1_BUTTON0_NUM_COLS_VALUE                 (cyCapsense_1_dsFlash.wdgtArray[0].numCols)
#define cyCapsense_1_BUTTON0_NUM_COLS_OFFSET                (27u)
#define cyCapsense_1_BUTTON0_NUM_COLS_SIZE                  (1u)
#define cyCapsense_1_BUTTON0_NUM_COLS_PARAM_ID              (0x5B00001Bu)

#define cyCapsense_1_BUTTON0_PTR2NOISE_ENVLP_VALUE          (cyCapsense_1_dsFlash.wdgtArray[0].ptr2NoiseEnvlp)
#define cyCapsense_1_BUTTON0_PTR2NOISE_ENVLP_OFFSET         (28u)
#define cyCapsense_1_BUTTON0_PTR2NOISE_ENVLP_SIZE           (4u)
#define cyCapsense_1_BUTTON0_PTR2NOISE_ENVLP_PARAM_ID       (0xD700001Cu)


#endif /* End CY_SENSE_cyCapsense_1_REGISTER_MAP_H */


/* [] END OF FILE */

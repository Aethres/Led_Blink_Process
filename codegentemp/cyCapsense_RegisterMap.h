/***************************************************************************//**
* \file cyCapsense_RegisterMap.h
* \version 6.0
*
* \brief
*   This file provides the definitions for the Component data structure register.
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

#if !defined(CY_SENSE_cyCapsense_REGISTER_MAP_H)
#define CY_SENSE_cyCapsense_REGISTER_MAP_H

#include <cytypes.h>
#include "cyCapsense_Configuration.h"
#include "cyCapsense_Structure.h"

/*****************************************************************************/
/* RAM Data structure register definitions                                   */
/*****************************************************************************/
#define cyCapsense_CONFIG_ID_VALUE                          (cyCapsense_dsRam.configId)
#define cyCapsense_CONFIG_ID_OFFSET                         (0u)
#define cyCapsense_CONFIG_ID_SIZE                           (2u)
#define cyCapsense_CONFIG_ID_PARAM_ID                       (0x87000000u)

#define cyCapsense_DEVICE_ID_VALUE                          (cyCapsense_dsRam.deviceId)
#define cyCapsense_DEVICE_ID_OFFSET                         (2u)
#define cyCapsense_DEVICE_ID_SIZE                           (2u)
#define cyCapsense_DEVICE_ID_PARAM_ID                       (0x8B000002u)

#define cyCapsense_HW_CLOCK_VALUE                           (cyCapsense_dsRam.hwClock)
#define cyCapsense_HW_CLOCK_OFFSET                          (4u)
#define cyCapsense_HW_CLOCK_SIZE                            (2u)
#define cyCapsense_HW_CLOCK_PARAM_ID                        (0x86000004u)

#define cyCapsense_TUNER_CMD_VALUE                          (cyCapsense_dsRam.tunerCmd)
#define cyCapsense_TUNER_CMD_OFFSET                         (6u)
#define cyCapsense_TUNER_CMD_SIZE                           (2u)
#define cyCapsense_TUNER_CMD_PARAM_ID                       (0xA1000006u)

#define cyCapsense_SCAN_COUNTER_VALUE                       (cyCapsense_dsRam.scanCounter)
#define cyCapsense_SCAN_COUNTER_OFFSET                      (8u)
#define cyCapsense_SCAN_COUNTER_SIZE                        (2u)
#define cyCapsense_SCAN_COUNTER_PARAM_ID                    (0x85000008u)

#define cyCapsense_STATUS_VALUE                             (cyCapsense_dsRam.status)
#define cyCapsense_STATUS_OFFSET                            (12u)
#define cyCapsense_STATUS_SIZE                              (4u)
#define cyCapsense_STATUS_PARAM_ID                          (0xCB00000Cu)

#define cyCapsense_WDGT_ENABLE0_VALUE                       (cyCapsense_dsRam.wdgtEnable[0u])
#define cyCapsense_WDGT_ENABLE0_OFFSET                      (16u)
#define cyCapsense_WDGT_ENABLE0_SIZE                        (4u)
#define cyCapsense_WDGT_ENABLE0_PARAM_ID                    (0xE6000010u)

#define cyCapsense_WDGT_STATUS0_VALUE                       (cyCapsense_dsRam.wdgtStatus[0u])
#define cyCapsense_WDGT_STATUS0_OFFSET                      (20u)
#define cyCapsense_WDGT_STATUS0_SIZE                        (4u)
#define cyCapsense_WDGT_STATUS0_PARAM_ID                    (0xCC000014u)

#define cyCapsense_SNS_STATUS0_VALUE                        (cyCapsense_dsRam.snsStatus[0u])
#define cyCapsense_SNS_STATUS0_OFFSET                       (24u)
#define cyCapsense_SNS_STATUS0_SIZE                         (1u)
#define cyCapsense_SNS_STATUS0_PARAM_ID                     (0x48000018u)

#define cyCapsense_SNS_STATUS1_VALUE                        (cyCapsense_dsRam.snsStatus[1u])
#define cyCapsense_SNS_STATUS1_OFFSET                       (25u)
#define cyCapsense_SNS_STATUS1_SIZE                         (1u)
#define cyCapsense_SNS_STATUS1_PARAM_ID                     (0x4E000019u)

#define cyCapsense_SNS_STATUS2_VALUE                        (cyCapsense_dsRam.snsStatus[2u])
#define cyCapsense_SNS_STATUS2_OFFSET                       (26u)
#define cyCapsense_SNS_STATUS2_SIZE                         (1u)
#define cyCapsense_SNS_STATUS2_PARAM_ID                     (0x4400001Au)

#define cyCapsense_CSD0_CONFIG_VALUE                        (cyCapsense_dsRam.csd0Config)
#define cyCapsense_CSD0_CONFIG_OFFSET                       (28u)
#define cyCapsense_CSD0_CONFIG_SIZE                         (2u)
#define cyCapsense_CSD0_CONFIG_PARAM_ID                     (0xA780001Cu)

#define cyCapsense_MOD_CSD_CLK_VALUE                        (cyCapsense_dsRam.modCsdClk)
#define cyCapsense_MOD_CSD_CLK_OFFSET                       (30u)
#define cyCapsense_MOD_CSD_CLK_SIZE                         (1u)
#define cyCapsense_MOD_CSD_CLK_PARAM_ID                     (0x6380001Eu)

#define cyCapsense_BUTTON0_RESOLUTION_VALUE                 (cyCapsense_dsRam.wdgtList.button0.resolution)
#define cyCapsense_BUTTON0_RESOLUTION_OFFSET                (32u)
#define cyCapsense_BUTTON0_RESOLUTION_SIZE                  (2u)
#define cyCapsense_BUTTON0_RESOLUTION_PARAM_ID              (0x80800020u)

#define cyCapsense_BUTTON0_FINGER_TH_VALUE                  (cyCapsense_dsRam.wdgtList.button0.fingerTh)
#define cyCapsense_BUTTON0_FINGER_TH_OFFSET                 (34u)
#define cyCapsense_BUTTON0_FINGER_TH_SIZE                   (2u)
#define cyCapsense_BUTTON0_FINGER_TH_PARAM_ID               (0x8C800022u)

#define cyCapsense_BUTTON0_NOISE_TH_VALUE                   (cyCapsense_dsRam.wdgtList.button0.noiseTh)
#define cyCapsense_BUTTON0_NOISE_TH_OFFSET                  (36u)
#define cyCapsense_BUTTON0_NOISE_TH_SIZE                    (1u)
#define cyCapsense_BUTTON0_NOISE_TH_PARAM_ID                (0x49800024u)

#define cyCapsense_BUTTON0_NNOISE_TH_VALUE                  (cyCapsense_dsRam.wdgtList.button0.nNoiseTh)
#define cyCapsense_BUTTON0_NNOISE_TH_OFFSET                 (37u)
#define cyCapsense_BUTTON0_NNOISE_TH_SIZE                   (1u)
#define cyCapsense_BUTTON0_NNOISE_TH_PARAM_ID               (0x4F800025u)

#define cyCapsense_BUTTON0_HYSTERESIS_VALUE                 (cyCapsense_dsRam.wdgtList.button0.hysteresis)
#define cyCapsense_BUTTON0_HYSTERESIS_OFFSET                (38u)
#define cyCapsense_BUTTON0_HYSTERESIS_SIZE                  (1u)
#define cyCapsense_BUTTON0_HYSTERESIS_PARAM_ID              (0x45800026u)

#define cyCapsense_BUTTON0_ON_DEBOUNCE_VALUE                (cyCapsense_dsRam.wdgtList.button0.onDebounce)
#define cyCapsense_BUTTON0_ON_DEBOUNCE_OFFSET               (39u)
#define cyCapsense_BUTTON0_ON_DEBOUNCE_SIZE                 (1u)
#define cyCapsense_BUTTON0_ON_DEBOUNCE_PARAM_ID             (0x43800027u)

#define cyCapsense_BUTTON0_LOW_BSLN_RST_VALUE               (cyCapsense_dsRam.wdgtList.button0.lowBslnRst)
#define cyCapsense_BUTTON0_LOW_BSLN_RST_OFFSET              (40u)
#define cyCapsense_BUTTON0_LOW_BSLN_RST_SIZE                (1u)
#define cyCapsense_BUTTON0_LOW_BSLN_RST_PARAM_ID            (0x4A800028u)

#define cyCapsense_BUTTON0_IDAC_MOD0_VALUE                  (cyCapsense_dsRam.wdgtList.button0.idacMod[0u])
#define cyCapsense_BUTTON0_IDAC_MOD0_OFFSET                 (41u)
#define cyCapsense_BUTTON0_IDAC_MOD0_SIZE                   (1u)
#define cyCapsense_BUTTON0_IDAC_MOD0_PARAM_ID               (0x41000029u)

#define cyCapsense_BUTTON0_SNS_CLK_VALUE                    (cyCapsense_dsRam.wdgtList.button0.snsClk)
#define cyCapsense_BUTTON0_SNS_CLK_OFFSET                   (42u)
#define cyCapsense_BUTTON0_SNS_CLK_SIZE                     (2u)
#define cyCapsense_BUTTON0_SNS_CLK_PARAM_ID                 (0x8E80002Au)

#define cyCapsense_BUTTON0_SNS_CLK_SOURCE_VALUE             (cyCapsense_dsRam.wdgtList.button0.snsClkSource)
#define cyCapsense_BUTTON0_SNS_CLK_SOURCE_OFFSET            (44u)
#define cyCapsense_BUTTON0_SNS_CLK_SOURCE_SIZE              (1u)
#define cyCapsense_BUTTON0_SNS_CLK_SOURCE_PARAM_ID          (0x4B80002Cu)

#define cyCapsense_BUTTON0_FINGER_CAP_VALUE                 (cyCapsense_dsRam.wdgtList.button0.fingerCap)
#define cyCapsense_BUTTON0_FINGER_CAP_OFFSET                (46u)
#define cyCapsense_BUTTON0_FINGER_CAP_SIZE                  (2u)
#define cyCapsense_BUTTON0_FINGER_CAP_PARAM_ID              (0xA900002Eu)

#define cyCapsense_BUTTON0_SIGPFC_VALUE                     (cyCapsense_dsRam.wdgtList.button0.sigPFC)
#define cyCapsense_BUTTON0_SIGPFC_OFFSET                    (48u)
#define cyCapsense_BUTTON0_SIGPFC_SIZE                      (2u)
#define cyCapsense_BUTTON0_SIGPFC_PARAM_ID                  (0xA3000030u)

#define cyCapsense_BUTTON1_RESOLUTION_VALUE                 (cyCapsense_dsRam.wdgtList.button1.resolution)
#define cyCapsense_BUTTON1_RESOLUTION_OFFSET                (50u)
#define cyCapsense_BUTTON1_RESOLUTION_SIZE                  (2u)
#define cyCapsense_BUTTON1_RESOLUTION_PARAM_ID              (0x8A810032u)

#define cyCapsense_BUTTON1_FINGER_TH_VALUE                  (cyCapsense_dsRam.wdgtList.button1.fingerTh)
#define cyCapsense_BUTTON1_FINGER_TH_OFFSET                 (52u)
#define cyCapsense_BUTTON1_FINGER_TH_SIZE                   (2u)
#define cyCapsense_BUTTON1_FINGER_TH_PARAM_ID               (0x87810034u)

#define cyCapsense_BUTTON1_NOISE_TH_VALUE                   (cyCapsense_dsRam.wdgtList.button1.noiseTh)
#define cyCapsense_BUTTON1_NOISE_TH_OFFSET                  (54u)
#define cyCapsense_BUTTON1_NOISE_TH_SIZE                    (1u)
#define cyCapsense_BUTTON1_NOISE_TH_PARAM_ID                (0x43810036u)

#define cyCapsense_BUTTON1_NNOISE_TH_VALUE                  (cyCapsense_dsRam.wdgtList.button1.nNoiseTh)
#define cyCapsense_BUTTON1_NNOISE_TH_OFFSET                 (55u)
#define cyCapsense_BUTTON1_NNOISE_TH_SIZE                   (1u)
#define cyCapsense_BUTTON1_NNOISE_TH_PARAM_ID               (0x45810037u)

#define cyCapsense_BUTTON1_HYSTERESIS_VALUE                 (cyCapsense_dsRam.wdgtList.button1.hysteresis)
#define cyCapsense_BUTTON1_HYSTERESIS_OFFSET                (56u)
#define cyCapsense_BUTTON1_HYSTERESIS_SIZE                  (1u)
#define cyCapsense_BUTTON1_HYSTERESIS_PARAM_ID              (0x4C810038u)

#define cyCapsense_BUTTON1_ON_DEBOUNCE_VALUE                (cyCapsense_dsRam.wdgtList.button1.onDebounce)
#define cyCapsense_BUTTON1_ON_DEBOUNCE_OFFSET               (57u)
#define cyCapsense_BUTTON1_ON_DEBOUNCE_SIZE                 (1u)
#define cyCapsense_BUTTON1_ON_DEBOUNCE_PARAM_ID             (0x4A810039u)

#define cyCapsense_BUTTON1_LOW_BSLN_RST_VALUE               (cyCapsense_dsRam.wdgtList.button1.lowBslnRst)
#define cyCapsense_BUTTON1_LOW_BSLN_RST_OFFSET              (58u)
#define cyCapsense_BUTTON1_LOW_BSLN_RST_SIZE                (1u)
#define cyCapsense_BUTTON1_LOW_BSLN_RST_PARAM_ID            (0x4081003Au)

#define cyCapsense_BUTTON1_IDAC_MOD0_VALUE                  (cyCapsense_dsRam.wdgtList.button1.idacMod[0u])
#define cyCapsense_BUTTON1_IDAC_MOD0_OFFSET                 (59u)
#define cyCapsense_BUTTON1_IDAC_MOD0_SIZE                   (1u)
#define cyCapsense_BUTTON1_IDAC_MOD0_PARAM_ID               (0x4B01003Bu)

#define cyCapsense_BUTTON1_SNS_CLK_VALUE                    (cyCapsense_dsRam.wdgtList.button1.snsClk)
#define cyCapsense_BUTTON1_SNS_CLK_OFFSET                   (60u)
#define cyCapsense_BUTTON1_SNS_CLK_SIZE                     (2u)
#define cyCapsense_BUTTON1_SNS_CLK_PARAM_ID                 (0x8581003Cu)

#define cyCapsense_BUTTON1_SNS_CLK_SOURCE_VALUE             (cyCapsense_dsRam.wdgtList.button1.snsClkSource)
#define cyCapsense_BUTTON1_SNS_CLK_SOURCE_OFFSET            (62u)
#define cyCapsense_BUTTON1_SNS_CLK_SOURCE_SIZE              (1u)
#define cyCapsense_BUTTON1_SNS_CLK_SOURCE_PARAM_ID          (0x4181003Eu)

#define cyCapsense_BUTTON1_FINGER_CAP_VALUE                 (cyCapsense_dsRam.wdgtList.button1.fingerCap)
#define cyCapsense_BUTTON1_FINGER_CAP_OFFSET                (64u)
#define cyCapsense_BUTTON1_FINGER_CAP_SIZE                  (2u)
#define cyCapsense_BUTTON1_FINGER_CAP_PARAM_ID              (0xA2010040u)

#define cyCapsense_BUTTON1_SIGPFC_VALUE                     (cyCapsense_dsRam.wdgtList.button1.sigPFC)
#define cyCapsense_BUTTON1_SIGPFC_OFFSET                    (66u)
#define cyCapsense_BUTTON1_SIGPFC_SIZE                      (2u)
#define cyCapsense_BUTTON1_SIGPFC_PARAM_ID                  (0xAE010042u)

#define cyCapsense_BUTTON2_RESOLUTION_VALUE                 (cyCapsense_dsRam.wdgtList.button2.resolution)
#define cyCapsense_BUTTON2_RESOLUTION_OFFSET                (68u)
#define cyCapsense_BUTTON2_RESOLUTION_SIZE                  (2u)
#define cyCapsense_BUTTON2_RESOLUTION_PARAM_ID              (0x80820044u)

#define cyCapsense_BUTTON2_FINGER_TH_VALUE                  (cyCapsense_dsRam.wdgtList.button2.fingerTh)
#define cyCapsense_BUTTON2_FINGER_TH_OFFSET                 (70u)
#define cyCapsense_BUTTON2_FINGER_TH_SIZE                   (2u)
#define cyCapsense_BUTTON2_FINGER_TH_PARAM_ID               (0x8C820046u)

#define cyCapsense_BUTTON2_NOISE_TH_VALUE                   (cyCapsense_dsRam.wdgtList.button2.noiseTh)
#define cyCapsense_BUTTON2_NOISE_TH_OFFSET                  (72u)
#define cyCapsense_BUTTON2_NOISE_TH_SIZE                    (1u)
#define cyCapsense_BUTTON2_NOISE_TH_PARAM_ID                (0x4B820048u)

#define cyCapsense_BUTTON2_NNOISE_TH_VALUE                  (cyCapsense_dsRam.wdgtList.button2.nNoiseTh)
#define cyCapsense_BUTTON2_NNOISE_TH_OFFSET                 (73u)
#define cyCapsense_BUTTON2_NNOISE_TH_SIZE                   (1u)
#define cyCapsense_BUTTON2_NNOISE_TH_PARAM_ID               (0x4D820049u)

#define cyCapsense_BUTTON2_HYSTERESIS_VALUE                 (cyCapsense_dsRam.wdgtList.button2.hysteresis)
#define cyCapsense_BUTTON2_HYSTERESIS_OFFSET                (74u)
#define cyCapsense_BUTTON2_HYSTERESIS_SIZE                  (1u)
#define cyCapsense_BUTTON2_HYSTERESIS_PARAM_ID              (0x4782004Au)

#define cyCapsense_BUTTON2_ON_DEBOUNCE_VALUE                (cyCapsense_dsRam.wdgtList.button2.onDebounce)
#define cyCapsense_BUTTON2_ON_DEBOUNCE_OFFSET               (75u)
#define cyCapsense_BUTTON2_ON_DEBOUNCE_SIZE                 (1u)
#define cyCapsense_BUTTON2_ON_DEBOUNCE_PARAM_ID             (0x4182004Bu)

#define cyCapsense_BUTTON2_LOW_BSLN_RST_VALUE               (cyCapsense_dsRam.wdgtList.button2.lowBslnRst)
#define cyCapsense_BUTTON2_LOW_BSLN_RST_OFFSET              (76u)
#define cyCapsense_BUTTON2_LOW_BSLN_RST_SIZE                (1u)
#define cyCapsense_BUTTON2_LOW_BSLN_RST_PARAM_ID            (0x4A82004Cu)

#define cyCapsense_BUTTON2_IDAC_MOD0_VALUE                  (cyCapsense_dsRam.wdgtList.button2.idacMod[0u])
#define cyCapsense_BUTTON2_IDAC_MOD0_OFFSET                 (77u)
#define cyCapsense_BUTTON2_IDAC_MOD0_SIZE                   (1u)
#define cyCapsense_BUTTON2_IDAC_MOD0_PARAM_ID               (0x4102004Du)

#define cyCapsense_BUTTON2_SNS_CLK_VALUE                    (cyCapsense_dsRam.wdgtList.button2.snsClk)
#define cyCapsense_BUTTON2_SNS_CLK_OFFSET                   (78u)
#define cyCapsense_BUTTON2_SNS_CLK_SIZE                     (2u)
#define cyCapsense_BUTTON2_SNS_CLK_PARAM_ID                 (0x8E82004Eu)

#define cyCapsense_BUTTON2_SNS_CLK_SOURCE_VALUE             (cyCapsense_dsRam.wdgtList.button2.snsClkSource)
#define cyCapsense_BUTTON2_SNS_CLK_SOURCE_OFFSET            (80u)
#define cyCapsense_BUTTON2_SNS_CLK_SOURCE_SIZE              (1u)
#define cyCapsense_BUTTON2_SNS_CLK_SOURCE_PARAM_ID          (0x4C820050u)

#define cyCapsense_BUTTON2_FINGER_CAP_VALUE                 (cyCapsense_dsRam.wdgtList.button2.fingerCap)
#define cyCapsense_BUTTON2_FINGER_CAP_OFFSET                (82u)
#define cyCapsense_BUTTON2_FINGER_CAP_SIZE                  (2u)
#define cyCapsense_BUTTON2_FINGER_CAP_PARAM_ID              (0xAE020052u)

#define cyCapsense_BUTTON2_SIGPFC_VALUE                     (cyCapsense_dsRam.wdgtList.button2.sigPFC)
#define cyCapsense_BUTTON2_SIGPFC_OFFSET                    (84u)
#define cyCapsense_BUTTON2_SIGPFC_SIZE                      (2u)
#define cyCapsense_BUTTON2_SIGPFC_PARAM_ID                  (0xA3020054u)

#define cyCapsense_BUTTON0_SNS0_RAW0_VALUE                  (cyCapsense_dsRam.snsList.button0[0u].raw[0u])
#define cyCapsense_BUTTON0_SNS0_RAW0_OFFSET                 (86u)
#define cyCapsense_BUTTON0_SNS0_RAW0_SIZE                   (2u)
#define cyCapsense_BUTTON0_SNS0_RAW0_PARAM_ID               (0x82000056u)

#define cyCapsense_BUTTON0_SNS0_BSLN0_VALUE                 (cyCapsense_dsRam.snsList.button0[0u].bsln[0u])
#define cyCapsense_BUTTON0_SNS0_BSLN0_OFFSET                (88u)
#define cyCapsense_BUTTON0_SNS0_BSLN0_SIZE                  (2u)
#define cyCapsense_BUTTON0_SNS0_BSLN0_PARAM_ID              (0x8D000058u)

#define cyCapsense_BUTTON0_SNS0_BSLN_EXT0_VALUE             (cyCapsense_dsRam.snsList.button0[0u].bslnExt[0u])
#define cyCapsense_BUTTON0_SNS0_BSLN_EXT0_OFFSET            (90u)
#define cyCapsense_BUTTON0_SNS0_BSLN_EXT0_SIZE              (1u)
#define cyCapsense_BUTTON0_SNS0_BSLN_EXT0_PARAM_ID          (0x4900005Au)

#define cyCapsense_BUTTON0_SNS0_DIFF_VALUE                  (cyCapsense_dsRam.snsList.button0[0u].diff)
#define cyCapsense_BUTTON0_SNS0_DIFF_OFFSET                 (92u)
#define cyCapsense_BUTTON0_SNS0_DIFF_SIZE                   (2u)
#define cyCapsense_BUTTON0_SNS0_DIFF_PARAM_ID               (0x8C00005Cu)

#define cyCapsense_BUTTON0_SNS0_NEG_BSLN_RST_CNT0_VALUE     (cyCapsense_dsRam.snsList.button0[0u].negBslnRstCnt[0u])
#define cyCapsense_BUTTON0_SNS0_NEG_BSLN_RST_CNT0_OFFSET    (94u)
#define cyCapsense_BUTTON0_SNS0_NEG_BSLN_RST_CNT0_SIZE      (1u)
#define cyCapsense_BUTTON0_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID  (0x4800005Eu)

#define cyCapsense_BUTTON1_SNS0_RAW0_VALUE                  (cyCapsense_dsRam.snsList.button1[0u].raw[0u])
#define cyCapsense_BUTTON1_SNS0_RAW0_OFFSET                 (96u)
#define cyCapsense_BUTTON1_SNS0_RAW0_SIZE                   (2u)
#define cyCapsense_BUTTON1_SNS0_RAW0_PARAM_ID               (0x80000060u)

#define cyCapsense_BUTTON1_SNS0_BSLN0_VALUE                 (cyCapsense_dsRam.snsList.button1[0u].bsln[0u])
#define cyCapsense_BUTTON1_SNS0_BSLN0_OFFSET                (98u)
#define cyCapsense_BUTTON1_SNS0_BSLN0_SIZE                  (2u)
#define cyCapsense_BUTTON1_SNS0_BSLN0_PARAM_ID              (0x8C000062u)

#define cyCapsense_BUTTON1_SNS0_BSLN_EXT0_VALUE             (cyCapsense_dsRam.snsList.button1[0u].bslnExt[0u])
#define cyCapsense_BUTTON1_SNS0_BSLN_EXT0_OFFSET            (100u)
#define cyCapsense_BUTTON1_SNS0_BSLN_EXT0_SIZE              (1u)
#define cyCapsense_BUTTON1_SNS0_BSLN_EXT0_PARAM_ID          (0x49000064u)

#define cyCapsense_BUTTON1_SNS0_DIFF_VALUE                  (cyCapsense_dsRam.snsList.button1[0u].diff)
#define cyCapsense_BUTTON1_SNS0_DIFF_OFFSET                 (102u)
#define cyCapsense_BUTTON1_SNS0_DIFF_SIZE                   (2u)
#define cyCapsense_BUTTON1_SNS0_DIFF_PARAM_ID               (0x8D000066u)

#define cyCapsense_BUTTON1_SNS0_NEG_BSLN_RST_CNT0_VALUE     (cyCapsense_dsRam.snsList.button1[0u].negBslnRstCnt[0u])
#define cyCapsense_BUTTON1_SNS0_NEG_BSLN_RST_CNT0_OFFSET    (104u)
#define cyCapsense_BUTTON1_SNS0_NEG_BSLN_RST_CNT0_SIZE      (1u)
#define cyCapsense_BUTTON1_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID  (0x4A000068u)

#define cyCapsense_BUTTON2_SNS0_RAW0_VALUE                  (cyCapsense_dsRam.snsList.button2[0u].raw[0u])
#define cyCapsense_BUTTON2_SNS0_RAW0_OFFSET                 (106u)
#define cyCapsense_BUTTON2_SNS0_RAW0_SIZE                   (2u)
#define cyCapsense_BUTTON2_SNS0_RAW0_PARAM_ID               (0x8E00006Au)

#define cyCapsense_BUTTON2_SNS0_BSLN0_VALUE                 (cyCapsense_dsRam.snsList.button2[0u].bsln[0u])
#define cyCapsense_BUTTON2_SNS0_BSLN0_OFFSET                (108u)
#define cyCapsense_BUTTON2_SNS0_BSLN0_SIZE                  (2u)
#define cyCapsense_BUTTON2_SNS0_BSLN0_PARAM_ID              (0x8300006Cu)

#define cyCapsense_BUTTON2_SNS0_BSLN_EXT0_VALUE             (cyCapsense_dsRam.snsList.button2[0u].bslnExt[0u])
#define cyCapsense_BUTTON2_SNS0_BSLN_EXT0_OFFSET            (110u)
#define cyCapsense_BUTTON2_SNS0_BSLN_EXT0_SIZE              (1u)
#define cyCapsense_BUTTON2_SNS0_BSLN_EXT0_PARAM_ID          (0x4700006Eu)

#define cyCapsense_BUTTON2_SNS0_DIFF_VALUE                  (cyCapsense_dsRam.snsList.button2[0u].diff)
#define cyCapsense_BUTTON2_SNS0_DIFF_OFFSET                 (112u)
#define cyCapsense_BUTTON2_SNS0_DIFF_SIZE                   (2u)
#define cyCapsense_BUTTON2_SNS0_DIFF_PARAM_ID               (0x85000070u)

#define cyCapsense_BUTTON2_SNS0_NEG_BSLN_RST_CNT0_VALUE     (cyCapsense_dsRam.snsList.button2[0u].negBslnRstCnt[0u])
#define cyCapsense_BUTTON2_SNS0_NEG_BSLN_RST_CNT0_OFFSET    (114u)
#define cyCapsense_BUTTON2_SNS0_NEG_BSLN_RST_CNT0_SIZE      (1u)
#define cyCapsense_BUTTON2_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID  (0x41000072u)

#define cyCapsense_SNR_TEST_WIDGET_ID_VALUE                 (cyCapsense_dsRam.snrTestWidgetId)
#define cyCapsense_SNR_TEST_WIDGET_ID_OFFSET                (116u)
#define cyCapsense_SNR_TEST_WIDGET_ID_SIZE                  (1u)
#define cyCapsense_SNR_TEST_WIDGET_ID_PARAM_ID              (0x67000074u)

#define cyCapsense_SNR_TEST_SENSOR_ID_VALUE                 (cyCapsense_dsRam.snrTestSensorId)
#define cyCapsense_SNR_TEST_SENSOR_ID_OFFSET                (117u)
#define cyCapsense_SNR_TEST_SENSOR_ID_SIZE                  (1u)
#define cyCapsense_SNR_TEST_SENSOR_ID_PARAM_ID              (0x61000075u)

#define cyCapsense_SNR_TEST_SCAN_COUNTER_VALUE              (cyCapsense_dsRam.snrTestScanCounter)
#define cyCapsense_SNR_TEST_SCAN_COUNTER_OFFSET             (118u)
#define cyCapsense_SNR_TEST_SCAN_COUNTER_SIZE               (2u)
#define cyCapsense_SNR_TEST_SCAN_COUNTER_PARAM_ID           (0x88000076u)

#define cyCapsense_SNR_TEST_RAW_COUNT0_VALUE                (cyCapsense_dsRam.snrTestRawCount[0u])
#define cyCapsense_SNR_TEST_RAW_COUNT0_OFFSET               (120u)
#define cyCapsense_SNR_TEST_RAW_COUNT0_SIZE                 (2u)
#define cyCapsense_SNR_TEST_RAW_COUNT0_PARAM_ID             (0x87000078u)


/*****************************************************************************/
/* Flash Data structure register definitions                                 */
/*****************************************************************************/
#define cyCapsense_BUTTON0_PTR2SNS_FLASH_VALUE              (cyCapsense_dsFlash.wdgtArray[0].ptr2SnsFlash)
#define cyCapsense_BUTTON0_PTR2SNS_FLASH_OFFSET             (0u)
#define cyCapsense_BUTTON0_PTR2SNS_FLASH_SIZE               (4u)
#define cyCapsense_BUTTON0_PTR2SNS_FLASH_PARAM_ID           (0xD1000000u)

#define cyCapsense_BUTTON0_PTR2WD_RAM_VALUE                 (cyCapsense_dsFlash.wdgtArray[0].ptr2WdgtRam)
#define cyCapsense_BUTTON0_PTR2WD_RAM_OFFSET                (4u)
#define cyCapsense_BUTTON0_PTR2WD_RAM_SIZE                  (4u)
#define cyCapsense_BUTTON0_PTR2WD_RAM_PARAM_ID              (0xD0000004u)

#define cyCapsense_BUTTON0_PTR2SNS_RAM_VALUE                (cyCapsense_dsFlash.wdgtArray[0].ptr2SnsRam)
#define cyCapsense_BUTTON0_PTR2SNS_RAM_OFFSET               (8u)
#define cyCapsense_BUTTON0_PTR2SNS_RAM_SIZE                 (4u)
#define cyCapsense_BUTTON0_PTR2SNS_RAM_PARAM_ID             (0xD3000008u)

#define cyCapsense_BUTTON0_PTR2FLTR_HISTORY_VALUE           (cyCapsense_dsFlash.wdgtArray[0].ptr2FltrHistory)
#define cyCapsense_BUTTON0_PTR2FLTR_HISTORY_OFFSET          (12u)
#define cyCapsense_BUTTON0_PTR2FLTR_HISTORY_SIZE            (4u)
#define cyCapsense_BUTTON0_PTR2FLTR_HISTORY_PARAM_ID        (0xD200000Cu)

#define cyCapsense_BUTTON0_PTR2DEBOUNCE_VALUE               (cyCapsense_dsFlash.wdgtArray[0].ptr2DebounceArr)
#define cyCapsense_BUTTON0_PTR2DEBOUNCE_OFFSET              (16u)
#define cyCapsense_BUTTON0_PTR2DEBOUNCE_SIZE                (4u)
#define cyCapsense_BUTTON0_PTR2DEBOUNCE_PARAM_ID            (0xD4000010u)

#define cyCapsense_BUTTON0_STATIC_CONFIG_VALUE              (cyCapsense_dsFlash.wdgtArray[0].staticConfig)
#define cyCapsense_BUTTON0_STATIC_CONFIG_OFFSET             (20u)
#define cyCapsense_BUTTON0_STATIC_CONFIG_SIZE               (4u)
#define cyCapsense_BUTTON0_STATIC_CONFIG_PARAM_ID           (0xD5000014u)

#define cyCapsense_BUTTON0_TOTAL_NUM_SNS_VALUE              (cyCapsense_dsFlash.wdgtArray[0].totalNumSns)
#define cyCapsense_BUTTON0_TOTAL_NUM_SNS_OFFSET             (24u)
#define cyCapsense_BUTTON0_TOTAL_NUM_SNS_SIZE               (2u)
#define cyCapsense_BUTTON0_TOTAL_NUM_SNS_PARAM_ID           (0x99000018u)

#define cyCapsense_BUTTON0_TYPE_VALUE                       (cyCapsense_dsFlash.wdgtArray[0].wdgtType)
#define cyCapsense_BUTTON0_TYPE_OFFSET                      (26u)
#define cyCapsense_BUTTON0_TYPE_SIZE                        (1u)
#define cyCapsense_BUTTON0_TYPE_PARAM_ID                    (0x5D00001Au)

#define cyCapsense_BUTTON0_NUM_COLS_VALUE                   (cyCapsense_dsFlash.wdgtArray[0].numCols)
#define cyCapsense_BUTTON0_NUM_COLS_OFFSET                  (27u)
#define cyCapsense_BUTTON0_NUM_COLS_SIZE                    (1u)
#define cyCapsense_BUTTON0_NUM_COLS_PARAM_ID                (0x5B00001Bu)

#define cyCapsense_BUTTON0_PTR2NOISE_ENVLP_VALUE            (cyCapsense_dsFlash.wdgtArray[0].ptr2NoiseEnvlp)
#define cyCapsense_BUTTON0_PTR2NOISE_ENVLP_OFFSET           (28u)
#define cyCapsense_BUTTON0_PTR2NOISE_ENVLP_SIZE             (4u)
#define cyCapsense_BUTTON0_PTR2NOISE_ENVLP_PARAM_ID         (0xD700001Cu)

#define cyCapsense_BUTTON1_PTR2SNS_FLASH_VALUE              (cyCapsense_dsFlash.wdgtArray[1].ptr2SnsFlash)
#define cyCapsense_BUTTON1_PTR2SNS_FLASH_OFFSET             (32u)
#define cyCapsense_BUTTON1_PTR2SNS_FLASH_SIZE               (4u)
#define cyCapsense_BUTTON1_PTR2SNS_FLASH_PARAM_ID           (0xD8010020u)

#define cyCapsense_BUTTON1_PTR2WD_RAM_VALUE                 (cyCapsense_dsFlash.wdgtArray[1].ptr2WdgtRam)
#define cyCapsense_BUTTON1_PTR2WD_RAM_OFFSET                (36u)
#define cyCapsense_BUTTON1_PTR2WD_RAM_SIZE                  (4u)
#define cyCapsense_BUTTON1_PTR2WD_RAM_PARAM_ID              (0xD9010024u)

#define cyCapsense_BUTTON1_PTR2SNS_RAM_VALUE                (cyCapsense_dsFlash.wdgtArray[1].ptr2SnsRam)
#define cyCapsense_BUTTON1_PTR2SNS_RAM_OFFSET               (40u)
#define cyCapsense_BUTTON1_PTR2SNS_RAM_SIZE                 (4u)
#define cyCapsense_BUTTON1_PTR2SNS_RAM_PARAM_ID             (0xDA010028u)

#define cyCapsense_BUTTON1_PTR2FLTR_HISTORY_VALUE           (cyCapsense_dsFlash.wdgtArray[1].ptr2FltrHistory)
#define cyCapsense_BUTTON1_PTR2FLTR_HISTORY_OFFSET          (44u)
#define cyCapsense_BUTTON1_PTR2FLTR_HISTORY_SIZE            (4u)
#define cyCapsense_BUTTON1_PTR2FLTR_HISTORY_PARAM_ID        (0xDB01002Cu)

#define cyCapsense_BUTTON1_PTR2DEBOUNCE_VALUE               (cyCapsense_dsFlash.wdgtArray[1].ptr2DebounceArr)
#define cyCapsense_BUTTON1_PTR2DEBOUNCE_OFFSET              (48u)
#define cyCapsense_BUTTON1_PTR2DEBOUNCE_SIZE                (4u)
#define cyCapsense_BUTTON1_PTR2DEBOUNCE_PARAM_ID            (0xDD010030u)

#define cyCapsense_BUTTON1_STATIC_CONFIG_VALUE              (cyCapsense_dsFlash.wdgtArray[1].staticConfig)
#define cyCapsense_BUTTON1_STATIC_CONFIG_OFFSET             (52u)
#define cyCapsense_BUTTON1_STATIC_CONFIG_SIZE               (4u)
#define cyCapsense_BUTTON1_STATIC_CONFIG_PARAM_ID           (0xDC010034u)

#define cyCapsense_BUTTON1_TOTAL_NUM_SNS_VALUE              (cyCapsense_dsFlash.wdgtArray[1].totalNumSns)
#define cyCapsense_BUTTON1_TOTAL_NUM_SNS_OFFSET             (56u)
#define cyCapsense_BUTTON1_TOTAL_NUM_SNS_SIZE               (2u)
#define cyCapsense_BUTTON1_TOTAL_NUM_SNS_PARAM_ID           (0x90010038u)

#define cyCapsense_BUTTON1_TYPE_VALUE                       (cyCapsense_dsFlash.wdgtArray[1].wdgtType)
#define cyCapsense_BUTTON1_TYPE_OFFSET                      (58u)
#define cyCapsense_BUTTON1_TYPE_SIZE                        (1u)
#define cyCapsense_BUTTON1_TYPE_PARAM_ID                    (0x5401003Au)

#define cyCapsense_BUTTON1_NUM_COLS_VALUE                   (cyCapsense_dsFlash.wdgtArray[1].numCols)
#define cyCapsense_BUTTON1_NUM_COLS_OFFSET                  (59u)
#define cyCapsense_BUTTON1_NUM_COLS_SIZE                    (1u)
#define cyCapsense_BUTTON1_NUM_COLS_PARAM_ID                (0x5201003Bu)

#define cyCapsense_BUTTON1_PTR2NOISE_ENVLP_VALUE            (cyCapsense_dsFlash.wdgtArray[1].ptr2NoiseEnvlp)
#define cyCapsense_BUTTON1_PTR2NOISE_ENVLP_OFFSET           (60u)
#define cyCapsense_BUTTON1_PTR2NOISE_ENVLP_SIZE             (4u)
#define cyCapsense_BUTTON1_PTR2NOISE_ENVLP_PARAM_ID         (0xDE01003Cu)

#define cyCapsense_BUTTON2_PTR2SNS_FLASH_VALUE              (cyCapsense_dsFlash.wdgtArray[2].ptr2SnsFlash)
#define cyCapsense_BUTTON2_PTR2SNS_FLASH_OFFSET             (64u)
#define cyCapsense_BUTTON2_PTR2SNS_FLASH_SIZE               (4u)
#define cyCapsense_BUTTON2_PTR2SNS_FLASH_PARAM_ID           (0xDA020040u)

#define cyCapsense_BUTTON2_PTR2WD_RAM_VALUE                 (cyCapsense_dsFlash.wdgtArray[2].ptr2WdgtRam)
#define cyCapsense_BUTTON2_PTR2WD_RAM_OFFSET                (68u)
#define cyCapsense_BUTTON2_PTR2WD_RAM_SIZE                  (4u)
#define cyCapsense_BUTTON2_PTR2WD_RAM_PARAM_ID              (0xDB020044u)

#define cyCapsense_BUTTON2_PTR2SNS_RAM_VALUE                (cyCapsense_dsFlash.wdgtArray[2].ptr2SnsRam)
#define cyCapsense_BUTTON2_PTR2SNS_RAM_OFFSET               (72u)
#define cyCapsense_BUTTON2_PTR2SNS_RAM_SIZE                 (4u)
#define cyCapsense_BUTTON2_PTR2SNS_RAM_PARAM_ID             (0xD8020048u)

#define cyCapsense_BUTTON2_PTR2FLTR_HISTORY_VALUE           (cyCapsense_dsFlash.wdgtArray[2].ptr2FltrHistory)
#define cyCapsense_BUTTON2_PTR2FLTR_HISTORY_OFFSET          (76u)
#define cyCapsense_BUTTON2_PTR2FLTR_HISTORY_SIZE            (4u)
#define cyCapsense_BUTTON2_PTR2FLTR_HISTORY_PARAM_ID        (0xD902004Cu)

#define cyCapsense_BUTTON2_PTR2DEBOUNCE_VALUE               (cyCapsense_dsFlash.wdgtArray[2].ptr2DebounceArr)
#define cyCapsense_BUTTON2_PTR2DEBOUNCE_OFFSET              (80u)
#define cyCapsense_BUTTON2_PTR2DEBOUNCE_SIZE                (4u)
#define cyCapsense_BUTTON2_PTR2DEBOUNCE_PARAM_ID            (0xDF020050u)

#define cyCapsense_BUTTON2_STATIC_CONFIG_VALUE              (cyCapsense_dsFlash.wdgtArray[2].staticConfig)
#define cyCapsense_BUTTON2_STATIC_CONFIG_OFFSET             (84u)
#define cyCapsense_BUTTON2_STATIC_CONFIG_SIZE               (4u)
#define cyCapsense_BUTTON2_STATIC_CONFIG_PARAM_ID           (0xDE020054u)

#define cyCapsense_BUTTON2_TOTAL_NUM_SNS_VALUE              (cyCapsense_dsFlash.wdgtArray[2].totalNumSns)
#define cyCapsense_BUTTON2_TOTAL_NUM_SNS_OFFSET             (88u)
#define cyCapsense_BUTTON2_TOTAL_NUM_SNS_SIZE               (2u)
#define cyCapsense_BUTTON2_TOTAL_NUM_SNS_PARAM_ID           (0x92020058u)

#define cyCapsense_BUTTON2_TYPE_VALUE                       (cyCapsense_dsFlash.wdgtArray[2].wdgtType)
#define cyCapsense_BUTTON2_TYPE_OFFSET                      (90u)
#define cyCapsense_BUTTON2_TYPE_SIZE                        (1u)
#define cyCapsense_BUTTON2_TYPE_PARAM_ID                    (0x5602005Au)

#define cyCapsense_BUTTON2_NUM_COLS_VALUE                   (cyCapsense_dsFlash.wdgtArray[2].numCols)
#define cyCapsense_BUTTON2_NUM_COLS_OFFSET                  (91u)
#define cyCapsense_BUTTON2_NUM_COLS_SIZE                    (1u)
#define cyCapsense_BUTTON2_NUM_COLS_PARAM_ID                (0x5002005Bu)

#define cyCapsense_BUTTON2_PTR2NOISE_ENVLP_VALUE            (cyCapsense_dsFlash.wdgtArray[2].ptr2NoiseEnvlp)
#define cyCapsense_BUTTON2_PTR2NOISE_ENVLP_OFFSET           (92u)
#define cyCapsense_BUTTON2_PTR2NOISE_ENVLP_SIZE             (4u)
#define cyCapsense_BUTTON2_PTR2NOISE_ENVLP_PARAM_ID         (0xDC02005Cu)


#endif /* End CY_SENSE_cyCapsense_REGISTER_MAP_H */


/* [] END OF FILE */

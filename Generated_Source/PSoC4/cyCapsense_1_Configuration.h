/*******************************************************************************
* \file cyCapsense_1_Configuration.h
* \version 6.0
*
* \brief
*   This file provides the customizer parameters definitions.
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

#if !defined(CY_SENSE_cyCapsense_1_CONFIGURATION_H)
#define CY_SENSE_cyCapsense_1_CONFIGURATION_H

#include <cytypes.h>

/*******************************************************************************
* Customizer-generated defines
*******************************************************************************/
#define cyCapsense_1_ENABLE                             (1u)
#define cyCapsense_1_DISABLE                            (0u)

#define cyCapsense_1_THIRD_GENERATION_BLOCK             (1u)
#define cyCapsense_1_FOURTH_GENERATION_BLOCK            (2u)

#define cyCapsense_1_GENERATION_BLOCK_VERSION           (1u)

/*******************************************************************************
* HW IP block global defines
*******************************************************************************/

#if (cyCapsense_1_GENERATION_BLOCK_VERSION == cyCapsense_1_THIRD_GENERATION_BLOCK)
    #define cyCapsense_1_CSDV1                          (cyCapsense_1_ENABLE)
    
    #ifdef CYIPBLOCK_m0s8csd_VERSION
        #if (0u == CYIPBLOCK_m0s8csd_VERSION)
            #define cyCapsense_1_CSDV1_VER1             (cyCapsense_1_ENABLE)
            #define cyCapsense_1_CSDV1_VER2             (cyCapsense_1_DISABLE)
        #else
            #define cyCapsense_1_CSDV1_VER1             (cyCapsense_1_DISABLE)
            #define cyCapsense_1_CSDV1_VER2             (cyCapsense_1_ENABLE)
        #endif
    #else
        #error "HW IP block version is not specified"
    #endif
#else
    #define cyCapsense_1_CSDV1                          (cyCapsense_1_DISABLE)
    #define cyCapsense_1_CSDV1_VER1                     (cyCapsense_1_DISABLE)
    #define cyCapsense_1_CSDV1_VER2                     (cyCapsense_1_DISABLE)
#endif

#if (cyCapsense_1_GENERATION_BLOCK_VERSION == cyCapsense_1_FOURTH_GENERATION_BLOCK)
    #define cyCapsense_1_CSDV2                          (cyCapsense_1_ENABLE)
    
    #ifdef CYIPBLOCK_m0s8csdv2_VERSION
        #if (1u == CYIPBLOCK_m0s8csdv2_VERSION)
            #define cyCapsense_1_CSDV2_VER1             (cyCapsense_1_ENABLE)
        #else
            #define cyCapsense_1_CSDV2_VER1             (cyCapsense_1_DISABLE)
        #endif
        #if (2u == CYIPBLOCK_m0s8csdv2_VERSION)
            #define cyCapsense_1_CSDV2_VER2             (cyCapsense_1_ENABLE)
        #else
            #define cyCapsense_1_CSDV2_VER2             (cyCapsense_1_DISABLE)
        #endif
    #else
        #error "HW IP block version is not specified"
    #endif
#else
    #define cyCapsense_1_CSDV2                          (cyCapsense_1_DISABLE)
    #define cyCapsense_1_CSDV2_VER1                     (cyCapsense_1_DISABLE)
    #define cyCapsense_1_CSDV2_VER2                     (cyCapsense_1_DISABLE)
#endif

/*******************************************************************************
* Project-global defines
*******************************************************************************/

#define cyCapsense_1_2000_MV                            (2000u)

#ifdef CYDEV_VDDA_MV
    #define cyCapsense_1_CYDEV_VDDA_MV                  (CYDEV_VDDA_MV)
#else
    #ifdef CYDEV_VDD_MV
        #define cyCapsense_1_CYDEV_VDDA_MV              (CYDEV_VDD_MV)
    #endif
#endif

#define cyCapsense_1_BAD_CONVERSIONS_NUM                (1u)
#define cyCapsense_1_RESAMPLING_CYCLES_MAX_NUMBER       (1u)


/*******************************************************************************
* Enabled Scan Methods
*******************************************************************************/
#define cyCapsense_1_CSD_EN                             (1u)
#define cyCapsense_1_CSX_EN                             (0u)
#define cyCapsense_1_ISX_EN                             (0u)
#define cyCapsense_1_CSD_CSX_EN                         (cyCapsense_1_CSD_EN && cyCapsense_1_CSX_EN)

#define cyCapsense_1_MANY_SENSE_MODES_EN                ((cyCapsense_1_CSD_EN && cyCapsense_1_CSX_EN) || \
                                                             (cyCapsense_1_CSD_EN && cyCapsense_1_ISX_EN) || \
                                                             (cyCapsense_1_CSX_EN && cyCapsense_1_ISX_EN) || \
                                                             (cyCapsense_1_SELF_TEST_EN))

#define cyCapsense_1_MANY_WIDGET_METHODS_EN             ((cyCapsense_1_CSD_EN && cyCapsense_1_CSX_EN) || \
                                                             (cyCapsense_1_CSD_EN && cyCapsense_1_ISX_EN) || \
                                                             (cyCapsense_1_CSX_EN && cyCapsense_1_ISX_EN))

#define cyCapsense_1_CSD2X_EN                           (0u)
#define cyCapsense_1_CSX2X_EN                           (0u)

/*******************************************************************************
* Definitions for number of widgets and sensors
*******************************************************************************/
#define cyCapsense_1_TOTAL_WIDGETS                      (1u)
#define cyCapsense_1_TOTAL_CSD_WIDGETS                  (1u)
#define cyCapsense_1_TOTAL_CSD_SENSORS                  (1u)
#define cyCapsense_1_TOTAL_CSX_WIDGETS                  (0u)
#define cyCapsense_1_TOTAL_ISX_WIDGETS                  (0u)
#define cyCapsense_1_TOTAL_CSX_NODES                    (0u)
#define cyCapsense_1_TOTAL_ISX_NODES                    (0u)

/*******************************************************************************
* Total number of CSD sensors + CSX nodes
*******************************************************************************/
#define cyCapsense_1_TOTAL_SENSORS            (cyCapsense_1_TOTAL_CSD_SENSORS + \
                                                   cyCapsense_1_TOTAL_CSX_NODES+ \
                                                   cyCapsense_1_TOTAL_ISX_NODES)

/*******************************************************************************
* Total number of scan slots (used only when dual-channel scan is enabled)
*******************************************************************************/
#define cyCapsense_1_TOTAL_SCAN_SLOTS         (1u)

/*******************************************************************************
* Defines widget IDs
*******************************************************************************/
#define cyCapsense_1_BUTTON0_WDGT_ID            (0u)

/*******************************************************************************
* Defines sensor IDs
*******************************************************************************/

/* Button0 sensor names */
#define cyCapsense_1_BUTTON0_SNS0_ID            (0u)



/*******************************************************************************
* Enabled widget types
*******************************************************************************/
#define cyCapsense_1_BUTTON_WIDGET_EN         (1u)
#define cyCapsense_1_SLIDER_WIDGET_EN         (0u)
#define cyCapsense_1_MATRIX_WIDGET_EN         (0u)
#define cyCapsense_1_PROXIMITY_WIDGET_EN      (0u)
#define cyCapsense_1_TOUCHPAD_WIDGET_EN       (0u)
#define cyCapsense_1_ENCODERDIAL_WIDGET_EN    (0u)

#define cyCapsense_1_CSD_MATRIX_WIDGET_EN     (0u)
#define cyCapsense_1_CSD_TOUCHPAD_WIDGET_EN   (0u)

#define cyCapsense_1_CSX_MATRIX_WIDGET_EN     (0u)
#define cyCapsense_1_CSX_TOUCHPAD_WIDGET_EN   (0u)

/*******************************************************************************
* Centroid APIs
*******************************************************************************/
#define cyCapsense_1_CENTROID_EN              (0u)
#define cyCapsense_1_TOTAL_DIPLEXED_SLIDERS   (0u)
#define cyCapsense_1_TOTAL_LINEAR_SLIDERS     (0u)
#define cyCapsense_1_TOTAL_RADIAL_SLIDERS     (0u)
#define cyCapsense_1_TOTAL_TOUCHPADS          (0u)
#define cyCapsense_1_MAX_CENTROID_LENGTH      (0u)
#define cyCapsense_1_SLIDER_MULT_METHOD       (0u)
#define cyCapsense_1_TOUCHPAD_MULT_METHOD     (0u)

/*******************************************************************************
* Enabled sensor types
*******************************************************************************/
#define cyCapsense_1_REGULAR_SENSOR_EN        (1u)
#define cyCapsense_1_PROXIMITY_SENSOR_EN      (0u)

/*******************************************************************************
* Sensor ganging
*******************************************************************************/
#define cyCapsense_1_GANGED_SNS_EN            (0u)
#define cyCapsense_1_CSD_GANGED_SNS_EN        (0u)
#define cyCapsense_1_CSX_GANGED_SNS_EN        (0u)

/*******************************************************************************
* Max number of sensors used among all the widgets
*******************************************************************************/
#define cyCapsense_1_MAX_SENSORS_PER_WIDGET   (1u)
#define cyCapsense_1_MAX_SENSORS_PER_5X5_TOUCHPAD (1u)

/*******************************************************************************
* Total number of all used electrodes (NOT unique)
*******************************************************************************/
#define cyCapsense_1_TOTAL_ELECTRODES         (1u)
/* Obsolete */
#define cyCapsense_1_TOTAL_SENSOR_IOS         cyCapsense_1_TOTAL_ELECTRODES

/*******************************************************************************
* Total number of used physical IOs (unique)
*******************************************************************************/
#define cyCapsense_1_TOTAL_IO_CNT             (1u)

/*******************************************************************************
* Array length for widget status registers
*******************************************************************************/
#define cyCapsense_1_WDGT_STATUS_WORDS        \
                        (((uint8)((cyCapsense_1_TOTAL_WIDGETS - 1u) / 32u)) + 1u)


/*******************************************************************************
* Auto-tuning mode selection
*******************************************************************************/
#define cyCapsense_1_CSD_SS_DIS         (0x00ul)
#define cyCapsense_1_CSD_SS_HW_EN       (0x01ul)
#define cyCapsense_1_CSD_SS_TH_EN       (0x02ul)
#define cyCapsense_1_CSD_SS_HWTH_EN     (cyCapsense_1_CSD_SS_HW_EN | \
                                             cyCapsense_1_CSD_SS_TH_EN)

#define cyCapsense_1_CSD_AUTOTUNE       cyCapsense_1_CSD_SS_HWTH_EN


/*******************************************************************************
* General settings
*******************************************************************************/

#define cyCapsense_1_AUTO_RESET_METHOD_LEGACY (0u)
#define cyCapsense_1_AUTO_RESET_METHOD_SAMPLE (1u)

#define cyCapsense_1_MULTI_FREQ_SCAN_EN       (0u)
#define cyCapsense_1_SENSOR_AUTO_RESET_EN     (0u)
#define cyCapsense_1_SENSOR_AUTO_RESET_METHOD (0u)
#define cyCapsense_1_NUM_CENTROIDS            (1u)
#define cyCapsense_1_4PTS_LOCAL_MAX_EN        (0u)
#define cyCapsense_1_OFF_DEBOUNCE_EN          (0u)
#define cyCapsense_1_CUSTOM_DS_RAM_SIZE       (0u)

/* Defines power status of HW block after scanning */
#define cyCapsense_1_BLOCK_OFF_AFTER_SCAN_EN  (0u)

/* Defines number of scan frequencies */
#if (cyCapsense_1_DISABLE != cyCapsense_1_MULTI_FREQ_SCAN_EN)
    #define cyCapsense_1_NUM_SCAN_FREQS       (3u)
#else
    #define cyCapsense_1_NUM_SCAN_FREQS       (1u)
#endif /* #if (cyCapsense_1_DISABLE != cyCapsense_1_MULTI_FREQ_SCAN_EN) */

/* Data size for thresholds / low baseline reset */
#define cyCapsense_1_SIZE_8BITS               (8u)
#define cyCapsense_1_SIZE_16BITS              (16u)

#define cyCapsense_1_THRESHOLD_SIZE           cyCapsense_1_SIZE_16BITS
typedef uint16 cyCapsense_1_THRESHOLD_TYPE;

#if (cyCapsense_1_AUTO_RESET_METHOD_LEGACY == cyCapsense_1_SENSOR_AUTO_RESET_METHOD)
    #define cyCapsense_1_LOW_BSLN_RST_SIZE        cyCapsense_1_SIZE_8BITS
    typedef uint8 cyCapsense_1_LOW_BSLN_RST_TYPE;
#else
    #define cyCapsense_1_LOW_BSLN_RST_SIZE    (16u)
    typedef uint16 cyCapsense_1_LOW_BSLN_RST_TYPE;
#endif /* #if (cyCapsense_1_AUTO_RESET_METHOD_LEGACY == cyCapsense_1_SENSOR_AUTO_RESET_METHOD) */

/* Coefficient to define touch threshold for proximity sensors */
#define cyCapsense_1_PROX_TOUCH_COEFF         (300u)

/*******************************************************************************
* General Filter Constants
*******************************************************************************/

/* Baseline algorithm options */
#define cyCapsense_1_IIR_BASELINE                 (0u)
#define cyCapsense_1_BUCKET_BASELINE              (1u)

#define cyCapsense_1_BASELINE_TYPE                cyCapsense_1_IIR_BASELINE

/* IIR baseline filter algorithm for regular sensors*/
#define cyCapsense_1_REGULAR_IIR_BL_TYPE          cyCapsense_1_IIR_FILTER_PERFORMANCE

/* IIR baseline coefficients for regular sensors */
#define cyCapsense_1_REGULAR_IIR_BL_N             (10u)
#define cyCapsense_1_REGULAR_IIR_BL_SHIFT         (8u)

/* IIR baseline filter algorithm for proximity sensors*/
#define cyCapsense_1_PROX_IIR_BL_TYPE             cyCapsense_1_IIR_FILTER_PERFORMANCE

/* IIR baseline coefficients for proximity sensors */
#define cyCapsense_1_PROX_IIR_BL_N                (1u)
#define cyCapsense_1_PROX_IIR_BL_SHIFT            (8u)


/* IIR filter constants */
#define cyCapsense_1_IIR_COEFFICIENT_K            (256u)

/* IIR filter type */
#define cyCapsense_1_IIR_FILTER_STANDARD          (1u)
#define cyCapsense_1_IIR_FILTER_PERFORMANCE       (2u)
#define cyCapsense_1_IIR_FILTER_MEMORY            (3u)

/* Regular sensor raw count filters */
#define cyCapsense_1_REGULAR_RC_FILTER_EN         (1u)
#define cyCapsense_1_REGULAR_RC_IIR_FILTER_EN     (0u)
#define cyCapsense_1_REGULAR_RC_MEDIAN_FILTER_EN  (0u)
#define cyCapsense_1_REGULAR_RC_AVERAGE_FILTER_EN (1u)
#define cyCapsense_1_REGULAR_RC_CUSTOM_FILTER_EN  (0u)
#define cyCapsense_1_REGULAR_RC_ALP_FILTER_EN     (0u)

/* Proximity sensor raw count filters */
#define cyCapsense_1_PROX_RC_FILTER_EN            (0u)
#define cyCapsense_1_PROX_RC_IIR_FILTER_EN        (0u)
#define cyCapsense_1_PROX_RC_MEDIAN_FILTER_EN     (0u)
#define cyCapsense_1_PROX_RC_AVERAGE_FILTER_EN    (0u)
#define cyCapsense_1_PROX_RC_CUSTOM_FILTER_EN     (0u)
#define cyCapsense_1_PROX_RC_ALP_FILTER_EN        (0u)

#define cyCapsense_1_ALP_FILTER_EN                (0u)
#define cyCapsense_1_REGULAR_RC_ALP_FILTER_COEFF  (2u)
#define cyCapsense_1_PROX_RC_ALP_FILTER_COEFF     (2u)

/* Raw count filters */
#define cyCapsense_1_RC_FILTER_EN                 (cyCapsense_1_REGULAR_RC_FILTER_EN || cyCapsense_1_PROX_RC_FILTER_EN)

/* IIR raw count filter algorithm for regular sensors */
#define cyCapsense_1_REGULAR_IIR_RC_TYPE          (cyCapsense_1_IIR_FILTER_STANDARD)

/* IIR raw count filter coefficients for regular sensors */
#define cyCapsense_1_REGULAR_IIR_RC_N             (128u)
#define cyCapsense_1_REGULAR_IIR_RC_SHIFT         (0u)

/* IIR raw count filter algorithm for proximity sensors*/
#define cyCapsense_1_PROX_IIR_RC_TYPE             (cyCapsense_1_IIR_FILTER_STANDARD)

/* IIR raw count filter coefficients for proximity sensors */
#define cyCapsense_1_PROX_IIR_RC_N                (128u)
#define cyCapsense_1_PROX_IIR_RC_SHIFT            (0u)

/* Median filter constants */

/* Order of regular sensor median filter */
#define cyCapsense_1_REGULAR_MEDIAN_LEN           (2u)

/* Order of proximity sensor median filter */
#define cyCapsense_1_PROX_MEDIAN_LEN              (2u)

/* Average filter constants*/
#define cyCapsense_1_AVERAGE_FILTER_LEN_2         (1u)
#define cyCapsense_1_AVERAGE_FILTER_LEN_4         (3u)

/* Order of regular sensor average filter */
#define cyCapsense_1_REGULAR_AVERAGE_LEN          (cyCapsense_1_AVERAGE_FILTER_LEN_4)

/* Order of proximity sensor average filter */
#define cyCapsense_1_PROX_AVERAGE_LEN             (cyCapsense_1_AVERAGE_FILTER_LEN_4)

/* Widget baseline coefficient enable */
#define cyCapsense_1_WD_BSLN_COEFF_EN             (0u)

/* Centroid position filters */
#define cyCapsense_1_POSITION_FILTER_EN           (0u)
#define cyCapsense_1_POS_MEDIAN_FILTER_EN         (0u)
#define cyCapsense_1_POS_IIR_FILTER_EN            (0u)
#define cyCapsense_1_POS_ADAPTIVE_IIR_FILTER_EN   (0u)
#define cyCapsense_1_POS_AVERAGE_FILTER_EN        (0u)
#define cyCapsense_1_POS_JITTER_FILTER_EN         (0u)
#define cyCapsense_1_BALLISTIC_MULTIPLIER_EN      (0u)
#define cyCapsense_1_CENTROID_3X3_CSD_EN          (0u)
#define cyCapsense_1_CENTROID_5X5_CSD_EN          (0u)
#define cyCapsense_1_CSD_5X5_MAX_FINGERS          (1u)

#define cyCapsense_1_POS_IIR_COEFF                (128u)
#define cyCapsense_1_POS_IIR_RESET_RADIAL_SLIDER  (35u)

#define cyCapsense_1_CSX_TOUCHPAD_UNDEFINED       (40u)

/* IDAC options */

/* Third-generation HW block IDAC gain */
#define cyCapsense_1_IDAC_GAIN_4X                 (4u)
#define cyCapsense_1_IDAC_GAIN_8X                 (8u)

/* Fourth-generation HW block IDAC gain */
#define cyCapsense_1_IDAC_GAIN_LOW                (0uL)
#define cyCapsense_1_IDAC_GAIN_MEDIUM             (1uL)
#define cyCapsense_1_IDAC_GAIN_HIGH               (2uL)

#define cyCapsense_1_IDAC_SOURCING                (0u)
#define cyCapsense_1_IDAC_SINKING                 (1u)

/* Shield tank capacitor precharge source */
#define cyCapsense_1_CSH_PRECHARGE_VREF           (0u)
#define cyCapsense_1_CSH_PRECHARGE_IO_BUF         (1u)

/* Shield electrode delay */
#define cyCapsense_1_NO_DELAY                     (0u)

#if(cyCapsense_1_ENABLE == cyCapsense_1_CSDV2)
    #define cyCapsense_1_SH_DELAY_5NS             (1u)
    #define cyCapsense_1_SH_DELAY_10NS            (2u)
    #define cyCapsense_1_SH_DELAY_20NS            (3u)
#else
    #if(cyCapsense_1_ENABLE == cyCapsense_1_CSDV1_VER2)
        #define cyCapsense_1_SH_DELAY_10NS        (3u)
        #define cyCapsense_1_SH_DELAY_50NS        (2u)
    #else
        #define cyCapsense_1_SH_DELAY_1CYCLES     (1u)
        #define cyCapsense_1_SH_DELAY_2CYCLES     (2u)
    #endif /* (cyCapsense_1_ENABLE == cyCapsense_1_CSDV1_VER2) */
#endif /* (cyCapsense_1_ENABLE == cyCapsense_1_CSDV2) */

/* Inactive sensor connection options */
#define cyCapsense_1_SNS_CONNECTION_GROUND        (0x00000006Lu)
#define cyCapsense_1_SNS_CONNECTION_HIGHZ         (0x00000000Lu)
#define cyCapsense_1_SNS_CONNECTION_SHIELD        (0x00000002Lu)

/* Sense clock selection options */
#if defined(cyCapsense_1_TAPEOUT_STAR_USED)
    #define cyCapsense_1_CSDV2_REF9P6UA_EN            (0u)
#else
    #define cyCapsense_1_CSDV2_REF9P6UA_EN            (0u)
#endif /* defined(cyCapsense_1_TAPEOUT_STAR_USED) */

#define cyCapsense_1_CLK_SOURCE_DIRECT            (0x00000000Lu)

#define cyCapsense_1_CLK_SOURCE_SSC1              (0x01u)
#define cyCapsense_1_CLK_SOURCE_SSC2              (0x02u)
#define cyCapsense_1_CLK_SOURCE_SSC3              (0x03u)
#define cyCapsense_1_CLK_SOURCE_SSC4              (0x04u)

#define cyCapsense_1_CLK_SOURCE_PRS8              (0x05u)
#define cyCapsense_1_CLK_SOURCE_PRS12             (0x06u)
#define cyCapsense_1_CLK_SOURCE_PRSAUTO           (0xFFu)

#define cyCapsense_1_MFS_IMO                      (0u)
#define cyCapsense_1_MFS_SNS_CLK                  (1u)

/* Defines scan resolutions */
#define cyCapsense_1_RES6BIT                      (6u)
#define cyCapsense_1_RES7BIT                      (7u)
#define cyCapsense_1_RES8BIT                      (8u)
#define cyCapsense_1_RES9BIT                      (9u)
#define cyCapsense_1_RES10BIT                     (10u)
#define cyCapsense_1_RES11BIT                     (11u)
#define cyCapsense_1_RES12BIT                     (12u)
#define cyCapsense_1_RES13BIT                     (13u)
#define cyCapsense_1_RES14BIT                     (14u)
#define cyCapsense_1_RES15BIT                     (15u)
#define cyCapsense_1_RES16BIT                     (16u)

/* Fourth-generation HW block: Initialization switch resistance */
#define cyCapsense_1_INIT_SW_RES_LOW              (0x00000000Lu)
#define cyCapsense_1_INIT_SW_RES_MEDIUM           (0x00000001Lu)
#define cyCapsense_1_INIT_SW_RES_HIGH             (0x00000002Lu)

/* Fourth-generation HW block: Initialization switch resistance */
#define cyCapsense_1_SCAN_SW_RES_LOW              (0x00000000Lu)
#define cyCapsense_1_SCAN_SW_RES_MEDIUM           (0x00000001Lu)
#define cyCapsense_1_SCAN_SW_RES_HIGH             (0x00000002Lu)

/* Fourth-generation HW block: CSD shield switch resistance */
#define cyCapsense_1_SHIELD_SW_RES_LOW            (0x00000000Lu)
#define cyCapsense_1_SHIELD_SW_RES_MEDIUM         (0x00000001Lu)
#define cyCapsense_1_SHIELD_SW_RES_HIGH           (0x00000002Lu)
#define cyCapsense_1_SHIELD_SW_RES_LOW_EMI        (0x00000003Lu)

/* Fourth-generation HW block: CSD shield switch resistance */
#define cyCapsense_1_INIT_SHIELD_SW_RES_LOW       (0x00000000Lu)
#define cyCapsense_1_INIT_SHIELD_SW_RES_MEDIUM    (0x00000001Lu)
#define cyCapsense_1_INIT_SHIELD_SW_RES_HIGH      (0x00000002Lu)
#define cyCapsense_1_INIT_SHIELD_SW_RES_LOW_EMI   (0x00000003Lu)

/* Fourth-generation HW block: CSD shield switch resistance */
#define cyCapsense_1_SCAN_SHIELD_SW_RES_LOW       (0x00000000Lu)
#define cyCapsense_1_SCAN_SHIELD_SW_RES_MEDIUM    (0x00000001Lu)
#define cyCapsense_1_SCAN_SHIELD_SW_RES_HIGH      (0x00000002Lu)
#define cyCapsense_1_SCAN_SHIELD_SW_RES_LOW_EMI   (0x00000003Lu)

/* Sensing method */
#define cyCapsense_1_SENSING_LEGACY               (0x00000000Lu)
#define cyCapsense_1_SENSING_LOW_EMI              (0x00000001Lu)
#define cyCapsense_1_SENSING_FULL_WAVE            (0x00000002Lu)


/*******************************************************************************
* CSD/CSX Common settings
*******************************************************************************/

#define cyCapsense_1_BLOCK_ANALOG_WAKEUP_DELAY_US (0u)

#define cyCapsense_1_MFS_METHOD                   (0u)
#define cyCapsense_1_IMO_FREQUENCY_OFFSET_F1      (20u)
#define cyCapsense_1_IMO_FREQUENCY_OFFSET_F2      (20u)

/*******************************************************************************
* CSD Specific settings
*******************************************************************************/

/* CSD scan method settings */
#define cyCapsense_1_CSD_IDAC_AUTOCAL_EN          (1u)
#define cyCapsense_1_CSD_IDAC_GAIN                (cyCapsense_1_IDAC_GAIN_4X)
#define cyCapsense_1_CSD_SHIELD_EN                (0u)
#define cyCapsense_1_CSD_SHIELD_TANK_EN           (0u)
#define cyCapsense_1_CSD_CSH_PRECHARGE_SRC        (cyCapsense_1_CSH_PRECHARGE_VREF)
#define cyCapsense_1_CSD_SHIELD_DELAY             (cyCapsense_1_NO_DELAY)
#define cyCapsense_1_CSD_TOTAL_SHIELD_COUNT       (0u)
#define cyCapsense_1_CSD_SCANSPEED_DIVIDER        (2u)
#define cyCapsense_1_CSD_COMMON_SNS_CLK_EN        (0u)
#define cyCapsense_1_CSD_SNS_CLK_SOURCE           (cyCapsense_1_CLK_SOURCE_PRS8)
#define cyCapsense_1_CSD_SNS_CLK_DIVIDER          (8u)
#define cyCapsense_1_CSD_INACTIVE_SNS_CONNECTION  (cyCapsense_1_SNS_CONNECTION_GROUND)
#define cyCapsense_1_CSD_IDAC_COMP_EN             (0u)
#define cyCapsense_1_CSD_IDAC_CONFIG              (cyCapsense_1_IDAC_SOURCING)
#define cyCapsense_1_CSD_RAWCOUNT_CAL_LEVEL       (85u)
#define cyCapsense_1_CSD_DUALIDAC_LEVEL           (50u)
#define cyCapsense_1_CSD_PRESCAN_SETTLING_TIME    (5u)
#define cyCapsense_1_CSD_SNSCLK_R_CONST           (1000u)
#define cyCapsense_1_CSD_VREF_MV                  (1200u)

/* CSD settings - Fourth-generation HW block */
#define cyCapsense_1_CSD_ANALOG_STARTUP_DELAY_US  (10u)
#define cyCapsense_1_CSD_FINE_INIT_TIME           (10u)
#define cyCapsense_1_CSD_DEDICATED_IDAC_COMP_EN   (1u)
#define cyCapsense_1_CSD_AUTO_ZERO_EN             (0u)
#define cyCapsense_1_CSD_AUTO_ZERO_TIME           (15Lu)
#define cyCapsense_1_CSD_NOISE_METRIC_EN          (0u)
#define cyCapsense_1_CSD_NOISE_METRIC_TH          (1Lu)
#define cyCapsense_1_CSD_INIT_SWITCH_RES          (cyCapsense_1_INIT_SW_RES_MEDIUM)
#define cyCapsense_1_CSD_SENSING_METHOD           (0)
#define cyCapsense_1_CSD_SHIELD_SWITCH_RES        (cyCapsense_1_SHIELD_SW_RES_MEDIUM)
#define cyCapsense_1_CSD_GAIN                     (31Lu)

#define cyCapsense_1_CSD_MFS_METHOD               (u)
#define cyCapsense_1_CSD_MFS_DIVIDER_OFFSET_F1    (1u)
#define cyCapsense_1_CSD_MFS_DIVIDER_OFFSET_F2    (2u)

/*******************************************************************************
* CSX Specific settings
*******************************************************************************/

/* CSX scan method settings */
#define cyCapsense_1_CSX_SCANSPEED_DIVIDER        (2u)
#define cyCapsense_1_CSX_COMMON_TX_CLK_EN         (0u)
#define cyCapsense_1_CSX_TX_CLK_SOURCE            (cyCapsense_1_CLK_SOURCE_DIRECT)
#define cyCapsense_1_CSX_TX_CLK_DIVIDER           (80u)
#define cyCapsense_1_CSX_MAX_FINGERS              (1u)
#define cyCapsense_1_CSX_MAX_LOCAL_PEAKS          (5u)
#define cyCapsense_1_CSX_IDAC_AUTOCAL_EN          (0u)
#define cyCapsense_1_CSX_IDAC_BITS_USED           (8u)
#define cyCapsense_1_CSX_RAWCOUNT_CAL_LEVEL       (40u)
#define cyCapsense_1_CSX_IDAC_GAIN                (cyCapsense_1_IDAC_GAIN_4X)
#define cyCapsense_1_CSX_SKIP_OVSMPL_SPECIFIC_NODES (0u)
#define cyCapsense_1_CSX_MULTIPHASE_TX_EN         (0u)
#define cyCapsense_1_CSX_MAX_TX_PHASE_LENGTH      (0u)

/* CSX settings - Fourth-generation HW block */
#define cyCapsense_1_CSX_ANALOG_STARTUP_DELAY_US  (10u)
#define cyCapsense_1_CSX_AUTO_ZERO_EN             (0u)
#define cyCapsense_1_CSX_AUTO_ZERO_TIME           (15u)
#define cyCapsense_1_CSX_FINE_INIT_TIME           (4u)
#define cyCapsense_1_CSX_NOISE_METRIC_EN          (0u)
#define cyCapsense_1_CSX_NOISE_METRIC_TH          (1u)
#define cyCapsense_1_CSX_INIT_SWITCH_RES          (cyCapsense_1_INIT_SW_RES_MEDIUM)
#define cyCapsense_1_CSX_SCAN_SWITCH_RES          (cyCapsense_1_SCAN_SW_RES_LOW)
#define cyCapsense_1_CSX_INIT_SHIELD_SWITCH_RES   (cyCapsense_1_INIT_SHIELD_SW_RES_HIGH)
#define cyCapsense_1_CSX_SCAN_SHIELD_SWITCH_RES   (cyCapsense_1_SCAN_SHIELD_SW_RES_LOW)

#define cyCapsense_1_CSX_MFS_METHOD               (u)
#define cyCapsense_1_CSX_MFS_DIVIDER_OFFSET_F1    (1u)
#define cyCapsense_1_CSX_MFS_DIVIDER_OFFSET_F2    (2u)

/* Gesture parameters */
#define cyCapsense_1_GES_GLOBAL_EN                (0u)

/*******************************************************************************
* ISX Specific settings
*******************************************************************************/

/* ISX scan method settings */
#define cyCapsense_1_ISX_SCANSPEED_DIVIDER        (2u)
#define cyCapsense_1_ISX_LX_CLK_DIVIDER           (80u)
#define cyCapsense_1_ISX_IDAC_AUTOCAL_EN          (0u)
#define cyCapsense_1_ISX_IDAC_BITS_USED           (7u)
#define cyCapsense_1_ISX_RAWCOUNT_CAL_LEVEL       (30u)
#define cyCapsense_1_ISX_IDAC_GAIN                (cyCapsense_1_IDAC_GAIN_4X)
#define cyCapsense_1_ISX_SKIP_OVSMPL_SPECIFIC_NODES (0u)
#define cyCapsense_1_ISX_MAX_TX_PHASE_LENGTH      (0u)
#define cyCapsense_1_ISX_PIN_COUNT_LX             (u)
/* ISX settings - Fourth-generation HW block */
#define cyCapsense_1_ISX_AUTO_ZERO_EN             (0u)
#define cyCapsense_1_ISX_AUTO_ZERO_TIME           (15u)
#define cyCapsense_1_ISX_FINE_INIT_TIME           (20u)
#define cyCapsense_1_ISX_NOISE_METRIC_EN          (0u)
#define cyCapsense_1_ISX_NOISE_METRIC_TH          (1u)
#define cyCapsense_1_ISX_INIT_SWITCH_RES          (cyCapsense_1_INIT_SW_RES_MEDIUM)
#define cyCapsense_1_ISX_SCAN_SWITCH_RES          (cyCapsense_1_SCAN_SW_RES_LOW)
#define cyCapsense_1_ISX_INIT_SHIELD_SWITCH_RES   (cyCapsense_1_INIT_SHIELD_SW_RES_HIGH)
#define cyCapsense_1_ISX_SCAN_SHIELD_SWITCH_RES   (cyCapsense_1_SCAN_SHIELD_SW_RES_LOW)
#define cyCapsense_1_ISX_SAMPLE_PHASE_DEG         (30u)

/*******************************************************************************
* Global Parameter Definitions
*******************************************************************************/

/* Compound section definitions */
#define cyCapsense_1_ANY_NONSS_AUTOCAL ((0u != cyCapsense_1_CSX_IDAC_AUTOCAL_EN) || \
                                       (0u != cyCapsense_1_ISX_IDAC_AUTOCAL_EN) || \
                                      ((cyCapsense_1_CSD_AUTOTUNE == cyCapsense_1_CSD_SS_DIS) && (0u != cyCapsense_1_CSD_IDAC_AUTOCAL_EN)))
#define cyCapsense_1_ANYMODE_AUTOCAL (((0u != cyCapsense_1_CSX_IDAC_AUTOCAL_EN) \
                                       || (0u != cyCapsense_1_ISX_IDAC_AUTOCAL_EN)) \
                                       || (0u != cyCapsense_1_CSD_IDAC_AUTOCAL_EN))
/* RAM Global Parameters Definitions */
#define cyCapsense_1_CONFIG_ID                  (0xF2E2u)
#define cyCapsense_1_DEVICE_ID                  (0x0800u)
#define cyCapsense_1_HW_CLOCK                   (0x1770u)
#define cyCapsense_1_CSD0_CONFIG                (0x0000u)

/*******************************************************************************
* Button0 initialization values for FLASH data structure
*******************************************************************************/
#define cyCapsense_1_BUTTON0_STATIC_CONFIG      (10241u)
#define cyCapsense_1_BUTTON0_NUM_SENSORS        (1u)

/*******************************************************************************
* Button0 initialization values for RAM data structure
*******************************************************************************/
#define cyCapsense_1_BUTTON0_RESOLUTION         (cyCapsense_1_RES12BIT)
#define cyCapsense_1_BUTTON0_FINGER_TH          (100u)
#define cyCapsense_1_BUTTON0_NOISE_TH           (40u)
#define cyCapsense_1_BUTTON0_NNOISE_TH          (40u)
#define cyCapsense_1_BUTTON0_HYSTERESIS         (10u)
#define cyCapsense_1_BUTTON0_ON_DEBOUNCE        (3u)
#define cyCapsense_1_BUTTON0_LOW_BSLN_RST       (30u)
#define cyCapsense_1_BUTTON0_IDAC_MOD0          (32u)
#define cyCapsense_1_BUTTON0_SNS_CLK            (4u)
#define cyCapsense_1_BUTTON0_SNS_CLK_SOURCE     (0u)
#define cyCapsense_1_BUTTON0_FINGER_CAP         (900u)
#define cyCapsense_1_BUTTON0_SIGPFC             (0u)

/* RAM Sensor Parameters Definitions */


/*******************************************************************************
* ADC Specific Macros
*******************************************************************************/
#define cyCapsense_1_ADC_RES8BIT                  (8u)
#define cyCapsense_1_ADC_RES10BIT                 (10u)

#define cyCapsense_1_ADC_FULLRANGE_MODE           (0u)
#define cyCapsense_1_ADC_VREF_MODE                (1u)

#define cyCapsense_1_ADC_MIN_CHANNELS             (1u)
#define cyCapsense_1_ADC_EN                       (0u)
#define cyCapsense_1_ADC_STANDALONE_EN            (0u)
#define cyCapsense_1_ADC_TOTAL_CHANNELS           (1u)
#define cyCapsense_1_ADC_RESOLUTION               (cyCapsense_1_ADC_RES10BIT)
#define cyCapsense_1_ADC_AMUXB_INPUT_EN           (0u)
#define cyCapsense_1_ADC_SELECT_AMUXB_CH          (0u)
#define cyCapsense_1_ADC_AZ_EN                    (1Lu)
#define cyCapsense_1_ADC_AZ_TIME                  (5u)
#define cyCapsense_1_ADC_VREF_MV                  (2133u)
#define cyCapsense_1_ADC_GAIN                     (17Lu)
#define cyCapsense_1_ADC_IDAC_DEFAULT             (15u)
#define cyCapsense_1_ADC_MODCLK_DIV_DEFAULT       (2u)
#define cyCapsense_1_ADC_MEASURE_MODE             (cyCapsense_1_ADC_FULLRANGE_MODE)
#define cyCapsense_1_ADC_ANALOG_STARTUP_DELAY_US  (5u)
#define cyCapsense_1_ADC_ACQUISITION_TIME_US      (10u)

/*******************************************************************************
* Built-In Self-Test Configuration
*******************************************************************************/
#define cyCapsense_1_SELF_TEST_EN                   (0Lu)
#define cyCapsense_1_TST_GLOBAL_CRC_EN              (0Lu)
#define cyCapsense_1_TST_WDGT_CRC_EN                (0Lu)
#define cyCapsense_1_TST_BSLN_DUPLICATION_EN        (0Lu)
#define cyCapsense_1_TST_BSLN_RAW_OUT_RANGE_EN      (0Lu)
#define cyCapsense_1_TST_SNS_SHORT_EN               (0Lu)
#define cyCapsense_1_TST_SNS2SNS_SHORT_EN           (0Lu)
#define cyCapsense_1_TST_SNS_CAP_EN                 (0Lu)
#define cyCapsense_1_TST_SH_CAP_EN                  (0Lu)
#define cyCapsense_1_TST_EXTERNAL_CAP_EN            (0Lu)
#define cyCapsense_1_TST_INTERNAL_CAP_EN            (0Lu)
#define cyCapsense_1_TST_VDDA_EN                    (0Lu)
#define cyCapsense_1_TST_FINE_INIT_TIME             (10Lu)


#define cyCapsense_1_TST_ANALOG_STARTUP_DELAY_US    (23u)

/*******************************************************************************
* Gesture Configuration
*******************************************************************************/
#define cyCapsense_1_TIMESTAMP_INTERVAL             (1Lu)
#define cyCapsense_1_GESTURE_EN_WIDGET_ID           (0Lu)
#define cyCapsense_1_BALLISTIC_EN_WIDGET_ID         (0Lu)


#endif /* CY_SENSE_cyCapsense_1_CONFIGURATION_H */


/* [] END OF FILE */

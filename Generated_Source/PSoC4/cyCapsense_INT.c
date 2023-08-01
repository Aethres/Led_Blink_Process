/***************************************************************************//**
* \file cyCapsense_INT.c
* \version 6.0
*
* \brief
*   This file contains the source code for implementation of the Component's
*   Interrupt Service Routine (ISR).
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
#include "cytypes.h"
#include "cyfitter.h"
#include "cyCapsense_Configuration.h"
#include "cyCapsense_Structure.h"
#include "cyCapsense_Sensing.h"
#if (cyCapsense_ENABLE == cyCapsense_CSD_EN)
    #include "cyCapsense_SensingCSD_LL.h"
#endif /* (cyCapsense_ENABLE == cyCapsense_CSD_EN) */
#include "cyapicallbacks.h"

/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/
/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

#if (((cyCapsense_ENABLE == cyCapsense_CSD_EN) || (cyCapsense_ENABLE == cyCapsense_CSD_CSX_EN)) && \
     (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN))
    static void cyCapsense_SsNextFrequencyScan(void);
#endif /* (((cyCapsense_ENABLE == cyCapsense_CSD_EN) || (cyCapsense_ENABLE == cyCapsense_CSD_CSX_EN)) && \
            (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)) */

#if ((cyCapsense_ENABLE == cyCapsense_CSD_EN) || (cyCapsense_ENABLE == cyCapsense_CSD_CSX_EN))
    static void cyCapsense_SsCSDPostScan(void);
    static void cyCapsense_SsCSDInitNextScan(void);
#endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_EN) || (cyCapsense_ENABLE == cyCapsense_CSD_CSX_EN)) */
/** \}
* \endcond */


/**
* \cond SECTION_C_INTERRUPT
* \addtogroup group_c_interrupt
* \{
*/


#if ((cyCapsense_ENABLE == cyCapsense_CSD_EN) || (cyCapsense_ENABLE == cyCapsense_CSD_CSX_EN))

#if (cyCapsense_ENABLE == cyCapsense_CSDV2)
    /* Fourth-generation HW block part */

    /*******************************************************************************
    * Function Name: cyCapsense_CSDPostSingleScan
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the single-sensor scanning implementation.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  cyCapsense_CSDScanExt() function.
    *
    *  The following tasks are performed for Third-generation HW block:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Update the Scan Counter.
    *    5. Reset the BUSY flag.
    *    6. Enable the CSD interrupt.
    *
    *  The following tasks are performed for Fourth-generation HW block:
    *    1. Check if the raw data is not noisy.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Configure and start the scan for the next frequency if the
    *      multi-frequency is enabled.
    *    4. Update the Scan Counter.
    *    5. Reset the BUSY flag.
    *    6. Enable the CSD interrupt.
    *
    *  The ISR handler changes the IMO and initializes scanning for the next frequency
    *  channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user code
    *  from macros specified in Component's generated code. Refer to the
    *  \ref group_c_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    CY_ISR(cyCapsense_CSDPostSingleScan)
    {
        #ifdef cyCapsense_ENTRY_CALLBACK
            cyCapsense_EntryCallback();
        #endif /* cyCapsense_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(cyCapsense_INTR_PTR, cyCapsense_INTR_SET_MASK);

        #if (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN)
            if ((cyCapsense_CSD_NOISE_METRIC_TH < ((CY_GET_REG32(cyCapsense_RESULT_VAL1_PTR) &
                                                        cyCapsense_RESULT_VAL1_BAD_CONVS_MASK) >>
                                                        cyCapsense_RESULT_VAL1_BAD_CONVS_SHIFT)) &&
                                                        (0u < cyCapsense_badConversionsNum))
            {
                /* Decrement bad conversions number */
                cyCapsense_badConversionsNum--;

                /* Start the re-scan */
                CY_SET_REG32(cyCapsense_SEQ_START_PTR, cyCapsense_SEQ_START_AZ0_SKIP_MASK |
                                                             cyCapsense_SEQ_START_AZ1_SKIP_MASK |
                                                             cyCapsense_SEQ_START_START_MASK);
            }
            else
            {
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN) */

            cyCapsense_SsCSDPostScan();

            #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                if (cyCapsense_FREQ_CHANNEL_2 > cyCapsense_scanFreqIndex)
                {
                    /* Scan the next channel */
                    cyCapsense_SsNextFrequencyScan();
                }
                else
                {
                    /* All channels are scanned. Set IMO to zero channel */
                    cyCapsense_scanFreqIndex = cyCapsense_FREQ_CHANNEL_0;

                    #if (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD)
                        cyCapsense_SsChangeImoFreq(cyCapsense_FREQ_CHANNEL_0);
                    #else
                        cyCapsense_SsChangeClkFreq(cyCapsense_FREQ_CHANNEL_0);
                    #endif /* (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD) */

                    #if (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN)
                        /* Disable Fourth-generation HW block */
                        CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd);
                    #endif /* (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN) */

                    /* Update Scan Counter */
                    cyCapsense_dsRam.scanCounter++;

                    /* Sensor is totally scanned. Reset BUSY flag */
                    cyCapsense_dsRam.status &= ~(cyCapsense_SW_STS_BUSY | cyCapsense_WDGT_SW_STS_BUSY);
                }
            #else
                {
                    #if (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN)
                        /* Disable Fourth-generation HW block */
                        CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd);
                    #endif /* (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN) */

                    /* Update Scan Counter */
                    cyCapsense_dsRam.scanCounter++;

                    /* Sensor is totally scanned. Reset BUSY flag */
                    cyCapsense_dsRam.status &= ~(cyCapsense_SW_STS_BUSY | cyCapsense_WDGT_SW_STS_BUSY);
                }
            #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */
    #if (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN)
        }
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN) */

        #ifdef cyCapsense_EXIT_CALLBACK
            cyCapsense_ExitCallback();
        #endif /* cyCapsense_EXIT_CALLBACK */
    }


    /*******************************************************************************
    * Function Name: cyCapsense_CSDPostMultiScan
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the multiple-sensor scanning
    *  implementation.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  cyCapsense_Scan() or cyCapsense_ScanAllWidgets() APIs.
    *
    *  The following tasks are performed:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Disable the CSD block (after the widget has been scanned).
    *    5. Update the Scan Counter.
    *    6. Reset the BUSY flag.
    *    7. Enable the CSD interrupt.
    *
    *  The ISR handler initializes scanning for the previous sensor when the
    *  widget has more than one sensor.
    *  The ISR handler initializes scanning for the next widget when the
    *  cyCapsense_ScanAllWidgets() APIs are called and the project has
    *  more than one widget.
    *  The ISR handler changes the IMO and initializes scanning for the next
    *  frequency channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user
    *  code from macros specified in Component's generated code. Refer to the
    *  \ref group_c_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    CY_ISR(cyCapsense_CSDPostMultiScan)
    {
        /* Declare and initialize ptr to sensor IO structure to appropriate address */
        cyCapsense_FLASH_IO_STRUCT const *curSnsIOPtr = (cyCapsense_FLASH_IO_STRUCT const *)
                                                          cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2SnsFlash
                                                          + cyCapsense_sensorIndex;

        #ifdef cyCapsense_ENTRY_CALLBACK
            cyCapsense_EntryCallback();
        #endif /* cyCapsense_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(cyCapsense_INTR_PTR, cyCapsense_INTR_SET_MASK);

        #if (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN)
            if ((cyCapsense_CSD_NOISE_METRIC_TH < ((CY_GET_REG32(cyCapsense_RESULT_VAL1_PTR) &
                                                      cyCapsense_RESULT_VAL1_BAD_CONVS_MASK) >>
                                                      cyCapsense_RESULT_VAL1_BAD_CONVS_SHIFT)) &&
                                                      (0u < cyCapsense_badConversionsNum))
            {
                /* Decrement bad conversions number */
                cyCapsense_badConversionsNum--;

                /* Start the re-scan */
                CY_SET_REG32(cyCapsense_SEQ_START_PTR, cyCapsense_SEQ_START_AZ0_SKIP_MASK |
                                                             cyCapsense_SEQ_START_AZ1_SKIP_MASK |
                                                             cyCapsense_SEQ_START_START_MASK);
            }
            else
            {
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN) */

            cyCapsense_SsCSDPostScan();

            /* Disable sensor when all frequency channels are scanned */
            #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                if (cyCapsense_FREQ_CHANNEL_2 == cyCapsense_scanFreqIndex)
            #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */
            {
                /* Disable sensor */
                cyCapsense_CSDDisconnectSns(curSnsIOPtr);
            }

            #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                if (cyCapsense_FREQ_CHANNEL_2 > cyCapsense_scanFreqIndex)
                {
                     /* Scan the next channel */
                    cyCapsense_SsNextFrequencyScan();
                }
                else
                {
                     /* All channels are scanned. Set IMO to zero channel */
                    cyCapsense_scanFreqIndex = cyCapsense_FREQ_CHANNEL_0;

                    #if (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD)
                        cyCapsense_SsChangeImoFreq(cyCapsense_FREQ_CHANNEL_0);
                    #else
                        cyCapsense_SsChangeClkFreq(cyCapsense_FREQ_CHANNEL_0);
                    #endif /* (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD) */

                     /* Scan the next sensor */
                    cyCapsense_SsCSDInitNextScan();
                }
            #else
                /* Scan the next sensor */
                cyCapsense_SsCSDInitNextScan();
            #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */
        #if (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN)
            }
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN) */

        #ifdef cyCapsense_EXIT_CALLBACK
            cyCapsense_ExitCallback();
        #endif /* cyCapsense_EXIT_CALLBACK */
    }


    #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
    /*******************************************************************************
    * Function Name: cyCapsense_CSDPostMultiScanGanged
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the multiple-sensor scanning
    *  implementation for ganged sensors.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  cyCapsense_Scan() API for a ganged sensor or the
    *  cyCapsense_ScanAllWidgets() API in the project with ganged sensors.
    *
    *  The following tasks are performed:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Disable the CSD block (after the widget has been scanned).
    *    5. Update the Scan Counter.
    *    6. Reset the BUSY flag.
    *    7. Enable the CSD interrupt.
    *
    *  The ISR handler initializes scanning for the previous sensor when the
    *  widget has more than one sensor.
    *  The ISR handler initializes scanning for the next widget when the
    *  cyCapsense_ScanAllWidgets() APIs are called and the project has
    *  more than one widget.
    *  The ISR handler changes the IMO and initializes scanning for the next
    *  frequency channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user
    *  code from macros specified in Component's generated code. Refer to the
    *  \ref group_c_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    CY_ISR(cyCapsense_CSDPostMultiScanGanged)
    {
        #ifdef cyCapsense_ENTRY_CALLBACK
            cyCapsense_EntryCallback();
        #endif /* cyCapsense_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(cyCapsense_INTR_PTR, cyCapsense_INTR_SET_MASK);

        #if (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN)
            if ((cyCapsense_CSD_NOISE_METRIC_TH < ((CY_GET_REG32(cyCapsense_RESULT_VAL1_PTR) &
                                                      cyCapsense_RESULT_VAL1_BAD_CONVS_MASK) >>
                                                      cyCapsense_RESULT_VAL1_BAD_CONVS_SHIFT)) &&
                                                      (0u < cyCapsense_badConversionsNum))
            {
                /* Decrement bad conversions number */
                cyCapsense_badConversionsNum--;

                /* Start the re-scan */
                CY_SET_REG32(cyCapsense_SEQ_START_PTR, cyCapsense_SEQ_START_AZ0_SKIP_MASK |
                                                             cyCapsense_SEQ_START_AZ1_SKIP_MASK |
                                                             cyCapsense_SEQ_START_START_MASK);
            }
            else
            {
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN) */

            cyCapsense_SsCSDPostScan();

            #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                if (cyCapsense_FREQ_CHANNEL_2 == cyCapsense_scanFreqIndex)
            #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */
            {
                cyCapsense_SsCSDDisconnectSnsExt((uint32)cyCapsense_widgetIndex, (uint32)cyCapsense_sensorIndex);
            }

            #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
                if (cyCapsense_FREQ_CHANNEL_2 > cyCapsense_scanFreqIndex)
                {
                     /* Scan the next channel */
                    cyCapsense_SsNextFrequencyScan();
                }
                else
                {
                    /* All channels are scanned. Set IMO to zero channel */
                    cyCapsense_scanFreqIndex = cyCapsense_FREQ_CHANNEL_0;

                    #if (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD)
                        cyCapsense_SsChangeImoFreq(cyCapsense_FREQ_CHANNEL_0);
                    #else
                        cyCapsense_SsChangeClkFreq(cyCapsense_FREQ_CHANNEL_0);
                    #endif /* (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD) */

                     /* Scan the next sensor */
                    cyCapsense_SsCSDInitNextScan();
                }
            #else
                 /* Scan the next sensor */
                cyCapsense_SsCSDInitNextScan();
            #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */
        #if (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN)
            }
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN) */

        #ifdef cyCapsense_EXIT_CALLBACK
            cyCapsense_ExitCallback();
        #endif /* cyCapsense_EXIT_CALLBACK */
    }
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN) */

#else

    /* Third-generation HW block part */

    /*******************************************************************************
    * Function Name: cyCapsense_CSDPostSingleScan
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the single-sensor scanning implementation.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  cyCapsense_CSDScanExt() function.
    *
    *  The following tasks are performed for Third-generation HW block:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Update the Scan Counter.
    *    5. Reset the BUSY flag.
    *    6. Enable the CSD interrupt.
    *
    *  The following tasks are performed for Fourth-generation HW block:
    *    1. Check if the raw data is not noisy.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Configure and start the scan for the next frequency if the
    *      multi-frequency is enabled.
    *    4. Update the Scan Counter.
    *    5. Reset the BUSY flag.
    *    6. Enable the CSD interrupt.
    *
    *  The ISR handler changes the IMO and initializes scanning for the next frequency
    *  channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user code
    *  from macros specified in Component's generated code. Refer to the
    *  \ref group_c_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    CY_ISR(cyCapsense_CSDPostSingleScan)
    {
        #ifdef cyCapsense_ENTRY_CALLBACK
            cyCapsense_EntryCallback();
        #endif /* cyCapsense_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(cyCapsense_INTR_PTR, cyCapsense_INTR_SET_MASK);

        /* Read Rawdata */
        cyCapsense_SsCSDPostScan();

        #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
            if (cyCapsense_FREQ_CHANNEL_2 > cyCapsense_scanFreqIndex)
            {
                /* Connect Vref Buffer to AMUX bus. Third-generation HW block is enabled */
                CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CTANK_PRECHARGE_CONFIG_CSD_EN);

                cyCapsense_SsNextFrequencyScan();
            }
            else
            {
                cyCapsense_scanFreqIndex = cyCapsense_FREQ_CHANNEL_0;

                #if (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD)
                    cyCapsense_SsChangeImoFreq(cyCapsense_FREQ_CHANNEL_0);
                #else
                    cyCapsense_SsChangeClkFreq(cyCapsense_FREQ_CHANNEL_0);
                #endif /* (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD) */

                #if (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN)
                    /* Disable Third-generation HW block. Connect Vref Buffer to AMUX bus */
                    #if ((cyCapsense_CSH_PRECHARGE_IO_BUF == cyCapsense_CSD_CSH_PRECHARGE_SRC) &&\
                         (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN))
                        CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CMOD_PRECHARGE_CONFIG);
                    #else
                        CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CTANK_PRECHARGE_CONFIG);
                    #endif /* ((cyCapsense_CSH_PRECHARGE_IO_BUF == cyCapsense_CSD_CSH_PRECHARGE_SRC) &&\
                               (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN)) */
                #else
                    /* Connect Vref Buffer to AMUX bus. Third-generation HW block is enabled */
                    CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CTANK_PRECHARGE_CONFIG_CSD_EN);
                #endif /* (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN) */

                /* Update Scan Counter */
                cyCapsense_dsRam.scanCounter++;

                /* Sensor is totally scanned. Reset BUSY flag */
                cyCapsense_dsRam.status &= ~(cyCapsense_SW_STS_BUSY | cyCapsense_WDGT_SW_STS_BUSY);
            }
        #else
            {
                #if (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN)
                    /* Disable Third-generation HW block. Connect Vref Buffer to AMUX bus */
                    #if ((cyCapsense_CSH_PRECHARGE_IO_BUF == cyCapsense_CSD_CSH_PRECHARGE_SRC) &&\
                         (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN))
                        CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CMOD_PRECHARGE_CONFIG);
                    #else
                        CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CTANK_PRECHARGE_CONFIG);
                    #endif /* ((cyCapsense_CSH_PRECHARGE_IO_BUF == cyCapsense_CSD_CSH_PRECHARGE_SRC) &&\
                               (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN)) */
                #else
                    /* Connect Vref Buffer to AMUX bus. Third-generation HW block is enabled */
                    CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CTANK_PRECHARGE_CONFIG_CSD_EN);
                #endif /* (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN) */

                /* Update Scan Counter */
                cyCapsense_dsRam.scanCounter++;

                /* Sensor is totally scanned. Reset BUSY flag */
                cyCapsense_dsRam.status &= ~(cyCapsense_SW_STS_BUSY | cyCapsense_WDGT_SW_STS_BUSY);
            }
        #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

        #ifdef cyCapsense_EXIT_CALLBACK
            cyCapsense_ExitCallback();
        #endif /* cyCapsense_EXIT_CALLBACK */
    }


    /*******************************************************************************
    * Function Name: cyCapsense_CSDPostMultiScan
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the multiple-sensor scanning
    *  implementation.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  cyCapsense_Scan() or cyCapsense_ScanAllWidgets() APIs.
    *
    *  The following tasks are performed:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Disable the CSD block (after the widget has been scanned).
    *    5. Update the Scan Counter.
    *    6. Reset the BUSY flag.
    *    7. Enable the CSD interrupt.
    *
    *  The ISR handler initializes scanning for the previous sensor when the
    *  widget has more than one sensor.
    *  The ISR handler initializes scanning for the next widget when the
    *  cyCapsense_ScanAllWidgets() APIs are called and the project has
    *  more than one widget.
    *  The ISR handler changes the IMO and initializes scanning for the next
    *  frequency channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user
    *  code from macros specified in Component's generated code. Refer to the
    *  \ref group_c_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    CY_ISR(cyCapsense_CSDPostMultiScan)
    {
        /* Declare and initialize ptr to sensor IO structure to appropriate address        */
        cyCapsense_FLASH_IO_STRUCT const *curSnsIOPtr = (cyCapsense_FLASH_IO_STRUCT const *)
                                                          cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2SnsFlash
                                                          + cyCapsense_sensorIndex;

        #ifdef cyCapsense_ENTRY_CALLBACK
            cyCapsense_EntryCallback();
        #endif /* cyCapsense_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(cyCapsense_INTR_PTR, cyCapsense_INTR_SET_MASK);

         /* Read Rawdata */
        cyCapsense_SsCSDPostScan();

        /* Connect Vref Buffer to AMUX bus */
        CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CTANK_PRECHARGE_CONFIG_CSD_EN);

        #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
            /* Disable sensor when all frequency channels are scanned */
            if (cyCapsense_FREQ_CHANNEL_2 == cyCapsense_scanFreqIndex)
            {
                /* Disable sensor */
                cyCapsense_CSDDisconnectSns(curSnsIOPtr);
            }
        #else
            /* Disable sensor */
            cyCapsense_CSDDisconnectSns(curSnsIOPtr);
        #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

        #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
            if (cyCapsense_FREQ_CHANNEL_2 > cyCapsense_scanFreqIndex)
            {
                 /* Scan the next channel */
                cyCapsense_SsNextFrequencyScan();
            }
            else
            {
                 /* All channels are scanned. Set IMO to zero channel */
                cyCapsense_scanFreqIndex = cyCapsense_FREQ_CHANNEL_0;

                #if (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD)
                    cyCapsense_SsChangeImoFreq(cyCapsense_FREQ_CHANNEL_0);
                #else
                    cyCapsense_SsChangeClkFreq(cyCapsense_FREQ_CHANNEL_0);
                #endif /* (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD) */

                 /* Scan the next sensor */
                cyCapsense_SsCSDInitNextScan();
            }
        #else
            /* Scan the next sensor */
            cyCapsense_SsCSDInitNextScan();
        #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

        #ifdef cyCapsense_EXIT_CALLBACK
            cyCapsense_ExitCallback();
        #endif /* cyCapsense_EXIT_CALLBACK */
    }


    #if (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN)
    /*******************************************************************************
    * Function Name: cyCapsense_CSDPostMultiScanGanged
    ****************************************************************************//**
    *
    * \brief
    *  This is an internal ISR function for the multiple-sensor scanning
    *  implementation for ganged sensors.
    *
    * \details
    *  This ISR handler is triggered when the user calls the
    *  cyCapsense_Scan() API for a ganged sensor or the
    *  cyCapsense_ScanAllWidgets() API in the project with ganged sensors.
    *
    *  The following tasks are performed:
    *    1. Disable the CSD interrupt.
    *    2. Read the Counter register and update the data structure with raw data.
    *    3. Connect the Vref buffer to the AMUX bus.
    *    4. Disable the CSD block (after the widget has been scanned).
    *    5. Update the Scan Counter.
    *    6. Reset the BUSY flag.
    *    7. Enable the CSD interrupt.
    *
    *  The ISR handler initializes scanning for the previous sensor when the
    *  widget has more than one sensor.
    *  The ISR handler initializes scanning for the next widget when the
    *  cyCapsense_ScanAllWidgets() APIs are called and the project has
    *  more than one widget.
    *  The ISR handler changes the IMO and initializes scanning for the next
    *  frequency channels when multi-frequency scanning is enabled.
    *
    *  This function has two Macro Callbacks that allow calling the user
    *  code from macros specified in Component's generated code. Refer to the
    *  \ref group_c_macrocallbacks section of the PSoC Creator User Guide
    *  for details.
    *
    *******************************************************************************/
    CY_ISR(cyCapsense_CSDPostMultiScanGanged)
    {
        #ifdef cyCapsense_ENTRY_CALLBACK
            cyCapsense_EntryCallback();
        #endif /* cyCapsense_ENTRY_CALLBACK */

        /* Clear pending interrupt */
        CY_SET_REG32(cyCapsense_INTR_PTR, cyCapsense_INTR_SET_MASK);

         /* Read Rawdata */
        cyCapsense_SsCSDPostScan();

        /* Connect Vref Buffer to AMUX bus */
        CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CTANK_PRECHARGE_CONFIG_CSD_EN);

        #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
            if (cyCapsense_FREQ_CHANNEL_2 == cyCapsense_scanFreqIndex)
            {
                cyCapsense_SsCSDDisconnectSnsExt((uint32)cyCapsense_widgetIndex, (uint32)cyCapsense_sensorIndex);
            }
        #else
            cyCapsense_SsCSDDisconnectSnsExt((uint32)cyCapsense_widgetIndex, (uint32)cyCapsense_sensorIndex);
        #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

        #if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
            if (cyCapsense_FREQ_CHANNEL_2 > cyCapsense_scanFreqIndex)
            {
                 /* Scan the next channel */
                cyCapsense_SsNextFrequencyScan();
            }
            else
            {
                /* All channels are scanned. Set IMO to zero channel */
                cyCapsense_scanFreqIndex = cyCapsense_FREQ_CHANNEL_0;

                #if (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD)
                    cyCapsense_SsChangeImoFreq(cyCapsense_FREQ_CHANNEL_0);
                #else
                    cyCapsense_SsChangeClkFreq(cyCapsense_FREQ_CHANNEL_0);
                #endif /* (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD) */

                 /* Scan the next sensor */
                cyCapsense_SsCSDInitNextScan();
            }
        #else
             /* Scan the next sensor */
            cyCapsense_SsCSDInitNextScan();
        #endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

        #ifdef cyCapsense_EXIT_CALLBACK
            cyCapsense_ExitCallback();
        #endif /* cyCapsense_EXIT_CALLBACK */
    }
    #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_GANGED_SNS_EN) */

#endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */

#endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_EN) || (cyCapsense_ENABLE == cyCapsense_CSD_CSX_EN)) */

/** \}
 * \endcond */


#if ((cyCapsense_ENABLE == cyCapsense_CSD_EN) || (cyCapsense_ENABLE == cyCapsense_CSD_CSX_EN))

/*******************************************************************************
* Function Name: cyCapsense_SsCSDPostScan
****************************************************************************//**
*
* \brief
*   This function reads rawdata and releases required HW resources after scan.
*
* \details
*   This function performs following tasks after scan:
*   - Reads SlotResult from Raw Counter;
*   - Inits bad Conversions number;
*   - Disconnects Vrefhi from AMUBUF positive input;
*   - Disconnects AMUBUF output from CSDBUSB with sych PHI2+HSCMP;
*   - Opens HCBV and HCBG switches.
*
*******************************************************************************/
static void cyCapsense_SsCSDPostScan(void)
{
    #if (cyCapsense_ENABLE == cyCapsense_CSDV2)

        uint32 tmpRawData;
        uint32 tmpMaxCount;
        cyCapsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (cyCapsense_RAM_WD_BASE_STRUCT *)
                                            cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2WdgtRam;

        /* Read SlotResult from Raw Counter */
        tmpRawData = cyCapsense_RESULT_VAL1_VALUE_MASK & CY_GET_REG32(cyCapsense_COUNTER_PTR);

        tmpMaxCount = ((1uL << ptrWdgt->resolution) - 1uL);
        if(tmpRawData < tmpMaxCount)
        {
            cyCapsense_curRamSnsPtr->raw[cyCapsense_scanFreqIndex] = LO16(tmpRawData);
        }
        else
        {
            cyCapsense_curRamSnsPtr->raw[cyCapsense_scanFreqIndex] = LO16(tmpMaxCount);
        }

        #if (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN)
            /* Init bad Conversions number */
            cyCapsense_badConversionsNum = cyCapsense_BAD_CONVERSIONS_NUM;
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_NOISE_METRIC_EN) */

        #if (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN)
            /* Open HCBV and HCBG switches */
            CY_SET_REG32(cyCapsense_SW_SHIELD_SEL_PTR, cyCapsense_SW_SHIELD_SEL_SW_HCBV_STATIC_OPEN |
                                                             cyCapsense_SW_SHIELD_SEL_SW_HCBG_STATIC_OPEN);
        #endif /* (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_EN) */

    #else

        /* Read SlotResult from Raw Counter */
       cyCapsense_curRamSnsPtr->raw[cyCapsense_scanFreqIndex] = (uint16)CY_GET_REG32(cyCapsense_COUNTER_PTR);

    #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
}


/*******************************************************************************
* Function Name: cyCapsense_SsCSDInitNextScan
****************************************************************************//**
*
* \brief
*   This function initializes the next sensor scan.
*
* \details
*   The function increments the sensor index, updates sense clock for matrix
*   or touchpad widgets only, sets up Compensation IDAC, enables the sensor and
*   scans it. When all the sensors are scanned it continues to set up the next widget
*   until all the widgets are scanned. The CSD block is disabled when all the widgets are
*   scanned.
*
*******************************************************************************/
static void cyCapsense_SsCSDInitNextScan(void)
{
    /* Declare and initialize ptr to widget and sensor structures to appropriate address */
    #if (((cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) || \
          (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN)) || \
          (((cyCapsense_DISABLE == cyCapsense_CSD_COMMON_SNS_CLK_EN) && \
          (cyCapsense_ENABLE == cyCapsense_CSDV2) && \
          (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN))))
        cyCapsense_RAM_WD_BASE_STRUCT *ptrWdgt = (cyCapsense_RAM_WD_BASE_STRUCT *)
                                                        cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2WdgtRam;
    #endif

    /* Check if all the sensors are scanned in widget */
    if (((uint8)cyCapsense_dsFlash.wdgtArray[(cyCapsense_widgetIndex)].totalNumSns - 1u) > cyCapsense_sensorIndex)
    {
        /* Increment sensor index to configure next sensor in widget */
        cyCapsense_sensorIndex++;

        /* Update global pointer to cyCapsense_RAM_SNS_STRUCT to current sensor  */
        cyCapsense_curRamSnsPtr = (cyCapsense_RAM_SNS_STRUCT *)
                                                  cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2SnsRam
                                                  + cyCapsense_sensorIndex;

        /* Configure clock divider to row or column */
        #if ((cyCapsense_DISABLE == cyCapsense_CSD_COMMON_SNS_CLK_EN) && \
             (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN))
            if ((cyCapsense_WD_TOUCHPAD_E == (cyCapsense_WD_TYPE_ENUM)cyCapsense_dsFlash.wdgtArray[(cyCapsense_widgetIndex)].wdgtType) ||
                (cyCapsense_WD_MATRIX_BUTTON_E == (cyCapsense_WD_TYPE_ENUM)cyCapsense_dsFlash.wdgtArray[(cyCapsense_widgetIndex)].wdgtType))
            {
                cyCapsense_SsCSDConfigClock();

                #if (cyCapsense_ENABLE == cyCapsense_CSDV2)
                     /* Set up scanning resolution */
                    cyCapsense_SsCSDCalculateScanDuration(ptrWdgt);
                #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
            }
        #endif /* ((cyCapsense_DISABLE == cyCapsense_CSD_COMMON_SNS_CLK_EN) && \
                   (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN))) */

        /* Setup Compensation IDAC for next sensor in widget */
        #if ((cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) || \
             (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN))
            cyCapsense_SsCSDSetUpIdacs(ptrWdgt);
        #endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_IDAC_COMP_EN) || \
                   (cyCapsense_CSD_MATRIX_WIDGET_EN || cyCapsense_CSD_TOUCHPAD_WIDGET_EN)) */

        /* Enable sensor */
        cyCapsense_SsCSDConnectSensorExt((uint32)cyCapsense_widgetIndex, (uint32)cyCapsense_sensorIndex);

        /* Proceed scanning */
        cyCapsense_SsCSDStartSample();
    }
    /* Call scan next widget API if requested, if not, complete the scan  */
    else
    {
        cyCapsense_sensorIndex = 0u;

        /* Current widget is totally scanned. Reset WIDGET BUSY flag */
        cyCapsense_dsRam.status &= ~cyCapsense_WDGT_SW_STS_BUSY;

        /* Check if all the widgets have been scanned */
        if (cyCapsense_ENABLE == cyCapsense_requestScanAllWidget)
        {
            /* Configure and begin scanning next widget */
            cyCapsense_SsPostAllWidgetsScan();
        }
        else
        {
            #if (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN)
                #if (cyCapsense_ENABLE == cyCapsense_CSDV2)
                    /* Disable the CSD block */
                    CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd);
                #else
                    /* Disable the CSD block. Connect Vref Buffer to AMUX bus */
                    #if ((cyCapsense_CSH_PRECHARGE_IO_BUF == cyCapsense_CSD_CSH_PRECHARGE_SRC) &&\
                         (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN))
                        CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CMOD_PRECHARGE_CONFIG);
                    #else
                        CY_SET_REG32(cyCapsense_CONFIG_PTR, cyCapsense_configCsd | cyCapsense_CTANK_PRECHARGE_CONFIG);
                    #endif /* ((cyCapsense_CSH_PRECHARGE_IO_BUF == cyCapsense_CSD_CSH_PRECHARGE_SRC) &&\
                               (cyCapsense_ENABLE == cyCapsense_CSD_SHIELD_TANK_EN)) */
                #endif /* (cyCapsense_ENABLE == cyCapsense_CSDV2) */
            #endif /* (cyCapsense_ENABLE == cyCapsense_BLOCK_OFF_AFTER_SCAN_EN) */

            /* All widgets are totally scanned. Reset BUSY flag */
            cyCapsense_dsRam.status &= ~cyCapsense_SW_STS_BUSY;

            /* Update scan Counter */
            cyCapsense_dsRam.scanCounter++;
        }
    }
}

#if (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN)
    /*******************************************************************************
    * Function Name: cyCapsense_SsNextFrequencyScan
    ****************************************************************************//**
    *
    * \brief
    *   This function scans the sensor on the next frequency channel.
    *
    * \details
    *   The function increments the frequency channel, changes IMO and initializes
    *   the scanning process of the same sensor.
    *
    *******************************************************************************/
    static void cyCapsense_SsNextFrequencyScan(void)
    {
        cyCapsense_RAM_WD_BASE_STRUCT const *ptrWdgt = (cyCapsense_RAM_WD_BASE_STRUCT *)
                                                        cyCapsense_dsFlash.wdgtArray[cyCapsense_widgetIndex].ptr2WdgtRam;

        cyCapsense_scanFreqIndex++;

        /* Set Immunity */
        #if (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD)
            cyCapsense_SsChangeImoFreq((uint32)cyCapsense_scanFreqIndex);
        #else
            cyCapsense_SsChangeClkFreq((uint32)cyCapsense_scanFreqIndex);
        #endif /* (cyCapsense_MFS_IMO == cyCapsense_MFS_METHOD) */

        /* Update IDAC registers */
        cyCapsense_SsCSDSetUpIdacs(ptrWdgt);

        /* Proceed scanning */
        cyCapsense_SsCSDStartSample();
    }
#endif /* (cyCapsense_ENABLE == cyCapsense_MULTI_FREQ_SCAN_EN) */

#endif /* ((cyCapsense_ENABLE == cyCapsense_CSD_EN) || (cyCapsense_ENABLE == cyCapsense_CSD_CSX_EN)) */


/* [] END OF FILE */

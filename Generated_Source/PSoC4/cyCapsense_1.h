/***************************************************************************//**
* \file cyCapsense_1.h
* \version 6.0
*
* \brief
*   This file includes all header files of the cyCapsense_1 Component modules.
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

#if !defined(CY_SENSE_cyCapsense_1_H)

#define CY_SENSE_cyCapsense_1_H

#include "cyCapsense_1_Configuration.h"
#include "cyCapsense_1_Control.h"
#include "cyCapsense_1_Filter.h"
#include "cyCapsense_1_Processing.h"
#include "cyCapsense_1_Sensing.h"
#if (cyCapsense_1_ENABLE == cyCapsense_1_CSD_EN)
    #include "cyCapsense_1_SensingCSD_LL.h"
#endif /* (cyCapsense_1_ENABLE == cyCapsense_1_CSD_EN) */
#if (cyCapsense_1_ENABLE == cyCapsense_1_CSX_EN)
    #include "cyCapsense_1_SensingCSX_LL.h"
#endif /* (cyCapsense_1_ENABLE == cyCapsense_1_CSX_EN) */
#if (cyCapsense_1_ENABLE == cyCapsense_1_ISX_EN)
    #include "cyCapsense_1_SensingISX_LL.h"
#endif /* (cyCapsense_1_ENABLE == cyCapsense_1_ISX_EN) */
#include "cyCapsense_1_Structure.h"
#include "cyCapsense_1_Tuner.h"

#endif /* End CY_SENSE_cyCapsense_1_H */


/* [] END OF FILE */
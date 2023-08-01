/*******************************************************************************
* File Name: cyBuzzerPWM.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the cyBuzzerPWM
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_cyBuzzerPWM_H)
#define CY_TCPWM_cyBuzzerPWM_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} cyBuzzerPWM_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  cyBuzzerPWM_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define cyBuzzerPWM_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define cyBuzzerPWM_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define cyBuzzerPWM_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define cyBuzzerPWM_QUAD_ENCODING_MODES            (0lu)
#define cyBuzzerPWM_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define cyBuzzerPWM_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define cyBuzzerPWM_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define cyBuzzerPWM_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define cyBuzzerPWM_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define cyBuzzerPWM_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define cyBuzzerPWM_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define cyBuzzerPWM_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define cyBuzzerPWM_TC_RUN_MODE                    (0lu)
#define cyBuzzerPWM_TC_COUNTER_MODE                (0lu)
#define cyBuzzerPWM_TC_COMP_CAP_MODE               (2lu)
#define cyBuzzerPWM_TC_PRESCALER                   (0lu)

/* Signal modes */
#define cyBuzzerPWM_TC_RELOAD_SIGNAL_MODE          (0lu)
#define cyBuzzerPWM_TC_COUNT_SIGNAL_MODE           (3lu)
#define cyBuzzerPWM_TC_START_SIGNAL_MODE           (0lu)
#define cyBuzzerPWM_TC_STOP_SIGNAL_MODE            (0lu)
#define cyBuzzerPWM_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define cyBuzzerPWM_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define cyBuzzerPWM_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define cyBuzzerPWM_TC_START_SIGNAL_PRESENT        (0lu)
#define cyBuzzerPWM_TC_STOP_SIGNAL_PRESENT         (0lu)
#define cyBuzzerPWM_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define cyBuzzerPWM_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define cyBuzzerPWM_PWM_KILL_EVENT                 (0lu)
#define cyBuzzerPWM_PWM_STOP_EVENT                 (0lu)
#define cyBuzzerPWM_PWM_MODE                       (4lu)
#define cyBuzzerPWM_PWM_OUT_N_INVERT               (0lu)
#define cyBuzzerPWM_PWM_OUT_INVERT                 (0lu)
#define cyBuzzerPWM_PWM_ALIGN                      (0lu)
#define cyBuzzerPWM_PWM_RUN_MODE                   (0lu)
#define cyBuzzerPWM_PWM_DEAD_TIME_CYCLE            (0lu)
#define cyBuzzerPWM_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define cyBuzzerPWM_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define cyBuzzerPWM_PWM_COUNT_SIGNAL_MODE          (3lu)
#define cyBuzzerPWM_PWM_START_SIGNAL_MODE          (0lu)
#define cyBuzzerPWM_PWM_STOP_SIGNAL_MODE           (0lu)
#define cyBuzzerPWM_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define cyBuzzerPWM_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define cyBuzzerPWM_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define cyBuzzerPWM_PWM_START_SIGNAL_PRESENT       (0lu)
#define cyBuzzerPWM_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define cyBuzzerPWM_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define cyBuzzerPWM_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define cyBuzzerPWM_TC_PERIOD_VALUE                (65535lu)
#define cyBuzzerPWM_TC_COMPARE_VALUE               (65535lu)
#define cyBuzzerPWM_TC_COMPARE_BUF_VALUE           (65535lu)
#define cyBuzzerPWM_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define cyBuzzerPWM_PWM_PERIOD_VALUE               (65535lu)
#define cyBuzzerPWM_PWM_PERIOD_BUF_VALUE           (65535lu)
#define cyBuzzerPWM_PWM_PERIOD_SWAP                (0lu)
#define cyBuzzerPWM_PWM_COMPARE_VALUE              (65535lu)
#define cyBuzzerPWM_PWM_COMPARE_BUF_VALUE          (65535lu)
#define cyBuzzerPWM_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define cyBuzzerPWM__LEFT 0
#define cyBuzzerPWM__RIGHT 1
#define cyBuzzerPWM__CENTER 2
#define cyBuzzerPWM__ASYMMETRIC 3

#define cyBuzzerPWM__X1 0
#define cyBuzzerPWM__X2 1
#define cyBuzzerPWM__X4 2

#define cyBuzzerPWM__PWM 4
#define cyBuzzerPWM__PWM_DT 5
#define cyBuzzerPWM__PWM_PR 6

#define cyBuzzerPWM__INVERSE 1
#define cyBuzzerPWM__DIRECT 0

#define cyBuzzerPWM__CAPTURE 2
#define cyBuzzerPWM__COMPARE 0

#define cyBuzzerPWM__TRIG_LEVEL 3
#define cyBuzzerPWM__TRIG_RISING 0
#define cyBuzzerPWM__TRIG_FALLING 1
#define cyBuzzerPWM__TRIG_BOTH 2

#define cyBuzzerPWM__INTR_MASK_TC 1
#define cyBuzzerPWM__INTR_MASK_CC_MATCH 2
#define cyBuzzerPWM__INTR_MASK_NONE 0
#define cyBuzzerPWM__INTR_MASK_TC_CC 3

#define cyBuzzerPWM__UNCONFIG 8
#define cyBuzzerPWM__TIMER 1
#define cyBuzzerPWM__QUAD 3
#define cyBuzzerPWM__PWM_SEL 7

#define cyBuzzerPWM__COUNT_UP 0
#define cyBuzzerPWM__COUNT_DOWN 1
#define cyBuzzerPWM__COUNT_UPDOWN0 2
#define cyBuzzerPWM__COUNT_UPDOWN1 3


/* Prescaler */
#define cyBuzzerPWM_PRESCALE_DIVBY1                ((uint32)(0u << cyBuzzerPWM_PRESCALER_SHIFT))
#define cyBuzzerPWM_PRESCALE_DIVBY2                ((uint32)(1u << cyBuzzerPWM_PRESCALER_SHIFT))
#define cyBuzzerPWM_PRESCALE_DIVBY4                ((uint32)(2u << cyBuzzerPWM_PRESCALER_SHIFT))
#define cyBuzzerPWM_PRESCALE_DIVBY8                ((uint32)(3u << cyBuzzerPWM_PRESCALER_SHIFT))
#define cyBuzzerPWM_PRESCALE_DIVBY16               ((uint32)(4u << cyBuzzerPWM_PRESCALER_SHIFT))
#define cyBuzzerPWM_PRESCALE_DIVBY32               ((uint32)(5u << cyBuzzerPWM_PRESCALER_SHIFT))
#define cyBuzzerPWM_PRESCALE_DIVBY64               ((uint32)(6u << cyBuzzerPWM_PRESCALER_SHIFT))
#define cyBuzzerPWM_PRESCALE_DIVBY128              ((uint32)(7u << cyBuzzerPWM_PRESCALER_SHIFT))

/* TCPWM set modes */
#define cyBuzzerPWM_MODE_TIMER_COMPARE             ((uint32)(cyBuzzerPWM__COMPARE         <<  \
                                                                  cyBuzzerPWM_MODE_SHIFT))
#define cyBuzzerPWM_MODE_TIMER_CAPTURE             ((uint32)(cyBuzzerPWM__CAPTURE         <<  \
                                                                  cyBuzzerPWM_MODE_SHIFT))
#define cyBuzzerPWM_MODE_QUAD                      ((uint32)(cyBuzzerPWM__QUAD            <<  \
                                                                  cyBuzzerPWM_MODE_SHIFT))
#define cyBuzzerPWM_MODE_PWM                       ((uint32)(cyBuzzerPWM__PWM             <<  \
                                                                  cyBuzzerPWM_MODE_SHIFT))
#define cyBuzzerPWM_MODE_PWM_DT                    ((uint32)(cyBuzzerPWM__PWM_DT          <<  \
                                                                  cyBuzzerPWM_MODE_SHIFT))
#define cyBuzzerPWM_MODE_PWM_PR                    ((uint32)(cyBuzzerPWM__PWM_PR          <<  \
                                                                  cyBuzzerPWM_MODE_SHIFT))

/* Quad Modes */
#define cyBuzzerPWM_MODE_X1                        ((uint32)(cyBuzzerPWM__X1              <<  \
                                                                  cyBuzzerPWM_QUAD_MODE_SHIFT))
#define cyBuzzerPWM_MODE_X2                        ((uint32)(cyBuzzerPWM__X2              <<  \
                                                                  cyBuzzerPWM_QUAD_MODE_SHIFT))
#define cyBuzzerPWM_MODE_X4                        ((uint32)(cyBuzzerPWM__X4              <<  \
                                                                  cyBuzzerPWM_QUAD_MODE_SHIFT))

/* Counter modes */
#define cyBuzzerPWM_COUNT_UP                       ((uint32)(cyBuzzerPWM__COUNT_UP        <<  \
                                                                  cyBuzzerPWM_UPDOWN_SHIFT))
#define cyBuzzerPWM_COUNT_DOWN                     ((uint32)(cyBuzzerPWM__COUNT_DOWN      <<  \
                                                                  cyBuzzerPWM_UPDOWN_SHIFT))
#define cyBuzzerPWM_COUNT_UPDOWN0                  ((uint32)(cyBuzzerPWM__COUNT_UPDOWN0   <<  \
                                                                  cyBuzzerPWM_UPDOWN_SHIFT))
#define cyBuzzerPWM_COUNT_UPDOWN1                  ((uint32)(cyBuzzerPWM__COUNT_UPDOWN1   <<  \
                                                                  cyBuzzerPWM_UPDOWN_SHIFT))

/* PWM output invert */
#define cyBuzzerPWM_INVERT_LINE                    ((uint32)(cyBuzzerPWM__INVERSE         <<  \
                                                                  cyBuzzerPWM_INV_OUT_SHIFT))
#define cyBuzzerPWM_INVERT_LINE_N                  ((uint32)(cyBuzzerPWM__INVERSE         <<  \
                                                                  cyBuzzerPWM_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define cyBuzzerPWM_TRIG_RISING                    ((uint32)cyBuzzerPWM__TRIG_RISING)
#define cyBuzzerPWM_TRIG_FALLING                   ((uint32)cyBuzzerPWM__TRIG_FALLING)
#define cyBuzzerPWM_TRIG_BOTH                      ((uint32)cyBuzzerPWM__TRIG_BOTH)
#define cyBuzzerPWM_TRIG_LEVEL                     ((uint32)cyBuzzerPWM__TRIG_LEVEL)

/* Interrupt mask */
#define cyBuzzerPWM_INTR_MASK_TC                   ((uint32)cyBuzzerPWM__INTR_MASK_TC)
#define cyBuzzerPWM_INTR_MASK_CC_MATCH             ((uint32)cyBuzzerPWM__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define cyBuzzerPWM_CC_MATCH_SET                   (0x00u)
#define cyBuzzerPWM_CC_MATCH_CLEAR                 (0x01u)
#define cyBuzzerPWM_CC_MATCH_INVERT                (0x02u)
#define cyBuzzerPWM_CC_MATCH_NO_CHANGE             (0x03u)
#define cyBuzzerPWM_OVERLOW_SET                    (0x00u)
#define cyBuzzerPWM_OVERLOW_CLEAR                  (0x04u)
#define cyBuzzerPWM_OVERLOW_INVERT                 (0x08u)
#define cyBuzzerPWM_OVERLOW_NO_CHANGE              (0x0Cu)
#define cyBuzzerPWM_UNDERFLOW_SET                  (0x00u)
#define cyBuzzerPWM_UNDERFLOW_CLEAR                (0x10u)
#define cyBuzzerPWM_UNDERFLOW_INVERT               (0x20u)
#define cyBuzzerPWM_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define cyBuzzerPWM_PWM_MODE_LEFT                  (cyBuzzerPWM_CC_MATCH_CLEAR        |   \
                                                         cyBuzzerPWM_OVERLOW_SET           |   \
                                                         cyBuzzerPWM_UNDERFLOW_NO_CHANGE)
#define cyBuzzerPWM_PWM_MODE_RIGHT                 (cyBuzzerPWM_CC_MATCH_SET          |   \
                                                         cyBuzzerPWM_OVERLOW_NO_CHANGE     |   \
                                                         cyBuzzerPWM_UNDERFLOW_CLEAR)
#define cyBuzzerPWM_PWM_MODE_ASYM                  (cyBuzzerPWM_CC_MATCH_INVERT       |   \
                                                         cyBuzzerPWM_OVERLOW_SET           |   \
                                                         cyBuzzerPWM_UNDERFLOW_CLEAR)

#if (cyBuzzerPWM_CY_TCPWM_V2)
    #if(cyBuzzerPWM_CY_TCPWM_4000)
        #define cyBuzzerPWM_PWM_MODE_CENTER                (cyBuzzerPWM_CC_MATCH_INVERT       |   \
                                                                 cyBuzzerPWM_OVERLOW_NO_CHANGE     |   \
                                                                 cyBuzzerPWM_UNDERFLOW_CLEAR)
    #else
        #define cyBuzzerPWM_PWM_MODE_CENTER                (cyBuzzerPWM_CC_MATCH_INVERT       |   \
                                                                 cyBuzzerPWM_OVERLOW_SET           |   \
                                                                 cyBuzzerPWM_UNDERFLOW_CLEAR)
    #endif /* (cyBuzzerPWM_CY_TCPWM_4000) */
#else
    #define cyBuzzerPWM_PWM_MODE_CENTER                (cyBuzzerPWM_CC_MATCH_INVERT       |   \
                                                             cyBuzzerPWM_OVERLOW_NO_CHANGE     |   \
                                                             cyBuzzerPWM_UNDERFLOW_CLEAR)
#endif /* (cyBuzzerPWM_CY_TCPWM_NEW) */

/* Command operations without condition */
#define cyBuzzerPWM_CMD_CAPTURE                    (0u)
#define cyBuzzerPWM_CMD_RELOAD                     (8u)
#define cyBuzzerPWM_CMD_STOP                       (16u)
#define cyBuzzerPWM_CMD_START                      (24u)

/* Status */
#define cyBuzzerPWM_STATUS_DOWN                    (1u)
#define cyBuzzerPWM_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   cyBuzzerPWM_Init(void);
void   cyBuzzerPWM_Enable(void);
void   cyBuzzerPWM_Start(void);
void   cyBuzzerPWM_Stop(void);

void   cyBuzzerPWM_SetMode(uint32 mode);
void   cyBuzzerPWM_SetCounterMode(uint32 counterMode);
void   cyBuzzerPWM_SetPWMMode(uint32 modeMask);
void   cyBuzzerPWM_SetQDMode(uint32 qdMode);

void   cyBuzzerPWM_SetPrescaler(uint32 prescaler);
void   cyBuzzerPWM_TriggerCommand(uint32 mask, uint32 command);
void   cyBuzzerPWM_SetOneShot(uint32 oneShotEnable);
uint32 cyBuzzerPWM_ReadStatus(void);

void   cyBuzzerPWM_SetPWMSyncKill(uint32 syncKillEnable);
void   cyBuzzerPWM_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   cyBuzzerPWM_SetPWMDeadTime(uint32 deadTime);
void   cyBuzzerPWM_SetPWMInvert(uint32 mask);

void   cyBuzzerPWM_SetInterruptMode(uint32 interruptMask);
uint32 cyBuzzerPWM_GetInterruptSourceMasked(void);
uint32 cyBuzzerPWM_GetInterruptSource(void);
void   cyBuzzerPWM_ClearInterrupt(uint32 interruptMask);
void   cyBuzzerPWM_SetInterrupt(uint32 interruptMask);

void   cyBuzzerPWM_WriteCounter(uint32 count);
uint32 cyBuzzerPWM_ReadCounter(void);

uint32 cyBuzzerPWM_ReadCapture(void);
uint32 cyBuzzerPWM_ReadCaptureBuf(void);

void   cyBuzzerPWM_WritePeriod(uint32 period);
uint32 cyBuzzerPWM_ReadPeriod(void);
void   cyBuzzerPWM_WritePeriodBuf(uint32 periodBuf);
uint32 cyBuzzerPWM_ReadPeriodBuf(void);

void   cyBuzzerPWM_WriteCompare(uint32 compare);
uint32 cyBuzzerPWM_ReadCompare(void);
void   cyBuzzerPWM_WriteCompareBuf(uint32 compareBuf);
uint32 cyBuzzerPWM_ReadCompareBuf(void);

void   cyBuzzerPWM_SetPeriodSwap(uint32 swapEnable);
void   cyBuzzerPWM_SetCompareSwap(uint32 swapEnable);

void   cyBuzzerPWM_SetCaptureMode(uint32 triggerMode);
void   cyBuzzerPWM_SetReloadMode(uint32 triggerMode);
void   cyBuzzerPWM_SetStartMode(uint32 triggerMode);
void   cyBuzzerPWM_SetStopMode(uint32 triggerMode);
void   cyBuzzerPWM_SetCountMode(uint32 triggerMode);

void   cyBuzzerPWM_SaveConfig(void);
void   cyBuzzerPWM_RestoreConfig(void);
void   cyBuzzerPWM_Sleep(void);
void   cyBuzzerPWM_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define cyBuzzerPWM_BLOCK_CONTROL_REG              (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define cyBuzzerPWM_BLOCK_CONTROL_PTR              ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define cyBuzzerPWM_COMMAND_REG                    (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define cyBuzzerPWM_COMMAND_PTR                    ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define cyBuzzerPWM_INTRRUPT_CAUSE_REG             (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define cyBuzzerPWM_INTRRUPT_CAUSE_PTR             ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define cyBuzzerPWM_CONTROL_REG                    (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__CTRL )
#define cyBuzzerPWM_CONTROL_PTR                    ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__CTRL )
#define cyBuzzerPWM_STATUS_REG                     (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__STATUS )
#define cyBuzzerPWM_STATUS_PTR                     ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__STATUS )
#define cyBuzzerPWM_COUNTER_REG                    (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__COUNTER )
#define cyBuzzerPWM_COUNTER_PTR                    ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__COUNTER )
#define cyBuzzerPWM_COMP_CAP_REG                   (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__CC )
#define cyBuzzerPWM_COMP_CAP_PTR                   ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__CC )
#define cyBuzzerPWM_COMP_CAP_BUF_REG               (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define cyBuzzerPWM_COMP_CAP_BUF_PTR               ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define cyBuzzerPWM_PERIOD_REG                     (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__PERIOD )
#define cyBuzzerPWM_PERIOD_PTR                     ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__PERIOD )
#define cyBuzzerPWM_PERIOD_BUF_REG                 (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define cyBuzzerPWM_PERIOD_BUF_PTR                 ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define cyBuzzerPWM_TRIG_CONTROL0_REG              (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define cyBuzzerPWM_TRIG_CONTROL0_PTR              ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define cyBuzzerPWM_TRIG_CONTROL1_REG              (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define cyBuzzerPWM_TRIG_CONTROL1_PTR              ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define cyBuzzerPWM_TRIG_CONTROL2_REG              (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define cyBuzzerPWM_TRIG_CONTROL2_PTR              ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define cyBuzzerPWM_INTERRUPT_REQ_REG              (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__INTR )
#define cyBuzzerPWM_INTERRUPT_REQ_PTR              ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__INTR )
#define cyBuzzerPWM_INTERRUPT_SET_REG              (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__INTR_SET )
#define cyBuzzerPWM_INTERRUPT_SET_PTR              ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__INTR_SET )
#define cyBuzzerPWM_INTERRUPT_MASK_REG             (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define cyBuzzerPWM_INTERRUPT_MASK_PTR             ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define cyBuzzerPWM_INTERRUPT_MASKED_REG           (*(reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__INTR_MASKED )
#define cyBuzzerPWM_INTERRUPT_MASKED_PTR           ( (reg32 *) cyBuzzerPWM_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define cyBuzzerPWM_MASK                           ((uint32)cyBuzzerPWM_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define cyBuzzerPWM_RELOAD_CC_SHIFT                (0u)
#define cyBuzzerPWM_RELOAD_PERIOD_SHIFT            (1u)
#define cyBuzzerPWM_PWM_SYNC_KILL_SHIFT            (2u)
#define cyBuzzerPWM_PWM_STOP_KILL_SHIFT            (3u)
#define cyBuzzerPWM_PRESCALER_SHIFT                (8u)
#define cyBuzzerPWM_UPDOWN_SHIFT                   (16u)
#define cyBuzzerPWM_ONESHOT_SHIFT                  (18u)
#define cyBuzzerPWM_QUAD_MODE_SHIFT                (20u)
#define cyBuzzerPWM_INV_OUT_SHIFT                  (20u)
#define cyBuzzerPWM_INV_COMPL_OUT_SHIFT            (21u)
#define cyBuzzerPWM_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define cyBuzzerPWM_RELOAD_CC_MASK                 ((uint32)(cyBuzzerPWM_1BIT_MASK        <<  \
                                                                            cyBuzzerPWM_RELOAD_CC_SHIFT))
#define cyBuzzerPWM_RELOAD_PERIOD_MASK             ((uint32)(cyBuzzerPWM_1BIT_MASK        <<  \
                                                                            cyBuzzerPWM_RELOAD_PERIOD_SHIFT))
#define cyBuzzerPWM_PWM_SYNC_KILL_MASK             ((uint32)(cyBuzzerPWM_1BIT_MASK        <<  \
                                                                            cyBuzzerPWM_PWM_SYNC_KILL_SHIFT))
#define cyBuzzerPWM_PWM_STOP_KILL_MASK             ((uint32)(cyBuzzerPWM_1BIT_MASK        <<  \
                                                                            cyBuzzerPWM_PWM_STOP_KILL_SHIFT))
#define cyBuzzerPWM_PRESCALER_MASK                 ((uint32)(cyBuzzerPWM_8BIT_MASK        <<  \
                                                                            cyBuzzerPWM_PRESCALER_SHIFT))
#define cyBuzzerPWM_UPDOWN_MASK                    ((uint32)(cyBuzzerPWM_2BIT_MASK        <<  \
                                                                            cyBuzzerPWM_UPDOWN_SHIFT))
#define cyBuzzerPWM_ONESHOT_MASK                   ((uint32)(cyBuzzerPWM_1BIT_MASK        <<  \
                                                                            cyBuzzerPWM_ONESHOT_SHIFT))
#define cyBuzzerPWM_QUAD_MODE_MASK                 ((uint32)(cyBuzzerPWM_3BIT_MASK        <<  \
                                                                            cyBuzzerPWM_QUAD_MODE_SHIFT))
#define cyBuzzerPWM_INV_OUT_MASK                   ((uint32)(cyBuzzerPWM_2BIT_MASK        <<  \
                                                                            cyBuzzerPWM_INV_OUT_SHIFT))
#define cyBuzzerPWM_MODE_MASK                      ((uint32)(cyBuzzerPWM_3BIT_MASK        <<  \
                                                                            cyBuzzerPWM_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define cyBuzzerPWM_CAPTURE_SHIFT                  (0u)
#define cyBuzzerPWM_COUNT_SHIFT                    (2u)
#define cyBuzzerPWM_RELOAD_SHIFT                   (4u)
#define cyBuzzerPWM_STOP_SHIFT                     (6u)
#define cyBuzzerPWM_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define cyBuzzerPWM_CAPTURE_MASK                   ((uint32)(cyBuzzerPWM_2BIT_MASK        <<  \
                                                                  cyBuzzerPWM_CAPTURE_SHIFT))
#define cyBuzzerPWM_COUNT_MASK                     ((uint32)(cyBuzzerPWM_2BIT_MASK        <<  \
                                                                  cyBuzzerPWM_COUNT_SHIFT))
#define cyBuzzerPWM_RELOAD_MASK                    ((uint32)(cyBuzzerPWM_2BIT_MASK        <<  \
                                                                  cyBuzzerPWM_RELOAD_SHIFT))
#define cyBuzzerPWM_STOP_MASK                      ((uint32)(cyBuzzerPWM_2BIT_MASK        <<  \
                                                                  cyBuzzerPWM_STOP_SHIFT))
#define cyBuzzerPWM_START_MASK                     ((uint32)(cyBuzzerPWM_2BIT_MASK        <<  \
                                                                  cyBuzzerPWM_START_SHIFT))

/* MASK */
#define cyBuzzerPWM_1BIT_MASK                      ((uint32)0x01u)
#define cyBuzzerPWM_2BIT_MASK                      ((uint32)0x03u)
#define cyBuzzerPWM_3BIT_MASK                      ((uint32)0x07u)
#define cyBuzzerPWM_6BIT_MASK                      ((uint32)0x3Fu)
#define cyBuzzerPWM_8BIT_MASK                      ((uint32)0xFFu)
#define cyBuzzerPWM_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define cyBuzzerPWM_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define cyBuzzerPWM_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(cyBuzzerPWM_QUAD_ENCODING_MODES     << cyBuzzerPWM_QUAD_MODE_SHIFT))       |\
         ((uint32)(cyBuzzerPWM_CONFIG                  << cyBuzzerPWM_MODE_SHIFT)))

#define cyBuzzerPWM_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(cyBuzzerPWM_PWM_STOP_EVENT          << cyBuzzerPWM_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(cyBuzzerPWM_PWM_OUT_INVERT          << cyBuzzerPWM_INV_OUT_SHIFT))         |\
         ((uint32)(cyBuzzerPWM_PWM_OUT_N_INVERT        << cyBuzzerPWM_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(cyBuzzerPWM_PWM_MODE                << cyBuzzerPWM_MODE_SHIFT)))

#define cyBuzzerPWM_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(cyBuzzerPWM_PWM_RUN_MODE         << cyBuzzerPWM_ONESHOT_SHIFT))
            
#define cyBuzzerPWM_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(cyBuzzerPWM_PWM_ALIGN            << cyBuzzerPWM_UPDOWN_SHIFT))

#define cyBuzzerPWM_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(cyBuzzerPWM_PWM_KILL_EVENT      << cyBuzzerPWM_PWM_SYNC_KILL_SHIFT))

#define cyBuzzerPWM_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(cyBuzzerPWM_PWM_DEAD_TIME_CYCLE  << cyBuzzerPWM_PRESCALER_SHIFT))

#define cyBuzzerPWM_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(cyBuzzerPWM_PWM_PRESCALER        << cyBuzzerPWM_PRESCALER_SHIFT))

#define cyBuzzerPWM_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(cyBuzzerPWM_TC_PRESCALER            << cyBuzzerPWM_PRESCALER_SHIFT))       |\
         ((uint32)(cyBuzzerPWM_TC_COUNTER_MODE         << cyBuzzerPWM_UPDOWN_SHIFT))          |\
         ((uint32)(cyBuzzerPWM_TC_RUN_MODE             << cyBuzzerPWM_ONESHOT_SHIFT))         |\
         ((uint32)(cyBuzzerPWM_TC_COMP_CAP_MODE        << cyBuzzerPWM_MODE_SHIFT)))
        
#define cyBuzzerPWM_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(cyBuzzerPWM_QUAD_PHIA_SIGNAL_MODE   << cyBuzzerPWM_COUNT_SHIFT))           |\
         ((uint32)(cyBuzzerPWM_QUAD_INDEX_SIGNAL_MODE  << cyBuzzerPWM_RELOAD_SHIFT))          |\
         ((uint32)(cyBuzzerPWM_QUAD_STOP_SIGNAL_MODE   << cyBuzzerPWM_STOP_SHIFT))            |\
         ((uint32)(cyBuzzerPWM_QUAD_PHIB_SIGNAL_MODE   << cyBuzzerPWM_START_SHIFT)))

#define cyBuzzerPWM_PWM_SIGNALS_MODES                                                              \
        (((uint32)(cyBuzzerPWM_PWM_SWITCH_SIGNAL_MODE  << cyBuzzerPWM_CAPTURE_SHIFT))         |\
         ((uint32)(cyBuzzerPWM_PWM_COUNT_SIGNAL_MODE   << cyBuzzerPWM_COUNT_SHIFT))           |\
         ((uint32)(cyBuzzerPWM_PWM_RELOAD_SIGNAL_MODE  << cyBuzzerPWM_RELOAD_SHIFT))          |\
         ((uint32)(cyBuzzerPWM_PWM_STOP_SIGNAL_MODE    << cyBuzzerPWM_STOP_SHIFT))            |\
         ((uint32)(cyBuzzerPWM_PWM_START_SIGNAL_MODE   << cyBuzzerPWM_START_SHIFT)))

#define cyBuzzerPWM_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(cyBuzzerPWM_TC_CAPTURE_SIGNAL_MODE  << cyBuzzerPWM_CAPTURE_SHIFT))         |\
         ((uint32)(cyBuzzerPWM_TC_COUNT_SIGNAL_MODE    << cyBuzzerPWM_COUNT_SHIFT))           |\
         ((uint32)(cyBuzzerPWM_TC_RELOAD_SIGNAL_MODE   << cyBuzzerPWM_RELOAD_SHIFT))          |\
         ((uint32)(cyBuzzerPWM_TC_STOP_SIGNAL_MODE     << cyBuzzerPWM_STOP_SHIFT))            |\
         ((uint32)(cyBuzzerPWM_TC_START_SIGNAL_MODE    << cyBuzzerPWM_START_SHIFT)))
        
#define cyBuzzerPWM_TIMER_UPDOWN_CNT_USED                                                          \
                ((cyBuzzerPWM__COUNT_UPDOWN0 == cyBuzzerPWM_TC_COUNTER_MODE)                  ||\
                 (cyBuzzerPWM__COUNT_UPDOWN1 == cyBuzzerPWM_TC_COUNTER_MODE))

#define cyBuzzerPWM_PWM_UPDOWN_CNT_USED                                                            \
                ((cyBuzzerPWM__CENTER == cyBuzzerPWM_PWM_ALIGN)                               ||\
                 (cyBuzzerPWM__ASYMMETRIC == cyBuzzerPWM_PWM_ALIGN))               
        
#define cyBuzzerPWM_PWM_PR_INIT_VALUE              (1u)
#define cyBuzzerPWM_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_cyBuzzerPWM_H */

/* [] END OF FILE */

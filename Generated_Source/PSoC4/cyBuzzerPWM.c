/*******************************************************************************
* File Name: cyBuzzerPWM.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the cyBuzzerPWM
*  component
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

#include "cyBuzzerPWM.h"

uint8 cyBuzzerPWM_initVar = 0u;


/*******************************************************************************
* Function Name: cyBuzzerPWM_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default cyBuzzerPWM configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (cyBuzzerPWM__QUAD == cyBuzzerPWM_CONFIG)
        cyBuzzerPWM_CONTROL_REG = cyBuzzerPWM_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        cyBuzzerPWM_TRIG_CONTROL1_REG  = cyBuzzerPWM_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        cyBuzzerPWM_SetInterruptMode(cyBuzzerPWM_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        cyBuzzerPWM_SetCounterMode(cyBuzzerPWM_COUNT_DOWN);
        cyBuzzerPWM_WritePeriod(cyBuzzerPWM_QUAD_PERIOD_INIT_VALUE);
        cyBuzzerPWM_WriteCounter(cyBuzzerPWM_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (cyBuzzerPWM__QUAD == cyBuzzerPWM_CONFIG) */

    #if (cyBuzzerPWM__TIMER == cyBuzzerPWM_CONFIG)
        cyBuzzerPWM_CONTROL_REG = cyBuzzerPWM_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        cyBuzzerPWM_TRIG_CONTROL1_REG  = cyBuzzerPWM_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        cyBuzzerPWM_SetInterruptMode(cyBuzzerPWM_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        cyBuzzerPWM_WritePeriod(cyBuzzerPWM_TC_PERIOD_VALUE );

        #if (cyBuzzerPWM__COMPARE == cyBuzzerPWM_TC_COMP_CAP_MODE)
            cyBuzzerPWM_WriteCompare(cyBuzzerPWM_TC_COMPARE_VALUE);

            #if (1u == cyBuzzerPWM_TC_COMPARE_SWAP)
                cyBuzzerPWM_SetCompareSwap(1u);
                cyBuzzerPWM_WriteCompareBuf(cyBuzzerPWM_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == cyBuzzerPWM_TC_COMPARE_SWAP) */
        #endif  /* (cyBuzzerPWM__COMPARE == cyBuzzerPWM_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (cyBuzzerPWM_CY_TCPWM_V2 && cyBuzzerPWM_TIMER_UPDOWN_CNT_USED && !cyBuzzerPWM_CY_TCPWM_4000)
            cyBuzzerPWM_WriteCounter(1u);
        #elif(cyBuzzerPWM__COUNT_DOWN == cyBuzzerPWM_TC_COUNTER_MODE)
            cyBuzzerPWM_WriteCounter(cyBuzzerPWM_TC_PERIOD_VALUE);
        #else
            cyBuzzerPWM_WriteCounter(0u);
        #endif /* (cyBuzzerPWM_CY_TCPWM_V2 && cyBuzzerPWM_TIMER_UPDOWN_CNT_USED && !cyBuzzerPWM_CY_TCPWM_4000) */
    #endif  /* (cyBuzzerPWM__TIMER == cyBuzzerPWM_CONFIG) */

    #if (cyBuzzerPWM__PWM_SEL == cyBuzzerPWM_CONFIG)
        cyBuzzerPWM_CONTROL_REG = cyBuzzerPWM_CTRL_PWM_BASE_CONFIG;

        #if (cyBuzzerPWM__PWM_PR == cyBuzzerPWM_PWM_MODE)
            cyBuzzerPWM_CONTROL_REG |= cyBuzzerPWM_CTRL_PWM_RUN_MODE;
            cyBuzzerPWM_WriteCounter(cyBuzzerPWM_PWM_PR_INIT_VALUE);
        #else
            cyBuzzerPWM_CONTROL_REG |= cyBuzzerPWM_CTRL_PWM_ALIGN | cyBuzzerPWM_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (cyBuzzerPWM_CY_TCPWM_V2 && cyBuzzerPWM_PWM_UPDOWN_CNT_USED && !cyBuzzerPWM_CY_TCPWM_4000)
                cyBuzzerPWM_WriteCounter(1u);
            #elif (cyBuzzerPWM__RIGHT == cyBuzzerPWM_PWM_ALIGN)
                cyBuzzerPWM_WriteCounter(cyBuzzerPWM_PWM_PERIOD_VALUE);
            #else 
                cyBuzzerPWM_WriteCounter(0u);
            #endif  /* (cyBuzzerPWM_CY_TCPWM_V2 && cyBuzzerPWM_PWM_UPDOWN_CNT_USED && !cyBuzzerPWM_CY_TCPWM_4000) */
        #endif  /* (cyBuzzerPWM__PWM_PR == cyBuzzerPWM_PWM_MODE) */

        #if (cyBuzzerPWM__PWM_DT == cyBuzzerPWM_PWM_MODE)
            cyBuzzerPWM_CONTROL_REG |= cyBuzzerPWM_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (cyBuzzerPWM__PWM_DT == cyBuzzerPWM_PWM_MODE) */

        #if (cyBuzzerPWM__PWM == cyBuzzerPWM_PWM_MODE)
            cyBuzzerPWM_CONTROL_REG |= cyBuzzerPWM_CTRL_PWM_PRESCALER;
        #endif  /* (cyBuzzerPWM__PWM == cyBuzzerPWM_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        cyBuzzerPWM_TRIG_CONTROL1_REG  = cyBuzzerPWM_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        cyBuzzerPWM_SetInterruptMode(cyBuzzerPWM_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (cyBuzzerPWM__PWM_PR == cyBuzzerPWM_PWM_MODE)
            cyBuzzerPWM_TRIG_CONTROL2_REG =
                    (cyBuzzerPWM_CC_MATCH_NO_CHANGE    |
                    cyBuzzerPWM_OVERLOW_NO_CHANGE      |
                    cyBuzzerPWM_UNDERFLOW_NO_CHANGE);
        #else
            #if (cyBuzzerPWM__LEFT == cyBuzzerPWM_PWM_ALIGN)
                cyBuzzerPWM_TRIG_CONTROL2_REG = cyBuzzerPWM_PWM_MODE_LEFT;
            #endif  /* ( cyBuzzerPWM_PWM_LEFT == cyBuzzerPWM_PWM_ALIGN) */

            #if (cyBuzzerPWM__RIGHT == cyBuzzerPWM_PWM_ALIGN)
                cyBuzzerPWM_TRIG_CONTROL2_REG = cyBuzzerPWM_PWM_MODE_RIGHT;
            #endif  /* ( cyBuzzerPWM_PWM_RIGHT == cyBuzzerPWM_PWM_ALIGN) */

            #if (cyBuzzerPWM__CENTER == cyBuzzerPWM_PWM_ALIGN)
                cyBuzzerPWM_TRIG_CONTROL2_REG = cyBuzzerPWM_PWM_MODE_CENTER;
            #endif  /* ( cyBuzzerPWM_PWM_CENTER == cyBuzzerPWM_PWM_ALIGN) */

            #if (cyBuzzerPWM__ASYMMETRIC == cyBuzzerPWM_PWM_ALIGN)
                cyBuzzerPWM_TRIG_CONTROL2_REG = cyBuzzerPWM_PWM_MODE_ASYM;
            #endif  /* (cyBuzzerPWM__ASYMMETRIC == cyBuzzerPWM_PWM_ALIGN) */
        #endif  /* (cyBuzzerPWM__PWM_PR == cyBuzzerPWM_PWM_MODE) */

        /* Set other values from customizer */
        cyBuzzerPWM_WritePeriod(cyBuzzerPWM_PWM_PERIOD_VALUE );
        cyBuzzerPWM_WriteCompare(cyBuzzerPWM_PWM_COMPARE_VALUE);

        #if (1u == cyBuzzerPWM_PWM_COMPARE_SWAP)
            cyBuzzerPWM_SetCompareSwap(1u);
            cyBuzzerPWM_WriteCompareBuf(cyBuzzerPWM_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == cyBuzzerPWM_PWM_COMPARE_SWAP) */

        #if (1u == cyBuzzerPWM_PWM_PERIOD_SWAP)
            cyBuzzerPWM_SetPeriodSwap(1u);
            cyBuzzerPWM_WritePeriodBuf(cyBuzzerPWM_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == cyBuzzerPWM_PWM_PERIOD_SWAP) */
    #endif  /* (cyBuzzerPWM__PWM_SEL == cyBuzzerPWM_CONFIG) */
    
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_Enable
********************************************************************************
*
* Summary:
*  Enables the cyBuzzerPWM.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    cyBuzzerPWM_BLOCK_CONTROL_REG |= cyBuzzerPWM_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (cyBuzzerPWM__PWM_SEL == cyBuzzerPWM_CONFIG)
        #if (0u == cyBuzzerPWM_PWM_START_SIGNAL_PRESENT)
            cyBuzzerPWM_TriggerCommand(cyBuzzerPWM_MASK, cyBuzzerPWM_CMD_START);
        #endif /* (0u == cyBuzzerPWM_PWM_START_SIGNAL_PRESENT) */
    #endif /* (cyBuzzerPWM__PWM_SEL == cyBuzzerPWM_CONFIG) */

    #if (cyBuzzerPWM__TIMER == cyBuzzerPWM_CONFIG)
        #if (0u == cyBuzzerPWM_TC_START_SIGNAL_PRESENT)
            cyBuzzerPWM_TriggerCommand(cyBuzzerPWM_MASK, cyBuzzerPWM_CMD_START);
        #endif /* (0u == cyBuzzerPWM_TC_START_SIGNAL_PRESENT) */
    #endif /* (cyBuzzerPWM__TIMER == cyBuzzerPWM_CONFIG) */
    
    #if (cyBuzzerPWM__QUAD == cyBuzzerPWM_CONFIG)
        #if (0u != cyBuzzerPWM_QUAD_AUTO_START)
            cyBuzzerPWM_TriggerCommand(cyBuzzerPWM_MASK, cyBuzzerPWM_CMD_RELOAD);
        #endif /* (0u != cyBuzzerPWM_QUAD_AUTO_START) */
    #endif  /* (cyBuzzerPWM__QUAD == cyBuzzerPWM_CONFIG) */
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_Start
********************************************************************************
*
* Summary:
*  Initializes the cyBuzzerPWM with default customizer
*  values when called the first time and enables the cyBuzzerPWM.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  cyBuzzerPWM_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time cyBuzzerPWM_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the cyBuzzerPWM_Start() routine.
*
*******************************************************************************/
void cyBuzzerPWM_Start(void)
{
    if (0u == cyBuzzerPWM_initVar)
    {
        cyBuzzerPWM_Init();
        cyBuzzerPWM_initVar = 1u;
    }

    cyBuzzerPWM_Enable();
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_Stop
********************************************************************************
*
* Summary:
*  Disables the cyBuzzerPWM.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_BLOCK_CONTROL_REG &= (uint32)~cyBuzzerPWM_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the cyBuzzerPWM. This function is used when
*  configured as a generic cyBuzzerPWM and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the cyBuzzerPWM to operate in
*   Values:
*   - cyBuzzerPWM_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - cyBuzzerPWM_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - cyBuzzerPWM_MODE_QUAD - Quadrature decoder
*         - cyBuzzerPWM_MODE_PWM - PWM
*         - cyBuzzerPWM_MODE_PWM_DT - PWM with dead time
*         - cyBuzzerPWM_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_CONTROL_REG &= (uint32)~cyBuzzerPWM_MODE_MASK;
    cyBuzzerPWM_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - cyBuzzerPWM_MODE_X1 - Counts on phi 1 rising
*         - cyBuzzerPWM_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - cyBuzzerPWM_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_CONTROL_REG &= (uint32)~cyBuzzerPWM_QUAD_MODE_MASK;
    cyBuzzerPWM_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - cyBuzzerPWM_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - cyBuzzerPWM_PRESCALE_DIVBY2    - Divide by 2
*         - cyBuzzerPWM_PRESCALE_DIVBY4    - Divide by 4
*         - cyBuzzerPWM_PRESCALE_DIVBY8    - Divide by 8
*         - cyBuzzerPWM_PRESCALE_DIVBY16   - Divide by 16
*         - cyBuzzerPWM_PRESCALE_DIVBY32   - Divide by 32
*         - cyBuzzerPWM_PRESCALE_DIVBY64   - Divide by 64
*         - cyBuzzerPWM_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_CONTROL_REG &= (uint32)~cyBuzzerPWM_PRESCALER_MASK;
    cyBuzzerPWM_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the cyBuzzerPWM runs
*  continuously or stops when terminal count is reached.  By default the
*  cyBuzzerPWM operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_CONTROL_REG &= (uint32)~cyBuzzerPWM_ONESHOT_MASK;
    cyBuzzerPWM_CONTROL_REG |= ((uint32)((oneShotEnable & cyBuzzerPWM_1BIT_MASK) <<
                                                               cyBuzzerPWM_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetPWMMode(uint32 modeMask)
{
    cyBuzzerPWM_TRIG_CONTROL2_REG = (modeMask & cyBuzzerPWM_6BIT_MASK);
}



/*******************************************************************************
* Function Name: cyBuzzerPWM_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_CONTROL_REG &= (uint32)~cyBuzzerPWM_PWM_SYNC_KILL_MASK;
    cyBuzzerPWM_CONTROL_REG |= ((uint32)((syncKillEnable & cyBuzzerPWM_1BIT_MASK)  <<
                                               cyBuzzerPWM_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_CONTROL_REG &= (uint32)~cyBuzzerPWM_PWM_STOP_KILL_MASK;
    cyBuzzerPWM_CONTROL_REG |= ((uint32)((stopOnKillEnable & cyBuzzerPWM_1BIT_MASK)  <<
                                                         cyBuzzerPWM_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_CONTROL_REG &= (uint32)~cyBuzzerPWM_PRESCALER_MASK;
    cyBuzzerPWM_CONTROL_REG |= ((uint32)((deadTime & cyBuzzerPWM_8BIT_MASK) <<
                                                          cyBuzzerPWM_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - cyBuzzerPWM_INVERT_LINE   - Inverts the line output
*         - cyBuzzerPWM_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_CONTROL_REG &= (uint32)~cyBuzzerPWM_INV_OUT_MASK;
    cyBuzzerPWM_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: cyBuzzerPWM_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_WriteCounter(uint32 count)
{
    cyBuzzerPWM_COUNTER_REG = (count & cyBuzzerPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 cyBuzzerPWM_ReadCounter(void)
{
    return (cyBuzzerPWM_COUNTER_REG & cyBuzzerPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - cyBuzzerPWM_COUNT_UP       - Counts up
*     - cyBuzzerPWM_COUNT_DOWN     - Counts down
*     - cyBuzzerPWM_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - cyBuzzerPWM_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_CONTROL_REG &= (uint32)~cyBuzzerPWM_UPDOWN_MASK;
    cyBuzzerPWM_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_WritePeriod(uint32 period)
{
    cyBuzzerPWM_PERIOD_REG = (period & cyBuzzerPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 cyBuzzerPWM_ReadPeriod(void)
{
    return (cyBuzzerPWM_PERIOD_REG & cyBuzzerPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_CONTROL_REG &= (uint32)~cyBuzzerPWM_RELOAD_CC_MASK;
    cyBuzzerPWM_CONTROL_REG |= (swapEnable & cyBuzzerPWM_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_WritePeriodBuf(uint32 periodBuf)
{
    cyBuzzerPWM_PERIOD_BUF_REG = (periodBuf & cyBuzzerPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 cyBuzzerPWM_ReadPeriodBuf(void)
{
    return (cyBuzzerPWM_PERIOD_BUF_REG & cyBuzzerPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_CONTROL_REG &= (uint32)~cyBuzzerPWM_RELOAD_PERIOD_MASK;
    cyBuzzerPWM_CONTROL_REG |= ((uint32)((swapEnable & cyBuzzerPWM_1BIT_MASK) <<
                                                            cyBuzzerPWM_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void cyBuzzerPWM_WriteCompare(uint32 compare)
{
    #if (cyBuzzerPWM_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (cyBuzzerPWM_CY_TCPWM_4000) */

    #if (cyBuzzerPWM_CY_TCPWM_4000)
        currentMode = ((cyBuzzerPWM_CONTROL_REG & cyBuzzerPWM_UPDOWN_MASK) >> cyBuzzerPWM_UPDOWN_SHIFT);

        if (((uint32)cyBuzzerPWM__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)cyBuzzerPWM__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (cyBuzzerPWM_CY_TCPWM_4000) */
    
    cyBuzzerPWM_COMP_CAP_REG = (compare & cyBuzzerPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 cyBuzzerPWM_ReadCompare(void)
{
    #if (cyBuzzerPWM_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (cyBuzzerPWM_CY_TCPWM_4000) */

    #if (cyBuzzerPWM_CY_TCPWM_4000)
        currentMode = ((cyBuzzerPWM_CONTROL_REG & cyBuzzerPWM_UPDOWN_MASK) >> cyBuzzerPWM_UPDOWN_SHIFT);
        
        regVal = cyBuzzerPWM_COMP_CAP_REG;
        
        if (((uint32)cyBuzzerPWM__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)cyBuzzerPWM__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & cyBuzzerPWM_16BIT_MASK);
    #else
        return (cyBuzzerPWM_COMP_CAP_REG & cyBuzzerPWM_16BIT_MASK);
    #endif /* (cyBuzzerPWM_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void cyBuzzerPWM_WriteCompareBuf(uint32 compareBuf)
{
    #if (cyBuzzerPWM_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (cyBuzzerPWM_CY_TCPWM_4000) */

    #if (cyBuzzerPWM_CY_TCPWM_4000)
        currentMode = ((cyBuzzerPWM_CONTROL_REG & cyBuzzerPWM_UPDOWN_MASK) >> cyBuzzerPWM_UPDOWN_SHIFT);

        if (((uint32)cyBuzzerPWM__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)cyBuzzerPWM__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (cyBuzzerPWM_CY_TCPWM_4000) */
    
    cyBuzzerPWM_COMP_CAP_BUF_REG = (compareBuf & cyBuzzerPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 cyBuzzerPWM_ReadCompareBuf(void)
{
    #if (cyBuzzerPWM_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (cyBuzzerPWM_CY_TCPWM_4000) */

    #if (cyBuzzerPWM_CY_TCPWM_4000)
        currentMode = ((cyBuzzerPWM_CONTROL_REG & cyBuzzerPWM_UPDOWN_MASK) >> cyBuzzerPWM_UPDOWN_SHIFT);

        regVal = cyBuzzerPWM_COMP_CAP_BUF_REG;
        
        if (((uint32)cyBuzzerPWM__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)cyBuzzerPWM__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & cyBuzzerPWM_16BIT_MASK);
    #else
        return (cyBuzzerPWM_COMP_CAP_BUF_REG & cyBuzzerPWM_16BIT_MASK);
    #endif /* (cyBuzzerPWM_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 cyBuzzerPWM_ReadCapture(void)
{
    return (cyBuzzerPWM_COMP_CAP_REG & cyBuzzerPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 cyBuzzerPWM_ReadCaptureBuf(void)
{
    return (cyBuzzerPWM_COMP_CAP_BUF_REG & cyBuzzerPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - cyBuzzerPWM_TRIG_LEVEL     - Level
*     - cyBuzzerPWM_TRIG_RISING    - Rising edge
*     - cyBuzzerPWM_TRIG_FALLING   - Falling edge
*     - cyBuzzerPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_TRIG_CONTROL1_REG &= (uint32)~cyBuzzerPWM_CAPTURE_MASK;
    cyBuzzerPWM_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - cyBuzzerPWM_TRIG_LEVEL     - Level
*     - cyBuzzerPWM_TRIG_RISING    - Rising edge
*     - cyBuzzerPWM_TRIG_FALLING   - Falling edge
*     - cyBuzzerPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_TRIG_CONTROL1_REG &= (uint32)~cyBuzzerPWM_RELOAD_MASK;
    cyBuzzerPWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << cyBuzzerPWM_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - cyBuzzerPWM_TRIG_LEVEL     - Level
*     - cyBuzzerPWM_TRIG_RISING    - Rising edge
*     - cyBuzzerPWM_TRIG_FALLING   - Falling edge
*     - cyBuzzerPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_TRIG_CONTROL1_REG &= (uint32)~cyBuzzerPWM_START_MASK;
    cyBuzzerPWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << cyBuzzerPWM_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - cyBuzzerPWM_TRIG_LEVEL     - Level
*     - cyBuzzerPWM_TRIG_RISING    - Rising edge
*     - cyBuzzerPWM_TRIG_FALLING   - Falling edge
*     - cyBuzzerPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_TRIG_CONTROL1_REG &= (uint32)~cyBuzzerPWM_STOP_MASK;
    cyBuzzerPWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << cyBuzzerPWM_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - cyBuzzerPWM_TRIG_LEVEL     - Level
*     - cyBuzzerPWM_TRIG_RISING    - Rising edge
*     - cyBuzzerPWM_TRIG_FALLING   - Falling edge
*     - cyBuzzerPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_TRIG_CONTROL1_REG &= (uint32)~cyBuzzerPWM_COUNT_MASK;
    cyBuzzerPWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << cyBuzzerPWM_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - cyBuzzerPWM_CMD_CAPTURE    - Trigger Capture/Switch command
*     - cyBuzzerPWM_CMD_RELOAD     - Trigger Reload/Index command
*     - cyBuzzerPWM_CMD_STOP       - Trigger Stop/Kill command
*     - cyBuzzerPWM_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    cyBuzzerPWM_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the cyBuzzerPWM.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - cyBuzzerPWM_STATUS_DOWN    - Set if counting down
*     - cyBuzzerPWM_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 cyBuzzerPWM_ReadStatus(void)
{
    return ((cyBuzzerPWM_STATUS_REG >> cyBuzzerPWM_RUNNING_STATUS_SHIFT) |
            (cyBuzzerPWM_STATUS_REG & cyBuzzerPWM_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - cyBuzzerPWM_INTR_MASK_TC       - Terminal count mask
*     - cyBuzzerPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetInterruptMode(uint32 interruptMask)
{
    cyBuzzerPWM_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - cyBuzzerPWM_INTR_MASK_TC       - Terminal count mask
*     - cyBuzzerPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 cyBuzzerPWM_GetInterruptSourceMasked(void)
{
    return (cyBuzzerPWM_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - cyBuzzerPWM_INTR_MASK_TC       - Terminal count mask
*     - cyBuzzerPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 cyBuzzerPWM_GetInterruptSource(void)
{
    return (cyBuzzerPWM_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - cyBuzzerPWM_INTR_MASK_TC       - Terminal count mask
*     - cyBuzzerPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_ClearInterrupt(uint32 interruptMask)
{
    cyBuzzerPWM_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: cyBuzzerPWM_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - cyBuzzerPWM_INTR_MASK_TC       - Terminal count mask
*     - cyBuzzerPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void cyBuzzerPWM_SetInterrupt(uint32 interruptMask)
{
    cyBuzzerPWM_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */

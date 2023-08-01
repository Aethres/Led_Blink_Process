/** @file       greenledprocess.c
 *  @brief      GREENLEDPROCESS application program file
 *  @copyright  (c) 2023-Arcelik - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Arcelik A.S.
 *  @author     Cagri
 *  @date       31.07.2023
 */
#define FILE_GREENLEDPROCESS_C

#include "process_ui.h"
#include "greenledprocess.h"
#include "rcos.h"
#include "system.h"

#define DEBUG_FILE_NAME ""

// #define DEBUG_PORT_
// DEBUG_START(0)

/**
 *  @addtogroup GREENLEDPROCESS
 *  @{
 */

typedef enum
{
    eLedP45,
} teLeds;

static PT_THREAD(greenLedProcessThread)
{
    tsGreenLedProcessParams *params       = process->parameters;
    const tsGreenLedProcessConsts *consts = process->constants;

    PT_BEGIN();

    for (;;)
    {
        PT_YIELD();
    }

    PT_END();
}

static PROCESS_HANDLER_PROTO(greenLedProcessHandler);
void ledGreenHandler(tsProcess *process, teLeds led, uint8 onOff);

/// @brief  Initialization function of greenLedProcess
PROCESS_INIT_PROTO(greenLedProcessInit)
{
    tsGreenLedProcessParams *params       = process->parameters;
    const tsGreenLedProcessConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED

    PROCESS_STATE_CHANGE(process, greenLedProcessHandler);
    threadStart(process, greenLedProcessThread);
    process->initialized = 1; // If process needs other checks, set this another time
    
    devIoInit(consts->leds, NULL);          //init led object
    timerEventStart(&params->stopAnimation, 2300); //animation stop timer
}

/// @brief  Deinitialization function of greenLedProcess
PROCESS_DEINIT_PROTO(greenLedProcessDeinit)
{
    tsGreenLedProcessParams *params       = process->parameters;
    const tsGreenLedProcessConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED

    PROCESS_STATE_CHANGE(process, NULL);
    threadStop(process, process->threadFunction);
    process->initialized = 0; // If process needs other checks, clear this another time
}

/// @brief  Event handler function of greenLedProcess
static PROCESS_HANDLER_PROTO(greenLedProcessHandler)
{
    tsGreenLedProcessParams *params       = process->parameters;
    const tsGreenLedProcessConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED

    switch(eventCurrent.event)
    {
        case p45light:
        ledGreenHandler(process, eLedP45, TRUE);
        break;
        
        case p45close:
        ledGreenHandler(process, eLedP45, FALSE);
        break;
    }
}

void ledGreenHandler(tsProcess *process, teLeds led, uint8 onOff)
{
    tsGreenLedProcessParams *params = process->parameters;
    const tsGreenLedProcessConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED

    if (onOff)
    {
        params->ledState |= BIT(led); //turn on
    }
    else
    {
        params->ledState &= ~BIT(led); //turn off
    }

    devIoPut(consts->leds, params->ledState);
}

/** @} */

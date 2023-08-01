/** @file       redledprocess.c
 *  @brief      REDLEDPROCESS application program file
 *  @copyright  (c) 2023-Arcelik - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Arcelik A.S.
 *  @author     Cagri
 *  @date       31.07.2023
 */
#define FILE_REDLEDPROCESS_C

#include "process_ui.h"
#include "redledprocess.h"
#include "rcos.h"
#include "system.h"

#define DEBUG_FILE_NAME ""

// #define DEBUG_PORT_
// DEBUG_START(0)

/**
 *  @addtogroup REDLEDPROCESS
 *  @{
 */

typedef enum
{
    eLedP43,
} teLeds;

static PT_THREAD(redLedProcessThread)
{
    tsRedLedProcessParams *params       = process->parameters;
    const tsRedLedProcessConsts *consts = process->constants;

    PT_BEGIN();

    for (;;)
    {
        PT_YIELD();
    }

    PT_END();
}

static PROCESS_HANDLER_PROTO(redLedProcessHandler);
void ledRedHandler(tsProcess *process, teLeds led, uint8 onOff);

/// @brief  Initialization function of redLedProcess
PROCESS_INIT_PROTO(redLedProcessInit)
{
    tsRedLedProcessParams *params       = process->parameters;
    const tsRedLedProcessConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED

    PROCESS_STATE_CHANGE(process, redLedProcessHandler);
    threadStart(process, redLedProcessThread);
    process->initialized = 1; // If process needs other checks, clear this another time
    
    devIoInit(consts->leds, NULL);          //init led object
    timerEventStart(&params->stopAnimation, 2300); //animation stop timer
}

/// @brief  Deinitialization function of redLedProcess
PROCESS_DEINIT_PROTO(redLedProcessDeinit)
{
    tsRedLedProcessParams *params       = process->parameters;
    const tsRedLedProcessConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED

    PROCESS_STATE_CHANGE(process, NULL);
    threadStop(process, process->threadFunction);
    process->initialized = 0; // If process needs other checks, clear this another time
}

/// @brief  Event handler function of redLedProcess
static PROCESS_HANDLER_PROTO(redLedProcessHandler)
{
    tsRedLedProcessParams *params       = process->parameters;
    const tsRedLedProcessConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED

    switch(eventCurrent.event)
    {
        case p43light:
        ledRedHandler(process, eLedP43, TRUE);
        break;
        
        case p43close:
        ledRedHandler(process, eLedP43, FALSE);
        break;
    }
}

void ledRedHandler(tsProcess *process, teLeds led, uint8 onOff)
{
    tsRedLedProcessParams *params = process->parameters;
    const tsRedLedProcessConsts *consts = process->constants;

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

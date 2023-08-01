/** @file       greenledprocess.h
 *  @brief      GREENLEDPROCESS application header file
 *  @copyright  (c) 2023-Arcelik - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Arcelik A.S.
 *  @author     Cagri
 *  @date       31.07.2023
 */
#ifndef FILE_GREENLEDPROCESS_H
#define FILE_GREENLEDPROCESS_H

/** INCLUDES ******************************************************************/
#include "rcos.h"

/// Interface definition for this file,
/// there should not be any includes after this define.
#ifndef FILE_GREENLEDPROCESS_C
#define INTERFACE extern
#else
#define INTERFACE
#endif

/**
 *  @defgroup   GREENLEDPROCESS GREENLEDPROCESS
 *  @ingroup    APP
 *  @brief      
 *  @{
 */

/// @brief  Events of a GreenLedProcess process
typedef enum
{    
    eGreenGetUi,
    eGreenStopAnimation,
    eGreenBlinkLed
} teGreenLedProcessEvents;

/// @brief  Parameters of a GreenLedProcess process
typedef struct
{    
    tsTimerEvent getUiData;
    tsTimerEvent stopAnimation;
    tsTimerEvent blinkLed;
    uint32_t ledState;
    uint8_t lockStatus;
} tsGreenLedProcessParams;

/// @brief  Constants of a GreenLedProcess process
typedef struct
{
    const tsDevIo* buzzerLevel;
    const tsDevIo* patternBuzzer;
    const tsDevIo* sevSeg;
    const tsDevIo* encoder;
    const tsDevIo *leds;
} tsGreenLedProcessConsts;

/** @brief  GreenLedProcess process object creation macro
 *  @param  _name   Name of process object
 *  @param  _enum   Process enumeration for this object
 */
#define PROCESS_GREENLEDPROCESS_CREATE(_name, _enum, _leds) \
    tsGreenLedProcessParams _name##Params =           \
        {                                         \
        .getUiData      = TIMER_EVENT_INIT(_enum, _enum,eGreenGetUi),                                 \
        .stopAnimation  = TIMER_EVENT_INIT(_enum, _enum,eGreenStopAnimation),                         \
        .blinkLed     = TIMER_EVENT_INIT(_enum, _enum,eGreenBlinkLed),                         \
        .ledState       = 0,        \
    };                                                    \
    const tsGreenLedProcessConsts _name##Consts =     \
        {                                         \
        .leds           = &_leds,   \
    };                                              \
    PROCESS_CREATE(_name, greenLedProcessInit, greenLedProcessDeinit, _enum, &_name##Params, &_name##Consts)

/** @} */

#undef INTERFACE // Should not let this roam free

#endif // FILE_GREENLEDPROCESS_H

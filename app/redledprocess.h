/** @file       redledprocess.h
 *  @brief      REDLEDPROCESS application header file
 *  @copyright  (c) 2023-Arcelik - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Arcelik A.S.
 *  @author     Cagri
 *  @date       31.07.2023
 */
#ifndef FILE_REDLEDPROCESS_H
#define FILE_REDLEDPROCESS_H

/** INCLUDES ******************************************************************/
#include "rcos.h"

/// Interface definition for this file,
/// there should not be any includes after this define.
#ifndef FILE_REDLEDPROCESS_C
#define INTERFACE extern
#else
#define INTERFACE
#endif

/**
 *  @defgroup   REDLEDPROCESS REDLEDPROCESS
 *  @ingroup    APP
 *  @brief      
 *  @{
 */

/// @brief  Events of a RedLedProcess process
typedef enum
{
    eRedGetUi,
    eRedStopAnimation,
    eRedBlinkLed,
} teRedLedProcessEvents;

/// @brief  Parameters of a RedLedProcess process
typedef struct
{
    tsTimerEvent getUiData;
    tsTimerEvent stopAnimation;
    tsTimerEvent blinkLed;
    uint32_t ledState;
    uint8_t lockStatus;

} tsRedLedProcessParams;

/// @brief  Constants of a RedLedProcess process
typedef struct
{
    const tsDevIo* buzzerLevel;
    const tsDevIo* patternBuzzer;
    const tsDevIo* sevSeg;
    const tsDevIo* encoder;
    const tsDevIo *leds;
} tsRedLedProcessConsts;

/** @brief  RedLedProcess process object creation macro
 *  @param  _name   Name of process object
 *  @param  _enum   Process enumeration for this object
 */
#define PROCESS_REDLEDPROCESS_CREATE(_name, _enum, _leds) \
    tsRedLedProcessParams _name##Params =           \
        {                                         \
        .getUiData      = TIMER_EVENT_INIT(_enum, _enum,eRedGetUi),                                 \
        .stopAnimation  = TIMER_EVENT_INIT(_enum, _enum,eRedStopAnimation),                         \
        .blinkLed     = TIMER_EVENT_INIT(_enum, _enum,eRedBlinkLed),                         \
        .ledState       = 0,        \
    };                                            \
    const tsRedLedProcessConsts _name##Consts =     \
        {                                         \
        .leds           = &_leds,   \
    };                                            \
    PROCESS_CREATE(_name, redLedProcessInit, redLedProcessDeinit, _enum, &_name##Params, &_name##Consts)

/** @} */

#undef INTERFACE // Should not let this roam free

#endif // FILE_REDLEDPROCESS_H

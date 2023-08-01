/** @file       process_ui.h
 *  @brief      PROCESS_UI application header file
 *  @copyright  (c) 2021-Arcelik - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Arcelik A.S.
 *  @author     mertGemalmaz
 *  @date       01.06.2021
 */
#ifndef FILE_PROCESS_UI_H
#define FILE_PROCESS_UI_H

/** INCLUDES ******************************************************************/
#include "rcos.h"
#include "dev\pattern.h"

/// Interface definition for this file,
/// there should not be any includes after this define.
#ifndef FILE_PROCESS_UI_C
#define INTERFACE extern
#else
#define INTERFACE
#endif

/**
 *  @defgroup   PROCESS_UI PROCESS_UI
 *  @ingroup    APP
 *  @brief      UI routines
 *  @{
 */

/// @brief  Events of a ProcessUi process
typedef enum
{
    eGuiGetUi,
    eGuiStopAnimation,
    eGuiEncoderCW,
    eGuiEncoderCCW,
    eBlinkLed,
    p43light,
    p44light,
    p45light,
    p43close,
    p44close,
    p45close,
    p46Pressed,
    p46Released,
    p70Pressed,
    p70PressedShort,
    p70PressedLong,
    p70Released,
    p71Pressed,
    p71PressedShort,
    p71PressedLong,
    p71Released,
    p46p70Pressed,
    p46p70Released,
    p70p71Pressed,
    p70p71Released,
    p46p71Pressed,
    p46p71Released,
    p46p70p71Pressed,
    p46p70p71Released,
} teProcessUiEvents;

/// @brief  Parameters of a ProcessUi process
typedef struct
{
    tsTimerEvent getUiData;
    tsTimerEvent stopAnimation;
    tsTimerEvent blinkLed;
    uint32_t ledState;
    uint8_t lockStatus;
    const tsDevIo *leds;
    const tsDevIo* buzzerLevel;
    const tsDevIo* patternBuzzer;
    const tsDevIo* sevSeg;
    const tsDevIo* encoder;
} tsProcessUiParams;

/// @brief  Constants of a ProcessUi process
typedef struct
{
    const tsDevIo *csdDevIo;
} tsProcessUiConsts;

/** @brief  ProcessUi process object creation macro
 *  @param  _name   Name of process object
 *  @param  _enum   Process enumeration for this object
 *  @param  _capSenseDevIo   capSense devIo object
 *  @param  _leds   led devIo object
 */
#define PROCESS_UI_CREATE(_name, _enum, _capSenseDevIo,_leds,_buzzer,_buzzerLevel,_sevSeg,_encoder) \
    DEV_IO_PATTERN_CREATE(_name##pattern,_buzzer, 0)                                                \
    tsProcessUiParams _name##Params =                                                               \
    {                                                                                               \
        .getUiData      = TIMER_EVENT_INIT(_enum, _enum,eGuiGetUi),                                 \
        .stopAnimation  = TIMER_EVENT_INIT(_enum, _enum,eGuiStopAnimation),                         \
        .blinkLed     = TIMER_EVENT_INIT(_enum, _enum,eBlinkLed),                         \
        .ledState       = 0,                                                                        \
        .leds           = &_leds,                                                                   \
        .buzzerLevel    = &_buzzerLevel,                                                            \
        .sevSeg         = &_sevSeg,                                                                 \
        .patternBuzzer  = &_name##pattern,                                                          \
        .lockStatus     = 0,                                                                        \
        .encoder        = &_encoder,                                                                \
    };                                                                                              \
    const tsProcessUiConsts _name##Consts =                                                         \
    {                                                                                               \
        .csdDevIo  = &_capSenseDevIo,                                                               \
    };                                                                                              \
    PROCESS_CREATE(_name, processUiInit, processUiDeinit, _enum, &_name##Params, &_name##Consts)

/** @} */

#undef INTERFACE // Should not let this roam free

#endif // FILE_PROCESS_UI_H

/** @file       process_ui.c
 *  @brief      PROCESS_UI application program file
 *  @copyright  (c) 2021-Arcelik - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Arcelik A.S.
 *  @author     mertGemalmaz
 *  @date       01.06.2021
 */
#define FILE_PROCESS_UI_C

#include "process_ui.h"
#include "rcos.h"
#include "system.h"
#include "dev\sevenSegmentdisplay.h"
#define DEBUG_FILE_NAME ""

// #define DEBUG_PORT_
// DEBUG_START(0)

/**
 *  @addtogroup PROCESS_UI
 *  @{
 */

static PT_THREAD(processUiThread)
{
    tsProcessUiParams *params = process->parameters;
    const tsProcessUiConsts *consts = process->constants;
    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED
    PT_BEGIN();

    for (;;)
    {
        PT_YIELD();
    }

    PT_END();
}


#define BUZZER_BEEP(data) (devIoPut(params->patternBuzzer, (uint32_t)data))
#define CHILD_LOCK_ENABLE TRUE
#define CHILD_LOCK_DISABLE FALSE
#define HALF_SECOND_IN_MS (500)
#define ONE_SECOND_IN_MS (1000)
#define TWO_SECOND_IN_MS (2000)
#define THREE_SECOND_IN_MS (3000)
#define FOUR_SECOND_IN_MS (4000)
#define FIVE_SECOND_IN_MS (5000)
#define BUTON_SHORT_PRESS_DURATION (50)
#define BUTON_LONG_PRESS_DURATION (THREE_SECOND_IN_MS)
#define SEVSEG_MAX_COUNT 19
#define SEVSEG_MIN_COUNT 0

/// @brief  Local Variables
typedef enum
{
    eLedP43,
    eLedP44,
    eLedP45,
} teLeds;

typedef enum
{
    eBuzzerLevel1 = 5,
    eBuzzerLevel2 = 10,
    eBuzzerLevel3 = 30,
} teBuzzerSoundLevel;

typedef struct
{
    uint8_t p46;
    teBool p70;
    teBool p71;
} tsButonStatus; //0: not pressed    1: is pressing

tsButonStatus guiButonStatus;
uint8_t sevSegCounter = 0;
uint8_t encoderStat = 0;
uint8_t encoderStatPrev = 0;

/// @brief  Buzzer Melodies
const tsPatternNode melodyArcelik[] =
    {
#define M_TEMPO TEMPO_Lento
        MELODY_TELVE_ARCELIK,
        PATTERN_NODE_END(0)
    };

const tsPatternNode melodyPres[] =
    {
        {NOTE_7_A, 150},
        PATTERN_NODE_END(0)
    };

const tsPatternNode melodyRelease[] =
    {
        {NOTE_7_G, 150},
        PATTERN_NODE_END(0)
    };

const tsPatternNode melodyKeyWarning[] =
    {
        {4000, 150},
        {3000, 200},
        {4000, 150},
        PATTERN_NODE_END(0)};

const tsPatternNode melodyLock[] =
    {
        {NOTE_7_A, 150},
        {NOTE_7_B, 200},
        {NOTE_7_C, 150},
        PATTERN_NODE_END(0)
    };

/// @brief  Local Function Prototypes
static PROCESS_HANDLER_PROTO(processUiHandler);
static void guiDefaultHandler(tsProcess *process);
void ledGuiHandler(tsProcess *process, teLeds led, uint8 onOff);
void allLedsOnOff(tsProcess *process, uint8 onOff);
void buttonMapper(tsProcess *process, teProcessUiEvents event, uint16_t pressDuration, teBool *butonStatus);


/// @brief  Initialization function of processUi
PROCESS_INIT_PROTO(processUiInit)
{
    tsProcessUiParams *params = process->parameters;
    const tsProcessUiConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED

    PROCESS_STATE_CHANGE(process, processUiHandler);
    threadStart(process, processUiThread);
    process->initialized = 1; // If process needs other checks, set this another time

    devIoInit(consts->csdDevIo, NULL);      //init capsense object
    devIoInit(params->leds, NULL);          //init led object
    devIoInit(params->patternBuzzer, NULL); //init buzzer pattern object
    devIoInit(params->buzzerLevel, NULL);   //init buzzer sound level object

    devIoPut(params->buzzerLevel, eBuzzerLevel3); //arrange buzzer sound level
    //allLedsOnOff(process, TRUE);
    //BUZZER_BEEP(melodyArcelik);                    //starUp Melody
    timerEventStart(&params->stopAnimation, 2300); //animation stop timer
    params->lockStatus = CHILD_LOCK_ENABLE;
}

/// @brief  Deinitialization function of processUi
PROCESS_DEINIT_PROTO(processUiDeinit)
{
    tsProcessUiParams *params = process->parameters;
    const tsProcessUiConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED

    PROCESS_STATE_CHANGE(process, NULL);
    threadStop(process, process->threadFunction);
    process->initialized = 0; // If process needs other checks, clear this another time
}


/// @brief  Event handler function of processUi
static PROCESS_HANDLER_PROTO(processUiHandler)
{
    tsProcessUiParams *params = process->parameters;
    const tsProcessUiConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED
    const tProcessEnum aaa = eRedLedProcess;

    switch (eventCurrent.event)
    {
        case p46Pressed:
            eventPost(eRedLedProcess, p43light, NULL, 0);
        break;
        case p46Released:
            eventPost(eRedLedProcess, p43close, NULL, 0);
        break;
        case p71Pressed:
            eventPost(eGreenLedProcess, p45light, NULL, 0);
        break;
        case p71Released:
            eventPost(eGreenLedProcess, p45close, NULL, 0);
        break;
        case p46p71Pressed:
            eventPost(eRedLedProcess, p43light, NULL, 0);
            eventPost(eGreenLedProcess, p45light, NULL, 0);
        break;
        case p46p71Released:
            eventPost(eRedLedProcess, p43close, NULL, 0);
            eventPost(eGreenLedProcess, p45close, NULL, 0);
        break;
        case p46p70p71Pressed:
            eventPost(eRedLedProcess, p43light, NULL, 0);
            eventPost(eGreenLedProcess, p45light, NULL, 0);
        break;
        case p46p70p71Released:
            eventPost(eRedLedProcess, p43close, NULL, 0);
            eventPost(eGreenLedProcess, p45close, NULL, 0);
        break;
        
        default:
        break;
    
    }
}

static void guiDefaultHandler(tsProcess *process)
{
    tsProcessUiParams *params = process->parameters;
    const tsProcessUiConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED


    switch (eventCurrent.event)
    {
    case eGuiGetUi: // gather ui data from DEVs
    {
        encoderStat = devIoGet(params->encoder);

        if (encoderStat ^ encoderStatPrev)
        {
            if ((encoderStat) > (encoderStatPrev)) //clockWise
            {
                eventPost(process->enumeration, eGuiEncoderCW, NULL, 0);
            }
            else // counterClockWise
            {
                eventPost(process->enumeration, eGuiEncoderCCW, NULL, 0);
            }
        }
        encoderStatPrev = encoderStat;
        timerEventStart(&params->getUiData, 100);
    }
    break;

    case p46Pressed:
    {
        ledGuiHandler(process, eLedP43, TRUE);
        BUZZER_BEEP(melodyPres);
    }
    break;

    case p46Released:
    {
        ledGuiHandler(process, eLedP43, FALSE);
        BUZZER_BEEP(melodyRelease);
    }
    break;

    case p70Pressed:
    {
        buttonMapper(process, p70PressedShort, BUTON_SHORT_PRESS_DURATION, &guiButonStatus.p70);
    }
    break;

    case p70Released:
    {
        guiButonStatus.p70 = FALSE;
    }
    break;

    case p71Pressed:
    {
        buttonMapper(process, p71PressedShort, BUTON_SHORT_PRESS_DURATION, &guiButonStatus.p71);
    }
    break;

    case p71Released:
    {
        guiButonStatus.p71 = FALSE;
    }
    break;

    default:
        break;
    }
}

void ledGuiHandler(tsProcess *process, teLeds led, uint8 onOff)
{
    tsProcessUiParams *params = process->parameters;
    const tsProcessUiConsts *consts = process->constants;

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

    devIoPut(params->leds, params->ledState);
}

void allLedsOnOff(tsProcess *process, uint8 onOff)
{
    tsProcessUiParams *params = process->parameters;
    const tsProcessUiConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED
    uint8 idx;
    for (idx = eLedP43; idx <= eLedP45; idx++)
    {
        ledGuiHandler(process, idx, onOff);
    }
}

void buttonMapper(tsProcess *process, teProcessUiEvents event, uint16_t pressDuration, teBool *butonStatus)
{
    tsProcessUiParams *params = process->parameters;
    const tsProcessUiConsts *consts = process->constants;

    UNUSED(params); // REMOVE IF USED
    UNUSED(consts); // REMOVE IF USED

    uint16_t duration;
    memcpy(&duration, &eventData, sizeof(uint16_t));

    if ((duration >= pressDuration) && (!*butonStatus))
    {
        *butonStatus = TRUE;
        if (!params->lockStatus)
        {
            eventPost(eventCurrent.destination, event, NULL, 0);
        }
        else
        {
            BUZZER_BEEP(melodyKeyWarning);
        }
    }
}

/** @} */

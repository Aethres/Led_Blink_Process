/** @file       system.h
 *  @brief      System wide definitions
 *  @copyright  (c) 2018-Arcelik - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Arcelik A.S.
 */
#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "rcos.h"

typedef enum
{
    eSysStUninitialized, // Power-on state nothing is initialized
    eSysStDeactive,      // POST is done and basic functionality is initialized, no UI
    eSysStActive,        // UI is activated for user configuration input
    eSysStProgram,       // Selected program is running
    eSysStProgramEnd,    // Results of program
    eSysStOtaDownload,   // New update is coming
    eSysStOtaInstall,    // Installing new update
    eSysStOtaFinish,     // Results of update
    eSysStMax
} teSystemStates;

typedef enum
{
    eProcessUi,
    eRedLedProcess,
    eGreenLedProcess
} teSystemProcesses;

typedef enum
{
    evShortPressed,
    evPressed,
    evLongPressed,
} teSystemEvents;

typedef enum
{
    eDataSetOtaMbCfg = 1,   // mbOTAConfInfoArray
    eDataSetWfaComOut,      // sp_WFACommInputTable
    eDataSetWfaComIn,       // sp_WFACommOutputTable
    eDataSetDispComIn,      // sp_DispCommOutputTable
    eDataSetMercekComOut,   // sp_MercekCommInputTable
    eDataSetMercekComIn,    // sp_MercekCommOutputTable
    eDataSetOvenCfg = 10,   // DB -> MB
    eDataSetNormalSend,     // DB -> MB
    eDataSetNormalReceive,  // MB -> DB
    eDataSetServiceReceive, // MB -> DB
    eDataSetServiceSend,    // DB -> MB
    eDataSetMercek,         // MB -> DB
} teDataSets;

#endif // FILE_SYSTEM_H

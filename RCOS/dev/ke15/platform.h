/** @file       ke15/platform.h
 *  @brief      Platform specific modifications for NXP KE15
 *  @copyright  (c) 2018-Arcelik - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Arcelik A.S.
 */
#ifndef FILE_PLATFORM_H
#define FILE_PLATFORM_H

/** 
 *  @defgroup   KE15 KE15
 *  @ingroup    PLATFORM
 *  @brief      NXP KE15 family cpu devices
 *  @{
 *      @defgroup   KE15_DEV_IO DEV_IO
 *      @defgroup   KE15_DEV_COM DEV_COM
 *      @defgroup   KE15_DEV_MEM DEV_MEM
 *      @defgroup   KE15_DEV_CPX DEV_CPX
 */

/*********************************************************************
 *  INCLUDES
 */
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKE15Z7.h"

/*********************************************************************
 *  EXPORTED TYPEDEFS
 */

/*********************************************************************
 *  EXPORTED MACROS
 */
/// @brief  Create a default tick configuration for this platform
/// @param  _freq   Frequency of RCoS Tick in Hz
#define CORE_TICK_DEFAULT(_freq)                                 \
    void tickStart(void)                                         \
    {                                                            \
        SysTick_Config(BOARD_BOOTCLOCKRUN_CORE_CLOCK / (_freq)); \
    }                                                            \
    void tickEnable(void)                                        \
    {                                                            \
        EnableIRQ(SysTick_IRQn);                                 \
    }                                                            \
    void tickDisable(void)                                       \
    {                                                            \
        DisableIRQ(SysTick_IRQn);                                \
    }                                                            \
    void SysTick_Handler(void)                                   \
    {                                                            \
        rcosTickIsr();                                           \
    }                                                            \
    CORE_TICK_CREATE(tickStart, tickEnable, tickDisable)

/// @brief  Create a default watchdog timer
/// @param  _flagCount  Number of flags
#define CORE_WDT_DEFAULT(_flagCount, _timeout)                              \
    void wdtRefresh(void)                                                   \
    {                                                                       \
        WDOG32_Refresh((WDOG_Type *)WDOG_BASE);                             \
    }                                                                       \
    void wdtStart(void)                                                     \
    {                                                                       \
        wdog32_config_t config;                                             \
        WDOG32_GetDefaultConfig(&config);                                   \
        /* kWDOG8_ClockSource1 is 128kHz by default */                      \
        config.prescaler = kWDOG32_ClockPrescalerDivide256; /*512Hz*/       \
        config.timeoutValue = (_timeout) / 2; /*ms*/                        \
        config.enableUpdate = true;                                         \
        WDOG32_Init((WDOG_Type *)WDOG_BASE, &config);                       \
    }                                                                       \
    void wdtStop(void)                                                      \
    {                                                                       \
        WDOG32_Deinit((WDOG_Type *)WDOG_BASE);                              \
    }                                                                       \
    CORE_WDT_CREATE(wdtRefresh, wdtStart, wdtStop, _flagCount)

/*********************************************************************
 *  INTERFACES
 */
#define PLATFORM_ASM(_asm) __ASM(_asm)
#define PLATFORM_SECTION(_text) __attribute__((section(_text)))
#define PLATFORM_ALIGNED(_align) __attribute__((aligned(_align)))
#define PLATFORM_STATIC_INLINE __STATIC_INLINE
#define PLATFORM_WEAK __WEAK
#define PLATFORM_PACKED __PACKED

/*********************************************************************
 *  INTERFACES: CONSTANTS
 */

/*********************************************************************
 *  INTERFACES: VARIABLES
 */

/*********************************************************************
 *  INTERFACES: FUNCTIONS
 */

/** @} */

#endif // FILE_PLATFORM_H

/***************************************************************************//**
* \file cyUart_p50_p51_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_cyUart_p50_p51_H)
#define CY_SCB_PINS_cyUart_p50_p51_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define cyUart_p50_p51_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define cyUart_p50_p51_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define cyUart_p50_p51_REMOVE_TX_SDA_MISO_PIN      (1u)
#define cyUart_p50_p51_REMOVE_CTS_SCLK_PIN      (1u)
#define cyUart_p50_p51_REMOVE_RTS_SS0_PIN      (1u)
#define cyUart_p50_p51_REMOVE_SS1_PIN                 (1u)
#define cyUart_p50_p51_REMOVE_SS2_PIN                 (1u)
#define cyUart_p50_p51_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define cyUart_p50_p51_REMOVE_I2C_PINS                (1u)
#define cyUart_p50_p51_REMOVE_SPI_MASTER_PINS         (1u)
#define cyUart_p50_p51_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define cyUart_p50_p51_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define cyUart_p50_p51_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define cyUart_p50_p51_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define cyUart_p50_p51_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define cyUart_p50_p51_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define cyUart_p50_p51_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define cyUart_p50_p51_REMOVE_SPI_SLAVE_PINS          (1u)
#define cyUart_p50_p51_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define cyUart_p50_p51_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define cyUart_p50_p51_REMOVE_UART_TX_PIN             (0u)
#define cyUart_p50_p51_REMOVE_UART_RX_TX_PIN          (1u)
#define cyUart_p50_p51_REMOVE_UART_RX_PIN             (0u)
#define cyUart_p50_p51_REMOVE_UART_RX_WAKE_PIN        (1u)
#define cyUart_p50_p51_REMOVE_UART_RTS_PIN            (1u)
#define cyUart_p50_p51_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN (0u == cyUart_p50_p51_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define cyUart_p50_p51_RX_SCL_MOSI_PIN     (0u == cyUart_p50_p51_REMOVE_RX_SCL_MOSI_PIN)
#define cyUart_p50_p51_TX_SDA_MISO_PIN     (0u == cyUart_p50_p51_REMOVE_TX_SDA_MISO_PIN)
#define cyUart_p50_p51_CTS_SCLK_PIN     (0u == cyUart_p50_p51_REMOVE_CTS_SCLK_PIN)
#define cyUart_p50_p51_RTS_SS0_PIN     (0u == cyUart_p50_p51_REMOVE_RTS_SS0_PIN)
#define cyUart_p50_p51_SS1_PIN                (0u == cyUart_p50_p51_REMOVE_SS1_PIN)
#define cyUart_p50_p51_SS2_PIN                (0u == cyUart_p50_p51_REMOVE_SS2_PIN)
#define cyUart_p50_p51_SS3_PIN                (0u == cyUart_p50_p51_REMOVE_SS3_PIN)

/* Mode defined pins */
#define cyUart_p50_p51_I2C_PINS               (0u == cyUart_p50_p51_REMOVE_I2C_PINS)
#define cyUart_p50_p51_SPI_MASTER_PINS        (0u == cyUart_p50_p51_REMOVE_SPI_MASTER_PINS)
#define cyUart_p50_p51_SPI_MASTER_SCLK_PIN    (0u == cyUart_p50_p51_REMOVE_SPI_MASTER_SCLK_PIN)
#define cyUart_p50_p51_SPI_MASTER_MOSI_PIN    (0u == cyUart_p50_p51_REMOVE_SPI_MASTER_MOSI_PIN)
#define cyUart_p50_p51_SPI_MASTER_MISO_PIN    (0u == cyUart_p50_p51_REMOVE_SPI_MASTER_MISO_PIN)
#define cyUart_p50_p51_SPI_MASTER_SS0_PIN     (0u == cyUart_p50_p51_REMOVE_SPI_MASTER_SS0_PIN)
#define cyUart_p50_p51_SPI_MASTER_SS1_PIN     (0u == cyUart_p50_p51_REMOVE_SPI_MASTER_SS1_PIN)
#define cyUart_p50_p51_SPI_MASTER_SS2_PIN     (0u == cyUart_p50_p51_REMOVE_SPI_MASTER_SS2_PIN)
#define cyUart_p50_p51_SPI_MASTER_SS3_PIN     (0u == cyUart_p50_p51_REMOVE_SPI_MASTER_SS3_PIN)
#define cyUart_p50_p51_SPI_SLAVE_PINS         (0u == cyUart_p50_p51_REMOVE_SPI_SLAVE_PINS)
#define cyUart_p50_p51_SPI_SLAVE_MOSI_PIN     (0u == cyUart_p50_p51_REMOVE_SPI_SLAVE_MOSI_PIN)
#define cyUart_p50_p51_SPI_SLAVE_MISO_PIN     (0u == cyUart_p50_p51_REMOVE_SPI_SLAVE_MISO_PIN)
#define cyUart_p50_p51_UART_TX_PIN            (0u == cyUart_p50_p51_REMOVE_UART_TX_PIN)
#define cyUart_p50_p51_UART_RX_TX_PIN         (0u == cyUart_p50_p51_REMOVE_UART_RX_TX_PIN)
#define cyUart_p50_p51_UART_RX_PIN            (0u == cyUart_p50_p51_REMOVE_UART_RX_PIN)
#define cyUart_p50_p51_UART_RX_WAKE_PIN       (0u == cyUart_p50_p51_REMOVE_UART_RX_WAKE_PIN)
#define cyUart_p50_p51_UART_RTS_PIN           (0u == cyUart_p50_p51_REMOVE_UART_RTS_PIN)
#define cyUart_p50_p51_UART_CTS_PIN           (0u == cyUart_p50_p51_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN)
    #include "cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (cyUart_p50_p51_RX_SCL_MOSI) */

#if (cyUart_p50_p51_RX_SCL_MOSI_PIN)
    #include "cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (cyUart_p50_p51_RX_SCL_MOSI) */

#if (cyUart_p50_p51_TX_SDA_MISO_PIN)
    #include "cyUart_p50_p51_uart_tx_i2c_sda_spi_miso.h"
#endif /* (cyUart_p50_p51_TX_SDA_MISO) */

#if (cyUart_p50_p51_CTS_SCLK_PIN)
    #include "cyUart_p50_p51_uart_cts_spi_sclk.h"
#endif /* (cyUart_p50_p51_CTS_SCLK) */

#if (cyUart_p50_p51_RTS_SS0_PIN)
    #include "cyUart_p50_p51_uart_rts_spi_ss0.h"
#endif /* (cyUart_p50_p51_RTS_SS0_PIN) */

#if (cyUart_p50_p51_SS1_PIN)
    #include "cyUart_p50_p51_spi_ss1.h"
#endif /* (cyUart_p50_p51_SS1_PIN) */

#if (cyUart_p50_p51_SS2_PIN)
    #include "cyUart_p50_p51_spi_ss2.h"
#endif /* (cyUart_p50_p51_SS2_PIN) */

#if (cyUart_p50_p51_SS3_PIN)
    #include "cyUart_p50_p51_spi_ss3.h"
#endif /* (cyUart_p50_p51_SS3_PIN) */

#if (cyUart_p50_p51_I2C_PINS)
    #include "cyUart_p50_p51_scl.h"
    #include "cyUart_p50_p51_sda.h"
#endif /* (cyUart_p50_p51_I2C_PINS) */

#if (cyUart_p50_p51_SPI_MASTER_PINS)
#if (cyUart_p50_p51_SPI_MASTER_SCLK_PIN)
    #include "cyUart_p50_p51_sclk_m.h"
#endif /* (cyUart_p50_p51_SPI_MASTER_SCLK_PIN) */

#if (cyUart_p50_p51_SPI_MASTER_MOSI_PIN)
    #include "cyUart_p50_p51_mosi_m.h"
#endif /* (cyUart_p50_p51_SPI_MASTER_MOSI_PIN) */

#if (cyUart_p50_p51_SPI_MASTER_MISO_PIN)
    #include "cyUart_p50_p51_miso_m.h"
#endif /*(cyUart_p50_p51_SPI_MASTER_MISO_PIN) */
#endif /* (cyUart_p50_p51_SPI_MASTER_PINS) */

#if (cyUart_p50_p51_SPI_SLAVE_PINS)
    #include "cyUart_p50_p51_sclk_s.h"
    #include "cyUart_p50_p51_ss_s.h"

#if (cyUart_p50_p51_SPI_SLAVE_MOSI_PIN)
    #include "cyUart_p50_p51_mosi_s.h"
#endif /* (cyUart_p50_p51_SPI_SLAVE_MOSI_PIN) */

#if (cyUart_p50_p51_SPI_SLAVE_MISO_PIN)
    #include "cyUart_p50_p51_miso_s.h"
#endif /*(cyUart_p50_p51_SPI_SLAVE_MISO_PIN) */
#endif /* (cyUart_p50_p51_SPI_SLAVE_PINS) */

#if (cyUart_p50_p51_SPI_MASTER_SS0_PIN)
    #include "cyUart_p50_p51_ss0_m.h"
#endif /* (cyUart_p50_p51_SPI_MASTER_SS0_PIN) */

#if (cyUart_p50_p51_SPI_MASTER_SS1_PIN)
    #include "cyUart_p50_p51_ss1_m.h"
#endif /* (cyUart_p50_p51_SPI_MASTER_SS1_PIN) */

#if (cyUart_p50_p51_SPI_MASTER_SS2_PIN)
    #include "cyUart_p50_p51_ss2_m.h"
#endif /* (cyUart_p50_p51_SPI_MASTER_SS2_PIN) */

#if (cyUart_p50_p51_SPI_MASTER_SS3_PIN)
    #include "cyUart_p50_p51_ss3_m.h"
#endif /* (cyUart_p50_p51_SPI_MASTER_SS3_PIN) */

#if (cyUart_p50_p51_UART_TX_PIN)
    #include "cyUart_p50_p51_tx.h"
#endif /* (cyUart_p50_p51_UART_TX_PIN) */

#if (cyUart_p50_p51_UART_RX_TX_PIN)
    #include "cyUart_p50_p51_rx_tx.h"
#endif /* (cyUart_p50_p51_UART_RX_TX_PIN) */

#if (cyUart_p50_p51_UART_RX_PIN)
    #include "cyUart_p50_p51_rx.h"
#endif /* (cyUart_p50_p51_UART_RX_PIN) */

#if (cyUart_p50_p51_UART_RX_WAKE_PIN)
    #include "cyUart_p50_p51_rx_wake.h"
#endif /* (cyUart_p50_p51_UART_RX_WAKE_PIN) */

#if (cyUart_p50_p51_UART_RTS_PIN)
    #include "cyUart_p50_p51_rts.h"
#endif /* (cyUart_p50_p51_UART_RTS_PIN) */

#if (cyUart_p50_p51_UART_CTS_PIN)
    #include "cyUart_p50_p51_cts.h"
#endif /* (cyUart_p50_p51_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (cyUart_p50_p51_RX_SCL_MOSI_PIN)
    #define cyUart_p50_p51_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define cyUart_p50_p51_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define cyUart_p50_p51_RX_SCL_MOSI_HSIOM_MASK      (cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define cyUart_p50_p51_RX_SCL_MOSI_HSIOM_POS       (cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_RX_SCL_MOSI_HSIOM_SEL_GPIO  (cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define cyUart_p50_p51_RX_SCL_MOSI_HSIOM_SEL_I2C   (cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define cyUart_p50_p51_RX_SCL_MOSI_HSIOM_SEL_SPI   (cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define cyUart_p50_p51_RX_SCL_MOSI_HSIOM_SEL_UART  (cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN)
    #define cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_MASK      (cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_POS       (cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define cyUart_p50_p51_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define cyUart_p50_p51_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define cyUart_p50_p51_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define cyUart_p50_p51_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) cyUart_p50_p51_INTCFG_TYPE_MASK << \
                                                                           cyUart_p50_p51_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins cyUart_p50_p51_RX_SCL_MOSI_PIN or cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (cyUart_p50_p51_RX_SCL_MOSI_PIN) */

#if (cyUart_p50_p51_TX_SDA_MISO_PIN)
    #define cyUart_p50_p51_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define cyUart_p50_p51_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define cyUart_p50_p51_TX_SDA_MISO_HSIOM_MASK      (cyUart_p50_p51_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define cyUart_p50_p51_TX_SDA_MISO_HSIOM_POS       (cyUart_p50_p51_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_TX_SDA_MISO_HSIOM_SEL_GPIO  (cyUart_p50_p51_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define cyUart_p50_p51_TX_SDA_MISO_HSIOM_SEL_I2C   (cyUart_p50_p51_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define cyUart_p50_p51_TX_SDA_MISO_HSIOM_SEL_SPI   (cyUart_p50_p51_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define cyUart_p50_p51_TX_SDA_MISO_HSIOM_SEL_UART  (cyUart_p50_p51_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (cyUart_p50_p51_TX_SDA_MISO_PIN) */

#if (cyUart_p50_p51_CTS_SCLK_PIN)
    #define cyUart_p50_p51_CTS_SCLK_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_uart_cts_spi_sclk__0__HSIOM)
    #define cyUart_p50_p51_CTS_SCLK_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_uart_cts_spi_sclk__0__HSIOM)
    
    #define cyUart_p50_p51_CTS_SCLK_HSIOM_MASK      (cyUart_p50_p51_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define cyUart_p50_p51_CTS_SCLK_HSIOM_POS       (cyUart_p50_p51_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_CTS_SCLK_HSIOM_SEL_GPIO  (cyUart_p50_p51_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define cyUart_p50_p51_CTS_SCLK_HSIOM_SEL_I2C   (cyUart_p50_p51_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define cyUart_p50_p51_CTS_SCLK_HSIOM_SEL_SPI   (cyUart_p50_p51_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define cyUart_p50_p51_CTS_SCLK_HSIOM_SEL_UART  (cyUart_p50_p51_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (cyUart_p50_p51_CTS_SCLK_PIN) */

#if (cyUart_p50_p51_RTS_SS0_PIN)
    #define cyUart_p50_p51_RTS_SS0_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_uart_rts_spi_ss0__0__HSIOM)
    #define cyUart_p50_p51_RTS_SS0_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_uart_rts_spi_ss0__0__HSIOM)
    
    #define cyUart_p50_p51_RTS_SS0_HSIOM_MASK      (cyUart_p50_p51_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define cyUart_p50_p51_RTS_SS0_HSIOM_POS       (cyUart_p50_p51_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_RTS_SS0_HSIOM_SEL_GPIO  (cyUart_p50_p51_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define cyUart_p50_p51_RTS_SS0_HSIOM_SEL_I2C   (cyUart_p50_p51_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define cyUart_p50_p51_RTS_SS0_HSIOM_SEL_SPI   (cyUart_p50_p51_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1)
    #define cyUart_p50_p51_RTS_SS0_HSIOM_SEL_UART  (cyUart_p50_p51_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(cyUart_p50_p51_CY_SCBIP_V0 || cyUart_p50_p51_CY_SCBIP_V1) */
#endif /* (cyUart_p50_p51_RTS_SS0_PIN) */

#if (cyUart_p50_p51_SS1_PIN)
    #define cyUart_p50_p51_SS1_HSIOM_REG  (*(reg32 *) cyUart_p50_p51_spi_ss1__0__HSIOM)
    #define cyUart_p50_p51_SS1_HSIOM_PTR  ( (reg32 *) cyUart_p50_p51_spi_ss1__0__HSIOM)
    
    #define cyUart_p50_p51_SS1_HSIOM_MASK     (cyUart_p50_p51_spi_ss1__0__HSIOM_MASK)
    #define cyUart_p50_p51_SS1_HSIOM_POS      (cyUart_p50_p51_spi_ss1__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_SS1_HSIOM_SEL_GPIO (cyUart_p50_p51_spi_ss1__0__HSIOM_GPIO)
    #define cyUart_p50_p51_SS1_HSIOM_SEL_I2C  (cyUart_p50_p51_spi_ss1__0__HSIOM_I2C)
    #define cyUart_p50_p51_SS1_HSIOM_SEL_SPI  (cyUart_p50_p51_spi_ss1__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SS1_PIN) */

#if (cyUart_p50_p51_SS2_PIN)
    #define cyUart_p50_p51_SS2_HSIOM_REG     (*(reg32 *) cyUart_p50_p51_spi_ss2__0__HSIOM)
    #define cyUart_p50_p51_SS2_HSIOM_PTR     ( (reg32 *) cyUart_p50_p51_spi_ss2__0__HSIOM)
    
    #define cyUart_p50_p51_SS2_HSIOM_MASK     (cyUart_p50_p51_spi_ss2__0__HSIOM_MASK)
    #define cyUart_p50_p51_SS2_HSIOM_POS      (cyUart_p50_p51_spi_ss2__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_SS2_HSIOM_SEL_GPIO (cyUart_p50_p51_spi_ss2__0__HSIOM_GPIO)
    #define cyUart_p50_p51_SS2_HSIOM_SEL_I2C  (cyUart_p50_p51_spi_ss2__0__HSIOM_I2C)
    #define cyUart_p50_p51_SS2_HSIOM_SEL_SPI  (cyUart_p50_p51_spi_ss2__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SS2_PIN) */

#if (cyUart_p50_p51_SS3_PIN)
    #define cyUart_p50_p51_SS3_HSIOM_REG     (*(reg32 *) cyUart_p50_p51_spi_ss3__0__HSIOM)
    #define cyUart_p50_p51_SS3_HSIOM_PTR     ( (reg32 *) cyUart_p50_p51_spi_ss3__0__HSIOM)
    
    #define cyUart_p50_p51_SS3_HSIOM_MASK     (cyUart_p50_p51_spi_ss3__0__HSIOM_MASK)
    #define cyUart_p50_p51_SS3_HSIOM_POS      (cyUart_p50_p51_spi_ss3__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_SS3_HSIOM_SEL_GPIO (cyUart_p50_p51_spi_ss3__0__HSIOM_GPIO)
    #define cyUart_p50_p51_SS3_HSIOM_SEL_I2C  (cyUart_p50_p51_spi_ss3__0__HSIOM_I2C)
    #define cyUart_p50_p51_SS3_HSIOM_SEL_SPI  (cyUart_p50_p51_spi_ss3__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SS3_PIN) */

#if (cyUart_p50_p51_I2C_PINS)
    #define cyUart_p50_p51_SCL_HSIOM_REG  (*(reg32 *) cyUart_p50_p51_scl__0__HSIOM)
    #define cyUart_p50_p51_SCL_HSIOM_PTR  ( (reg32 *) cyUart_p50_p51_scl__0__HSIOM)
    
    #define cyUart_p50_p51_SCL_HSIOM_MASK     (cyUart_p50_p51_scl__0__HSIOM_MASK)
    #define cyUart_p50_p51_SCL_HSIOM_POS      (cyUart_p50_p51_scl__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_SCL_HSIOM_SEL_GPIO (cyUart_p50_p51_sda__0__HSIOM_GPIO)
    #define cyUart_p50_p51_SCL_HSIOM_SEL_I2C  (cyUart_p50_p51_sda__0__HSIOM_I2C)
    
    #define cyUart_p50_p51_SDA_HSIOM_REG  (*(reg32 *) cyUart_p50_p51_sda__0__HSIOM)
    #define cyUart_p50_p51_SDA_HSIOM_PTR  ( (reg32 *) cyUart_p50_p51_sda__0__HSIOM)
    
    #define cyUart_p50_p51_SDA_HSIOM_MASK     (cyUart_p50_p51_sda__0__HSIOM_MASK)
    #define cyUart_p50_p51_SDA_HSIOM_POS      (cyUart_p50_p51_sda__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_SDA_HSIOM_SEL_GPIO (cyUart_p50_p51_sda__0__HSIOM_GPIO)
    #define cyUart_p50_p51_SDA_HSIOM_SEL_I2C  (cyUart_p50_p51_sda__0__HSIOM_I2C)
#endif /* (cyUart_p50_p51_I2C_PINS) */

#if (cyUart_p50_p51_SPI_SLAVE_PINS)
    #define cyUart_p50_p51_SCLK_S_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_sclk_s__0__HSIOM)
    #define cyUart_p50_p51_SCLK_S_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_sclk_s__0__HSIOM)
    
    #define cyUart_p50_p51_SCLK_S_HSIOM_MASK      (cyUart_p50_p51_sclk_s__0__HSIOM_MASK)
    #define cyUart_p50_p51_SCLK_S_HSIOM_POS       (cyUart_p50_p51_sclk_s__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_SCLK_S_HSIOM_SEL_GPIO  (cyUart_p50_p51_sclk_s__0__HSIOM_GPIO)
    #define cyUart_p50_p51_SCLK_S_HSIOM_SEL_SPI   (cyUart_p50_p51_sclk_s__0__HSIOM_SPI)
    
    #define cyUart_p50_p51_SS0_S_HSIOM_REG    (*(reg32 *) cyUart_p50_p51_ss0_s__0__HSIOM)
    #define cyUart_p50_p51_SS0_S_HSIOM_PTR    ( (reg32 *) cyUart_p50_p51_ss0_s__0__HSIOM)
    
    #define cyUart_p50_p51_SS0_S_HSIOM_MASK       (cyUart_p50_p51_ss0_s__0__HSIOM_MASK)
    #define cyUart_p50_p51_SS0_S_HSIOM_POS        (cyUart_p50_p51_ss0_s__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_SS0_S_HSIOM_SEL_GPIO   (cyUart_p50_p51_ss0_s__0__HSIOM_GPIO)  
    #define cyUart_p50_p51_SS0_S_HSIOM_SEL_SPI    (cyUart_p50_p51_ss0_s__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SPI_SLAVE_PINS) */

#if (cyUart_p50_p51_SPI_SLAVE_MOSI_PIN)
    #define cyUart_p50_p51_MOSI_S_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_mosi_s__0__HSIOM)
    #define cyUart_p50_p51_MOSI_S_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_mosi_s__0__HSIOM)
    
    #define cyUart_p50_p51_MOSI_S_HSIOM_MASK      (cyUart_p50_p51_mosi_s__0__HSIOM_MASK)
    #define cyUart_p50_p51_MOSI_S_HSIOM_POS       (cyUart_p50_p51_mosi_s__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_MOSI_S_HSIOM_SEL_GPIO  (cyUart_p50_p51_mosi_s__0__HSIOM_GPIO)
    #define cyUart_p50_p51_MOSI_S_HSIOM_SEL_SPI   (cyUart_p50_p51_mosi_s__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SPI_SLAVE_MOSI_PIN) */

#if (cyUart_p50_p51_SPI_SLAVE_MISO_PIN)
    #define cyUart_p50_p51_MISO_S_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_miso_s__0__HSIOM)
    #define cyUart_p50_p51_MISO_S_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_miso_s__0__HSIOM)
    
    #define cyUart_p50_p51_MISO_S_HSIOM_MASK      (cyUart_p50_p51_miso_s__0__HSIOM_MASK)
    #define cyUart_p50_p51_MISO_S_HSIOM_POS       (cyUart_p50_p51_miso_s__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_MISO_S_HSIOM_SEL_GPIO  (cyUart_p50_p51_miso_s__0__HSIOM_GPIO)
    #define cyUart_p50_p51_MISO_S_HSIOM_SEL_SPI   (cyUart_p50_p51_miso_s__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SPI_SLAVE_MISO_PIN) */

#if (cyUart_p50_p51_SPI_MASTER_MISO_PIN)
    #define cyUart_p50_p51_MISO_M_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_miso_m__0__HSIOM)
    #define cyUart_p50_p51_MISO_M_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_miso_m__0__HSIOM)
    
    #define cyUart_p50_p51_MISO_M_HSIOM_MASK      (cyUart_p50_p51_miso_m__0__HSIOM_MASK)
    #define cyUart_p50_p51_MISO_M_HSIOM_POS       (cyUart_p50_p51_miso_m__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_MISO_M_HSIOM_SEL_GPIO  (cyUart_p50_p51_miso_m__0__HSIOM_GPIO)
    #define cyUart_p50_p51_MISO_M_HSIOM_SEL_SPI   (cyUart_p50_p51_miso_m__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SPI_MASTER_MISO_PIN) */

#if (cyUart_p50_p51_SPI_MASTER_MOSI_PIN)
    #define cyUart_p50_p51_MOSI_M_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_mosi_m__0__HSIOM)
    #define cyUart_p50_p51_MOSI_M_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_mosi_m__0__HSIOM)
    
    #define cyUart_p50_p51_MOSI_M_HSIOM_MASK      (cyUart_p50_p51_mosi_m__0__HSIOM_MASK)
    #define cyUart_p50_p51_MOSI_M_HSIOM_POS       (cyUart_p50_p51_mosi_m__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_MOSI_M_HSIOM_SEL_GPIO  (cyUart_p50_p51_mosi_m__0__HSIOM_GPIO)
    #define cyUart_p50_p51_MOSI_M_HSIOM_SEL_SPI   (cyUart_p50_p51_mosi_m__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SPI_MASTER_MOSI_PIN) */

#if (cyUart_p50_p51_SPI_MASTER_SCLK_PIN)
    #define cyUart_p50_p51_SCLK_M_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_sclk_m__0__HSIOM)
    #define cyUart_p50_p51_SCLK_M_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_sclk_m__0__HSIOM)
    
    #define cyUart_p50_p51_SCLK_M_HSIOM_MASK      (cyUart_p50_p51_sclk_m__0__HSIOM_MASK)
    #define cyUart_p50_p51_SCLK_M_HSIOM_POS       (cyUart_p50_p51_sclk_m__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_SCLK_M_HSIOM_SEL_GPIO  (cyUart_p50_p51_sclk_m__0__HSIOM_GPIO)
    #define cyUart_p50_p51_SCLK_M_HSIOM_SEL_SPI   (cyUart_p50_p51_sclk_m__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SPI_MASTER_SCLK_PIN) */

#if (cyUart_p50_p51_SPI_MASTER_SS0_PIN)
    #define cyUart_p50_p51_SS0_M_HSIOM_REG    (*(reg32 *) cyUart_p50_p51_ss0_m__0__HSIOM)
    #define cyUart_p50_p51_SS0_M_HSIOM_PTR    ( (reg32 *) cyUart_p50_p51_ss0_m__0__HSIOM)
    
    #define cyUart_p50_p51_SS0_M_HSIOM_MASK       (cyUart_p50_p51_ss0_m__0__HSIOM_MASK)
    #define cyUart_p50_p51_SS0_M_HSIOM_POS        (cyUart_p50_p51_ss0_m__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_SS0_M_HSIOM_SEL_GPIO   (cyUart_p50_p51_ss0_m__0__HSIOM_GPIO)
    #define cyUart_p50_p51_SS0_M_HSIOM_SEL_SPI    (cyUart_p50_p51_ss0_m__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SPI_MASTER_SS0_PIN) */

#if (cyUart_p50_p51_SPI_MASTER_SS1_PIN)
    #define cyUart_p50_p51_SS1_M_HSIOM_REG    (*(reg32 *) cyUart_p50_p51_ss1_m__0__HSIOM)
    #define cyUart_p50_p51_SS1_M_HSIOM_PTR    ( (reg32 *) cyUart_p50_p51_ss1_m__0__HSIOM)
    
    #define cyUart_p50_p51_SS1_M_HSIOM_MASK       (cyUart_p50_p51_ss1_m__0__HSIOM_MASK)
    #define cyUart_p50_p51_SS1_M_HSIOM_POS        (cyUart_p50_p51_ss1_m__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_SS1_M_HSIOM_SEL_GPIO   (cyUart_p50_p51_ss1_m__0__HSIOM_GPIO)
    #define cyUart_p50_p51_SS1_M_HSIOM_SEL_SPI    (cyUart_p50_p51_ss1_m__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SPI_MASTER_SS1_PIN) */

#if (cyUart_p50_p51_SPI_MASTER_SS2_PIN)
    #define cyUart_p50_p51_SS2_M_HSIOM_REG    (*(reg32 *) cyUart_p50_p51_ss2_m__0__HSIOM)
    #define cyUart_p50_p51_SS2_M_HSIOM_PTR    ( (reg32 *) cyUart_p50_p51_ss2_m__0__HSIOM)
    
    #define cyUart_p50_p51_SS2_M_HSIOM_MASK       (cyUart_p50_p51_ss2_m__0__HSIOM_MASK)
    #define cyUart_p50_p51_SS2_M_HSIOM_POS        (cyUart_p50_p51_ss2_m__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_SS2_M_HSIOM_SEL_GPIO   (cyUart_p50_p51_ss2_m__0__HSIOM_GPIO)
    #define cyUart_p50_p51_SS2_M_HSIOM_SEL_SPI    (cyUart_p50_p51_ss2_m__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SPI_MASTER_SS2_PIN) */

#if (cyUart_p50_p51_SPI_MASTER_SS3_PIN)
    #define cyUart_p50_p51_SS3_M_HSIOM_REG    (*(reg32 *) cyUart_p50_p51_ss3_m__0__HSIOM)
    #define cyUart_p50_p51_SS3_M_HSIOM_PTR    ( (reg32 *) cyUart_p50_p51_ss3_m__0__HSIOM)
    
    #define cyUart_p50_p51_SS3_M_HSIOM_MASK      (cyUart_p50_p51_ss3_m__0__HSIOM_MASK)
    #define cyUart_p50_p51_SS3_M_HSIOM_POS       (cyUart_p50_p51_ss3_m__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_SS3_M_HSIOM_SEL_GPIO  (cyUart_p50_p51_ss3_m__0__HSIOM_GPIO)
    #define cyUart_p50_p51_SS3_M_HSIOM_SEL_SPI   (cyUart_p50_p51_ss3_m__0__HSIOM_SPI)
#endif /* (cyUart_p50_p51_SPI_MASTER_SS3_PIN) */

#if (cyUart_p50_p51_UART_RX_PIN)
    #define cyUart_p50_p51_RX_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_rx__0__HSIOM)
    #define cyUart_p50_p51_RX_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_rx__0__HSIOM)
    
    #define cyUart_p50_p51_RX_HSIOM_MASK      (cyUart_p50_p51_rx__0__HSIOM_MASK)
    #define cyUart_p50_p51_RX_HSIOM_POS       (cyUart_p50_p51_rx__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_RX_HSIOM_SEL_GPIO  (cyUart_p50_p51_rx__0__HSIOM_GPIO)
    #define cyUart_p50_p51_RX_HSIOM_SEL_UART  (cyUart_p50_p51_rx__0__HSIOM_UART)
#endif /* (cyUart_p50_p51_UART_RX_PIN) */

#if (cyUart_p50_p51_UART_RX_WAKE_PIN)
    #define cyUart_p50_p51_RX_WAKE_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_rx_wake__0__HSIOM)
    #define cyUart_p50_p51_RX_WAKE_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_rx_wake__0__HSIOM)
    
    #define cyUart_p50_p51_RX_WAKE_HSIOM_MASK      (cyUart_p50_p51_rx_wake__0__HSIOM_MASK)
    #define cyUart_p50_p51_RX_WAKE_HSIOM_POS       (cyUart_p50_p51_rx_wake__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_RX_WAKE_HSIOM_SEL_GPIO  (cyUart_p50_p51_rx_wake__0__HSIOM_GPIO)
    #define cyUart_p50_p51_RX_WAKE_HSIOM_SEL_UART  (cyUart_p50_p51_rx_wake__0__HSIOM_UART)
#endif /* (cyUart_p50_p51_UART_WAKE_RX_PIN) */

#if (cyUart_p50_p51_UART_CTS_PIN)
    #define cyUart_p50_p51_CTS_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_cts__0__HSIOM)
    #define cyUart_p50_p51_CTS_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_cts__0__HSIOM)
    
    #define cyUart_p50_p51_CTS_HSIOM_MASK      (cyUart_p50_p51_cts__0__HSIOM_MASK)
    #define cyUart_p50_p51_CTS_HSIOM_POS       (cyUart_p50_p51_cts__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_CTS_HSIOM_SEL_GPIO  (cyUart_p50_p51_cts__0__HSIOM_GPIO)
    #define cyUart_p50_p51_CTS_HSIOM_SEL_UART  (cyUart_p50_p51_cts__0__HSIOM_UART)
#endif /* (cyUart_p50_p51_UART_CTS_PIN) */

#if (cyUart_p50_p51_UART_TX_PIN)
    #define cyUart_p50_p51_TX_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_tx__0__HSIOM)
    #define cyUart_p50_p51_TX_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_tx__0__HSIOM)
    
    #define cyUart_p50_p51_TX_HSIOM_MASK      (cyUart_p50_p51_tx__0__HSIOM_MASK)
    #define cyUart_p50_p51_TX_HSIOM_POS       (cyUart_p50_p51_tx__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_TX_HSIOM_SEL_GPIO  (cyUart_p50_p51_tx__0__HSIOM_GPIO)
    #define cyUart_p50_p51_TX_HSIOM_SEL_UART  (cyUart_p50_p51_tx__0__HSIOM_UART)
#endif /* (cyUart_p50_p51_UART_TX_PIN) */

#if (cyUart_p50_p51_UART_RX_TX_PIN)
    #define cyUart_p50_p51_RX_TX_HSIOM_REG   (*(reg32 *) cyUart_p50_p51_rx_tx__0__HSIOM)
    #define cyUart_p50_p51_RX_TX_HSIOM_PTR   ( (reg32 *) cyUart_p50_p51_rx_tx__0__HSIOM)
    
    #define cyUart_p50_p51_RX_TX_HSIOM_MASK      (cyUart_p50_p51_rx_tx__0__HSIOM_MASK)
    #define cyUart_p50_p51_RX_TX_HSIOM_POS       (cyUart_p50_p51_rx_tx__0__HSIOM_SHIFT)
    #define cyUart_p50_p51_RX_TX_HSIOM_SEL_GPIO  (cyUart_p50_p51_rx_tx__0__HSIOM_GPIO)
    #define cyUart_p50_p51_RX_TX_HSIOM_SEL_UART  (cyUart_p50_p51_rx_tx__0__HSIOM_UART)
#endif /* (cyUart_p50_p51_UART_RX_TX_PIN) */

#if (cyUart_p50_p51_UART_RTS_PIN)
    #define cyUart_p50_p51_RTS_HSIOM_REG      (*(reg32 *) cyUart_p50_p51_rts__0__HSIOM)
    #define cyUart_p50_p51_RTS_HSIOM_PTR      ( (reg32 *) cyUart_p50_p51_rts__0__HSIOM)
    
    #define cyUart_p50_p51_RTS_HSIOM_MASK     (cyUart_p50_p51_rts__0__HSIOM_MASK)
    #define cyUart_p50_p51_RTS_HSIOM_POS      (cyUart_p50_p51_rts__0__HSIOM_SHIFT)    
    #define cyUart_p50_p51_RTS_HSIOM_SEL_GPIO (cyUart_p50_p51_rts__0__HSIOM_GPIO)
    #define cyUart_p50_p51_RTS_HSIOM_SEL_UART (cyUart_p50_p51_rts__0__HSIOM_UART)    
#endif /* (cyUart_p50_p51_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define cyUart_p50_p51_HSIOM_DEF_SEL      (0x00u)
#define cyUart_p50_p51_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for cyUart_p50_p51_CY_SCBIP_V0 
* and cyUart_p50_p51_CY_SCBIP_V1. It is not recommended to use them for 
* cyUart_p50_p51_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define cyUart_p50_p51_HSIOM_UART_SEL     (0x09u)
#define cyUart_p50_p51_HSIOM_I2C_SEL      (0x0Eu)
#define cyUart_p50_p51_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define cyUart_p50_p51_RX_SCL_MOSI_PIN_INDEX       (0u)
#define cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX       (1u)
#define cyUart_p50_p51_CTS_SCLK_PIN_INDEX       (2u)
#define cyUart_p50_p51_RTS_SS0_PIN_INDEX       (3u)
#define cyUart_p50_p51_SS1_PIN_INDEX                  (4u)
#define cyUart_p50_p51_SS2_PIN_INDEX                  (5u)
#define cyUart_p50_p51_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define cyUart_p50_p51_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << cyUart_p50_p51_RX_SCL_MOSI_PIN_INDEX)
#define cyUart_p50_p51_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX)
#define cyUart_p50_p51_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << cyUart_p50_p51_CTS_SCLK_PIN_INDEX)
#define cyUart_p50_p51_RTS_SS0_PIN_MASK     ((uint32) 0x01u << cyUart_p50_p51_RTS_SS0_PIN_INDEX)
#define cyUart_p50_p51_SS1_PIN_MASK                ((uint32) 0x01u << cyUart_p50_p51_SS1_PIN_INDEX)
#define cyUart_p50_p51_SS2_PIN_MASK                ((uint32) 0x01u << cyUart_p50_p51_SS2_PIN_INDEX)
#define cyUart_p50_p51_SS3_PIN_MASK                ((uint32) 0x01u << cyUart_p50_p51_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define cyUart_p50_p51_INTCFG_TYPE_MASK           (0x03u)
#define cyUart_p50_p51_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define cyUart_p50_p51_PIN_DM_ALG_HIZ  (0u)
#define cyUart_p50_p51_PIN_DM_DIG_HIZ  (1u)
#define cyUart_p50_p51_PIN_DM_OD_LO    (4u)
#define cyUart_p50_p51_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define cyUart_p50_p51_DM_MASK    (0x7u)
#define cyUart_p50_p51_DM_SIZE    (3u)
#define cyUart_p50_p51_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) cyUart_p50_p51_DM_MASK << (cyUart_p50_p51_DM_SIZE * (pos)))) >> \
                                                              (cyUart_p50_p51_DM_SIZE * (pos)) )

#if (cyUart_p50_p51_TX_SDA_MISO_PIN)
    #define cyUart_p50_p51_CHECK_TX_SDA_MISO_PIN_USED \
                (cyUart_p50_p51_PIN_DM_ALG_HIZ != \
                    cyUart_p50_p51_GET_P4_PIN_DM(cyUart_p50_p51_uart_tx_i2c_sda_spi_miso_PC, \
                                                   cyUart_p50_p51_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (cyUart_p50_p51_TX_SDA_MISO_PIN) */

#if (cyUart_p50_p51_RTS_SS0_PIN)
    #define cyUart_p50_p51_CHECK_RTS_SS0_PIN_USED \
                (cyUart_p50_p51_PIN_DM_ALG_HIZ != \
                    cyUart_p50_p51_GET_P4_PIN_DM(cyUart_p50_p51_uart_rts_spi_ss0_PC, \
                                                   cyUart_p50_p51_uart_rts_spi_ss0_SHIFT))
#endif /* (cyUart_p50_p51_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define cyUart_p50_p51_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define cyUart_p50_p51_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define cyUart_p50_p51_SET_HSIOM_SEL(reg, mask, pos, sel) cyUart_p50_p51_SET_REGISTER_BITS(reg, mask, pos, sel)
#define cyUart_p50_p51_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        cyUart_p50_p51_SET_REGISTER_BITS(reg, mask, pos, intType)
#define cyUart_p50_p51_SET_INP_DIS(reg, mask, val) cyUart_p50_p51_SET_REGISTER_BIT(reg, mask, val)

/* cyUart_p50_p51_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  cyUart_p50_p51_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (cyUart_p50_p51_CY_SCBIP_V0)
#if (cyUart_p50_p51_I2C_PINS)
    #define cyUart_p50_p51_SET_I2C_SCL_DR(val) cyUart_p50_p51_scl_Write(val)

    #define cyUart_p50_p51_SET_I2C_SCL_HSIOM_SEL(sel) \
                          cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_SCL_HSIOM_REG,  \
                                                         cyUart_p50_p51_SCL_HSIOM_MASK, \
                                                         cyUart_p50_p51_SCL_HSIOM_POS,  \
                                                         (sel))
    #define cyUart_p50_p51_WAIT_SCL_SET_HIGH  (0u == cyUart_p50_p51_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN)
    #define cyUart_p50_p51_SET_I2C_SCL_DR(val) \
                            cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define cyUart_p50_p51_SET_I2C_SCL_HSIOM_SEL(sel) \
                    cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define cyUart_p50_p51_WAIT_SCL_SET_HIGH  (0u == cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (cyUart_p50_p51_RX_SCL_MOSI_PIN)
    #define cyUart_p50_p51_SET_I2C_SCL_DR(val) \
                            cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define cyUart_p50_p51_SET_I2C_SCL_HSIOM_SEL(sel) \
                            cyUart_p50_p51_SET_HSIOM_SEL(cyUart_p50_p51_RX_SCL_MOSI_HSIOM_REG,  \
                                                           cyUart_p50_p51_RX_SCL_MOSI_HSIOM_MASK, \
                                                           cyUart_p50_p51_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define cyUart_p50_p51_WAIT_SCL_SET_HIGH  (0u == cyUart_p50_p51_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define cyUart_p50_p51_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define cyUart_p50_p51_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define cyUart_p50_p51_WAIT_SCL_SET_HIGH  (0u)
#endif /* (cyUart_p50_p51_I2C_PINS) */

/* SCB I2C: sda signal */
#if (cyUart_p50_p51_I2C_PINS)
    #define cyUart_p50_p51_WAIT_SDA_SET_HIGH  (0u == cyUart_p50_p51_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (cyUart_p50_p51_TX_SDA_MISO_PIN)
    #define cyUart_p50_p51_WAIT_SDA_SET_HIGH  (0u == cyUart_p50_p51_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define cyUart_p50_p51_WAIT_SDA_SET_HIGH  (0u)
#endif /* (cyUart_p50_p51_MOSI_SCL_RX_PIN) */
#endif /* (cyUart_p50_p51_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (cyUart_p50_p51_RX_SCL_MOSI_PIN)
    #define cyUart_p50_p51_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN)
    #define cyUart_p50_p51_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) cyUart_p50_p51_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(cyUart_p50_p51_UART_RX_WAKE_PIN)
    #define cyUart_p50_p51_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) cyUart_p50_p51_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (cyUart_p50_p51_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define cyUart_p50_p51_REMOVE_MOSI_SCL_RX_WAKE_PIN    cyUart_p50_p51_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define cyUart_p50_p51_REMOVE_MOSI_SCL_RX_PIN         cyUart_p50_p51_REMOVE_RX_SCL_MOSI_PIN
#define cyUart_p50_p51_REMOVE_MISO_SDA_TX_PIN         cyUart_p50_p51_REMOVE_TX_SDA_MISO_PIN
#ifndef cyUart_p50_p51_REMOVE_SCLK_PIN
#define cyUart_p50_p51_REMOVE_SCLK_PIN                cyUart_p50_p51_REMOVE_CTS_SCLK_PIN
#endif /* cyUart_p50_p51_REMOVE_SCLK_PIN */
#ifndef cyUart_p50_p51_REMOVE_SS0_PIN
#define cyUart_p50_p51_REMOVE_SS0_PIN                 cyUart_p50_p51_REMOVE_RTS_SS0_PIN
#endif /* cyUart_p50_p51_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define cyUart_p50_p51_MOSI_SCL_RX_WAKE_PIN   cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN
#define cyUart_p50_p51_MOSI_SCL_RX_PIN        cyUart_p50_p51_RX_SCL_MOSI_PIN
#define cyUart_p50_p51_MISO_SDA_TX_PIN        cyUart_p50_p51_TX_SDA_MISO_PIN
#ifndef cyUart_p50_p51_SCLK_PIN
#define cyUart_p50_p51_SCLK_PIN               cyUart_p50_p51_CTS_SCLK_PIN
#endif /* cyUart_p50_p51_SCLK_PIN */
#ifndef cyUart_p50_p51_SS0_PIN
#define cyUart_p50_p51_SS0_PIN                cyUart_p50_p51_RTS_SS0_PIN
#endif /* cyUart_p50_p51_SS0_PIN */

#if (cyUart_p50_p51_MOSI_SCL_RX_WAKE_PIN)
    #define cyUart_p50_p51_MOSI_SCL_RX_WAKE_HSIOM_REG     cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define cyUart_p50_p51_MOSI_SCL_RX_WAKE_HSIOM_PTR     cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define cyUart_p50_p51_MOSI_SCL_RX_WAKE_HSIOM_MASK    cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define cyUart_p50_p51_MOSI_SCL_RX_WAKE_HSIOM_POS     cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define cyUart_p50_p51_MOSI_SCL_RX_WAKE_INTCFG_REG    cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define cyUart_p50_p51_MOSI_SCL_RX_WAKE_INTCFG_PTR    cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define cyUart_p50_p51_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define cyUart_p50_p51_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  cyUart_p50_p51_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN) */

#if (cyUart_p50_p51_MOSI_SCL_RX_PIN)
    #define cyUart_p50_p51_MOSI_SCL_RX_HSIOM_REG      cyUart_p50_p51_RX_SCL_MOSI_HSIOM_REG
    #define cyUart_p50_p51_MOSI_SCL_RX_HSIOM_PTR      cyUart_p50_p51_RX_SCL_MOSI_HSIOM_PTR
    #define cyUart_p50_p51_MOSI_SCL_RX_HSIOM_MASK     cyUart_p50_p51_RX_SCL_MOSI_HSIOM_MASK
    #define cyUart_p50_p51_MOSI_SCL_RX_HSIOM_POS      cyUart_p50_p51_RX_SCL_MOSI_HSIOM_POS
#endif /* (cyUart_p50_p51_MOSI_SCL_RX_PIN) */

#if (cyUart_p50_p51_MISO_SDA_TX_PIN)
    #define cyUart_p50_p51_MISO_SDA_TX_HSIOM_REG      cyUart_p50_p51_TX_SDA_MISO_HSIOM_REG
    #define cyUart_p50_p51_MISO_SDA_TX_HSIOM_PTR      cyUart_p50_p51_TX_SDA_MISO_HSIOM_REG
    #define cyUart_p50_p51_MISO_SDA_TX_HSIOM_MASK     cyUart_p50_p51_TX_SDA_MISO_HSIOM_REG
    #define cyUart_p50_p51_MISO_SDA_TX_HSIOM_POS      cyUart_p50_p51_TX_SDA_MISO_HSIOM_REG
#endif /* (cyUart_p50_p51_MISO_SDA_TX_PIN_PIN) */

#if (cyUart_p50_p51_SCLK_PIN)
    #ifndef cyUart_p50_p51_SCLK_HSIOM_REG
    #define cyUart_p50_p51_SCLK_HSIOM_REG     cyUart_p50_p51_CTS_SCLK_HSIOM_REG
    #define cyUart_p50_p51_SCLK_HSIOM_PTR     cyUart_p50_p51_CTS_SCLK_HSIOM_PTR
    #define cyUart_p50_p51_SCLK_HSIOM_MASK    cyUart_p50_p51_CTS_SCLK_HSIOM_MASK
    #define cyUart_p50_p51_SCLK_HSIOM_POS     cyUart_p50_p51_CTS_SCLK_HSIOM_POS
    #endif /* cyUart_p50_p51_SCLK_HSIOM_REG */
#endif /* (cyUart_p50_p51_SCLK_PIN) */

#if (cyUart_p50_p51_SS0_PIN)
    #ifndef cyUart_p50_p51_SS0_HSIOM_REG
    #define cyUart_p50_p51_SS0_HSIOM_REG      cyUart_p50_p51_RTS_SS0_HSIOM_REG
    #define cyUart_p50_p51_SS0_HSIOM_PTR      cyUart_p50_p51_RTS_SS0_HSIOM_PTR
    #define cyUart_p50_p51_SS0_HSIOM_MASK     cyUart_p50_p51_RTS_SS0_HSIOM_MASK
    #define cyUart_p50_p51_SS0_HSIOM_POS      cyUart_p50_p51_RTS_SS0_HSIOM_POS
    #endif /* cyUart_p50_p51_SS0_HSIOM_REG */
#endif /* (cyUart_p50_p51_SS0_PIN) */

#define cyUart_p50_p51_MOSI_SCL_RX_WAKE_PIN_INDEX cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_INDEX
#define cyUart_p50_p51_MOSI_SCL_RX_PIN_INDEX      cyUart_p50_p51_RX_SCL_MOSI_PIN_INDEX
#define cyUart_p50_p51_MISO_SDA_TX_PIN_INDEX      cyUart_p50_p51_TX_SDA_MISO_PIN_INDEX
#ifndef cyUart_p50_p51_SCLK_PIN_INDEX
#define cyUart_p50_p51_SCLK_PIN_INDEX             cyUart_p50_p51_CTS_SCLK_PIN_INDEX
#endif /* cyUart_p50_p51_SCLK_PIN_INDEX */
#ifndef cyUart_p50_p51_SS0_PIN_INDEX
#define cyUart_p50_p51_SS0_PIN_INDEX              cyUart_p50_p51_RTS_SS0_PIN_INDEX
#endif /* cyUart_p50_p51_SS0_PIN_INDEX */

#define cyUart_p50_p51_MOSI_SCL_RX_WAKE_PIN_MASK cyUart_p50_p51_RX_WAKE_SCL_MOSI_PIN_MASK
#define cyUart_p50_p51_MOSI_SCL_RX_PIN_MASK      cyUart_p50_p51_RX_SCL_MOSI_PIN_MASK
#define cyUart_p50_p51_MISO_SDA_TX_PIN_MASK      cyUart_p50_p51_TX_SDA_MISO_PIN_MASK
#ifndef cyUart_p50_p51_SCLK_PIN_MASK
#define cyUart_p50_p51_SCLK_PIN_MASK             cyUart_p50_p51_CTS_SCLK_PIN_MASK
#endif /* cyUart_p50_p51_SCLK_PIN_MASK */
#ifndef cyUart_p50_p51_SS0_PIN_MASK
#define cyUart_p50_p51_SS0_PIN_MASK              cyUart_p50_p51_RTS_SS0_PIN_MASK
#endif /* cyUart_p50_p51_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_cyUart_p50_p51_H) */


/* [] END OF FILE */

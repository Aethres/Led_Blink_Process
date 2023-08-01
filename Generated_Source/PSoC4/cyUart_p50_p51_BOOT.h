/***************************************************************************//**
* \file cyUart_p50_p51_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_cyUart_p50_p51_H)
#define CY_SCB_BOOT_cyUart_p50_p51_H

#include "cyUart_p50_p51_PVT.h"

#if (cyUart_p50_p51_SCB_MODE_I2C_INC)
    #include "cyUart_p50_p51_I2C.h"
#endif /* (cyUart_p50_p51_SCB_MODE_I2C_INC) */

#if (cyUart_p50_p51_SCB_MODE_EZI2C_INC)
    #include "cyUart_p50_p51_EZI2C.h"
#endif /* (cyUart_p50_p51_SCB_MODE_EZI2C_INC) */

#if (cyUart_p50_p51_SCB_MODE_SPI_INC || cyUart_p50_p51_SCB_MODE_UART_INC)
    #include "cyUart_p50_p51_SPI_UART.h"
#endif /* (cyUart_p50_p51_SCB_MODE_SPI_INC || cyUart_p50_p51_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define cyUart_p50_p51_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_cyUart_p50_p51) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (cyUart_p50_p51_SCB_MODE_I2C_INC)
    #define cyUart_p50_p51_I2C_BTLDR_COMM_ENABLED     (cyUart_p50_p51_BTLDR_COMM_ENABLED && \
                                                            (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             cyUart_p50_p51_I2C_SLAVE_CONST))
#else
     #define cyUart_p50_p51_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (cyUart_p50_p51_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (cyUart_p50_p51_SCB_MODE_EZI2C_INC)
    #define cyUart_p50_p51_EZI2C_BTLDR_COMM_ENABLED   (cyUart_p50_p51_BTLDR_COMM_ENABLED && \
                                                         cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define cyUart_p50_p51_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (cyUart_p50_p51_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (cyUart_p50_p51_SCB_MODE_SPI_INC)
    #define cyUart_p50_p51_SPI_BTLDR_COMM_ENABLED     (cyUart_p50_p51_BTLDR_COMM_ENABLED && \
                                                            (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             cyUart_p50_p51_SPI_SLAVE_CONST))
#else
        #define cyUart_p50_p51_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (cyUart_p50_p51_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (cyUart_p50_p51_SCB_MODE_UART_INC)
       #define cyUart_p50_p51_UART_BTLDR_COMM_ENABLED    (cyUart_p50_p51_BTLDR_COMM_ENABLED && \
                                                            (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (cyUart_p50_p51_UART_RX_DIRECTION && \
                                                              cyUart_p50_p51_UART_TX_DIRECTION)))
#else
     #define cyUart_p50_p51_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (cyUart_p50_p51_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define cyUart_p50_p51_BTLDR_COMM_MODE_ENABLED    (cyUart_p50_p51_I2C_BTLDR_COMM_ENABLED   || \
                                                     cyUart_p50_p51_SPI_BTLDR_COMM_ENABLED   || \
                                                     cyUart_p50_p51_EZI2C_BTLDR_COMM_ENABLED || \
                                                     cyUart_p50_p51_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (cyUart_p50_p51_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void cyUart_p50_p51_I2CCyBtldrCommStart(void);
    void cyUart_p50_p51_I2CCyBtldrCommStop (void);
    void cyUart_p50_p51_I2CCyBtldrCommReset(void);
    cystatus cyUart_p50_p51_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus cyUart_p50_p51_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (cyUart_p50_p51_SCB_MODE_I2C_CONST_CFG)
        #define cyUart_p50_p51_CyBtldrCommStart   cyUart_p50_p51_I2CCyBtldrCommStart
        #define cyUart_p50_p51_CyBtldrCommStop    cyUart_p50_p51_I2CCyBtldrCommStop
        #define cyUart_p50_p51_CyBtldrCommReset   cyUart_p50_p51_I2CCyBtldrCommReset
        #define cyUart_p50_p51_CyBtldrCommRead    cyUart_p50_p51_I2CCyBtldrCommRead
        #define cyUart_p50_p51_CyBtldrCommWrite   cyUart_p50_p51_I2CCyBtldrCommWrite
    #endif /* (cyUart_p50_p51_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (cyUart_p50_p51_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (cyUart_p50_p51_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void cyUart_p50_p51_EzI2CCyBtldrCommStart(void);
    void cyUart_p50_p51_EzI2CCyBtldrCommStop (void);
    void cyUart_p50_p51_EzI2CCyBtldrCommReset(void);
    cystatus cyUart_p50_p51_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus cyUart_p50_p51_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (cyUart_p50_p51_SCB_MODE_EZI2C_CONST_CFG)
        #define cyUart_p50_p51_CyBtldrCommStart   cyUart_p50_p51_EzI2CCyBtldrCommStart
        #define cyUart_p50_p51_CyBtldrCommStop    cyUart_p50_p51_EzI2CCyBtldrCommStop
        #define cyUart_p50_p51_CyBtldrCommReset   cyUart_p50_p51_EzI2CCyBtldrCommReset
        #define cyUart_p50_p51_CyBtldrCommRead    cyUart_p50_p51_EzI2CCyBtldrCommRead
        #define cyUart_p50_p51_CyBtldrCommWrite   cyUart_p50_p51_EzI2CCyBtldrCommWrite
    #endif /* (cyUart_p50_p51_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (cyUart_p50_p51_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (cyUart_p50_p51_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void cyUart_p50_p51_SpiCyBtldrCommStart(void);
    void cyUart_p50_p51_SpiCyBtldrCommStop (void);
    void cyUart_p50_p51_SpiCyBtldrCommReset(void);
    cystatus cyUart_p50_p51_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus cyUart_p50_p51_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (cyUart_p50_p51_SCB_MODE_SPI_CONST_CFG)
        #define cyUart_p50_p51_CyBtldrCommStart   cyUart_p50_p51_SpiCyBtldrCommStart
        #define cyUart_p50_p51_CyBtldrCommStop    cyUart_p50_p51_SpiCyBtldrCommStop
        #define cyUart_p50_p51_CyBtldrCommReset   cyUart_p50_p51_SpiCyBtldrCommReset
        #define cyUart_p50_p51_CyBtldrCommRead    cyUart_p50_p51_SpiCyBtldrCommRead
        #define cyUart_p50_p51_CyBtldrCommWrite   cyUart_p50_p51_SpiCyBtldrCommWrite
    #endif /* (cyUart_p50_p51_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (cyUart_p50_p51_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (cyUart_p50_p51_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void cyUart_p50_p51_UartCyBtldrCommStart(void);
    void cyUart_p50_p51_UartCyBtldrCommStop (void);
    void cyUart_p50_p51_UartCyBtldrCommReset(void);
    cystatus cyUart_p50_p51_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus cyUart_p50_p51_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (cyUart_p50_p51_SCB_MODE_UART_CONST_CFG)
        #define cyUart_p50_p51_CyBtldrCommStart   cyUart_p50_p51_UartCyBtldrCommStart
        #define cyUart_p50_p51_CyBtldrCommStop    cyUart_p50_p51_UartCyBtldrCommStop
        #define cyUart_p50_p51_CyBtldrCommReset   cyUart_p50_p51_UartCyBtldrCommReset
        #define cyUart_p50_p51_CyBtldrCommRead    cyUart_p50_p51_UartCyBtldrCommRead
        #define cyUart_p50_p51_CyBtldrCommWrite   cyUart_p50_p51_UartCyBtldrCommWrite
    #endif /* (cyUart_p50_p51_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (cyUart_p50_p51_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (cyUart_p50_p51_BTLDR_COMM_ENABLED)
    #if (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void cyUart_p50_p51_CyBtldrCommStart(void);
        void cyUart_p50_p51_CyBtldrCommStop (void);
        void cyUart_p50_p51_CyBtldrCommReset(void);
        cystatus cyUart_p50_p51_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus cyUart_p50_p51_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (cyUart_p50_p51_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_cyUart_p50_p51)
        #define CyBtldrCommStart    cyUart_p50_p51_CyBtldrCommStart
        #define CyBtldrCommStop     cyUart_p50_p51_CyBtldrCommStop
        #define CyBtldrCommReset    cyUart_p50_p51_CyBtldrCommReset
        #define CyBtldrCommWrite    cyUart_p50_p51_CyBtldrCommWrite
        #define CyBtldrCommRead     cyUart_p50_p51_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_cyUart_p50_p51) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (cyUart_p50_p51_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define cyUart_p50_p51_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define cyUart_p50_p51_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define cyUart_p50_p51_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define cyUart_p50_p51_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef cyUart_p50_p51_SPI_BYTE_TO_BYTE
    #define cyUart_p50_p51_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef cyUart_p50_p51_UART_BYTE_TO_BYTE
    #define cyUart_p50_p51_UART_BYTE_TO_BYTE  (175u)
#endif /* cyUart_p50_p51_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_cyUart_p50_p51_H) */


/* [] END OF FILE */

/**
 ****************************************************************************************
 *
 * @file uart_spp.h
 *
 * @brief UART driver for SPP
 *
 * Copyright (C) 2012. Dialog Semiconductor Ltd, unpublished work. This computer 
 * program includes Confidential, Proprietary Information and is a Trade Secret of 
 * Dialog Semiconductor Ltd.  All use, disclosure, and/or reproduction is prohibited 
 * unless authorized in writing. All Rights Reserved.
 *
 * <bluetooth.support@diasemi.com> and contributors.
 *
 ****************************************************************************************
 */

#ifndef _UART_H_
#define _UART_H_

/**
 ****************************************************************************************
 * @defgroup UART UART
 * @ingroup DRIVERS
 *
 * @brief UART driver
 *
 * @{
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>       // integer definition
#include <stdbool.h>      // boolean definition

/*
 * DEFINES
 *****************************************************************************************
 */
 
 /// Baud rate
#define UART_SPS_BAUDRATE				UART_BAUDRATE_115K2
 
 /// Flow control bytes
#define	UART_STUFFING_BYTE 							(uint8_t)0x39
#define	UART_XON_BYTE 									(uint8_t)0x11
#define	UART_XOFF_BYTE 									(uint8_t)0x13

///	Turn HW/SW flow control on(1) or off(0) and enable or disable bytestuffing
#define UART_SW_FLOW_ENABLED						1
#define UART_HW_FLOW_ENABLED						0

#if (UART_SW_FLOW_ENABLED)
#define UART_BYTESTUFFING_ENABLED				0

#undef UART_HW_FLOW_ENABLED
#endif

/* FORMULA ON HOW TO CALCULATE DIVISORS FOR BAUD RATES
** baud rate = serial clock frequency / (16*divisor)
** baud rate = 16*10^6 Hertz / (16*104) = ~9600 baud
** divisor = serial clock frequency / (16 * baud rate)
*/
// Divider for 115200 bits/s
#define UART_BAUDRATE_115K2         	9 
// Divider for 57600 bits/s
#define UART_BAUDRATE_57K6        		17
// Divider for 9600 bits/s
#define UART_BAUDRATE_9K6           	104


/// Baudrate used on the UART
#ifndef CFG_ROM
#define UART_BAUDRATE  UART_BAUDRATE_115K2
#else //CFG_ROM
#define UART_BAUDRATE  UART_BAUDRATE_460K8
#endif //CFG_ROM

#if (UART_BAUDRATE == UART_BAUDRATE_921K6)
    #define UART_CHAR_DURATION        11
#else
    #define UART_CHAR_DURATION       (UART_BAUDRATE * 22)
#endif 

/*
 * ENUMERATION DEFINITIONS
 *****************************************************************************************
 */

/// Generic enable/disable enum for UART driver
enum
{
    /// uart disable
    UART_DISABLE = 0,
    /// uart enable
    UART_ENABLE  = 1
};

/// Character format
enum
{
    /// char format 5
    UART_CHARFORMAT_5 = 0,
    /// char format 6
    UART_CHARFORMAT_6 = 1,
    /// char format 7
    UART_CHARFORMAT_7 = 2,
    /// char format 8
    UART_CHARFORMAT_8 = 3
};

/// Stop bit
enum
{
    /// stop bit 1
    UART_STOPBITS_1 = 0,
    /* Note: The number of stop bits is 1.5 if a
     * character format with 5 bit is chosen */
    /// stop bit 2
    UART_STOPBITS_2 = 1
};

/// Parity bit
enum
{
    /// even parity
    UART_PARITYBIT_EVEN  = 0,
    /// odd parity
    UART_PARITYBIT_ODD   = 1,
    /// space parity
    UART_PARITYBIT_SPACE = 2, // The parity bit is always 0.
    /// mark parity
    UART_PARITYBIT_MARK  = 3  // The parity bit is always 1.
};

/* Error detection */
enum
{
    /// error detection disabled
    UART_ERROR_DETECT_DISABLED = 0,
    /// error detection enabled
    UART_ERROR_DETECT_ENABLED  = 1
};

/// status values
enum
{
    /// status ok
    UART_STATUS_OK,
    /// status not ok
    UART_STATUS_ERROR,
		/// timeout occured
	UART_STATUS_TIMEOUT
};

/// flow control states
enum
{
    /// just data send or received
    UART_NONE 	= (uint8_t)0x00,
    /// 
    UART_XON 		= (uint8_t)0x01,
		/// 
	UART_XOFF 	= (uint8_t)0x02,
};

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initializes the UART to default values.
 *****************************************************************************************
 */
void uart_sps_init( uint8_t, uint8_t);

#ifndef CFG_ROM
/**
 ****************************************************************************************
 * @brief Enable UART flow.
 *****************************************************************************************
 */
void uart_sps_flow_on(void);

/**
 ****************************************************************************************
 * @brief Disable UART flow.
 *****************************************************************************************
 */
bool uart_sps_flow_off(void);

/**
 ****************************************************************************************
 * @brief Finish current UART transfers
 *****************************************************************************************
 */
void uart_sps_finish_transfers(void);
#endif //CFG_ROM

/**
 ****************************************************************************************
 * @brief Starts a data reception.
 *
 * As soon as the end of the data transfer or a buffer overflow is detected,
 * the hci_uart_rx_done function is executed.
 *
 * @param[in,out]  bufptr Pointer to the RX buffer
 * @param[in]      size   Size of the expected reception
 *****************************************************************************************
 */
void uart_sps_read(uint8_t *bufptr, uint32_t size, uint8_t *state, void (*callback) (uint8_t));


/**
 ****************************************************************************************
 * @brief Starts a data transmission.
 *
 * As soon as the end of the data transfer is detected, the hci_uart_tx_done function is
 * executed.
 *
 * @param[in]  bufptr Pointer to the TX buffer
 * @param[in]  size   Size of the transmission
 *****************************************************************************************
 */
void uart_sps_write(uint8_t *bufptr, uint32_t size, uint8_t *state, void (*callback) (uint8_t));

/**
 ****************************************************************************************
 * @brief Serves the data transfer interrupt requests.
 *
 * It clears the requests and executes the appropriate callback function.
 *****************************************************************************************
 */
void uart_sps_isr(void);

/// @} UART
#endif /* _UART_H_ */

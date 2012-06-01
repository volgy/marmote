//-----------------------------------------------------------------------------
// Title         : Max2830 firmware header
// Project       : Marmote SDR
//-----------------------------------------------------------------------------
// File          : max2830.h
// Author        : Benjamin Babjak and Sandor Szilvasi
// Company       : Vanderbilt University, ISIS
// Created       : 2012-05-29 10:13
// Last update   : 2011-05-31 09:15
// Platform      : Marmote
// Target device : Actel A2F500M3G
// Tool version  : CoreConsole v3.3
// Standard      : CMSIS
//-----------------------------------------------------------------------------
// Description   : Firmware for the Max2830 RF transceiver chip found on the
//                 Marmote Joshua module.
//-----------------------------------------------------------------------------
// Copyright (c) 2006-2012, Vanderbilt University
// All rights reserved.
//
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without written agreement is
// hereby granted, provided that the above copyright notice, the following
// two paragraphs and the author appear in all copies of this software.
//
// IN NO EVENT SHALL THE VANDERBILT UNIVERSITY BE LIABLE TO ANY PARTY FOR
// DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
// OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE VANDERBILT
// UNIVERSITY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE VANDERBILT UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
// ON AN "AS IS" BASIS, AND THE VANDERBILT UNIVERSITY HAS NO OBLIGATION TO
// PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
//-----------------------------------------------------------------------------
// Revisions     :
// Date            Version  Author			Description
// 2012-05-31      1.1      Sandor Szilvasi
// 2012-05-29      1.0      Benjamin Babjak	Created
//-----------------------------------------------------------------------------



#ifndef MAX2830_H_
#define MAX2830_H_

#include <a2fxxxm3.h>
#include <mss_gpio.h>
#include <mss_spi.h>

#define MSS_GPIO_LD         	MSS_GPIO_2		// Lock-Detect
#define MSS_GPIO_SHDN       	MSS_GPIO_3		// Shutdown (active-low)
#define MSS_GPIO_RXHP       	MSS_GPIO_4		// Receiver Baseband AC-Coupling High-Pass Corner Frequency
#define MSS_GPIO_ANTSEL     	MSS_GPIO_5		// Antenna Selection
#define MSS_GPIO_RXTX       	MSS_GPIO_28		// Rx/Tx Mode (Rx = 0, Tx = 1)

// FIXME: Derive these values from the non-mask defines above
#define MSS_GPIO_LD_MASK		MSS_GPIO_2_MASK
#define MSS_GPIO_SHDN_MASK      MSS_GPIO_3_MASK
#define MSS_GPIO_RXHP_MASK      MSS_GPIO_4_MASK
#define MSS_GPIO_ANTSEL_MASK    MSS_GPIO_5_MASK
#define MSS_GPIO_RXTX_MASK      MSS_GPIO_28_MASK


static const uint16_t max2830_lpf_bws[24] =
{
		 7200u,  7600u,	 8000u,	 8400u,	 8800u,	 9200u, //  8.0 MHz
		 9900u,	10450u,	11000u,	11550u,	12100u,	12650u, // 11.0 MHz
		14850u,	15675u,	16500u,	17325u,	18150u,	18975u, // 16.5 MHz
		20250u,	21375u,	22500u,	23625u,	24750u,	25875u, // 22.5 MHz
};



typedef enum __Max2830_RXTX_BW_t
{
	// 8MHz
	MAX2830_RXTX_BW_7_2MHz		= 0,
	MAX2830_RXTX_BW_7_6MHz		= 1,
	MAX2830_RXTX_BW_8MHz 		= 2,
	MAX2830_RXTX_BW_8_4MHz		= 3,
	MAX2830_RXTX_BW_8_8MHz		= 4,
	MAX2830_RXTX_BW_9_2MHz		= 5,

	// 11MHz
	MAX2830_RXTX_BW_9_9MHz		= 6,
	MAX2830_RXTX_BW_10_45MHz	= 7,
	MAX2830_RXTX_BW_11MHz		= 8,
	MAX2830_RXTX_BW_11_55MHz	= 9,
	MAX2830_RXTX_BW_12_1MHz		= 10,
	MAX2830_RXTX_BW_12_65MHz	= 11,

	// 16.5MHz
	MAX2830_RXTX_BW_14_85MHz	= 12,
	MAX2830_RXTX_BW_15_675MHz	= 13,
	MAX2830_RXTX_BW_16_5MHz		= 14,
	MAX2830_RXTX_BW_17_325MHz	= 15,
	MAX2830_RXTX_BW_18_15MHz	= 16,
	MAX2830_RXTX_BW_18_975MHz	= 17,

	// 22.5MHz
	MAX2830_RXTX_BW_20_25MHz	= 18,
	MAX2830_RXTX_BW_21_375MHz	= 19,
	MAX2830_RXTX_BW_22_5MHz		= 20,
	MAX2830_RXTX_BW_23_625MHz	= 21,
	MAX2830_RXTX_BW_24_75MHz	= 22,
	MAX2830_RXTX_BW_25_875MHz	= 23
} Max2830_RXTX_BW_t;



typedef enum __Max2830_mode_t
{
	MAX2830_SHUTDOWN_MODE	= 0,
	MAX2830_STANDBY_MODE	= 1,
	MAX2830_RX_MODE			= 2,
	MAX2830_TX_MODE 		= 3,
	MAX2830_RX_CALIBRATION_MODE = 4,
	MAX2830_TX_CALIBRATION_MODE = 5
} Max2830_mode_t;



/**
 * The number of bits in a MAX2830 SPI transaction.
 */
#define SPI_FRAME_SIZE_MAX2830 18

/**
 * Array representing the 14-bit values of the 16 MAX2830 registers.
 *
 * Note: As MAX2839 does not support register write the value of its
 *       registers is kept in this array as a reference. Register reads
 *       implicitly read values from this array.
 */
static uint16_t max2830_regs[16] =
{
		0x1740,
		0x119A,
		0x1003,
		0x0079,
		0x3666,
		0x00A0,
		0x0060,
		0x1022,
		0x2021,
		0x07B5,
		0x1DA4,
		0x007F,
		0x0140,
		0x0E92,
		0x0300,
		0x0145,
};



/**
 * The Max2830_init() function initializes the Max2830 RF transceiver chip.
 * It sets the GPIO pins that control the MAX2830 chip and configures it through
 * the SPI bus.
 *
 * Note: - The Max2830_init() function assumes that MSS_GPIO_init() has been
 *         called previously.
 *       - Make sure that the GPIO #defines match the Libero design FPGA I/O pins.
 *       - The Joshua board is initialized with minimal transmit gain.
 *
 * @param
 *   This function does not have a parameter.
 *
 * @return
 *   This function does not return a value.
 */
void Max2830_init ( void );




/**
 * The Max2830_read_register() function returns the actual content of a MAX2830 register.
 * Note: - The MAX2830 chip does not support SPI read, thus this function returns a locally
 *         stored value, e.g. no actual SPI transaction takes place.
 *
 * @param addr
 *   The address of the MAX2830 register. The valid address range is from 0 to 15.
 *
 * @return
 *   This function returns the value of the MAX2830 register at the address
 *   defined by the parameter addr.
 */
uint16_t Max2830_read_register( uint8_t addr );



/**
 * The Max2830_write_register() function writes a MAX2830 register through the SPI
 * port and updates the local copy of the register value.
 *
 * @param addr
 *   The address of the MAX2830 register. The valid address range is from 0 to 15.
 *
 * @param data
 *   The value to write to the MAX2830 register at address defined by addr.
 *
 * @return
 *   This function does not return a value.
 */
void Max2830_write_register( uint8_t addr, uint16_t data );




/**
 * The Joshua_calibrate() function calibrates the [RX/TX?] path. // FIXME
 *
 * Note: Tx calibration involves sine generation in the baseband and this
 *       feature is NOT IMPLMENTED YET.
 *
 * @param
 *   This function does not have a parameter.
 *
 * @return
 *   This function does not return a value.
 */
//void Joshua_calibrate( void );



/**
 * The Max2830_get_frequency() function reads the local oscillator frequency
 * and returns it in Hz.
 *
 * @param
 *   This function does not have a parameter.
 *
 * @return
 *   The local oscillator frequency in Hz.
 */
uint32_t Max2830_get_frequency( void );

/**
 * The Max2830_set_frequency() function sets the local oscillator frequency to
 * the value specified in the parameter.
 *
 * Note: The frequency step resolution is 20 Hz.
 *
 * @param freq
 *   The requested local oscillator frequency in Hz.
 *
 * @return
 *   This function does not return a value.
 */
void Max2830_set_frequency( uint32_t freq );


/**
 * The Joshua_get_tx_gain() function reads the actual transmit gain and returns it in dB.
 *
 * @param
 *   This function does not have a parameter.
 *
 * @return
 *   The transmit gain in dB.
 */
float Max2830_get_tx_gain( void );


/**
 * The Max2830_set_tx_gain() function sets the transmitter VGA gain to the dB value given
 * as the parameter.
 *
 * @param gain
 *   The requested transmit gain in dB. The valid gain range is from 0 to 31 dB.
 *
 * @return
 *   This function does not return a value.
 */
void Max2830_set_tx_gain( float gain );



/**
 * The Max2830_get_bandwidth() function reads the baseband
 * filter cut-off frequency and returns it in kHz.
 *
 * @param
 *   This function does not have a parameter.
 *
 * @return
 *   The baseband filter cut-off frequency in kHz.
 */
uint32_t Max2830_get_bandwidth( void );


/**
 * The Max2830_set_bandwidth() function sets the baseband low-pass filter
 * cut-off frequency to the value specified in the parameter.
 *
 * Note: The bandwidth of the baseband filter can be set in coarse steps.
 *       Thus, the actually set frequency may differ from the requested.
 *       Use the Josuha_get_bandwidth() function to determine the actual
 *       value set.
 *
 * @param
 *   The requested baseband low-pass filter cut-off frequency in Hz.
 *
 *   Valid range: TBD
 *
 * @return
 *   This function does not return a value.
 */
void Max2830_set_bandwidth( uint32_t bandwidth );


/**
 * The Max2830_Set_RXTX() function sets the RXTX pin of the MAX2830
 * to the value specified in the parameter.
 *
 * Note: The state of this pin selects not between Rx and Tx modes, but also
 *       between Shutdown and Standby, and Rx Calibration and Tx Calibration.
 *
 * @param
 *   The requested state of RXTX.
 *
 * @return
 *   This function does not return a value.
 */
//void Max2830_Set_RXTX( Max2830_RXTX_Mode_t	RXTX_mode );

/**
 * The Max2830_Set_mode() function sets the operating mode of the MAX2830
 * to the value specified in the parameter.
 *
 * Note: The state of this pin selects not between Rx and Tx modes, but also
 *       between Shutdown and Standby, and Rx Calibration and Tx Calibration.
 *
 * @param
 *   The requested state of the MAX2830 transceiver.
 *
 *   Valid values:
 *
 *  	- MAX2830_SHUTDOWN_MODE
 *  	- MAX2830_STANDBY_MODE
 *  	- MAX2830_RX_MODE
 *  	- MAX2830_TX_MODE
 *  	- MAX2830_RX_CALIBRATION_MODE
 *  	- MAX2830_TX_CALIBRATION_MODE
 *
 * @return
 *   This function does not return a value.
 */
void Max2830_set_mode( Max2830_mode_t mode );



#endif /* MAX2830_H_ */
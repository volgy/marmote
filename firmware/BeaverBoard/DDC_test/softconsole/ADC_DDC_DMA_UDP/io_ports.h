/*
 * io_ports.h
 *
 *  Created on: Nov 11, 2011
 *      Author: babjak
 */

#ifndef IO_PORTS_H_
#define IO_PORTS_H_

#include "top_hw_platform.h"

#include <stdint.h>


//Config	R/W
#define GPIO_CONFIG_REG0		(0x00+COREGPIO_0)
#define GPIO_CONFIG_REG1		(0x04+COREGPIO_0)
#define GPIO_CONFIG_REG2		(0x08+COREGPIO_0)
#define GPIO_CONFIG_REG3		(0x0C+COREGPIO_0)
#define GPIO_CONFIG_REG4		(0x10+COREGPIO_0)
#define GPIO_CONFIG_REG5		(0x14+COREGPIO_0)
#define GPIO_CONFIG_REG6		(0x18+COREGPIO_0)
#define GPIO_CONFIG_REG7		(0x1C+COREGPIO_0)
#define GPIO_CONFIG_REG8		(0x20+COREGPIO_0)
#define GPIO_CONFIG_REG9		(0x24+COREGPIO_0)
#define GPIO_CONFIG_REG10		(0x28+COREGPIO_0)
#define GPIO_CONFIG_REG11		(0x2C+COREGPIO_0)
#define GPIO_CONFIG_REG12		(0x30+COREGPIO_0)
#define GPIO_CONFIG_REG13		(0x34+COREGPIO_0)
#define GPIO_CONFIG_REG14		(0x38+COREGPIO_0)
#define GPIO_CONFIG_REG15		(0x3C+COREGPIO_0)
#define GPIO_CONFIG_REG16		(0x40+COREGPIO_0)
#define GPIO_CONFIG_REG17		(0x44+COREGPIO_0)
#define GPIO_CONFIG_REG18		(0x48+COREGPIO_0)
#define GPIO_CONFIG_REG19		(0x4C+COREGPIO_0)
#define GPIO_CONFIG_REG20		(0x50+COREGPIO_0)
#define GPIO_CONFIG_REG21		(0x54+COREGPIO_0)
#define GPIO_CONFIG_REG22		(0x58+COREGPIO_0)
#define GPIO_CONFIG_REG23		(0x5C+COREGPIO_0)
#define GPIO_CONFIG_REG24		(0x60+COREGPIO_0)
#define GPIO_CONFIG_REG25		(0x64+COREGPIO_0)
#define GPIO_CONFIG_REG26		(0x68+COREGPIO_0)
#define GPIO_CONFIG_REG27		(0x6C+COREGPIO_0)
#define GPIO_CONFIG_REG28		(0x70+COREGPIO_0)
#define GPIO_CONFIG_REG29		(0x74+COREGPIO_0)
#define GPIO_CONFIG_REG30		(0x78+COREGPIO_0)
#define GPIO_CONFIG_REG31		(0x7C+COREGPIO_0)


//Interrupt clear	W
#define GPIO_INT_CLEAR			(0x80+COREGPIO_0)


//Input R
#define GPIO_INPUT				(0x90+COREGPIO_0)


//Output R/W
#define GPIO_OUTPUT				(0xA0+COREGPIO_0)


//Bitmasks

//IO_RX_07		-> V1	-> MSS_GP_IO_0	-> 0.
//IO_RX_06		-> R3	-> MSS_GP_IO_1	-> 1.
//IO_RX_05		-> W1	-> MSS_GP_IO_2	-> 2.
//IO_RX_02		-> Y1	-> MSS_GP_IO_3	-> 3.
//IO_RX_00		-> AA1	-> MSS_GP_IO_4	-> 4.
//ADC_SCLK		-> U2	-> MSS_GP_IO_5	->
//ADC_SDOUT_A	-> V2	-> MSS_GP_IO_6	->
//ADC_SDOUT_B	-> W2	-> MSS_GP_IO_7	->
//ADC_CS		-> T3	-> MSS_GP_IO_8	->
//DAC_SYNC		-> V3	-> MSS_GP_IO_9	->
//DAC_SDIN		-> U3	-> MSS_GP_IO_10	->
//DAC_SCLK		-> T4	-> MSS_GP_IO_11 ->
//				-> AA2	-> MSS_GP_IO_12 -> 5.
//CLKOUT1		-> AB2	-> MSS_GP_IO_13 ->
//SCL			-> AB3	-> MSS_GP_IO_14 -> 6.	(I2C)
//SDA			-> Y3	-> MSS_GP_IO_15 -> 7.	(I2C)
//SCLK			-> E3	-> F2-200-IO_0	-> 8.	(SPI)
//SEN_RX		-> F3	-> F2-200-IO_1	-> 9.	(SPI)
//SDI			-> G4	-> F2-200-IO_2	-> 10.	(SPI)
//SEN_TX		-> H5	-> F2-200-IO_3	-> 11.	(SPI)
//				-> H6	-> F2-200-IO_4	-> 12.
//IO_TX_02		-> J6	-> F2-200-IO_5	-> 13.
//IO_TX_05		-> B22	-> F2-200-IO_6	-> 14.
//IO_TX_07		-> C22	-> F2-200-IO_7	-> 15.
//IO_TX_06		-> F1	-> F2-200-IO_8	-> 16.

#define GPIO_IO_RX_07	0x00000001
#define GPIO_IO_RX_06	0x00000002
#define GPIO_IO_RX_05	0x00000004
#define GPIO_IO_RX_02	0x00000008
#define GPIO_IO_RX_00	0x00000010
//						0x00000020
#define GPIO_SCL		0x00000040
#define GPIO_SDA		0x00000080
#define GPIO_SCLK		0x00000100
#define GPIO_SEN_RX		0x00000200
#define GPIO_SDI		0x00000400
#define GPIO_SEN_TX		0x00000800
//						0x00001000
#define GPIO_IO_TX_02	0x00002000
#define GPIO_IO_TX_05	0x00004000
#define GPIO_IO_TX_07	0x00008000
#define GPIO_IO_TX_06	0x00010000


void io_ports_init();
void send_SPI(uint32_t data, uint8_t data_size);


#endif /* IO_PORTS_H_ */


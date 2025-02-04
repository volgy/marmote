/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : hw_config.h
* Author             : MCD Application Team
* Version            : V3.3.0
* Date               : 21-March-2011
* Description        : Hardware Configuration & Setup
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Codec Control defines */
#define PLLon             1
#define PLLoff            0

#define VerifData         1
#define NoVerifData       0 

#define Codec_PDN_GPIO    GPIOG
#define Codec_PDN_Pin     GPIO_Pin_11

#define BufferSize        100
#define CodecAddress      0x27


#define USB_USBDP_PIN    		GPIO_Pin_12 // PA.12
#define USB_USBDP_GPIO_PORT    	GPIOA
#define USB_USBDP_GPIO_CLK    	RCC_APB2Periph_GPIOA

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* External variables --------------------------------------------------------*/
void Set_System(void);
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Config(void);
void Audio_Config(void);
void USB_Cable_Config (FunctionalState NewState);
void Speaker_Config(void);

void NVIC_Config(void);
void GPIO_Config(void);
uint32_t Sound_release(uint16_t Standard, uint16_t MCLKOutput, uint16_t AudioFreq, uint8_t AudioRepetitions);
void I2S_Config(uint16_t Standard, uint16_t MCLKOutput, uint16_t AudioFreq);
void Codec_PowerDown(void);
uint32_t I2SCodec_WriteRegister(uint32_t RegisterAddr, uint32_t RegisterValue, uint32_t Verify);
uint32_t Codec_SpeakerConfig(uint16_t I2S_Standard, uint8_t volume, uint32_t verif, uint8_t pll);
void Get_SerialNum(void);

void USB_FsInit(void); // USB_Init() is reserved by STM USB library
void USB_SoftReset(void);

#endif  /*__HW_CONFIG_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

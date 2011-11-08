#include "stm32f10x_conf.h"
#include "stm32f10x.h"

#include "power_board.h"


volatile uint32_t msTicks;                       /* timeTicks counter */

void SysTick_Handler(void) {
	msTicks++;                                     /* increment timeTicks counter */
}

static void Delay (uint32_t dlyTicks) {
	uint32_t curTicks = msTicks;

	while ((msTicks - curTicks) < dlyTicks);
}


int main (void) {

	uint16_t ctr;					

	LED_Init();			
	PowerControl_Init();
	CON_SPI_Init();
	CON_I2C_Init();

	SD_SPI_Init();
	BAT_I2C_Init();

#ifdef CON_GPIO_TEST
	CON_GPIO_Init();
#endif

	SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
	SysTick->LOAD = 72000;	
					
	ctr = 0;	

	while (1)
	{
		//LED_Toggle(LED2);
		//Delay(250);		
		//Delay(1000);	
		LED_On(LED2);	
		
//#ifdef POWER_CONTROL_TEST
		//USB_EnableSuspendMode();
		//USB_DisableSuspendMode();

		//USB_EnableHighPowerMode();
		//USB_DisableHighPowerMode();

		/*
		if (WALL_IsPowerGood())
		{
			LED_On(LED1);
			LED_Off(LED2);	
		}
		else
		{
			LED_Off(LED1);
			LED_On(LED2);	
		}
		*/
//#endif

//	POW_EnableMasterSwitch();
//	POW_DisableMasterSwitch();

//#ifdef SPI1_TEST
		//CON_SPI_SendData(ctr++);
		
		/*if
		{
			LED_On(LED2);	
			Delay(100);
		}
		*/
//#endif

//#ifdef I2C1_TEST
		//CON_I2C_SendData(ctr++,0);
//#endif

//#ifdef SPI2_TEST
		SD_SPI_SendData(ctr++);
		
		LED_Off(LED2);	
		Delay(1000);		
//#endif


//#ifdef I2C2_TEST
		//BAT_ReadRegister(00);
		//LED_Off(LED2);
		//while (1);
        /*
        GPIO_ResetBits(BAT_I2C_SCL_GPIO_PORT, BAT_I2C_SCL_PIN);
        GPIO_SetBits(BAT_I2C_SCL_GPIO_PORT, BAT_I2C_SCL_PIN);

        GPIO_ResetBits(BAT_I2C_SDA_GPIO_PORT, BAT_I2C_SDA_PIN);
        GPIO_SetBits(BAT_I2C_SDA_GPIO_PORT, BAT_I2C_SDA_PIN);
        */
//#endif

#ifdef CON_GPIO_TEST
		CON_GPIO_Set(CON_GPIO0 | CON_GPIO1 | CON_GPIO2 | CON_GPIO3 | CON_GPIO4);
		Delay(500);
		CON_GPIO_Clear(CON_GPIO0 | CON_GPIO1 | CON_GPIO2 | CON_GPIO3 | CON_GPIO4);
		Delay(500);
#endif
	}
}


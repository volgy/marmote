
#include <string.h>
#include <mss_gpio.h>
#include <mss_rtc.h>

#include "yellowstone.h"
#include "teton.h"

extern uint8_t spi_cmd_buf[];
extern uint8_t spi_cmd_length;

#include "cmd_def.h"
extern uint32_t g_rate;

int main()
{
	MSS_GPIO_init();
	Yellowstone_init();
	Max19706_init(MSS_SPI_SLAVE_1);
	Joshua_init();
	Teton_init();

	Max2830_set_tx_bandwidth(15000uL);
	Max2830_set_frequency(2405000000uL);
	Max2830_set_tx_gain(0);

	set_mode(RADIO_TX_MODE);

	TX_CTRL->PTRN = PTRN_DEFAULT;
	TX_CTRL->MASK = (node_id == 8 ? 0x55555555uL : 0xAAAAAAAAuL) & MASK_DEFAULT;
	TX_CTRL->GAIN = 1;

	while (1)
	{
		if (spi_cmd_length > 0)
		{
			process_spi_cmd_buf((const char*)spi_cmd_buf, spi_cmd_length);
			spi_cmd_length = 0;
		}

		if (tx_done_it_flag)
		{
			tx_done_it_flag = 0;
			set_mode(RADIO_STANDBY_MODE);
			MSS_GPIO_set_output(MSS_GPIO_LED1, 0);
		}
	}
}


void Timer1_IRQHandler(void)
{
	send_demo_symbols();

	MSS_GPIO_set_output(MSS_GPIO_LED1, 1);

//	if (TX_CTRL->CTRL & 1uL)
//	{
//		TX_CTRL->CTRL &= ~1uL;
//		MSS_GPIO_set_output(MSS_GPIO_LED1, 0);
//	}
//	else
//	{
//		TX_CTRL->CTRL |= 1uL;
//		MSS_GPIO_set_output(MSS_GPIO_LED1, 1);
//	}
	MSS_TIM1_clear_irq();
}
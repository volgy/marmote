// **************************************************************************
// Standard Includes */
// **************************************************************************

//#include <stdio.h>
//#include <stdlib.h>

// **************************************************************************
// Firmware Includes
// **************************************************************************

#include "CMSIS/a2fxxxm3.h"

#include "./drivers/mss_ethernet_mac/mss_ethernet_mac.h"
#include "./drivers/mss_timer/mss_timer.h"

#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/ip.h"
#include "lwip/udp.h"
#include "lwip/tcp_impl.h"
#include "lwip/dhcp.h"
#include "lwip/init.h"
#include "netif/etharp.h"

#include "SmartFusionethernetif.h"
#include "sampleserver.h"


// **************************************************************************
// Preprocessor Macros
// **************************************************************************

static uint64_t System_ticks = 0;

// Simple periodic polling function
#define PERIODIC(var,time,function) \
    if((System_ticks - var) > time) \
    {                               \
        var += time;                \
        function;                   \
    }                               \

/*
// **************************************************************************
// Declaration of global variables
// **************************************************************************
// *************************************************************************
// Extern Declarations
// **************************************************************************
*/
// Returns the current time in milliseconds,
// may be the same as sys_jiffies or at least based on it.
u32_t sys_now(void)
{
	return (u32_t) System_ticks;
}

// **************************************************************************
// Functions for Interrupt Handlers
// **************************************************************************

void Timer1_IRQHandler( void )
{
    System_ticks++;
    MSS_TIM1_clear_irq();
}


void init_system()
{
    SystemCoreClockUpdate();

//    timer1_load_value = g_FrequencyPCLK0/10000;
    MSS_TIM1_init( MSS_TIMER_PERIODIC_MODE );
    MSS_TIM1_load_immediate( (uint32_t) (g_FrequencyPCLK0/1000) ); //Divide by 1000 means an interrupt at every 1/1000 sec = 1 msec
    MSS_TIM1_start();
    MSS_TIM1_enable_irq();
}

static struct netif l_netif;                // the single network interface


// ****************************************************************
// Entry to Main form user boot code
// ****************************************************************
int main()
{
#if LWIP_ARP
    uint64_t arp_timer = 0;
#endif
#if LWIP_TCP
    uint64_t tcp_timer = 0;
#endif
#if LWIP_DHCP
    uint64_t dhcp_fine_timer = 0;
    uint64_t dhcp_coarse_timer = 0;
#endif

    // Initialization all necessary hardware components
    init_system();

    lwip_init();                                // Initialize the lwIP stack

    ethernetif_init(&l_netif);

    server_init(6000);         			// initialize the simple server
//    server_init();         			// initialize the simple server

    while (1)
    {
#if LWIP_TCP
        PERIODIC(tcp_timer, TCP_TMR_INTERVAL, tcp_tmr());
#endif
#if LWIP_ARP
        PERIODIC(arp_timer, ARP_TMR_INTERVAL, etharp_tmr());
#endif
#if LWIP_DHCP
        PERIODIC(dhcp_fine_timer, DHCP_FINE_TIMER_MSECS, dhcp_fine_tmr());
        PERIODIC(dhcp_coarse_timer, DHCP_COARSE_TIMER_MSECS, dhcp_coarse_tmr());
#endif

        ethernetif_input(&l_netif);
    }

    return 0;
}

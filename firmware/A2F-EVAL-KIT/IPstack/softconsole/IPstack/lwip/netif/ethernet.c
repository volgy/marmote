#include <string.h>

#include "conf_eth.h"
#include "lwipopts.h"

/* Scheduler include files. */
#if (NO_SYS == 0)
#include "FreeRTOS.h"
#include "task.h"
#endif


/* ethernet includes */
#include "ethernet.h"
#include "conf_eth.h"
#include "mss_ethernet_mac.h"
//BB #include "mss_watchdog.h"

#if (HTTP_USED == 1)
  #include "BasicWEB.h"
#endif

#if (TFTP_USED == 1)
  #include "BasicTFTP.h"
#endif

#if (SMTP_USED == 1)
  #include "BasicSMTP.h"
#endif

/* lwIP includes */
#include "lwip/sys.h"
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/memp.h"
#include "lwip/stats.h"
#include "netif/loopif.h"
#include "lwipopts.h"
#include "lwip/ip.h"
#include "lwip/init.h"

/* global variable containing MAC Config (hw addr, IP, GW, ...) */
struct netif MACB_if;


/* Initialization required by lwIP. */
void prvlwIPInit( void );

/* Initialization of Ethernet interfaces by reading config file */
static void ethernetConfigInterface(void * param);


#if (NO_SYS == 0)
extern portTASK_FUNCTION( vBasicWEBServer, pvParameters );


void vStartEthernetTask( unsigned portBASE_TYPE uxPriority )
{
  /* Setup lwIP. */
    prvlwIPInit();


}
#endif

void portlwIPInit( void )
{
    /* Initialize lwIP and its interface layer. */
    #if LWIP_STATS
        stats_init();
    #endif
    lwip_init();
#if (NO_SYS == 0)
    /* once TCP stack has been initalized, set hw and IP parameters, initialize MACB too */
    tcpip_init( ethernetConfigInterface, NULL );
#else
	ethernetConfigInterface(NULL);
#endif
}

#if (NO_SYS == 0)
extern void vMBServerTask( void *arg );
#endif
static void ethernetConfigInterface(void * param)
{
    struct ip_addr xIpAddr, xNetMask, xGateway;
    extern err_t ethernetif_init( struct netif *netif );
    extern unsigned char my_ip[4];
    unsigned char MacAddress[6];
    /* Default MAC addr. */
    MacAddress[0] = ETHERNET_CONF_ETHADDR0;
    MacAddress[1] = ETHERNET_CONF_ETHADDR1;
    MacAddress[2] = ETHERNET_CONF_ETHADDR2;
    MacAddress[3] = ETHERNET_CONF_ETHADDR3;
    MacAddress[4] = ETHERNET_CONF_ETHADDR4;
    MacAddress[5] = ETHERNET_CONF_ETHADDR5;

    /* pass the MAC address to MACB module */
    MSS_MAC_set_mac_address((uint8_t *)MacAddress);

    /* set MAC hardware address length to be used by lwIP */
    MACB_if.hwaddr_len = 6;

   /* set MAC hardware address to be used by lwIP */
    memcpy( MACB_if.hwaddr, MacAddress, MACB_if.hwaddr_len );
    /* Default ip addr. */
    IP4_ADDR( &xIpAddr,my_ip[0],my_ip[1],my_ip[2],my_ip[3] );

    /* Default Subnet mask. */
    IP4_ADDR( &xNetMask,ETHERNET_CONF_NET_MASK0,ETHERNET_CONF_NET_MASK1,ETHERNET_CONF_NET_MASK2,ETHERNET_CONF_NET_MASK3 );

    /* Default Gw addr. */
    IP4_ADDR( &xGateway,ETHERNET_CONF_GATEWAY_ADDR0,ETHERNET_CONF_GATEWAY_ADDR1,ETHERNET_CONF_GATEWAY_ADDR2,ETHERNET_CONF_GATEWAY_ADDR3 );
    /* add data to netif */
    netif_add( &MACB_if, &xIpAddr, &xNetMask, &xGateway, NULL, ethernetif_init, ip_input );

    /* make it the default interface */
    netif_set_default( &MACB_if );

   /* bring it up */
    netif_set_up( &MACB_if );
#if LWIP_DHCP
    dhcp_start(&MACB_if);
#endif
#if (NO_SYS == 0)
    sys_thread_new( "webtask",vBasicWEBServer, ( void * ) NULL, 1024, /*ethWEBSERVER_PRIORITY*/ configMAX_PRIORITIES - 1  );
#endif
}




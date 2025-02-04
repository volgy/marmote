/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/*
 * This file is a skeleton for developing Ethernet network interface
 * drivers for lwIP. Add code to the low_level functions and do a
 * search-and-replace for the word "ethernetif" to replace it with
 * something that better describes your network interface.
 */
#include <stdio.h>
#include <string.h> //BB

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include <lwip/stats.h>

#include "conf_eth.h"
#include "lwipopts.h"

#include "netif/etharp.h"

/* FreeRTOS includes. */
#if (NO_SYS == 0)
#include "FreeRTOS.h"
#endif

#include "mss_ethernet_mac.h"



#define netifMTU                    ( 4096 )
#define netifGUARD_BLOCK_TIME       ( 100)
#define IFNAME0 's'
#define IFNAME1 'f'


extern char ethAddr[6];

struct ethernetif {
    struct eth_addr *ethaddr;
    /* Add whatever per-interface state that is needed here. */
};

/* Forward declarations. */
void  ethernetif_input(void * );
static err_t ethernetif_output(struct netif *netif, struct pbuf *p,
             struct ip_addr *ipaddr);
static struct netif *xNetIf = NULL;

static void low_level_init(struct netif *netif)
{

    /* set MAC hardware address */
    netif->hwaddr[0] = ETHERNET_CONF_ETHADDR0;
    netif->hwaddr[1] = ETHERNET_CONF_ETHADDR1;
    netif->hwaddr[2] = ETHERNET_CONF_ETHADDR2;
    netif->hwaddr[3] = ETHERNET_CONF_ETHADDR3;
    netif->hwaddr[4] = ETHERNET_CONF_ETHADDR4;
    netif->hwaddr[5] = ETHERNET_CONF_ETHADDR5;
    /* maximum transfer unit */
    netif->mtu = netifMTU;

    /* broadcast capability */
    netif->flags = NETIF_FLAG_BROADCAST;/* | NETIF_FLAG_ETHARP;*/

    /* Do whatever else is needed to initialize interface. */
    xNetIf = netif;
#if (NO_SYS == 0)
    sys_thread_new(( portCHAR * ) "ETH_INT",
                   ethernetif_input,
                   NULL,
                   netifINTERFACE_TASK_STACK_SIZE,
                   netifINTERFACE_TASK_PRIORITY );
#endif
}

/*
 * low_level_output():
 *
 * Should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 */


static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
    unsigned char out_buffer[2048];
    struct pbuf *q;
#if (NO_SYS == 0)
    static xSemaphoreHandle xTxSemaphore = NULL;
#endif
    err_t xReturn = ERR_OK;
    unsigned char *ptr;

    ptr=out_buffer;
     /* Parameter not used. */
    ( void ) netif;
#if (NO_SYS == 0)
    if( xTxSemaphore == NULL )
    {
        vSemaphoreCreateBinary( xTxSemaphore );
    }
#endif
#if ETH_PAD_SIZE
        pbuf_header( p, -ETH_PAD_SIZE );    /* drop the padding word */
#endif

  /* Access to the MACB is guarded using a semaphore. */
#if (NO_SYS == 0)
    if( xSemaphoreTake( xTxSemaphore, netifGUARD_BLOCK_TIME ) )
#endif
    {
        for( q = p; q != NULL; q = q->next )
        {
            /* Send the data from the pbuf to the interface, one pbuf at a
               time. The size of the data in each pbuf is kept in the ->len
               variable.  if q->next == NULL then this is the last pbuf in the
               chain. */
            memcpy( ptr, q->payload, q->len );
            ptr+=q->len;
        }

        if( !MSS_MAC_tx_packet( out_buffer, p->tot_len, MSS_MAC_BLOCKING) )
        {
#if (NO_SYS == 0)
            xSemaphoreGive( xTxSemaphore );
#endif
            printf("Failed Sending Data to Eth len =%d\n\r", p->tot_len);
            return( ~ERR_OK);
        }
#if (NO_SYS == 0)
        xSemaphoreGive( xTxSemaphore );
#endif
    }

 #if ETH_PAD_SIZE
    pbuf_header( p, ETH_PAD_SIZE );     /* reclaim the padding word */
 #endif

 #if LINK_STATS
    lwip_stats.link.xmit++;
 #endif /* LINK_STATS */
    return xReturn;
}

/*
 * low_level_input():
 *
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 */

static struct pbuf *low_level_input(struct netif *netif)
{
    u8_t s_rxBuff[4096];
    struct pbuf *p, *q;
    u16_t len, l;
#if (NO_SYS == 0)
    static xSemaphoreHandle xRxSemaphore = NULL;
#endif
    l = 0;
    p = NULL;

#if (NO_SYS == 0)
    if( xRxSemaphore == NULL )
    {
        vSemaphoreCreateBinary( xRxSemaphore );
    }

    if( xSemaphoreTake( xRxSemaphore, netifGUARD_BLOCK_TIME ) )
#endif
    {
    /* Obtain the size of the packet and put it into the "len"
       variable. */
        len = MSS_MAC_rx_packet( s_rxBuff, 4096, MSS_MAC_NONBLOCKING);
        if(len)
        {
#if ETH_PAD_SIZE
            len += ETH_PAD_SIZE;/* allow room for Ethernet padding */
#endif
            /* We allocate a pbuf chain of pbufs from the pool. */
            p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
            if (p != NULL)
            {
#if ETH_PAD_SIZE
                pbuf_header(p, -ETH_PAD_SIZE);/* drop the padding word */
#endif

                /* We iterate over the pbuf chain until we have read the entire
                 * packet into the pbuf. */
                for(q = p; q != NULL; q = q->next)
                {
                    /* Read enough bytes to fill this pbuf in the chain. The
                     * available data in the pbuf is given by the q->len
                     * variable. */
#if (NO_SYS == 0)
                    vTaskSuspendAll();
#endif
                    memcpy((u8_t*)q->payload, &s_rxBuff[l], q->len);
#if (NO_SYS == 0)
                    xTaskResumeAll();
#endif
                    l = l + q->len;
               }


#if ETH_PAD_SIZE
               pbuf_header(p, ETH_PAD_SIZE);/* reclaim the padding word */
#endif
               LINK_STATS_INC(link.recv);
            }
            else
            {
                LINK_STATS_INC(link.memerr);
                LINK_STATS_INC(link.drop);
            } /* End else */
        } /* End if */
#if (NO_SYS == 0)
        xSemaphoreGive( xRxSemaphore );
#endif
    }
    return p;
}

/*
 * ethernetif_output():
 *
 * This function is called by the TCP/IP stack when an IP packet
 * should be sent. It calls the function called low_level_output() to
 * do the actual transmission of the packet.
 *
 */

static err_t
ethernetif_output(struct netif		*netif,
				struct pbuf			*p,
				struct ip_addr		*ipaddr)
{

    /* resolve hardware address, then send (or queue) packet */
    return etharp_output(netif, p, ipaddr); //BB

}

/*
 * ethernetif_input():
 *
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface.
 *
 */

void ethernetif_input( void * pvParameters )
{
    struct ethernetif   *ethernetif;
    struct eth_hdr      *ethhdr;
    struct pbuf         *p;

    ( void ) pvParameters;

    ethernetif = xNetIf->state;
    do
    {
      /* move received packet into a new pbuf */
        p = low_level_input( xNetIf );
    } while( p == NULL );

    /* points to packet payload, which starts with an Ethernet header */
    ethhdr = p->payload;

    #if LINK_STATS
    lwip_stats.link.recv++;
    #endif /* LINK_STATS */

    ethhdr = p->payload;

    switch( htons( ethhdr->type ) )
    {
      /* IP packet? */
        case ETHTYPE_IP:
            /* update ARP table */
            etharp_ip_input( xNetIf, p );

            /* skip Ethernet header */
            pbuf_header( p, (s16_t)-sizeof(struct eth_hdr) );
            /* pass to network layer */
            if ( xNetIf->input( p, xNetIf ) != ERR_OK)
            {
                printf("Freeing the Buff\n\r");
                pbuf_free(p);
                p = NULL;
            }
            break;
        case ETHTYPE_ARP:
            /* pass p to ARP module */
            etharp_arp_input( xNetIf, ethernetif->ethaddr, p );
            break;
        default:
            pbuf_free( p );
            p = NULL;
            break;
    }
}

static void arp_timer(void *arg)
{
    etharp_tmr();
    sys_timeout(ARP_TMR_INTERVAL, arp_timer, NULL);
}

/*
 * ethernetif_init():
 *
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 */
extern struct netif MACB_if;
err_t ethernetif_init(struct netif *netif)
{
    struct ethernetif *ethernetif;
    int i;
    ethernetif = (struct ethernetif *)mem_malloc(sizeof(struct ethernetif));

    if (ethernetif == NULL)
    {
        LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory\n"));
        return ERR_MEM;
    }

    netif->state = ethernetif;
    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;
    netif->output = etharp_output;/*ethernetif_output;*/
    netif->linkoutput = low_level_output;

    for(i = 0; i < 6; i++)
    {
        netif->hwaddr[i] = MACB_if.hwaddr[i];
    }

    low_level_init(netif);

    etharp_init();

    sys_timeout(ARP_TMR_INTERVAL, arp_timer, NULL);

    return ERR_OK;
}


/**
 * @file
 * Ethernet Interface Skeleton
 *
 */

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

#include "lwip/opt.h"


#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include <lwip/stats.h>
#include "lwip/dhcp.h"
//#include <lwip/snmp.h>
#include "netif/etharp.h"


#include "drivers/mss_ethernet_mac/mss_ethernet_mac.h"

#include <stdio.h>
#include <string.h>                                         /* for memcpy() */

#include "SmartFusionethernetif.h"

/* Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
//struct ethernetif {
//  struct eth_addr *ethaddr;
//  /* Add whatever per-interface state that is needed here. */
//};

/* Forward declarations. */
//static void  ethernetif_input(struct netif *netif);

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static err_t
low_level_init(struct netif *netif)
{
//  struct ethernetif *ethernetif = netif->state;

  /* set MAC hardware address length */
//  netif->hwaddr_len = ETHARP_HWADDR_LEN;

  /* set MAC hardware address */
/*  netif->hwaddr[0] = STATIC_MACADDR0;
  netif->hwaddr[1] = STATIC_MACADDR1;
  netif->hwaddr[2] = STATIC_MACADDR2;
  netif->hwaddr[3] = STATIC_MACADDR3;
  netif->hwaddr[4] = STATIC_MACADDR4;
  netif->hwaddr[5] = STATIC_MACADDR5;
*/
  /* maximum transfer unit */
  netif->mtu = 1500;

  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

  /* Do whatever else is needed to initialize interface. */
//SmartFusion begin
  MSS_MAC_init(  MSS_PHY_ADDRESS_AUTO_DETECT );
//  MSS_MAC_init(  1 );
  // Configure the MAC.

  int32_t mac_cfg;
  mac_cfg = MSS_MAC_get_configuration();

  mac_cfg &= ~( MSS_MAC_CFG_STORE_AND_FORWARD | MSS_MAC_CFG_PASS_BAD_FRAMES );
  mac_cfg |=
  		MSS_MAC_CFG_RECEIVE_ALL |
  		MSS_MAC_CFG_PROMISCUOUS_MODE |
  		MSS_MAC_CFG_FULL_DUPLEX_MODE |
  		MSS_MAC_CFG_TRANSMIT_THRESHOLD_MODE |
  		MSS_MAC_CFG_THRESHOLD_CONTROL_00;

  MSS_MAC_configure( mac_cfg );
  MSS_MAC_set_mac_address( (uint8_t *) &(netif->hwaddr[0]) );
//SmartFusion end

  return ERR_OK;
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
//  struct ethernetif *ethernetif = netif->state;
  struct pbuf *q;

//SmartFusion begin
//  initiate transfer();
  unsigned char out_buffer[2048];
  unsigned char *ptr = out_buffer;
//SmartFusion end

#if ETH_PAD_SIZE
  pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

  for(q = p; q != NULL; q = q->next) {
    /* Send the data from the pbuf to the interface, one pbuf at a
       time. The size of the data in each pbuf is kept in the ->len
       variable. */
//SmartFusion begin
//    send data from(q->payload, q->len);
      memcpy((void*) ptr, q->payload, q->len);
      ptr += q->len;
//SmartFusion end
  }

//SmartFusion begin
//  signal that packet should be sent();
  if( !MSS_MAC_tx_packet( out_buffer, p->tot_len, MSS_MAC_BLOCKING) )
  {
//      printf("Failed Sending Data to Eth len =%d\n\r", p->tot_len);
      return( ~ERR_OK);
  }
//SmartFusion end

#if ETH_PAD_SIZE
  pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

  LINK_STATS_INC(link.xmit);

  return ERR_OK;
}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *
low_level_input(struct netif *netif)
{
//  struct ethernetif *ethernetif = netif->state;
  struct pbuf *p, *q;
  u16_t len;
//SmartFusion begin
  u16_t l;
  u8_t s_rxBuff[4096];
//SmartFusion end

  /* Obtain the size of the packet and put it into the "len"
     variable. */
//SmartFusion begin
  l = 0;
  p = NULL;
  len = MSS_MAC_rx_packet( s_rxBuff, 4096, MSS_MAC_NONBLOCKING );
  if (!len)
	  return p;
//SmartFusion end

#if ETH_PAD_SIZE
  len += ETH_PAD_SIZE; /* allow room for Ethernet padding */
#endif

  /* We allocate a pbuf chain of pbufs from the pool. */
  p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);

  if (p != NULL) {

#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

    /* We iterate over the pbuf chain until we have read the entire
     * packet into the pbuf. */
    for(q = p; q != NULL; q = q->next) {
      /* Read enough bytes to fill this pbuf in the chain. The
       * available data in the pbuf is given by the q->len
       * variable.
       * This does not necessarily have to be a memcpy, you can also preallocate
       * pbufs for a DMA-enabled MAC and after receiving truncate it to the
       * actually received size. In this case, ensure the tot_len member of the
       * pbuf is the sum of the chained pbuf len members.
       */
//SmartFusion begin
//      read data into(q->payload, q->len);
      memcpy((u8_t*)q->payload, &s_rxBuff[l], q->len);

      l = l + q->len;
//SmartFusion end
    }
//SmartFusion begin
//    acknowledge that packet has been read();
//SmartFusion end

#if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

    LINK_STATS_INC(link.recv);
  } else {
//SmartFusion begin
//    drop packet();
//SmartFusion end
    LINK_STATS_INC(link.memerr);
    LINK_STATS_INC(link.drop);
  }

  return p;
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
void
ethernetif_input(struct netif *netif)
{
//  struct ethernetif *ethernetif;
  struct eth_hdr *ethhdr;
  struct pbuf *p;

//  ethernetif = netif->state;

  /* move received packet into a new pbuf */
  p = low_level_input(netif);
  /* no packet could be read, silently ignore this */
  if (p == NULL) return;
  /* points to packet payload, which starts with an Ethernet header */
  ethhdr = p->payload;

/*
  switch (htons(ethhdr->type)) {
  // IP or ARP packet?
  case ETHTYPE_IP:
  case ETHTYPE_ARP:
#if PPPOE_SUPPORT
  // PPPoE packet?
  case ETHTYPE_PPPOEDISC:
  case ETHTYPE_PPPOE:
#endif // PPPOE_SUPPORT
    // full packet send to tcpip_thread to process
    if (netif->input(p, netif)!=ERR_OK)
     { LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
       pbuf_free(p);
       p = NULL;
     }
    break;

  default:
    pbuf_free(p);
    p = NULL;
    break;
  }
*/

/*
  switch( htons( ethhdr->type ) )
  {
    // IP packet?
      case ETHTYPE_IP:
      case ETHTYPE_ARP:
          // update ARP table
//          etharp_ip_input( netif, p );
//          ethernet_input( p, netif );

          // skip Ethernet header
          //pbuf_header( p, (s16_t)-sizeof(struct eth_hdr) );
          // pass to network layer
//          if (netif->input(p, netif)!=ERR_OK)
          if (ethernet_input( p, netif )!=ERR_OK)
           { LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
             pbuf_free(p);
             p = NULL;
           }
          break;
//      case ETHTYPE_ARP:
//          // pass p to ARP module
//          etharp_arp_input( netif, (struct eth_addr *)&(netif->hwaddr[0]), p );
//          break;
      default:
          pbuf_free( p );
          p = NULL;
          break;
  }
*/

  if (ethernet_input( p, netif )!=ERR_OK)
   { LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
     pbuf_free(p);
     p = NULL;
   }

}


/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t
ethernetif_init(struct netif *netif)
{
//SmartFusion begin
    // set MAC address in the network interface...
	netif->hwaddr_len = NETIF_MAX_HWADDR_LEN;

	netif->hwaddr[0] = STATIC_MACADDR0;
	netif->hwaddr[1] = STATIC_MACADDR1;
	netif->hwaddr[2] = STATIC_MACADDR2;
	netif->hwaddr[3] = STATIC_MACADDR3;
	netif->hwaddr[4] = STATIC_MACADDR4;
	netif->hwaddr[5] = STATIC_MACADDR5;
//SmartFusion end

//  struct ethernetif *ethernetif;

  LWIP_ASSERT("netif != NULL", (netif != NULL));

//  ethernetif = mem_malloc(sizeof(struct ethernetif));
//  if (ethernetif == NULL) {
//    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory\n"));
//    return ERR_MEM;
//  }

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

  /*
   * Initialize the snmp variables and counters inside the struct netif.
   * The last argument should be replaced with your link speed, in units
   * of bits per second.
   */
  NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, LINK_SPEED_OF_YOUR_NETIF_IN_BPS);

//  netif->state = ethernetif;
  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) */
  netif->output = etharp_output;
  netif->linkoutput = low_level_output;

//  ethernetif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);

  /* initialize the hardware */
//  low_level_init(netif);

//SmartFusion begin
  struct ip_addr ipaddr;
  struct ip_addr netmask;
  struct ip_addr gw;

#if (LWIP_DHCP == 0)
          /* No mechanism of obtaining IP address specified, use static IP: */
    IP4_ADDR(&ipaddr,  STATIC_IPADDR0,    STATIC_IPADDR1,
                       STATIC_IPADDR2,    STATIC_IPADDR3);
    IP4_ADDR(&netmask, STATIC_NET_MASK0,  STATIC_NET_MASK1,
                       STATIC_NET_MASK2,  STATIC_NET_MASK3);
    IP4_ADDR(&gw,  STATIC_GW_IPADDR0, STATIC_GW_IPADDR1,
                       STATIC_GW_IPADDR2, STATIC_GW_IPADDR3);
#else
     /* either DHCP or AUTOIP are configured, start with zero IP addresses: */
    IP4_ADDR(&ipaddr,  0, 0, 0, 0);
    IP4_ADDR(&netmask, 0, 0, 0, 0);
    IP4_ADDR(&gw,      0, 0, 0, 0);
#endif
          /* add and configure the Ethernet interface with default settings */
    netif_add(netif,
              &ipaddr, &netmask, &gw,            /* configured IP addresses */
              NULL,                /* use this active object as the state */
              &low_level_init,        /* Ethernet interface initialization */
              &ip_input);                   /* standard IP input processing */

    netif_set_default(netif);

    netif_set_up(netif);                       /* bring the interface up */

#if (LWIP_DHCP != 0)
    dhcp_start(netif);         /* start DHCP if configured in lwipopts.h */
#endif
//SmartFusion end

  return ERR_OK;
}

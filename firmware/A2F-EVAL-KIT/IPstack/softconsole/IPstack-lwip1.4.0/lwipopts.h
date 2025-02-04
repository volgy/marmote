#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__


#define STATIC_MACADDR0                 0x00
#define STATIC_MACADDR1                 0x00
#define STATIC_MACADDR2                 0x23
#define STATIC_MACADDR3                 0x10
#define STATIC_MACADDR4                 0x20
#define STATIC_MACADDR5                 0x30

//****************************************************************************
// -------------- Static IPv4 addresses  ----------------
// (relevant only when DHCP is NOT enabled)
//****************************************************************************
                                      // the default IP address of the host...
#define STATIC_IPADDR0                  192
#define STATIC_IPADDR1                  168
#define STATIC_IPADDR2                  1
#define STATIC_IPADDR3                  2
                                                // the default network mask...
#define STATIC_NET_MASK0                255
#define STATIC_NET_MASK1                255
#define STATIC_NET_MASK2                255
#define STATIC_NET_MASK3                0
                                          // the default gateway IP address...
#define STATIC_GW_IPADDR0               129
#define STATIC_GW_IPADDR1               59
#define STATIC_GW_IPADDR2               129
#define STATIC_GW_IPADDR3               1



//See src/include/lwip/opt.h for default define values


/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#define NO_SYS                          1

/**
 * MEMP_NUM_SYS_TIMEOUT: the number of simulateously active timeouts.
 * (requires NO_SYS==0)
 */
#define MEMP_NUM_SYS_TIMEOUT            5

/**
 * LWIP_DHCP==1: Enable DHCP module.
 */
#define LWIP_DHCP                       0

/**
 * LWIP_UDP==1: Turn on UDP.
 */
//#define LWIP_UDP                        0

/**
 * LWIP_NETCONN==1: Enable Netconn API (require to use api_lib.c)
 */
#define LWIP_NETCONN                    0

/**
 * LWIP_SOCKET==1: Enable Socket API (require to use sockets.c)
 */
#define LWIP_SOCKET                     0


#endif /* __LWIPOPTS_H__ */

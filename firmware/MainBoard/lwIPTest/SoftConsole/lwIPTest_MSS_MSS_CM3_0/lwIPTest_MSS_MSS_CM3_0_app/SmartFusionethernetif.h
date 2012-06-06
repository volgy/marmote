/*
 * SmartFusionethernetif.h
 *
 *  Created on: May 8, 2011
 *      Author: babjak
 */

#ifndef SMARTFUSIONETHERNETIF_H_
#define SMARTFUSIONETHERNETIF_H_

#ifdef __cplusplus
extern "C" {
#endif

err_t ethernetif_init(struct netif *netif);
void ethernetif_input(struct netif *netif);

#ifdef __cplusplus
}
#endif

#endif /* SMARTFUSIONETHERNETIF_H_ */

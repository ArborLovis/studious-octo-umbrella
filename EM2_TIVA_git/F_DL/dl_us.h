/*
 * dl_us.h
 *
 *  Created on: 13.06.2018
 *      Author: Patrick
 */

#ifndef F_DL_DL_US_H_
#define F_DL_DL_US_H_

#define HALF_VEL_SONIC      17100     // cm/s (already round down)
#define VEL_SONIC           343     // m/s
#define TWICE_VEL_SONIC     686     // m/s

unsigned int dlGetDistance_US1();
unsigned int dlGetDistance_US2();

#endif /* F_DL_DL_US_H_ */

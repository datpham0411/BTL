/*
 * led7_segment.h
 *
 *  Created on: Oct 28, 2024
 *      Author: datph
 */

#ifndef INC_LED7_SEGMENT_H_
#define INC_LED7_SEGMENT_H_

#include "main.h"
#include "stdio.h"
#include "traffic_light.h"
#include "global.h"
#include "i2c-lcd.h"
#include "software_timer.h"

void display_time();
void display_num(char group, int num);

#endif /* INC_LED7_SEGMENT_H_ */

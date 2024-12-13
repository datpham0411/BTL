/*
 * traffic_light.h
 *
 *  Created on: Oct 28, 2024
 *      Author: datph
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "main.h"
#include "global.h"

#define ON GPIO_PIN_SET
#define OFF GPIO_PIN_RESET

void select_num (char group, int num);
void setColor(GPIO_TypeDef *GPIO1, GPIO_TypeDef *GPIO2, uint16_t Led_1, uint16_t Led_2, GPIO_PinState Led_1_State, GPIO_PinState Led_2_State);
void setColorToggle(GPIO_TypeDef *GPIO1, GPIO_TypeDef *GPIO2, uint16_t Led_1, uint16_t Led_2, char color);

#endif /* INC_TRAFFIC_LIGHT_H_ */

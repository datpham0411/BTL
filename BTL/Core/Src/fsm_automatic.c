/*
 * fsm_normal.c
 *
 *  Created on: Oct 26, 2024
 *      Author: datph
 */
#include <fsm_automatic.h>

int color = INIT;

void fsm_automatic_run() {
	switch (color) {
		case INIT:
			setColor(GPIOC, GPIOB, LED_TRAFFIC_VERTICAL_1A_Pin, LED_TRAFFIC_VERTICAL_1B_Pin, OFF, OFF);
			setColor(GPIOA, GPIOA, LED_TRAFFIC_VERTICAL_2A_Pin, LED_TRAFFIC_VERTICAL_2B_Pin, OFF, OFF);
			setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_1A_Pin, LED_TRAFFIC_HORIZONTAL_1B_Pin, OFF, OFF);
			setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_2A_Pin, LED_TRAFFIC_HORIZONTAL_2B_Pin, OFF, OFF);

			color = RED;
			setTimer1(red_duration);
			break;
		case RED:
			display_time();
			setColor(GPIOC, GPIOB, LED_TRAFFIC_VERTICAL_1A_Pin, LED_TRAFFIC_VERTICAL_1B_Pin, ON, ON);
			setColor(GPIOA, GPIOA, LED_TRAFFIC_VERTICAL_2A_Pin, LED_TRAFFIC_VERTICAL_2B_Pin, ON, ON);

			if (isTimer1Paused(red_duration - green_duration)) {
				display_num('B', (timer1_counter + 1000)/1000);
				setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_1A_Pin, LED_TRAFFIC_HORIZONTAL_1B_Pin, OFF, ON);
				setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_2A_Pin, LED_TRAFFIC_HORIZONTAL_2B_Pin, OFF, ON);
			}
			else {
				display_num('B', ((timer1_counter + 1000)/1000 - amber_duration/1000));
				setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_1A_Pin, LED_TRAFFIC_HORIZONTAL_1B_Pin, ON, OFF);
				setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_2A_Pin, LED_TRAFFIC_HORIZONTAL_2B_Pin, ON, OFF);
			}

			if (timer1_flag == 1) {
				color = GREEN;
				setTimer1(green_duration);
			}
			break;
		case AMBER:
			display_time();
			setColor(GPIOC, GPIOB, LED_TRAFFIC_VERTICAL_1A_Pin, LED_TRAFFIC_VERTICAL_1B_Pin, OFF, ON);
			setColor(GPIOA, GPIOA, LED_TRAFFIC_VERTICAL_2A_Pin, LED_TRAFFIC_VERTICAL_2B_Pin, OFF, ON);
			display_num('B', (timer1_counter + 1000)/1000);

			setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_1A_Pin, LED_TRAFFIC_HORIZONTAL_1B_Pin, ON, ON);
			setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_2A_Pin, LED_TRAFFIC_HORIZONTAL_2B_Pin, ON, ON);

			if (timer1_flag == 1) {
				color = RED;
				setTimer1(red_duration);
			}
			break;
		case GREEN:
			display_time();
			setColor(GPIOC, GPIOB, LED_TRAFFIC_VERTICAL_1A_Pin, LED_TRAFFIC_VERTICAL_1B_Pin, ON, OFF);
			setColor(GPIOA, GPIOA, LED_TRAFFIC_VERTICAL_2A_Pin, LED_TRAFFIC_VERTICAL_2B_Pin, ON, OFF);

			display_num('B', ((timer1_counter + 1000)/1000 + amber_duration/1000));

			setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_1A_Pin, LED_TRAFFIC_HORIZONTAL_1B_Pin, ON, ON);
			setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_2A_Pin, LED_TRAFFIC_HORIZONTAL_2B_Pin, ON, ON);

			if (timer1_flag == 1) {
				color = AMBER;
				setTimer1(amber_duration);
			}
			break;
		default:
			break;
	}
}


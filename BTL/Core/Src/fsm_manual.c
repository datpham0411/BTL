/*
 * fsm_traffic.c
 *
 *  Created on: Oct 26, 2024
 *      Author: datph
 */
#include "fsm_manual.h"

int status = NORMAL;
int red_duration = 5000;
int red_duration_temp = 0;
int amber_duration = 2000;
int amber_duration_temp = 0;
int green_duration = 3000;
int green_duration_temp = 0;
char str[16];

void fsm_manual_run() {
	switch(status) {
		case NORMAL:
			fsm_automatic_run();

			if (isButton1Pressed()) {
				status = INITIAL;
			}
			break;
		case INITIAL:
			setColor(GPIOC, GPIOB, LED_TRAFFIC_VERTICAL_1A_Pin, LED_TRAFFIC_VERTICAL_1B_Pin, OFF, OFF);
			setColor(GPIOA, GPIOA, LED_TRAFFIC_VERTICAL_2A_Pin, LED_TRAFFIC_VERTICAL_2B_Pin, OFF, OFF);
			setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_1A_Pin, LED_TRAFFIC_HORIZONTAL_1B_Pin, OFF, OFF);
			setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_2A_Pin, LED_TRAFFIC_HORIZONTAL_2B_Pin, OFF, OFF);

			red_duration_temp = red_duration;
			green_duration_temp = green_duration;
			amber_duration_temp = amber_duration;

			lcd_clear_display();
			status = MODIFY_RED;
			setTimer3(250);
			setTimer2(147);
			setTimer1(153);
			break;
		case MODIFY_RED:
			if (timer1_flag == 1) {
				setTimer1(153);
				lcd_goto_XY(1, 0);
				lcd_send_string("Mod: MOD RED");
				lcd_goto_XY(2, 0);
				lcd_send_string("Red Dur: ");
				lcd_goto_XY(2, 12);
				if (red_duration/1000 < 10) sprintf(str, "0%u", red_duration/1000);
				else sprintf(str, "%u", red_duration/1000);
				lcd_send_string(str);
			}

			if (timer3_flag == 1) {
				setTimer3(250);

				setColorToggle(GPIOC, GPIOB, LED_TRAFFIC_VERTICAL_1A_Pin, LED_TRAFFIC_VERTICAL_1B_Pin, 'R');
				setColorToggle(GPIOA, GPIOA, LED_TRAFFIC_VERTICAL_2A_Pin, LED_TRAFFIC_VERTICAL_2B_Pin, 'R');
				setColorToggle(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_1A_Pin, LED_TRAFFIC_HORIZONTAL_1B_Pin, 'R');
				setColorToggle(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_2A_Pin, LED_TRAFFIC_HORIZONTAL_2B_Pin, 'R');
			}

			if(isButton3Pressed()) {
				red_duration = red_duration - 1000;
				if (red_duration < 0) red_duration = 0;
			}

			if(isButton2Pressed()) {
				red_duration = red_duration + 1000;
				if (red_duration > 99000) red_duration = 1000;
			}

			if (isButton1Pressed()) {
				lcd_clear_display();
				status = MODIFY_AMBER;
				setTimer3(250);
				setTimer2(147);
				setTimer1(153);
			}
			break;
		case MODIFY_AMBER:
			lcd_goto_XY(1, 0);
			lcd_send_string("Mod: MOD AMBER");
			lcd_goto_XY(2, 0);
			lcd_send_string("Amber Dur: ");
			lcd_goto_XY(2, 12);
			if (amber_duration/1000 < 10) sprintf(str, "0%u", amber_duration/1000);
			else sprintf(str, "%u", amber_duration/1000);
			lcd_send_string(str);

			if (timer3_flag == 1) {
				setTimer3(250);

				setColorToggle(GPIOC, GPIOB, LED_TRAFFIC_VERTICAL_1A_Pin, LED_TRAFFIC_VERTICAL_1B_Pin, 'Y');
				setColorToggle(GPIOA, GPIOA, LED_TRAFFIC_VERTICAL_2A_Pin, LED_TRAFFIC_VERTICAL_2B_Pin, 'Y');
				setColorToggle(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_1A_Pin, LED_TRAFFIC_HORIZONTAL_1B_Pin, 'Y');
				setColorToggle(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_2A_Pin, LED_TRAFFIC_HORIZONTAL_2B_Pin, 'Y');
			}

			if(isButton3Pressed()) {
				amber_duration = amber_duration - 1000;
				if (amber_duration < 0) amber_duration = 0;
			}

			if(isButton2Pressed()) {
				amber_duration = amber_duration + 1000;
				if (amber_duration > 99000) amber_duration = 1000;
			}

			if (isButton1Pressed()) {
				lcd_clear_display();
				status = MODIFY_GREEN;
				setTimer3(250);
				setTimer2(147);
				setTimer1(153);
			}
			break;
		case MODIFY_GREEN:
			lcd_goto_XY(1, 0);
			lcd_send_string("Mod: MOD GREEN");
			lcd_goto_XY(2, 0);
			lcd_send_string("Green Dur: ");
			lcd_goto_XY(2, 12);
			if (green_duration/1000 < 10) sprintf(str, "0%u", green_duration/1000);
			else sprintf(str, "%u", green_duration/1000);
			lcd_send_string(str);

			if (timer3_flag == 1) {
				setTimer3(250);

				setColorToggle(GPIOC, GPIOB, LED_TRAFFIC_VERTICAL_1A_Pin, LED_TRAFFIC_VERTICAL_1B_Pin, 'G');
				setColorToggle(GPIOA, GPIOA, LED_TRAFFIC_VERTICAL_2A_Pin, LED_TRAFFIC_VERTICAL_2B_Pin, 'G');
				setColorToggle(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_1A_Pin, LED_TRAFFIC_HORIZONTAL_1B_Pin, 'G');
				setColorToggle(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_2A_Pin, LED_TRAFFIC_HORIZONTAL_2B_Pin, 'G');
			}

			if(isButton3Pressed()) {
//				if(isErrorOccured()) {
//					setTimer1(153);
//					setTimer2(147);
//					lcd_clear_display();
//					status = FAULT_CONDITION;
//				}
				green_duration = green_duration - 1000;
				if (green_duration < 0) green_duration = 0;
			}

			if(isButton2Pressed()) {
				green_duration = green_duration + 1000;
				if (green_duration > 99000) green_duration = 1000;
			}

			if (isButton1Pressed()) {
				lcd_clear_display();
				if(isErrorOccured()) {
					setTimer1(153);
					setTimer2(147);
					status = FAULT_CONDITION;
				}
				else {
					status = NORMAL;
				}
			}
			break;
		case FAULT_CONDITION:
			setColor(GPIOA, GPIOA, LED_TRAFFIC_VERTICAL_2A_Pin, LED_TRAFFIC_VERTICAL_2B_Pin, OFF, OFF);
			setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_1A_Pin, LED_TRAFFIC_HORIZONTAL_1B_Pin, OFF, OFF);
			setColor(GPIOB, GPIOB, LED_TRAFFIC_HORIZONTAL_2A_Pin, LED_TRAFFIC_HORIZONTAL_2B_Pin, OFF, OFF);
			lcd_goto_XY(1, 0);
			lcd_send_string("Mod: FAULT CONDI");
			lcd_goto_XY(2, 0);
			lcd_send_string("YES: 1");
			lcd_goto_XY(2, 10);
			lcd_send_string("NO: 3");

			red_duration = red_duration_temp;
			amber_duration = amber_duration_temp;
			green_duration = green_duration_temp;

			if (isButton1Pressed()) {
				lcd_clear_display();
				status = MODIFY_RED;
			}

			if (isButton3Pressed()) {
				lcd_clear_display();
				status = NORMAL;
			}
			break;
		default:
			break;
	}
}


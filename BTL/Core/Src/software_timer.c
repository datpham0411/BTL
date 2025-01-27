/*
 * software_timer.c
 *
 *  Created on: Oct 13, 2024
 *      Author: datph
 */
#include "software_timer.h"

int timer1_counter = 0;
int timer1_flag = 0;

int timer2_counter = 0;
int timer2_flag = 0;

int timer3_counter = 0;
int timer3_flag = 0;

int idx = 0;
int toggle_flag = 0;
int TICK = 1;

void setTimer1 (int duration) {
	timer1_counter = duration/TICK;
	timer1_flag = 0;
}

void setTimer2 (int duration) {
	timer2_counter = duration/TICK;
	timer2_flag = 0;
}

void setTimer3 (int duration) {
	timer3_counter = duration/TICK;
	timer3_flag = 0;
}

int isTimer1Paused(int pause) {
//	pause = pause / 10;
//	if (timer1_counter <= pause) return 1;
//	return 0;
	if (timer1_counter > (pause + 5)) return 0;
	else if (timer1_counter <= (pause + 5) && timer1_counter >= pause) lcd_clear_display();
	else return 1;
}

void timerRun() {
	if (timer1_counter > 0) --timer1_counter;
	else timer1_flag = 1;

	if (timer2_counter > 0) --timer2_counter;
	else {
		timer2_flag = 1;
		switch (idx) {
			case 0:
				++idx;
				break;
			case 1:
				idx = 0;
				break;
			default:
				break;
		}
	}

	if (timer3_counter > 0) --timer3_counter;
	else {
		timer3_flag = 1;
		switch (toggle_flag) {
			case 0:
				++toggle_flag;
				break;
			case 1:
				toggle_flag = 0;
				break;
			default:
				break;
		}
	}
}


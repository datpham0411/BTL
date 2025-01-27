/*
 * led7_segment.c
 *
 *  Created on: Oct 28, 2024
 *      Author: datph
 */
#include "led7_segment.h"
char str[16];

void display_num (char group, int num) {
	if (group == 'A') {
		lcd_goto_XY(1, 0);
		lcd_send_string("Vertical: ");
		lcd_goto_XY(1, 12);
		if (num < 10) sprintf(str, "0%u", num);
		else sprintf(str, "%u", num);
		lcd_send_string(str);
	}
	else if (group == 'B') {
		lcd_goto_XY(2, 0);
		lcd_send_string("Horizontal: ");
		lcd_goto_XY(2, 12);
		if (num < 10) sprintf(str, "0%u", num);
		else sprintf(str, "%u", num);
		lcd_send_string(str);
	}
}

void display_time() {
	if (timer2_flag == 1) {
		setTimer2(150);
		display_num('A', (timer1_counter + 1000)/1000);
	}
}

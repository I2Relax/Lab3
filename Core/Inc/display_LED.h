/*
 * display_LED.h
 *
 *  Created on: Nov 9, 2022
 *      Author: Acer
 */

#ifndef INC_DISPLAY_LED_H_
#define INC_DISPLAY_LED_H_

extern int led_index;
extern int led_buffer[4];

void display7SEG(int num);
void clear7SEG();
void updateledbuffer(int num1, int num2);
void display_led(int num1, int num2, int duration);
void clear_led();

#endif /* INC_DISPLAY_LED_H_ */

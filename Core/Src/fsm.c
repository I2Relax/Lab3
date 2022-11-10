/*
 * fsm.c
 *
 *  Created on: Nov 9, 2022
 *      Author: Acer
 */

#include "main.h"
#include "global.h"
#include "fsm.h"
#include "software_timer.h"
#include "button.h"
#include "display_LED.h"

void normal_fsm_run() {
	switch (status) {
	case INIT:
		counter=RED_TIME;
		updateledbuffer(counter, 0);
		display_led(counter, 0, 250);
		setTimer2(RED_TIME*1000);
		setTimer3(1000);
		status=RED;
		break;
	case RED:
		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, SET);
		HAL_GPIO_WritePin(AMBER1_GPIO_Port, AMBER1_Pin, RESET);
		HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, RESET);
		if (counter>AMBER_TIME) {
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, RESET);
			HAL_GPIO_WritePin(AMBER2_GPIO_Port, AMBER2_Pin, RESET);
			HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, SET);
			updateledbuffer(counter, counter-AMBER_TIME);
			display_led(counter, counter-AMBER_TIME, 250);
		}
		else {
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, RESET);
			HAL_GPIO_WritePin(AMBER2_GPIO_Port, AMBER2_Pin, SET);
			HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, RESET);
			updateledbuffer(counter, counter);
			display_led(counter, counter, 250);
		}
		if (timer3_flag==1) {
			counter--;
			setTimer3(1000);
		}
		if (timer2_flag==1) {
			counter=GREEN_TIME;
			status=GREEN;
			setTimer2(GREEN_TIME*1000);
			setTimer3(1000);
		}
		if (button_SEL_flag==1) {
			button_SEL_flag=0;
			status=MOD_RED;
			setTimer2(0);
			setTimer3(0);
			setTimer4(500);
			clear_led();
		}
		break;
	case GREEN:
		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, RESET);
		HAL_GPIO_WritePin(AMBER1_GPIO_Port, AMBER1_Pin, RESET);
		HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, SET);
		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, SET);
		HAL_GPIO_WritePin(AMBER2_GPIO_Port, AMBER2_Pin, RESET);
		HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, RESET);
		updateledbuffer(counter, counter+AMBER_TIME);
		display_led(counter, counter+AMBER_TIME, 250);
		if (timer3_flag==1) {
			counter--;
			setTimer3(1000);
		}
		if (timer2_flag==1) {
			counter=AMBER_TIME;
			status=AMBER;
			setTimer2(AMBER_TIME*1000);
			setTimer3(1000);
		}
		if (button_SEL_flag==1) {
			button_SEL_flag=0;
			status=MOD_RED;
			setTimer2(0);
			setTimer3(0);
			setTimer4(500);
			clear_led();
		}
		break;
	case AMBER:
		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, RESET);
		HAL_GPIO_WritePin(AMBER1_GPIO_Port, AMBER1_Pin, SET);
		HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, RESET);
		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, SET);
		HAL_GPIO_WritePin(AMBER2_GPIO_Port, AMBER2_Pin, RESET);
		HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, RESET);
		updateledbuffer(counter, counter);
		display_led(counter, counter, 250);
		if (timer3_flag==1) {
			counter--;
			setTimer3(1000);
		}
		if (timer2_flag==1) {
			counter=RED_TIME;
			status=RED;
			setTimer2(RED_TIME*1000);
			setTimer3(1000);
		}
		if (button_SEL_flag==1) {
			button_SEL_flag=0;
			status=MOD_RED;
			setTimer2(0);
			setTimer3(0);
			setTimer4(500);
			clear_led();
		}
		break;
	default:
		break;
	}
}
void modify_fsm_run() {
	switch (status) {
	case MOD_RED:
		//Display led
		updateledbuffer(RED_TIME, 2);
		display_led(RED_TIME, 2, 250);
		if (timer4_flag==1) {
			HAL_GPIO_TogglePin(RED1_GPIO_Port, RED1_Pin);
			HAL_GPIO_TogglePin(RED2_GPIO_Port, RED2_Pin);
			setTimer4(500);
		}
		//Modify
		if (button_MOD_flag==1) {
			button_MOD_flag=0;
			RED_TIME++;
			if (RED_TIME>99) RED_TIME=1;
			display_led(RED_TIME, 2, 250);
		}
		//Set
		if (button_SET_flag==1) {
			button_SET_flag=0;
			status=INIT;
		}
		//Select
		if (button_SEL_flag==1) {
			button_SEL_flag=0;
			status=MOD_AMBER;
			setTimer5(500);
			clear_led();
		}
		break;
	case MOD_AMBER:
		//Display led
		updateledbuffer(AMBER_TIME, 3);
		display_led(AMBER_TIME, 3, 250);
		if (timer5_flag==1) {
			HAL_GPIO_TogglePin(AMBER1_GPIO_Port, AMBER1_Pin);
			HAL_GPIO_TogglePin(AMBER2_GPIO_Port, AMBER2_Pin);
			setTimer5(500);
		}
		//Modify
		if (button_MOD_flag==1) {
			button_MOD_flag=0;
			AMBER_TIME++;
			if (AMBER_TIME>99) AMBER_TIME=1;
			display_led(AMBER_TIME, 3, 250);
		}
		//Set
		if (button_SET_flag==1) {
			button_SET_flag=0;
			status=INIT;
		}
		//Select
		if (button_SEL_flag==1) {
			button_SEL_flag=0;
			status=MOD_GREEN;
			setTimer6(500);
			clear_led();
		}
		break;
	case MOD_GREEN:
		//Display led
		updateledbuffer(GREEN_TIME, 4);
		display_led(GREEN_TIME, 4, 250);
		if (timer6_flag==1) {
			HAL_GPIO_TogglePin(GREEN1_GPIO_Port, GREEN1_Pin);
			HAL_GPIO_TogglePin(GREEN2_GPIO_Port, GREEN2_Pin);
			setTimer6(500);
		}
		//Modify
		if (button_MOD_flag==1) {
			button_MOD_flag=0;
			GREEN_TIME++;
			if (GREEN_TIME>99) GREEN_TIME=1;
			display_led(GREEN_TIME, 4, 250);
		}
		//Set
		if (button_SET_flag==1) {
			button_SET_flag=0;
			status=INIT;
		}
		//Select
		if (button_SEL_flag==1) {
			button_SEL_flag=0;
			status=INIT;
			clear_led();
		}
		break;
	default:
		break;
	}
}

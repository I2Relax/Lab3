/*
 * button.h
 *
 *  Created on: Nov 9, 2022
 *      Author: Acer
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#define NORMAL_STATE  GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

void getKeyInput();
extern int button_SEL_flag;
extern int button_MOD_flag;
extern int button_SET_flag;

#endif /* INC_BUTTON_H_ */

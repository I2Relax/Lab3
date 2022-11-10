/*
 * button.c
 *
 *  Created on: Nov 9, 2022
 *      Author: Acer
 */

#include "button.h"
#include "main.h"

int KeyReg0_SEL = NORMAL_STATE;
int KeyReg1_SEL = NORMAL_STATE;
int KeyReg2_SEL = NORMAL_STATE;
int KeyReg3_SEL = NORMAL_STATE;
int button_SEL_flag=0;

int KeyReg0_MOD = NORMAL_STATE;
int KeyReg1_MOD = NORMAL_STATE;
int KeyReg2_MOD = NORMAL_STATE;
int KeyReg3_MOD = NORMAL_STATE;
int button_MOD_flag=0;

int KeyReg0_SET = NORMAL_STATE;
int KeyReg1_SET = NORMAL_STATE;
int KeyReg2_SET = NORMAL_STATE;
int KeyReg3_SET = NORMAL_STATE;
int button_SET_flag=0;

int TimeOutForKeyPress_SEL = 200;
int TimeOutForKeyPress_MOD = 200;
int TimeOutForKeyPress_SET = 200;

void subKeyProcess() {
	if (KeyReg3_SEL == PRESSED_STATE) {
		button_SEL_flag=1;
	}
	if (KeyReg3_MOD == PRESSED_STATE) {
		button_MOD_flag=1;
	}
	if (KeyReg3_SET == PRESSED_STATE) {
		button_SET_flag=1;
	}
}
void getKeyInput(){
	//Chong rung va nhan de cho button SELECT
	KeyReg0_SEL = KeyReg1_SEL;
	KeyReg1_SEL = KeyReg2_SEL;
	KeyReg2_SEL = HAL_GPIO_ReadPin(SELECT_GPIO_Port, SELECT_Pin);
	if ((KeyReg0_SEL == KeyReg1_SEL) && (KeyReg1_SEL == KeyReg2_SEL)) {
		if (KeyReg3_SEL != KeyReg2_SEL) {
		  KeyReg3_SEL = KeyReg2_SEL;
		  if (KeyReg3_SEL == PRESSED_STATE){
			TimeOutForKeyPress_SEL=200;
			subKeyProcess();
		  }
		}
		else {
		   TimeOutForKeyPress_SEL--;
			if (TimeOutForKeyPress_SEL == 0){
			  KeyReg3_SEL = NORMAL_STATE;
			}
		}
	}
	//Chong rung va nhan de cho button MOD
    KeyReg0_MOD = KeyReg1_MOD;
    KeyReg1_MOD = KeyReg2_MOD;
    KeyReg2_MOD = HAL_GPIO_ReadPin(MOD_GPIO_Port, MOD_Pin);
    if ((KeyReg0_MOD == KeyReg1_MOD) && (KeyReg1_MOD == KeyReg2_MOD)) {
      if (KeyReg3_MOD != KeyReg2_MOD) {
        KeyReg3_MOD = KeyReg2_MOD;
        if (KeyReg3_MOD == PRESSED_STATE){
          TimeOutForKeyPress_MOD=200;
          subKeyProcess();
        }
      }
      else {
         TimeOutForKeyPress_MOD--;
          if (TimeOutForKeyPress_MOD == 0){
        	  KeyReg3_MOD = NORMAL_STATE;
          }
      }
    }
	//Chong rung va nhan de cho button SET
    KeyReg0_SET = KeyReg1_SET;
	KeyReg1_SET = KeyReg2_SET;
	KeyReg2_SET = HAL_GPIO_ReadPin(SET_GPIO_Port, SET_Pin);
	if ((KeyReg0_SET == KeyReg1_SET) && (KeyReg1_SET == KeyReg2_SET)) {
	  if (KeyReg3_SET != KeyReg2_SET) {
		KeyReg3_SET = KeyReg2_SET;
		if (KeyReg3_SET == PRESSED_STATE){
		  TimeOutForKeyPress_SET = 200;
		  subKeyProcess();
		}
	  }
	  else {
		 TimeOutForKeyPress_SET--;
		  if (TimeOutForKeyPress_SET == 0){
			  KeyReg3_SET = NORMAL_STATE;
		  }
	  }
	}
}

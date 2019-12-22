/*----------------------------------------------------------------------------
 *minigame.c
 *Tic tac Toe
 *Lucas Gigliozzi
 *----------------------------------------------------------------------------*/  
#include "stdio.h"
#include "stdlib.h"
#include "LPC17xx.h"
#include "KBD.h"
#include "GLCD.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include "LED.h"

#define DELAY_2N    18

extern void main_menu();

//delay called inbetween button clicks so one click is not registered as multiple
static void delay1 (int cnt) {
  cnt <<= DELAY_2N;
  while (cnt--);
}

//Start Screen and game for stop the light
int mini_game(){
	char text [10];
	int score = 0, current_light = 0;
	int lives = 3;
	int button;
	int btn_press = 0;	
	
	GLCD_Clear(Black);
	while(1){
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(Green);
	GLCD_DisplayString(0, 0, 1, "     Welcome to       ");
	GLCD_DisplayString(1, 0, 1, "   Stop the Light      ");
  GLCD_SetTextColor(White);
	GLCD_DisplayString(3, 0, 1, "When the bottom most");
	GLCD_DisplayString(4, 0, 1, "LED is on, press");
	GLCD_DisplayString(5, 0, 1, "     SELECT!   ");
	GLCD_DisplayString(6, 0, 1, "      ");	
	GLCD_SetTextColor(Green);	
	GLCD_DisplayString(8, 0, 1, "   Score:");	
	GLCD_DisplayString(9, 0, 1, "   Lives:");	
	GLCD_SetTextColor(Red);	
	sprintf(text, "%d", score);       /* format text for print out     */
	GLCD_DisplayString(8, 10, 1, (unsigned char *)text);	
	sprintf(text, "%d", lives);       /* format text for print out     */
	GLCD_DisplayString(9, 10, 1, (unsigned char *)text);	
	
	//loop for lights to alternate on and off
	LPC_GPIO1->FIOPIN |=  (1UL<<28);
	current_light = 0;
	  button = get_button();
		if(button == KBD_SELECT) {
			  if(current_light == 8){
					score++;
				} else{
					lives--;
				}
				delay1(10);
				if (lives <= 0){
					break;
				}
		}
	delay1(7);
	LPC_GPIO1->FIOPIN &= ~(1UL<<28);
	LPC_GPIO1->FIOPIN |=  (1UL<<29);	
	current_light = 1;
		  button = get_button();
		if(button == KBD_SELECT) {
			  if(current_light == 8){
					score++;
				} else{
					lives--;
				}
				delay1(10);
				if (lives <= 0){
					break;
				}
		}
	delay1(7);
	LPC_GPIO1->FIOPIN &= ~(1UL<<29);
	LPC_GPIO1->FIOPIN |=  (1UL<<31);
  current_light = 2;
  button = get_button();
		if(button == KBD_SELECT) {
			  if(current_light == 8){
					score++;
				} else{
					lives--;
				}
				delay1(10);
				if (lives <= 0){
					break;
				}
		}		
	delay1(7);
	LPC_GPIO1->FIOPIN &= ~(1UL<<31);
	LPC_GPIO2->FIOPIN |=  (1UL<<2);
	current_light = 3;
		  button = get_button();
		if(button == KBD_SELECT) {
			  if(current_light == 8){
					score++;
				} else{
					lives--;
				}
				delay1(10);
				if (lives <= 0){
					break;
				}
		}
	delay1(7);
	LPC_GPIO2->FIOPIN &= ~(1UL<<2);
	LPC_GPIO2->FIOPIN |=  (1UL<<3);
	current_light = 4;
		  button = get_button();
		if(button == KBD_SELECT) {
			  if(current_light == 8){
					score++;
				} else{
					lives--;
				}
				delay1(10);
				if (lives <= 0){
					break;
				}
		}
	delay1(7);
	LPC_GPIO2->FIOPIN &= ~(1UL<<3);
	LPC_GPIO2->FIOPIN |=  (1UL<<4);
	current_light = 5;
		  button = get_button();
		if(button == KBD_SELECT) {
			  if(current_light == 8){
					score++;
				} else{
					lives--;
				}
				delay1(10);
				if (lives <= 0){
					break;
				}
		}
	delay1(7);
	LPC_GPIO2->FIOPIN &= ~(1UL<<4);
	LPC_GPIO2->FIOPIN |=  (1UL<<5);
	current_light = 6;
		  button = get_button();
		if(button == KBD_SELECT) {
			  if(current_light == 7){
					score++;
				} else{
					lives--;
				}
				delay1(10);
				if (lives <= 0){
					break;
				}
		}
	delay1(7);
	LPC_GPIO2->FIOPIN &= ~(1UL<<5);
	LPC_GPIO2->FIOPIN |=  (1UL<<6);
	current_light = 7;
		  button = get_button();
		if(button == KBD_SELECT) {
			  if(current_light == 7){
					score++;
				} else{
					lives--;
				}
				delay1(10);
				if (lives <= 0){
					break;
				}
		}
	delay1(7);
	LPC_GPIO2->FIOPIN &= ~(1UL<<6);
	current_light = 8;
		  button = get_button();
		if(button == KBD_SELECT) {
			  if(current_light == 7){
					score++;
				} else{
					lives--;
				}
				delay1(10);
				if (lives <= 0){
					break;
				}
		}
		delay1(7);
	
  button = get_button();
		if(button == KBD_SELECT) {
			  if(current_light == 7){
					score++;
				} else{
					lives--;
				}
				delay1(10);
				if (lives <= 0){
					break;
				}
		}
	}
	GLCD_Clear(Black);
	while(1){
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(Red);
	GLCD_DisplayString(2, 0, 1, "     Game Over       ");
	GLCD_SetTextColor(Green);
	GLCD_DisplayString(4, 0, 1, "   Final Score: ");
	sprintf(text, "%d", score);       /* format text for print out     */
	GLCD_DisplayString(4, 15, 1,(unsigned char *)text);	
	GLCD_SetTextColor(White);		
	GLCD_DisplayString(8, 0, 1, "Down for main menu ");
	GLCD_DisplayString(9, 0, 1, "Select to play again ");
		
	 button = get_button();
	if(button == KBD_SELECT) {
	mini_game();
	} else if(button ==KBD_DOWN){
	main_menu();
	}
	}
	return 0;
}
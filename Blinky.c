/*--------------------------------------------------------------------------
* Media Center Project
* Lucas Gigliozzi
*---------------------------------------------------------------------------*/

#include <LPC17xx.H>
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"


#define __FI 1

//Menu icons
//extern unsigned char MEDIA2_pixel_data[];


//Initailize external functions
extern int mp3_player(void);
extern int start_game(void);
extern int start_ttt(void);
extern int gallery(void);
extern int mini_game(void);

void main_menu();

//store input
int button;

// main menu
void main_menu() {
	int btn_press = 0;
	
	GLCD_Clear(Black);
	while(1) {
		GLCD_SetBackColor(Black);
		GLCD_SetTextColor(Blue);
		GLCD_DisplayString(0,0,__FI,"    Menu Select     ");
		GLCD_SetTextColor(White);
		GLCD_DisplayString(8,0,__FI,"  Joystick Up/Down  ");
		GLCD_DisplayString(9,0,__FI,"  Choose w/ Select  ");
		
		button = get_button();
		if(button == KBD_DOWN) {
			if(btn_press == 4) {
				btn_press = 0;
			}
			else {
				btn_press++;
			}
		}
		else if(button == KBD_UP){
			if(btn_press ==0) {
					btn_press = 4;
			}
			else {
				btn_press--;
			}
		}
		
		//gallery selected and highlighted
		if(btn_press==0) {
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(3,0,__FI,"1) Picture Gallery         ");
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(4,0,__FI,"2) mp3 player              ");			
				GLCD_DisplayString(5,0,__FI,"3) Game             ");
				GLCD_DisplayString(6,0,__FI,"4) Minigame             ");
			
			
				if(button == KBD_SELECT) {
					GLCD_Clear(White);
					gallery();
				}
			}

		//mp3 player is selected and highlighted
		if(btn_press==1) {
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(3,0,__FI,"1) Picture Gallery          ");
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(4,0,__FI,"2) mp3 player              ");
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);			
				GLCD_DisplayString(5,0,__FI,"3) Game             ");
				GLCD_DisplayString(6,0,__FI,"4) Minigame             ");
			
			
				if(button == KBD_SELECT) {
					GLCD_Clear(Black);
					mp3_player();
					GLCD_Clear(Black);
				}
			}
		
			//Game is selected and highlighted
		if(btn_press==2) {
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(3,0,__FI,"1) Picture Gallery          ");
				GLCD_DisplayString(4,0,__FI,"2) mp3 player              ");
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(Black);		
				GLCD_DisplayString(5,0,__FI,"3) Game             ");
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(6,0,__FI,"4) Minigame             ");
			
				if(button == KBD_SELECT) {
					GLCD_Clear(Black);
					start_ttt();
				}
			}
					//Minigame is selected and highlighted
		if(btn_press==3) {
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(3,0,__FI,"1) Picture Gallery          ");
				GLCD_DisplayString(4,0,__FI,"2) mp3 player              ");
				GLCD_DisplayString(5,0,__FI,"3) Game             ");
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(Black);		
			  GLCD_DisplayString(6,0,__FI,"4) Minigame             ");
			
				if(button == KBD_SELECT) {
					GLCD_Clear(Black);
					mini_game();
				}
			}
		}
	}

// main method/start screen
int main(void) {
		LED_Init();
		GLCD_Init();
		KBD_Init();
	
		GLCD_Clear(Black);
		GLCD_SetBackColor(Black);
		GLCD_SetTextColor(White);
		GLCD_DisplayString(1,0,__FI,"  COE 718 ");
		GLCD_SetTextColor(White);
		GLCD_DisplayString(2,5,__FI," Media Center   ");
		GLCD_SetTextColor(Blue);		
		GLCD_DisplayString(4,6,__FI,"Lucas  ");
	  GLCD_DisplayString(5,2,__FI,"   Gigliozzi  ");
		GLCD_SetTextColor(White);		
		GLCD_DisplayString(7,0,__FI," Press the Joystick");
	  GLCD_DisplayString(8,0,__FI,"      to Enter");
	
		while(1) {
			if(get_button() == KBD_SELECT) {
					main_menu();
			}
		}
	}
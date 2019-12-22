/*----------------------------------------------------------------------------
 * Name:    snake.c
 * Purpose: Media Center Project// Game mode (Snake)
 * By: Lucas
 *----------------------------------------------------------------------------*/
            
#include "stdio.h"
#include "stdlib.h"
#include "LPC17xx.h"
#include "KBD.h"
#include "GLCD.h"
#include "LED.h"

//Snake directions
#define UP		0
#define RIGHT	1
#define DOWN	2
#define LEFT	3

//Snake variables
int snake[100][2]; //snake coordinates. First represents max size of snake bodies. Second represents x,y pos.
int row_snake; //horizontal position
int col_snake; //vertical position
int l_snake; //Length of snake, body count
int dir_snake; //current direction
int prev_dir_snake; //previous direction
int speed; //how fast the snake will move

//Collectible - Food for snake
int row_food, col_food; //eat_food coordinates

//Joystick variables
int joystick_val = KBD_UP; //current joystick val
int joystick_prev_val = KBD_UP; //previous joystick val

//Buffer variable to hold score value
char str[20];

//Tracker variables for snake
int isHit = 0;
int score = 0;
int isGameDone = 0;

//Declarations
int start_game(void);
int restart(void);
void eat_food();
void add_body();
void check_state();
void update();
void direction();

//----------------------------------------------------------------------------------
//LCD DELAY, Refresh rate of game, can alter speed of game
void delay (int count){
	int val= 10000000;
	val /= count;
	while(val--);
}



//Function: If snake eats food, randomize next location of food
void eat_food(){

	row_food = (rand()%8)+1; // 0th row used by score counter
	col_food = rand()%19;
	
	if(row_food == snake[0][0])
		if(col_food == snake[0][1])
			eat_food();
	
	//Display character to represent eat_food
	GLCD_SetTextColor(Red);
	GLCD_DisplayChar(row_food,col_food,1,0x81);
	
}

//Function: Increment snake length/body block + score
void add_body(){
	l_snake++;
	score += 1;
}

//Function: Checks hit tail, eat food
void check_state(){
	int i;
	
	//If snake eats food, add body and randomize new food location
	if(row_food == snake[0][0])
		if(col_food == snake[0][1]){
			add_body();
			eat_food();
		}
		
	//If snake hits tail, isHit = 1, lose
	for(i=1;i<l_snake;i++){
		if(snake[0][0] == snake[i][0])
			if(snake[0][1] == snake[i][1])
				isHit = 1;
	}
	
}

//Function: Handles GLCD updates for snake
//Adds more body blocks to snake, determines color, moves according to speed
//Updates snake position according to x,y positions acquired
void update(){
	int i;
	GLCD_SetTextColor(Green);
	if(dir_snake == UP){ //Move up
		for(i=l_snake;i>0;i--){
			if(i-1 == 0){
				snake[0][1] = col_snake;
				snake[0][0] = row_snake;				
			}else{
				GLCD_DisplayChar(snake[i-1][0],snake[i-1][1],1,' ');
				snake[i-1][1] = snake[i-2][1];
				snake[i-1][0] = snake[i-2][0];
			}
		}
		for(i=1;i<l_snake;i++){
			GLCD_DisplayChar(snake[0][0],snake[0][1],1,0x85);
			GLCD_DisplayChar(snake[i][0],snake[i][1],1,0x83);
		}
		delay(speed);
	}
	else if(dir_snake == RIGHT){  //Move right
		for(i=l_snake;i>0;i--){
			if(i -1 == 0){
				snake[0][1] = col_snake;
				snake[0][0] = row_snake;				
			}else{
				GLCD_DisplayChar(snake[i-1][0],snake[i-1][1],1,' ');
				snake[i-1][1] = snake[i-2][1];
				snake[i-1][0] = snake[i-2][0];
			}
		}		
		for(i=1;i<l_snake;i++){
			GLCD_DisplayChar(snake[0][0],snake[0][1],1,0x8B);
			GLCD_DisplayChar(snake[i][0],snake[i][1],1,0x83);
		}
		delay(speed);
	}
	else if(dir_snake == DOWN){ //Move down
		for(i=l_snake;i>0;i--){
			if(i -1 == 0){
				snake[0][1] = col_snake;
				snake[0][0] = row_snake;				
			}else{
				GLCD_DisplayChar(snake[i-1][0],snake[i-1][1],1,' ');
				snake[i-1][1] = snake[i-2][1];
				snake[i-1][0] = snake[i-2][0];
			}
		}
		for(i=1;i<l_snake;i++){
			GLCD_DisplayChar(snake[0][0],snake[0][1],1,0x87);
			GLCD_DisplayChar(snake[i][0],snake[i][1],1,0x83);
		}
		delay(speed);
	}
	else if(dir_snake == LEFT){ //Move left
		for(i=l_snake;i>0;i--){
			if(i -1 == 0){
				snake[0][1] = col_snake;
				snake[0][0] = row_snake;				
			}else{
				GLCD_DisplayChar(snake[i-1][0],snake[i-1][1],1,' ');
				snake[i-1][1] = snake[i-2][1];
				snake[i-1][0] = snake[i-2][0];
			}
		}
		for(i=1;i<l_snake;i++){
			GLCD_DisplayChar(snake[0][0],snake[0][1],1,0x89);
			GLCD_DisplayChar(snake[i][0],snake[i][1],1,0x83);
		}
		delay(speed);
	}
	check_state();
}

//Function: Only able to rotate/move in 90 deg increments (ie. Up -> Left OR Right NOT Down)
//Updates x,y position of snake, displays change in update()
void direction(int joystick_val){

	switch(joystick_val){
		case KBD_UP:		//Move up
			if (joystick_prev_val == KBD_LEFT || joystick_prev_val == KBD_RIGHT){
				row_snake--;
				
				dir_snake = UP;
				prev_dir_snake = dir_snake;
				joystick_prev_val = joystick_val;
				update();
			}
			break;
		case KBD_RIGHT:		//Move right
			if (joystick_prev_val == KBD_UP || joystick_prev_val == KBD_DOWN){
				col_snake++;

				dir_snake = RIGHT;
				prev_dir_snake = dir_snake;
				joystick_prev_val = joystick_val;
				update();
			}
			break;			
		case KBD_DOWN:		//Move down
			if (joystick_prev_val == KBD_LEFT || joystick_prev_val == KBD_RIGHT){
				row_snake++;
				
				dir_snake = DOWN;
				prev_dir_snake = dir_snake;
				joystick_prev_val = joystick_val;
				update();
			}
			break;
		case KBD_LEFT:		//Move left
			if (joystick_prev_val == KBD_UP || joystick_prev_val == KBD_DOWN){
				col_snake--;

				dir_snake = LEFT;
				prev_dir_snake = dir_snake;
				joystick_prev_val = joystick_val;
				update();
			}
			break;

		default:		//If snake reaches edge of screen, arrive from opposite edge
			switch(dir_snake){
				case RIGHT:
					col_snake++;
					if (col_snake > 20){
						col_snake = 0;
					}
					update();
					check_state();
					break;
				case LEFT:
					col_snake--;
					if (col_snake < 0){
						col_snake = 20;
					}
					update();
					check_state();
					break;
				case DOWN:
					row_snake++;
					if (row_snake > 9){
						row_snake = 0;
					}
					update();
					check_state();
					break;
				case UP:
					row_snake--;
					if (row_snake < 0){
						row_snake = 9;
					}
					update();
					check_state();
					break;
			}
			break;
	}	
}


int restart(void)
{
	start_game();
	return 0;
}
/*----------------------------------------------------------------------------
  SNAKE GAME - 3 Difficulties, Collect as many apples as you can
 *----------------------------------------------------------------------------*/
int start_game(){
	//Variables to handle game menu
	int js_menu;
	int active_sel = 0;
	int sel_menu = 1;
	
	//Flag to track game is in active state
	isGameDone = 0;
	
	//Initialize game parameters
	score = 0;
	isHit = 0;
	dir_snake = UP;
	prev_dir_snake = UP;
	joystick_val = KBD_UP;
	joystick_prev_val = KBD_UP;
	l_snake = 2;
	row_snake = 4;
	col_snake = 9;
	
	//Initialize menu screen
	KBD_Init();
	GLCD_Init();
	
	GLCD_Clear(Black);
	GLCD_SetBackColor(Green);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0, 0, 1, "     SNAKE GAME     ");
	GLCD_DisplayString(1, 0, 1, "   EAT THE APPLES!  ");
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(2, 0, 1, "                    ");
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 0, 1, "       EASY         ");
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(5, 0, 1, "       MEDIUM       ");
	GLCD_DisplayString(6, 0, 1, "       HARD         ");					
	GLCD_DisplayString(7, 0, 1, "       RETURN       "); 	
	
	while(!isGameDone){
		
			while(sel_menu)  {		//While in main menu
			
				js_menu = get_button();
				if(js_menu == KBD_DOWN){
					if(active_sel == 4){
						 active_sel = 0;
					}
					else {
						active_sel++;
					}
				}
				else if(js_menu == KBD_UP){
					if(active_sel == 0){
						active_sel = 4;
					}
					else {
						active_sel--;
					}
				}

				if(active_sel== 0)  {		//EASY Selected
							GLCD_SetBackColor(Yellow);
							GLCD_SetTextColor(Black);
							GLCD_DisplayString(4, 0, 1, "       EASY         ");
							GLCD_SetBackColor(Black);
							GLCD_SetTextColor(White);
							GLCD_DisplayString(5, 0, 1, "       MEDIUM       ");
							GLCD_DisplayString(6, 0, 1, "       HARD         ");					
							GLCD_DisplayString(7, 0, 1, "       RETURN       "); 				
					
							if(js_menu == KBD_SELECT){
									speed = 2;
									break;
						
							}
				}
				else if (active_sel == 1)  {		//MEDIUM Selected
							GLCD_SetBackColor(Black);
							GLCD_SetTextColor(White);
							GLCD_DisplayString(4, 0, 1, "       EASY         ");
							GLCD_SetBackColor(Yellow);
							GLCD_SetTextColor(Black);
							GLCD_DisplayString(5, 0, 1, "       MEDIUM       ");
							GLCD_SetBackColor(Black);
							GLCD_SetTextColor(White);
							GLCD_DisplayString(6, 0, 1, "       HARD         ");	
							GLCD_DisplayString(7, 0, 1, "       RETURN       "); 					
					
							if(js_menu == KBD_SELECT){
									speed = 4;
									break;
							}
				}
				else if (active_sel == 2) {			//HARD Selected
							GLCD_SetBackColor(Black);
							GLCD_SetTextColor(White);
							GLCD_DisplayString(4, 0, 1, "       EASY         ");
							GLCD_DisplayString(5, 0, 1, "       MEDIUM       ");
							GLCD_SetBackColor(Yellow);
							GLCD_SetTextColor(Black);				 
							GLCD_DisplayString(6, 0, 1, "       HARD         ");	
							GLCD_SetBackColor(Black);
							GLCD_SetTextColor(White);					
							GLCD_DisplayString(7, 0, 1, "       RETURN       "); 
					
							if(js_menu == KBD_SELECT){
									speed = 6;
									break;						
							}
				}				
				else if (active_sel == 3) {				//RETURN to menu selected
							GLCD_SetBackColor(Black);
							GLCD_SetTextColor(White);
							GLCD_DisplayString(4, 0, 1, "       EASY         ");
							GLCD_DisplayString(5, 0, 1, "       MEDIUM       ");		 
							GLCD_DisplayString(6, 0, 1, "       HARD         ");	
							GLCD_SetBackColor(Red);
							GLCD_SetTextColor(White);					
							GLCD_DisplayString(7, 0, 1, "       RETURN       "); 
					
							if(js_menu == KBD_SELECT){
									GLCD_Clear(Black);
									isGameDone = 1;
									return 0;
							}
				}			
		}
			
		//Game Logic, Start game.
		//If snake hits self, lose game
		GLCD_Clear(Black);
		GLCD_SetBackColor(Black);
		eat_food();	
		while(isHit == 0){    //Playing state
			joystick_val = get_button();
			direction(joystick_val);
			sprintf(str,"SCORE: %d",score);
			GLCD_DisplayString(0, 5,1,(unsigned char *)str);	
		}
		if(isHit == 1){       //Lose Condition
			GLCD_Clear(Maroon);
			GLCD_SetBackColor(Maroon);
			GLCD_SetTextColor(White);
			sprintf(str, "  FINAL SCORE: %d  ", score);
			GLCD_DisplayString(3,0,1,(unsigned char *)str);
			GLCD_DisplayString(5,0,1, "      YOU LOSE      ");
			delay(1);
			delay(1);
			delay(1);
			delay(1);
			
			//Repeat state, return to game menu
			restart();
		}
		delay(1);
	}
	return 0;
}


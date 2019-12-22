/*----------------------------------------------------------------------------
 *ttt.c
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

#define DELAY_2N    18

extern int main(void);
extern void create_screen_multi(void);

static int cursor = 0; //current user position
static int computer_cursor = 0; //current computer psotion
static int cursor_positions[9] = {0,0,0,0,0,0,0,0,0}; //track user move son game board
static int com_cursor_positions[9] = {0,0,0,0,0,0,0,0,0}; //track computer moves on game board

//delay called inbetween button clicks so one click is not registered as multiple
static void delay1 (int cnt) {
  cnt <<= DELAY_2N;
  while (cnt--);
}

//display for when the user wins
void win_display(){
	int i =0;
	      GLCD_Clear(White);
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(3,0,1,"      You Win          "); //win message
	      GLCD_SetTextColor(Black);
				GLCD_DisplayString(5,0,1,"    Press Select       ");
				GLCD_DisplayString(6,0,1,"    to Return to       ");
	      GLCD_DisplayString(7,0,1,"     Main Menu         ");
	//reset global variables to 0 so game can be replayed
     cursor = 0; 
     computer_cursor = 0; 
	   for(i=0;i<9;i++)
     cursor_positions[i] = 0;
     for(i=0;i<9;i++)
     com_cursor_positions[i] = 0;
	      while(1){ //listen for select and return to menu
	     if(get_button() == KBD_SELECT) {  
				GLCD_Clear(Black);
		    main();
			}
		}
}
//display for when user loses and computer wins
void lose_display(){
	int i = 0;
	      GLCD_Clear(Black);
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(Red);
				GLCD_DisplayString(3,0,1,"      You Lose          ");
	      GLCD_SetTextColor(White);
				GLCD_DisplayString(5,0,1,"    Press Select        ");
				GLCD_DisplayString(6,0,1,"    to Return to       ");
	      GLCD_DisplayString(7,0,1,"     Main Menu         ");
		//reset global variables to 0 so game can be replayed
     cursor = 0; 
     computer_cursor = 0; 
	   for(i=0;i<9;i++)
     cursor_positions[i] = 0;
     for(i=0;i<9;i++)
     com_cursor_positions[i] = 0;
	      while(1){ 
	     if(get_button() == KBD_SELECT) {  
				GLCD_Clear(Black);
		    main();
			}
		}
}

//display for draw
void draw_display(){
	int i = 0;
	      GLCD_Clear(Black);
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(Green);
				GLCD_DisplayString(3,0,1,"       Draw          ");
	      GLCD_SetTextColor(White);
				GLCD_DisplayString(5,0,1,"    Press Select        ");
				GLCD_DisplayString(6,0,1,"    to Return to       ");
	      GLCD_DisplayString(7,0,1,"     Main Menu         ");
		//reset global variables to 0 so game can be replayed
     cursor = 0; 
     computer_cursor = 0; 
	   for(i=0;i<9;i++)
     cursor_positions[i] = 0;
     for(i=0;i<9;i++)
     com_cursor_positions[i] = 0;
	      while(1){ 
	     if(get_button() == KBD_SELECT) {  
				GLCD_Clear(Black);
		    main();
			}
		}
}

//check if the use has three X's in a row
void check_user_win(){
	int i = 0;
	int draw_count = 0;

	for(i = 0;i<9;i++){
		draw_count += com_cursor_positions[i] + cursor_positions[i];
	}
	if(draw_count == 9){
		}else{
			draw_count = 0;
		}
	 if(cursor_positions[0] == 1 && cursor_positions[1] == 1 && cursor_positions[2] == 1){ //3 across top
    win_display();
    }else if (cursor_positions[3] == 1 && cursor_positions[4] == 1 && cursor_positions[5] == 1){ //3 across middle
     win_display();
		}else if (cursor_positions[6] == 1 && cursor_positions[7] == 1 && cursor_positions[8] == 1){ //3 across bottom
      win_display();
		}else if (cursor_positions[0] == 1 && cursor_positions[3] == 1 && cursor_positions[6] == 1){ //3down left
      win_display();
		}else if (cursor_positions[1] == 1 && cursor_positions[4] == 1 && cursor_positions[7] == 1){ //3 down middle
			win_display();
		}else if (cursor_positions[2] == 1 && cursor_positions[5] == 1 && cursor_positions[8] == 1){ //3 down right
			win_display();
		}else if (cursor_positions[0] == 1 && cursor_positions[4] == 1 && cursor_positions[8] == 1){ //3 across diagonal
			win_display();
		}else if (cursor_positions[2] == 1 && cursor_positions[4] == 1 && cursor_positions[6] == 1){ //3 across diagonal
			win_display();
		}else if(draw_count == 9){
		draw_display();
		}else {
		return;
	}
}

//check if the computer has three O's in a row
void check_computer_win(){
	int i = 0;
	int draw_count = 0;

	for(i = 0;i<9;i++){
		draw_count += com_cursor_positions[i] + cursor_positions[i];
	}
	if(draw_count == 9){
		}else{
			draw_count = 0;
		}
	
	 if(com_cursor_positions[0] == 1 && com_cursor_positions[1] == 1 && com_cursor_positions[2] == 1){
    delay1(110);
		 lose_display();
    }else if (com_cursor_positions[3] == 1 && com_cursor_positions[4] == 1 && com_cursor_positions[5] == 1){
     delay1(110);
			lose_display();
		}else if (com_cursor_positions[6] == 1 && com_cursor_positions[7] == 1 && com_cursor_positions[8] == 1){
      delay1(110);
			lose_display();
		}else if (com_cursor_positions[0] == 1 && com_cursor_positions[3] == 1 && com_cursor_positions[6] == 1){
      delay1(110);
			lose_display();
		}else if (com_cursor_positions[1] == 1 && com_cursor_positions[4] == 1 && com_cursor_positions[7] == 1){
			delay1(110);
			lose_display();
		}else if (com_cursor_positions[2] == 1 && com_cursor_positions[5] == 1 && com_cursor_positions[8] == 1){
			delay1(110);
			lose_display();
		}else if (com_cursor_positions[0] == 1 && com_cursor_positions[4] == 1 && com_cursor_positions[8] == 1){
			delay1(110);
			lose_display();
		}else if (com_cursor_positions[2] == 1 && com_cursor_positions[4] == 1 && com_cursor_positions[6] == 1){
			delay1(110);
			lose_display();
		}else if(draw_count == 9){
		draw_display();
		}else {
		return;
	}
}

/*checks the position of the cursor to make sure an X or O does not already exist -- if it exists it will randomly a free space*/
int check_cursor(int cursor){
	int cursor1 = 0, i = 0;
	cursor1 = cursor;
	if(cursor_positions[cursor1] == 1 || com_cursor_positions[cursor1] == 1){ //check coms cursor and users cursor seperately so game knows which one wins
		cursor1 = rand()%(8 + 1); //randomly slect new square since +1 can get stuck in a loop
		cursor1 = check_cursor(cursor1);  //**when going from square 2 to square 1 and its occupied gets stuck in a loop between cursor value 1 and 2 
	}	
		if(cursor1 > 8){        
			cursor1 = 0;
			check_cursor(cursor1);
}
return cursor1;
}
//responsible for choosing a space for the computer to go in and storing its value and checking if it won
void computers_turn(){
	//srand(time(NULL)); //seed rand with time for a more random generation of numbers
	computer_cursor = rand()%(8 + 1 - 0); //return a random number between 0-8 for the computers turn
	computer_cursor = check_cursor(computer_cursor); //check and make sure the cursor position is empty, if not change it
	
	GLCD_SetTextColor(White);
  GLCD_DisplayString(0, 0, 1, "  Computer's Turn    ");
	
	delay1(130);
	
	if (computer_cursor == 0){
	GLCD_DisplayString(1, 3, 1, "O");
		com_cursor_positions[0] = 1;
		check_computer_win();
	}
	else if (computer_cursor == 1){
	GLCD_DisplayString(1, 9, 1, "O");
		com_cursor_positions[1] = 1;
				check_computer_win();
	}
	else if (computer_cursor == 2){
	GLCD_DisplayString(1, 16, 1, "O");
		com_cursor_positions[2] = 1;
				check_computer_win();
	}
	else if (computer_cursor == 3){
	GLCD_DisplayString(5, 3, 1, "O");
		com_cursor_positions[3] = 1;
				check_computer_win();
	}
	else if (computer_cursor == 4){
	GLCD_DisplayString(5, 9, 1, "O");
		com_cursor_positions[4] = 1;
				check_computer_win();
	}
	else if (computer_cursor == 5){
	GLCD_DisplayString(5, 16, 1, "O");
		com_cursor_positions[5] = 1;
				check_computer_win();
	}
	else if (computer_cursor == 6){
	GLCD_DisplayString(8, 3, 1, "O");
		com_cursor_positions[6] = 1;
				check_computer_win();
	}
	else if (computer_cursor == 7){
	GLCD_DisplayString(8, 9, 1, "O");
		com_cursor_positions[7] = 1;
				check_computer_win();
	}
	else if (computer_cursor == 8){
	GLCD_DisplayString(8, 16, 1, "O");
		com_cursor_positions[8] = 1;
				check_computer_win();
	}
	delay1(100);
}

/*when the user selects a square this function confirms and displays a permanent X in the cursor position
  next it calls check_user_win to determine if the user made a winning move*/
void select_square(int cursor){
	if (cursor == 0){
	GLCD_DisplayString(1, 3, 1, "X");
		cursor_positions[0] = 1;
		check_user_win();
	}
	else if (cursor == 1){
	GLCD_DisplayString(1, 9, 1, "X");
		cursor_positions[1] = 1;
		check_user_win();
	}
	else if (cursor == 2){
	GLCD_DisplayString(1, 16, 1, "X");
		cursor_positions[2] = 1;
				check_user_win();
	}
	else if (cursor == 3){
	GLCD_DisplayString(5, 3, 1, "X");
		cursor_positions[3] = 1;
				check_user_win();
	}
	else if (cursor == 4){
	GLCD_DisplayString(5, 9, 1, "X");
		cursor_positions[4] = 1;
				check_user_win();
	}
	else if (cursor == 5){
	GLCD_DisplayString(5, 16, 1, "X");
		cursor_positions[5] = 1;
				check_user_win();
	}
	else if (cursor == 6){
	GLCD_DisplayString(8, 3, 1, "X");
		cursor_positions[6] = 1;
				check_user_win();
	}
	else if (cursor == 7){
	GLCD_DisplayString(8, 9, 1, "X");
		cursor_positions[7] = 1;
				check_user_win();
	}
	else if (cursor == 8){
	GLCD_DisplayString(8, 16, 1, "X");
		cursor_positions[8] = 1;
				check_user_win();
	}
}

//creates the Tic Tac Toe game board and listens for input from user 
void create_screen(){
	
	while(1){
			
	GLCD_SetTextColor(White);
  GLCD_DisplayString(0, 0, 1, "      Your Turn       ");
	GLCD_DisplayString(1, 6, 1, "|");
	GLCD_DisplayString(2, 6, 1, "|");
	//GLCD_DisplayString(3, 6, 1, "|");	
  GLCD_DisplayString(4, 6, 1, "|");		
  GLCD_DisplayString(5, 6, 1, "|");		
  GLCD_DisplayString(6, 6, 1, "|");		
  //GLCD_DisplayString(7, 6, 1, "|");		
  GLCD_DisplayString(8, 6, 1, "|");		
  GLCD_DisplayString(9, 6, 1, "|");		

  GLCD_DisplayString(1, 13, 1, "|");	
	GLCD_DisplayString(2, 13, 1, "|");
	//GLCD_DisplayString(3, 13, 1, "|");	
  GLCD_DisplayString(4, 13, 1, "|");		
  GLCD_DisplayString(5, 13, 1, "|");		
  GLCD_DisplayString(6, 13, 1, "|");		
  //GLCD_DisplayString(7, 13, 1, "|");		
  GLCD_DisplayString(8, 13, 1, "|");		
  GLCD_DisplayString(9, 13, 1, "|");		
	
	GLCD_DisplayString(3, 0, 1, "------------------------");	
	GLCD_DisplayString(7, 0, 1, "------------------------");
	delay1(15);
	//tracks where the users cursor is and allows them to navigate with the joystick -- calls the select_square function when select is clicked
	while(1){
	cursor = check_cursor(cursor); //check cursor again after comp turn
	if(cursor == 0){
	GLCD_DisplayString(1, 3, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square(cursor);
			 delay1(10);
			 cursor ++;
			 cursor = check_cursor(cursor);
			delay1(10);
					computers_turn();
			 break;
			} else if (get_button() == KBD_RIGHT){
				cursor = 1;  
        cursor = check_cursor(cursor);
				GLCD_DisplayString(1, 3, 1, " ");
				break;
		 } else if (get_button() == KBD_DOWN){
			 cursor = 3;
			 cursor = check_cursor(cursor);			 
			 GLCD_DisplayString(1, 3, 1, " ");
			 break;
	}
	}	else if(cursor == 1){
		GLCD_DisplayString(1, 9, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square(cursor);
			 cursor ++;
		   cursor = check_cursor(cursor);
			delay1(10);
					computers_turn();
			 delay1(10);
			 break;
			} else if (get_button() == KBD_RIGHT){
		    cursor = 2;
				cursor = check_cursor(cursor);	
				GLCD_DisplayString(1, 9, 1, " ");
        break;
		} else if (get_button() == KBD_DOWN){
			  cursor = 4;
		    cursor = check_cursor(cursor);		
  			GLCD_DisplayString(1, 9, 1, " ");
        break;
		}else if (get_button() == KBD_LEFT){
			  cursor = 0;
		    cursor = check_cursor(cursor);		
			  GLCD_DisplayString(1, 9, 1, " ");
        break;       
	}
	} else if(cursor == 2){
		GLCD_DisplayString(1, 16, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square(cursor);
			 cursor ++;
			 cursor = check_cursor(cursor);
			delay1(10);
					computers_turn();
			 delay1(10);
			 break;
		} else if (get_button() == KBD_DOWN){
			 cursor = 5;
			 cursor = check_cursor(cursor);	
			 GLCD_DisplayString(1, 16, 1, " ");
        break;
		}else if (get_button() == KBD_LEFT){
		   cursor = 1;
		   cursor = check_cursor(cursor);		 
			GLCD_DisplayString(1, 16, 1, " ");
       break;
		} 
} else if(cursor == 3){
		GLCD_DisplayString(5, 3, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square(cursor);
			 cursor ++;
			 cursor = check_cursor(cursor);
			delay1(10);
					computers_turn();
			 delay1(10);
			 break;
		} else if (get_button() == KBD_DOWN){
			  cursor = 6;   
		    cursor = check_cursor(cursor);
			GLCD_DisplayString(5, 3, 1, " ");
        break;
		}else if (get_button() == KBD_RIGHT){
			 	cursor = 4;
			  cursor = check_cursor(cursor);
			GLCD_DisplayString(5, 3, 1, " ");
        break;
		}else if (get_button() == KBD_UP){
				cursor = 0;
			  cursor = check_cursor(cursor);
			GLCD_DisplayString(5, 3, 1, " ");
        break;
		}
}else if(cursor == 4){
		GLCD_DisplayString(5, 9, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square(cursor);
			 cursor ++;
			 cursor = check_cursor(cursor);
			delay1(10);
					computers_turn();
			 delay1(10);
			 break;
		} else if (get_button() == KBD_DOWN){
			  cursor = 7;
			  cursor = check_cursor(cursor);
			  GLCD_DisplayString(5, 9, 1, " ");  
        break;
		}else if (get_button() == KBD_RIGHT){
			 	cursor = 5;
			  cursor = check_cursor(cursor);
			GLCD_DisplayString(5, 9, 1, " ");
        break;
		}else if (get_button() == KBD_UP){
				cursor = 1;
			  cursor = check_cursor(cursor);
  			GLCD_DisplayString(5, 9, 1, " ");
        break;
		}else if (get_button() == KBD_LEFT){
				cursor = 3;
			  cursor = check_cursor(cursor);
			GLCD_DisplayString(5, 9, 1, " ");
        break;
		}
} else if(cursor == 5){
		GLCD_DisplayString(5, 16, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square(cursor);
			 cursor ++;
			 cursor = check_cursor(cursor);
			delay1(10);
					computers_turn();
			 delay1(10);
			 break;
		} else if (get_button() == KBD_DOWN){
			  cursor = 8;
			  cursor = check_cursor(cursor);
			GLCD_DisplayString(5, 16, 1, " ");
        break;
		}else if (get_button() == KBD_UP){
				cursor = 2;
			  cursor = check_cursor(cursor);
			GLCD_DisplayString(5, 16, 1, " ");
        break;
		}else if (get_button() == KBD_LEFT){
				cursor = 4;
			  cursor = check_cursor(cursor);
			GLCD_DisplayString(5, 16, 1, " ");
        break;
		}
} else if(cursor == 6){
		GLCD_DisplayString(8, 3, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square(cursor);
			 cursor ++;
			 cursor = check_cursor(cursor);
			delay1(10);
					computers_turn();
			 delay1(10);
			 break;
		}else if (get_button() == KBD_UP){
				cursor = 3;
			  cursor = check_cursor(cursor);
			GLCD_DisplayString(8, 3, 1, " ");
        break;
		}else if (get_button() == KBD_RIGHT){
				cursor = 7;
		    cursor = check_cursor(cursor);
			GLCD_DisplayString(8, 3, 1, " ");
        break;
		}
} else if(cursor == 7){
		GLCD_DisplayString(8, 9, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square(cursor);
			 cursor ++;
			 cursor = check_cursor(cursor);
			delay1(10);
					computers_turn();
			 delay1(10);
			 break;
		} else if (get_button() == KBD_RIGHT){
			  cursor = 8;
			cursor = check_cursor(cursor);
			GLCD_DisplayString(8, 9, 1, " ");
        break;
		}else if (get_button() == KBD_UP){
				cursor = 4;
		    cursor = check_cursor(cursor);
			GLCD_DisplayString(8, 9, 1, " ");
        break;
		}else if (get_button() == KBD_LEFT){
				cursor = 6;
			cursor = check_cursor(cursor);
			GLCD_DisplayString(8, 9, 1, " ");
        break;
		}
} else if(cursor == 8){
		GLCD_DisplayString(8, 16, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square(cursor);
			 cursor --;
			 cursor = check_cursor(cursor);
			delay1(10);
					computers_turn();
			 delay1(10);
			 break;
		} else if (get_button() == KBD_UP){
				cursor = 5;
			  cursor = check_cursor(cursor);
			GLCD_DisplayString(8, 16, 1, " ");
        break;
		}else if (get_button() == KBD_LEFT){
				cursor = 7;
			cursor = check_cursor(cursor);
			GLCD_DisplayString(8, 16, 1, " ");
        break;
		}
}
}
}
}

//Start Screen and option select for Tic Tac Toe game
int start_ttt(){
	int button;
	int btn_press = 0;	
	
	GLCD_Clear(Black);
	while(1){
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(Red);
	GLCD_DisplayString(0, 0, 1, "    Welcome to       ");
	GLCD_DisplayString(1, 0, 1, "    Tic Tac Toe      ");
  GLCD_SetTextColor(White);
  GLCD_DisplayString(3, 0, 1, "Choose the game mode ");
	
  button = get_button();
		if(button == KBD_DOWN) {
			if(btn_press == 0) {
				btn_press = 1;
			}
		}
		else if(button == KBD_UP){
			if(btn_press ==1) {
					btn_press = 0;
			} 
		}
		
		if(btn_press==0) {
				GLCD_SetBackColor(Red);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(6,0,1,"1) VS Computer         ");
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(7,0,1,"2) Multiplayer            ");			
			
			
				if(button == KBD_SELECT) {
					GLCD_Clear(Black);
					create_screen();
				}
			}
		
			if(btn_press==1) {
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(6,0,1,"1) VS Computer         ");
				GLCD_SetBackColor(Red);
				GLCD_SetTextColor(Black);
				GLCD_DisplayString(7,0,1,"2) Multiplayer            ");			
			
			
				if(button == KBD_SELECT) {
					GLCD_SetBackColor(Black);
					GLCD_Clear(Black);
					create_screen_multi();
				}
			}
		}
	return 0;
}
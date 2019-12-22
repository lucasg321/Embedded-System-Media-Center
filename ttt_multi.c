/*----------------------------------------------------------------------------
 *ttt_multi.c
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

static int cursor = 0; //current user position
static int computer_cursor = 0; //current computer psotion
static int cursor_positions[9] = {0,0,0,0,0,0,0,0,0}; //track user move son game board
static int com_cursor_positions[9] = {0,0,0,0,0,0,0,0,0}; //track computer moves on game board

//delay called inbetween button clicks so one click is not registered as multiple
static void delay2 (int cnt) {
  cnt <<= DELAY_2N;
  while (cnt--);
}

//display for when the user wins
void win_display_multi(){
	int i =0;
	      GLCD_Clear(White);
				GLCD_SetBackColor(White);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(3,0,1,"   Player 1 Wins          "); //player 1 win message
	      GLCD_SetTextColor(Black);
				GLCD_DisplayString(5,0,1,"    Press Select       ");
				GLCD_DisplayString(6,0,1,"    to Return to       ");
	      GLCD_DisplayString(7,0,1,"     Main Menu         ");
	//reset global variables to 0 so game can be replayed after returning to main menu
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
void lose_display_multi(){
	int i = 0;
	      GLCD_Clear(Black);
				GLCD_SetBackColor(Black);
				GLCD_SetTextColor(Red);
				GLCD_DisplayString(3,0,1,"   Player 2 Wins  ");
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

//display for when user loses and computer wins
void draw_display_multi(){
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
void check_user_win_multi(){
	int i = 0;
int draw_count = 0;

	//check if there is a draw
	for(i = 0;i<9;i++){
		draw_count += com_cursor_positions[i] + cursor_positions[i];
	}
if(draw_count == 9){
		}else{
			draw_count = 0;
		}
	 if(cursor_positions[0] == 1 && cursor_positions[1] == 1 && cursor_positions[2] == 1){ //3 across top
    win_display_multi();
    }else if (cursor_positions[3] == 1 && cursor_positions[4] == 1 && cursor_positions[5] == 1){ //3 across middle
     win_display_multi();
		}else if (cursor_positions[6] == 1 && cursor_positions[7] == 1 && cursor_positions[8] == 1){ //3 across bottom
      win_display_multi();
		}else if (cursor_positions[0] == 1 && cursor_positions[3] == 1 && cursor_positions[6] == 1){ //3 down left
      win_display_multi();
		}else if (cursor_positions[1] == 1 && cursor_positions[4] == 1 && cursor_positions[7] == 1){ //3 down middle
			win_display_multi();
		}else if (cursor_positions[2] == 1 && cursor_positions[5] == 1 && cursor_positions[8] == 1){ //3 down right
			win_display_multi();
		}else if (cursor_positions[0] == 1 && cursor_positions[4] == 1 && cursor_positions[8] == 1){ //3 across diagonal
			win_display_multi();
		}else if (cursor_positions[2] == 1 && cursor_positions[4] == 1 && cursor_positions[6] == 1){ //3 across diagonal
			win_display_multi();
		}else if(draw_count == 9){
		draw_display_multi();
		}else {
		return;
	}
}

//check if the computer has three O's in a row
void check_computer_win_multi(){
	int i = 0;
	int draw_count = 0;

	//check if there is a draw
	for(i = 0;i<9;i++){
		draw_count += com_cursor_positions[i] + cursor_positions[i];
	}
	if(draw_count == 9){
		}else{
			draw_count = 0;
		}
	
	 if(com_cursor_positions[0] == 1 && com_cursor_positions[1] == 1 && com_cursor_positions[2] == 1){
    lose_display_multi();
    }else if (com_cursor_positions[3] == 1 && com_cursor_positions[4] == 1 && com_cursor_positions[5] == 1){
     lose_display_multi();
		}else if (com_cursor_positions[6] == 1 && com_cursor_positions[7] == 1 && com_cursor_positions[8] == 1){
      lose_display_multi();
		}else if (com_cursor_positions[0] == 1 && com_cursor_positions[3] == 1 && com_cursor_positions[6] == 1){
      lose_display_multi();
		}else if (com_cursor_positions[1] == 1 && com_cursor_positions[4] == 1 && com_cursor_positions[7] == 1){
			lose_display_multi();
		}else if (com_cursor_positions[2] == 1 && com_cursor_positions[5] == 1 && com_cursor_positions[8] == 1){
			lose_display_multi();
		}else if (com_cursor_positions[0] == 1 && com_cursor_positions[4] == 1 && com_cursor_positions[8] == 1){
			lose_display_multi();
		}else if (com_cursor_positions[2] == 1 && com_cursor_positions[4] == 1 && com_cursor_positions[6] == 1){
			lose_display_multi();
		}else if(draw_count == 9){
		draw_display_multi();
		}else {
		return;
	}
}


/*checks the position of the cursor to make sure an X or O does not already exist -- if it exists it will dec or inc until it finds a free space*/
int check_cursor_multi(int cursor){
	int cursor1 = 0, i = 0;
	cursor1 = cursor;
	if(cursor_positions[cursor1] == 1 || com_cursor_positions[cursor1] == 1){ //check coms cursor and users cursor seperately so game knows which one wins
		cursor1 = rand()%(8 + 1); //randomly select new square since +1 can get stuck in a loop
		cursor1 = check_cursor_multi(cursor1);  //make sure new value is ok and change it if not 
	}	
		if(cursor1 > 8){        
			cursor1 = 0;
			cursor1 = check_cursor_multi(cursor1);
}
return cursor1;
}

void select_square_multi_2(int cursor){
	if (cursor == 0){
	GLCD_DisplayString(1, 3, 1, "O");
		com_cursor_positions[0] = 1;
		check_computer_win_multi();
	}
	else if (cursor == 1){
	GLCD_DisplayString(1, 9, 1, "O");
		com_cursor_positions[1] = 1;
		check_computer_win_multi();
	}
	else if (cursor == 2){
	GLCD_DisplayString(1, 16, 1, "O");
		com_cursor_positions[2] = 1;
				check_computer_win_multi();
	}
	else if (cursor == 3){
	GLCD_DisplayString(5, 3, 1, "O");
		com_cursor_positions[3] = 1;
				check_computer_win_multi();
	}
	else if (cursor == 4){
	GLCD_DisplayString(5, 9, 1, "O");
		com_cursor_positions[4] = 1;
				check_computer_win_multi();
	}
	else if (cursor == 5){
	GLCD_DisplayString(5, 16, 1, "O");
		com_cursor_positions[5] = 1;
				check_computer_win_multi();
	}
	else if (cursor == 6){
	GLCD_DisplayString(8, 3, 1, "O");
		com_cursor_positions[6] = 1;
				check_computer_win_multi();
	}
	else if (cursor == 7){
	GLCD_DisplayString(8, 9, 1, "O");
		com_cursor_positions[7] = 1;
				check_computer_win_multi();
	}
	else if (cursor == 8){
	GLCD_DisplayString(8, 16, 1, "O");
		com_cursor_positions[8] = 1;
				check_computer_win_multi();
	}
}

//responsible for choosing a space for the computer to go in and storing its value and checking if it won
void computers_turn_multi(){
	
	GLCD_SetTextColor(White);
  GLCD_DisplayString(0, 0, 1, "  Player 2's Turn   ");
	
	delay2(30);
	
	//user cursor tracker and incrementor is below
	//tracks where player 2's computer_cursor is and allows them to navigate with the joystick -- calls the select_square_multi function when select is clicked
	while(1){
	computer_cursor = check_cursor_multi(computer_cursor); //check cursor again after comp turn
	if(computer_cursor == 0){
	GLCD_DisplayString(1, 3, 1, "O");
		if(get_button() == KBD_SELECT) {
			 select_square_multi_2(computer_cursor);
			 delay2(20);
			 computer_cursor ++;
			 computer_cursor = check_cursor_multi(computer_cursor);
			 break;
			} else if (get_button() == KBD_RIGHT){
				computer_cursor = 1;  
        computer_cursor = check_cursor_multi(computer_cursor);
				GLCD_DisplayString(1, 3, 1, " ");
				delay2(20);
		 } else if (get_button() == KBD_DOWN){
			 computer_cursor = 3;
			 computer_cursor = check_cursor_multi(computer_cursor);			 
			 GLCD_DisplayString(1, 3, 1, " ");
			 delay2(20);
	}
	}	else if(computer_cursor == 1){
		GLCD_DisplayString(1, 9, 1, "O");
		if(get_button() == KBD_SELECT) {
			 select_square_multi_2(computer_cursor);
			 computer_cursor ++;
		   computer_cursor = check_cursor_multi(computer_cursor);
			 delay2(10);
			 break;
			} else if (get_button() == KBD_RIGHT){
		    computer_cursor = 2;
				computer_cursor = check_cursor_multi(computer_cursor);	
				GLCD_DisplayString(1, 9, 1, " ");
				delay2(20);
		} else if (get_button() == KBD_DOWN){
			  computer_cursor = 4;
		    computer_cursor = check_cursor_multi(computer_cursor);		
  			GLCD_DisplayString(1, 9, 1, " ");
			delay2(20);
		}else if (get_button() == KBD_LEFT){
			  computer_cursor = 0;
		    computer_cursor = check_cursor_multi(computer_cursor);		
			  GLCD_DisplayString(1, 9, 1, " ");  
delay2(20);			
	}
	} else if(computer_cursor == 2){
		GLCD_DisplayString(1, 16, 1, "O");
		if(get_button() == KBD_SELECT) {
			 select_square_multi_2(computer_cursor);
			 computer_cursor ++;
			 computer_cursor = check_cursor_multi(computer_cursor);
			 delay2(10);
			 break;
		} else if (get_button() == KBD_DOWN){
			 computer_cursor = 5;
			 computer_cursor = check_cursor_multi(computer_cursor);	
			 GLCD_DisplayString(1, 16, 1, " ");
			delay2(20);
		}else if (get_button() == KBD_LEFT){
		   computer_cursor = 1;
		   computer_cursor = check_cursor_multi(computer_cursor);		 
			GLCD_DisplayString(1, 16, 1, " ");
			delay2(20);
		} 
} else if(computer_cursor == 3){
		GLCD_DisplayString(5, 3, 1, "O");
		if(get_button() == KBD_SELECT) {
			 select_square_multi_2(computer_cursor);
			 computer_cursor ++;
			 computer_cursor = check_cursor_multi(computer_cursor);
			 delay2(10);
			 break;
		} else if (get_button() == KBD_DOWN){
			  computer_cursor = 6;   
		    computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(5, 3, 1, " ");
			delay2(20);
		}else if (get_button() == KBD_RIGHT){
			 	computer_cursor = 4;
			  computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(5, 3, 1, " ");
			delay2(20);
		}else if (get_button() == KBD_UP){
				computer_cursor = 0;
			  computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(5, 3, 1, " ");
			delay2(20);
		}
}else if(computer_cursor == 4){
		GLCD_DisplayString(5, 9, 1, "O");
		if(get_button() == KBD_SELECT) {
			 select_square_multi_2(computer_cursor);
			 computer_cursor ++;
			 computer_cursor = check_cursor_multi(computer_cursor);
			 delay2(10);
			 break;
		} else if (get_button() == KBD_DOWN){
			  computer_cursor = 7;
			  computer_cursor = check_cursor_multi(computer_cursor);
			  GLCD_DisplayString(5, 9, 1, " "); 
        delay2(20);			
		}else if (get_button() == KBD_RIGHT){
			 	computer_cursor = 5;
			  computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(5, 9, 1, " ");
			delay2(20);
		}else if (get_button() == KBD_UP){
				computer_cursor = 1;
			  computer_cursor = check_cursor_multi(computer_cursor);
  			GLCD_DisplayString(5, 9, 1, " ");
			delay2(20);
		}else if (get_button() == KBD_LEFT){
				computer_cursor = 3;
			  computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(5, 9, 1, " ");
			delay2(20);
		}
} else if(computer_cursor == 5){
		GLCD_DisplayString(5, 16, 1, "O");
		if(get_button() == KBD_SELECT) {
			 select_square_multi_2(computer_cursor);
			 computer_cursor ++;
			 computer_cursor = check_cursor_multi(computer_cursor);
			 delay2(10);
			 break;
		} else if (get_button() == KBD_DOWN){
			  computer_cursor = 8;
			  computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(5, 16, 1, " ");
			delay2(20);
		}else if (get_button() == KBD_UP){
				computer_cursor = 2;
			  computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(5, 16, 1, " ");
			delay2(20);
		}else if (get_button() == KBD_LEFT){
				computer_cursor = 4;
			  computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(5, 16, 1, " ");
			delay2(20);
		}
} else if(computer_cursor == 6){
		GLCD_DisplayString(8, 3, 1, "O");
		if(get_button() == KBD_SELECT) {
			 select_square_multi_2(computer_cursor);
			 computer_cursor ++;
			 computer_cursor = check_cursor_multi(computer_cursor);
			 delay2(10);
			 break;
		}else if (get_button() == KBD_UP){
				computer_cursor = 3;
			  computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(8, 3, 1, " ");
			delay2(20);
		}else if (get_button() == KBD_RIGHT){
				computer_cursor = 7;
		    computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(8, 3, 1, " ");
			delay2(20);
		}
} else if(computer_cursor == 7){
		GLCD_DisplayString(8, 9, 1, "O");
		if(get_button() == KBD_SELECT) {
			 select_square_multi_2(computer_cursor);
			 computer_cursor ++;
			 computer_cursor = check_cursor_multi(computer_cursor);
			 delay2(10);
			 break;
		} else if (get_button() == KBD_RIGHT){
			  computer_cursor = 8;
			computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(8, 9, 1, " ");
			delay2(20);
		}else if (get_button() == KBD_UP){
				computer_cursor = 4;
		    computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(8, 9, 1, " ");
			delay2(20);
		}else if (get_button() == KBD_LEFT){
				computer_cursor = 6;
			computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(8, 9, 1, " ");
			delay2(20);
		}
} else if(computer_cursor == 8){
		GLCD_DisplayString(8, 16, 1, "O");
		if(get_button() == KBD_SELECT) {
			 select_square_multi_2(computer_cursor);
			 computer_cursor --;
			 computer_cursor = check_cursor_multi(computer_cursor);
			 delay2(10);
			 break;
		} else if (get_button() == KBD_UP){
				computer_cursor = 5;
			  computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(8, 16, 1, " ");
			delay2(20);
		}else if (get_button() == KBD_LEFT){
				computer_cursor = 7;
			computer_cursor = check_cursor_multi(computer_cursor);
			GLCD_DisplayString(8, 16, 1, " ");
			delay2(20);
		}
}
}
}

/*when player 1 selects a square this function confirms and displays a permanent X in the cursor position
  next it calls check_user_win_multi to determine if the user made a winning move*/
void select_square_multi(int cursor){
	if (cursor == 0){
	GLCD_DisplayString(1, 3, 1, "X");
		cursor_positions[0] = 1;
		check_user_win_multi();
	}
	else if (cursor == 1){
	GLCD_DisplayString(1, 9, 1, "X");
		cursor_positions[1] = 1;
		check_user_win_multi();
	}
	else if (cursor == 2){
	GLCD_DisplayString(1, 16, 1, "X");
		cursor_positions[2] = 1;
				check_user_win_multi();
	}
	else if (cursor == 3){
	GLCD_DisplayString(5, 3, 1, "X");
		cursor_positions[3] = 1;
				check_user_win_multi();
	}
	else if (cursor == 4){
	GLCD_DisplayString(5, 9, 1, "X");
		cursor_positions[4] = 1;
				check_user_win_multi();
	}
	else if (cursor == 5){
	GLCD_DisplayString(5, 16, 1, "X");
		cursor_positions[5] = 1;
				check_user_win_multi();
	}
	else if (cursor == 6){
	GLCD_DisplayString(8, 3, 1, "X");
		cursor_positions[6] = 1;
				check_user_win_multi();
	}
	else if (cursor == 7){
	GLCD_DisplayString(8, 9, 1, "X");
		cursor_positions[7] = 1;
				check_user_win_multi();
	}
	else if (cursor == 8){
	GLCD_DisplayString(8, 16, 1, "X");
		cursor_positions[8] = 1;
				check_user_win_multi();
	}
}

//creates the Tic Tac Toe game board and listens for input from user 
void create_screen_multi(){
	GLCD_Clear(Black);
	while(1){
	//these intial GLCD functions are used to create the game board for tic tac toe
	GLCD_SetTextColor(White);
  GLCD_DisplayString(0, 0, 1, "  Player 1's Turn       ");
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
	delay2(15);
	//user cursor tracker and incrementor is below
	//tracks where the users cursor is and allows them to navigate with the joystick -- calls the select_square_multi function when select is clicked
	while(1){
	cursor = check_cursor_multi(cursor); //check cursor again after comp turn
	if(cursor == 0){
	GLCD_DisplayString(1, 3, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square_multi(cursor);
			 delay2(10);
			 cursor ++;
			 cursor = check_cursor_multi(cursor);
			 computers_turn_multi();
			 break;
			} else if (get_button() == KBD_RIGHT){
				cursor = 1;  
        cursor = check_cursor_multi(cursor);
				GLCD_DisplayString(1, 3, 1, " ");
        break;
		 } else if (get_button() == KBD_DOWN){
			 cursor = 3;
			 cursor = check_cursor_multi(cursor);			 
			 GLCD_DisplayString(1, 3, 1, " ");
        break;
	}
	}	else if(cursor == 1){
		GLCD_DisplayString(1, 9, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square_multi(cursor);
			 cursor ++;
		   cursor = check_cursor_multi(cursor);
					computers_turn_multi();
			 delay2(10);
			 break;
			} else if (get_button() == KBD_RIGHT){
		    cursor = 2;
				cursor = check_cursor_multi(cursor);	
				GLCD_DisplayString(1, 9, 1, " ");
        break;
		} else if (get_button() == KBD_DOWN){
			  cursor = 4;
		    cursor = check_cursor_multi(cursor);		
  			GLCD_DisplayString(1, 9, 1, " ");
        break;
		}else if (get_button() == KBD_LEFT){
			  cursor = 0;
		    cursor = check_cursor_multi(cursor);		
			  GLCD_DisplayString(1, 9, 1, " ");
        break;       
	}
	} else if(cursor == 2){
		GLCD_DisplayString(1, 16, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square_multi(cursor);
			 cursor ++;
			 cursor = check_cursor_multi(cursor);
					computers_turn_multi();
			 delay2(10);
			 break;
		} else if (get_button() == KBD_DOWN){
			 cursor = 5;
			 cursor = check_cursor_multi(cursor);	
			 GLCD_DisplayString(1, 16, 1, " ");
        break;
		}else if (get_button() == KBD_LEFT){
		   cursor = 1;
		   cursor = check_cursor_multi(cursor);		 
			GLCD_DisplayString(1, 16, 1, " ");
       break;
		} 
} else if(cursor == 3){
		GLCD_DisplayString(5, 3, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square_multi(cursor);
			 cursor ++;
			 cursor = check_cursor_multi(cursor);
					computers_turn_multi();
			 delay2(10);
			 break;
		} else if (get_button() == KBD_DOWN){
			  cursor = 6;   
		    cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(5, 3, 1, " ");
        break;
		}else if (get_button() == KBD_RIGHT){
			 	cursor = 4;
			  cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(5, 3, 1, " ");
        break;
		}else if (get_button() == KBD_UP){
				cursor = 0;
			  cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(5, 3, 1, " ");
        break;
		}
}else if(cursor == 4){
		GLCD_DisplayString(5, 9, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square_multi(cursor);
			 cursor ++;
			 cursor = check_cursor_multi(cursor);
					computers_turn_multi();
			 delay2(10);
			 break;
		} else if (get_button() == KBD_DOWN){
			  cursor = 7;
			  cursor = check_cursor_multi(cursor);
			  GLCD_DisplayString(5, 9, 1, " ");  
        break;
		}else if (get_button() == KBD_RIGHT){
			 	cursor = 5;
			  cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(5, 9, 1, " ");
        break;
		}else if (get_button() == KBD_UP){
				cursor = 1;
			  cursor = check_cursor_multi(cursor);
  			GLCD_DisplayString(5, 9, 1, " ");
        break;
		}else if (get_button() == KBD_LEFT){
				cursor = 3;
			  cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(5, 9, 1, " ");
        break;
		}
} else if(cursor == 5){
		GLCD_DisplayString(5, 16, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square_multi(cursor);
			 cursor ++;
			 cursor = check_cursor_multi(cursor);
					computers_turn_multi();
			 delay2(10);
			 break;
		} else if (get_button() == KBD_DOWN){
			  cursor = 8;
			  cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(5, 16, 1, " ");
        break;
		}else if (get_button() == KBD_UP){
				cursor = 2;
			  cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(5, 16, 1, " ");
        break;
		}else if (get_button() == KBD_LEFT){
				cursor = 4;
			  cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(5, 16, 1, " ");
        break;
		}
} else if(cursor == 6){
		GLCD_DisplayString(8, 3, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square_multi(cursor);
			 cursor ++;
			 cursor = check_cursor_multi(cursor);
					computers_turn_multi();
			 delay2(10);
			 break;
		}else if (get_button() == KBD_UP){
				cursor = 3;
			  cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(8, 3, 1, " ");
        break;
		}else if (get_button() == KBD_RIGHT){
				cursor = 7;
		    cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(8, 3, 1, " ");
        break;
		}
} else if(cursor == 7){
		GLCD_DisplayString(8, 9, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square_multi(cursor);
			 cursor ++;
			 cursor = check_cursor_multi(cursor);
					computers_turn_multi();
			 delay2(10);
			 break;
		} else if (get_button() == KBD_RIGHT){
			  cursor = 8;
			cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(8, 9, 1, " ");
        break;
		}else if (get_button() == KBD_UP){
				cursor = 4;
		    cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(8, 9, 1, " ");
        break;
		}else if (get_button() == KBD_LEFT){
				cursor = 6;
			cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(8, 9, 1, " ");
        break;
		}
} else if(cursor == 8){
		GLCD_DisplayString(8, 16, 1, "X");
		if(get_button() == KBD_SELECT) {
			 select_square_multi(cursor);
			 cursor --;
			 cursor = check_cursor_multi(cursor);
					computers_turn_multi();
			 delay2(10);
			 break;
		} else if (get_button() == KBD_UP){
				cursor = 5;
			  cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(8, 16, 1, " ");
        break;
		}else if (get_button() == KBD_LEFT){
				cursor = 7;
			cursor = check_cursor_multi(cursor);
			GLCD_DisplayString(8, 16, 1, " ");
        break;
		}
}
}
}
}

//Start Screen for Tic Tac Toe game
int start_ttt_multi(){
	GLCD_Clear(Black);
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0, 0, 1, "    Welcome to   ");
	GLCD_DisplayString(1, 0, 1, "    Tic Tac Toe   ");
	
	GLCD_DisplayString(5, 0, 1, " Press the Joystick  ");
	GLCD_DisplayString(6, 0, 1, "      to Play   ");	

	while(1){
	if(get_button() == KBD_SELECT) {  //calls create_screen_multi function when Select is clicked which then creates the game board and starts listening for input
				GLCD_Clear(Black);
		    create_screen_multi();
			}
		}
	return 0;
}
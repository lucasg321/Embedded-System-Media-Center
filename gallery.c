// Media Center Project - Gallery 
// By: Lucas Gigliozzi
            
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include "csharp.c"
#include "java.c"
#include "python.c"
#include "php.c"

#define __FI        1                      /* Font index 16x24               */

/*----------------------------------------------------------------------------
  Gallery - programming pictures
 *----------------------------------------------------------------------------*/
int gallery(void){
	int pic_shown = 0, press = 0;


		while(1){
			GLCD_SetBackColor(Black);
      GLCD_SetTextColor(White);
			GLCD_DisplayString(0, 0, __FI, "       Gallery        ");
			GLCD_DisplayString(5, 0, __FI, "<-");
			GLCD_DisplayString(5, 18, __FI, "->");
		 GLCD_SetBackColor(White);
      GLCD_SetTextColor(Black);
			GLCD_DisplayString(4, 0, 0, "                    Select to Exit    ");
			
			press = get_button();
			
			//Scroll through the available pictures	
			if(press == KBD_LEFT){
				if(pic_shown == 0){
					pic_shown = 3;
				}
				else {
					pic_shown--;
				}
			}
			else if(press == KBD_RIGHT) {
				if(pic_shown == 4){
					pic_shown = 0;
				}
				else {
					pic_shown++;
				}
			}
			else if(press == KBD_SELECT){ 
					GLCD_Clear(Black);
					return 0;
			
			}
			
			//picture is displayed depending on user joystick input
			if(pic_shown == 0)  {	
				  GLCD_Bitmap(60, 40, 200, 200, (unsigned char *)&GIMP_IMAGE_pixel_data);
			}
			else if (pic_shown == 1) {
				GLCD_Bitmap(60, 40, 200, 200, (unsigned char *)&JAVA_pixel_data);
			}
			else if (pic_shown == 2) {
				GLCD_Bitmap(60, 40, 200, 200, (unsigned char *)&PYTHON_pixel_data);
			}
			else if (pic_shown == 3)
			{
				GLCD_Bitmap(60, 40, 200, 200, (unsigned char *)&PHP_pixel_data);
			}
		}


}
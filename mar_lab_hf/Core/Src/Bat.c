#include "Bat.h"
#include "bsp_uart.h"
Bats bat = { default_bat_location,PIXELS_Y - default_bat_height,default_bat_width,default_bat_height, default_bat_moveX };
void check_bat_move(int x)
{
	if(lastReceivedUartCommand == 'a' || lastReceivedUartCommand == 'd')
		 {
		move_and_only_bat_display(x);
		lastReceivedUartCommand=0;
		 }
}
void move_Bat(int x)
{
    switch(x)
    {
        //move right
        case 'd':
            if (bat.locationX + bat.width + bat.moveX > PIXELS_X)
                bat.locationX = PIXELS_X - bat.width;
            else
                bat.locationX += bat.moveX;
        break;
        //move left
        case 'a':
            if (bat.locationX - bat.moveX < 0)
                bat.locationX = 0;
            else
                bat.locationX -= bat.moveX;
        break;
        default:
        break;
    }
}

void bat_display()
{
	 char this_obj = '1';

	for (int i = 0, j = 0; j < bat.height;j++)
	{
		for(i=0;i<bat.width;i++)
		{
			LCD_DISPLAY[bat.locationX + i][bat.locationY + j] = this_obj;
		}
	}
}

void move_and_only_bat_display(int x)
{
	int prev_batX=bat.locationX;
	move_Bat(x);

	for (int i = 0, j = 0; j < bat.height;j++)
		{
			for(i=0;i<bat.width;i++)
			{
			LCD_DISPLAY[prev_batX + i][bat.locationY + j] = '0';
			}
		}

	char this_obj = '1';

	for (int i = 0, j = 0; j < bat.height;j++)
	{
		for(i=0;i<bat.width;i++)
		{
			LCD_DISPLAY[bat.locationX + i][bat.locationY + j] = this_obj;
		}
	}
	ONLY_BAT_OUTPUT(prev_batX);
}

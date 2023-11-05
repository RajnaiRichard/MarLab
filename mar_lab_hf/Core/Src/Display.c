#include "Display.h"
#include "bsp_uart.h"
#include "mainloop.h"
char LCD_DISPLAY[PIXELS_X][PIXELS_Y];
char PREV_LCD_DISPLAY[PIXELS_X][PIXELS_Y];
char OUTPUT[800];
int OUTPUT_SIZE=0;

void reset_lcd_display()
{
	for (int i = 0; i < PIXELS_X;i++)
			{
				for (int j = 0; j < PIXELS_Y; j++)
				{
					PREV_LCD_DISPLAY[i][j]='4';
					LCD_DISPLAY[i][j]='0';
				}

			}
}
void fill_lcd_display_array()
{
	char this_obj = '0';
	for (int i = 0; i < PIXELS_X;i++)
	{
		for (int j = 0; j < PIXELS_Y; j++)
		{
			PREV_LCD_DISPLAY[i][j]=LCD_DISPLAY[i][j];
			LCD_DISPLAY[i][j] = this_obj;
		}
	
	}
	ball_display();
	brick_display();
	bat_display();
}
void GO_OUTPUT()
{
	OUTPUT_SIZE=0;
	char buf[4];
	int i,j;
	 for(j=0;j<PIXELS_Y;j++)
	  	  {
	  		  for(i=0;i<PIXELS_X;i++)
	  		  {
				if(PREV_LCD_DISPLAY[i][j]!=LCD_DISPLAY[i][j])
				{
					buf[0]=i+1;
					buf[1]=j+1;
					buf[2]=LCD_DISPLAY[i][j];
					buf[3]='\0';
					UART_SendString(buf);
				}
			}

		}
	buf[0]='e';
	buf[1]='e';
	buf[2]='e';
	buf[3]='\0';
	UART_SendString(buf);
}

void FIRST_OUTPUT()
{
	   char c[4];
	   int i,j;
	   for(j=0;j<PIXELS_Y;j++)
	   	  {
	   		  for(i=0;i<PIXELS_X;i++)
	   		  {
	   			 c[0]=i+1;
	 			 c[1]=j+1;
	   			 c[2]=LCD_DISPLAY[i][j];
	   			 c[3]='\0';
	   			UART_SendString(c);
	   		  }
	   	  }
	   c[0]='e';
	   c[1]='e';
	   c[2]='e';
	   c[3]='\0';
	    UART_SendString(c);
}
void ONLY_BAT_OUTPUT(int prev_batX)
{
	char c[4];
	int width;
	if(prev_batX-bat.locationX < 0)
	{
		width=bat.locationX-prev_batX;
	}
	else
	{
		width=prev_batX-bat.locationX;
	}

	width+=bat.width;
	int start;
	if(prev_batX<bat.locationX)
	{
		start=prev_batX;
	}
	else
	{
		start=bat.locationX;
	}
	for (int i, j = bat.locationY; j < bat.locationY+bat.height;j++)
		{
			for(i=start;i<start+width;i++)
			{
			 c[0]=i+1;
			 c[1]=j+1;
			 c[2]=LCD_DISPLAY[i][j];
			 c[3]='\0';
			 UART_SendString(c);
			}
		}

	c[0]='e';
	c[1]='e';
	c[2]='e';
	c[3]='\0';
	UART_SendString(c);
}
void game_over()
{
	ball_display_en=0;
	fill_lcd_display_array();
	GO_OUTPUT();

	char buf[4];
	buf[0]='o';
	buf[1]='o';
	buf[2]='o';
	buf[3]='\0';
	UART_SendString(buf);
	while(1)
	{
		if(lastReceivedUartCommand=='r')
			{
				break;
			}
	}
}
void game_over_PCB()
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
}


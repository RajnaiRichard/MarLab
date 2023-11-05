#include "Ball.h"

Balls ball;
int ball_display_en=1;
void ball_init()
{
	Balls temp ={ default_ball_locationX,default_ball_locationY,default_ball_moveX,default_ball_moveY, default_ball_radius };
	ball = temp;
	ball_display_en=1;
}
void move_Ball()
{
	ball.locationX += ball.moveX;
	ball.locationY += ball.moveY;

    //bal falr�l visszapattan� labda
	if (ball.locationX - ball.radius < 0)
	{
		ball.moveX = -ball.moveX;
		ball.locationX = -(ball.locationX - ball.radius);
	}
    // jobb falr�l visszapattan� labda
    if (ball.locationX + ball.radius> PIXELS_X)
    {
        ball.moveX = -ball.moveX;
        ball.locationX = PIXELS_X - (ball.locationX + ball.radius - PIXELS_X);
    }
    // fels� falr�l visszapattan� labda
    if (ball.locationY - ball.radius < 0)
    {
        ball.moveY = -ball.moveY;
        ball.locationY = -(ball.locationY - ball.radius);
    }
    
    //  �t�r�l visszapattan� labda 
    if ((ball.locationY + ball.radius) == (PIXELS_Y - bat.height) && ball.locationX >= bat.locationX && ball.locationX <= bat.locationX + bat.width)
    {
        ball.moveY = -ball.moveY;
    }

    // t�gl�r�l visszapattan� labda
    for (int i, j = 0; j < default_brick_row;j++)
    {
    	for(i=0;i<default_brick_col;i++)
    	{
    		if (bricks_on_map[i][j].active)
    		{
    			brick_collision(i,j);
    		}
    	}
    }
    if(ball.locationY + ball.radius>PIXELS_Y)
    {
    	//game_over();
    	game_over_PCB();

    }
}

int brick_collision(int i,int j)
{
    //jobbr�l �tk�zik a t�gl�ba
    // akkor ha a bal sz�l�n�l kisebb az X koordin�t�ja, az el�z� �llapotban nagyobb volt �s ugyan abban a magass�gban van
    if (ball.locationX - ball.radius > bricks_on_map[i][j].locationX+bricks_on_map[i][j].width && ball.locationX - ball.radius + ball.moveX <= bricks_on_map[i][j].locationX + bricks_on_map[i][j].width && ball.locationY - ball.radius <= bricks_on_map[i][j].locationY+bricks_on_map[i][j].height && ball.locationY + ball.radius>=bricks_on_map[i][j].locationY )
    {
    	bricks_on_map[i][j].active = 0;
        ball.moveX = -ball.moveX;
        ball.locationX = bricks_on_map[i][j].locationX + bricks_on_map[i][j].width + (bricks_on_map[i][j].locationX + bricks_on_map[i][j].width - (ball.locationX - ball.radius));
        return 1;
    }

    //balr�l �tk�zik a t�gl�ba
    if (ball.locationX + ball.radius < bricks_on_map[i][j].locationX && ball.locationX + ball.radius + ball.moveX>= bricks_on_map[i][j].locationX && ball.locationY - ball.radius <= bricks_on_map[i][j].locationY + bricks_on_map[i][j].height && ball.locationY + ball.radius>=bricks_on_map[i][j].locationY)
    {
    	bricks_on_map[i][j].active = 0;
        ball.moveX = -ball.moveX;
        ball.locationX = bricks_on_map[i][j].locationX - (ball.locationX + ball.radius - bricks_on_map[i][j].locationX);
        return 1;
    }

    //alulr�l �tk�zik a t�gl�ba
    if (ball.locationY - ball.radius > bricks_on_map[i][j].locationY + bricks_on_map[i][j].height && ball.locationY - ball.radius + ball.moveY <= bricks_on_map[i][j].locationY + bricks_on_map[i][j].height && ball.locationX - ball.radius <= bricks_on_map[i][j].locationX + bricks_on_map[i][j].width && ball.locationX + ball.radius>=bricks_on_map[i][j].locationX)
    {
    	bricks_on_map[i][j].active = 0;
        ball.moveY = -ball.moveY;
        ball.locationY = bricks_on_map[i][j].locationY + bricks_on_map[i][j].height  + ( bricks_on_map[i][j].locationY + bricks_on_map[i][j].height - (ball.locationY - ball.radius));
        return 1;
    }

    //fel�lr�l �tk�zik a t�gl�ba
    if (ball.locationY + ball.radius < bricks_on_map[i][j].locationY&& ball.locationY + ball.radius + ball.moveY >= bricks_on_map[i][j].locationY  && ball.locationX - ball.radius <= bricks_on_map[i][j].locationX + bricks_on_map[i][j].width && ball.locationX + ball.radius>=bricks_on_map[i][j].locationX)
    {
    	bricks_on_map[i][j].active = 0;
        ball.moveY = -ball.moveY;
        ball.locationY = bricks_on_map[i][j].locationY - ( (ball.locationY + ball.radius) - bricks_on_map[i][j].locationY );
        return 1;
    }
    return 0;
}

void ball_display()
{
	if(ball_display_en)
	{
    char this_obj = '2';
    for (int j = -default_ball_radius; j <= default_ball_radius;j++)
    {
        LCD_DISPLAY[ball.locationX][ball.locationY + j] = this_obj;

    }
    for (int i = -default_ball_radius; i <= default_ball_radius; i++)
    {

        LCD_DISPLAY[ball.locationX + i][ball.locationY] = this_obj;

    }
	}
}

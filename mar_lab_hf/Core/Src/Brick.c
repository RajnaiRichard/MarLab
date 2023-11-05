#include "Brick.h"

Bricks bricks_on_map[default_brick_col][default_brick_row];

void generate_Bricks()
{
	for (int i = 0,j=0; j < default_brick_row;)
	{
		bricks_on_map[i][j].locationX= default_brick_dist_from_side + default_brick_width *i + default_brick_dist_from_brick * i;
		bricks_on_map[i][j].locationY = default_brick_dist_from_side + default_brick_height * j + default_brick_dist_from_brick * j;
		bricks_on_map[i][j].width = default_brick_width;
		bricks_on_map[i][j].height = default_brick_height;
		bricks_on_map[i][j].active = 1;
			i++;
			if (i == default_brick_col)
			{
				i = 0;
				j++;
			}
	}
}

void brick_display()
{
	 int this_obj= '3';
	for (int i = 0, j = 0; j < default_brick_row;)
	{
		if (bricks_on_map[i][j].active)
		{
			for (int k = 0, p = 0; p < bricks_on_map[i][j].height;)
			{
				LCD_DISPLAY[bricks_on_map[i][j].locationX + k][bricks_on_map[i][j].locationY + p] = this_obj;

				k++;
				if (k == bricks_on_map[i][j].width)
				{
					k = 0;
					p++;
				}
			}
		}

		i++;
		if (i == default_brick_col)
		{
			i = 0;
			j++;
		}
	}
}

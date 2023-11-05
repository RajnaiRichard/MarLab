#pragma once
#ifndef BRICK_H
#define BRICK_H
#include "Map.h"
#include "Display.h"
#include "Ball.h"
// 15 pixel balr�l + 9*10=90pixel t�ga + 1*8=8 pixel minden t�gla k�z�tt +15 pixel jobbr�l 
#define default_brick_dist_from_side 15
#define default_brick_dist_from_brick 1
#define default_brick_height 5
#define default_brick_width 10
#define default_brick_row 4
#define default_brick_col 9

typedef struct Bricks {
	int locationX;
	int locationY;
	int width;
	int height;
	int active;
}Bricks;

extern Bricks bricks_on_map[default_brick_col][default_brick_row];

void generate_Bricks();
void brick_display();
#endif

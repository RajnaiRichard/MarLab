#pragma once
#ifndef BAT_H
#define BAT_H
#include "Ball.h"
#include "Map.h"
#include "Display.h"
#define default_bat_location 0
#define default_bat_moveX 2
#define default_bat_height 2
#define default_bat_width 20

typedef struct {
	int locationX;
	int locationY;
	int width;
	int height;
	int moveX;
}Bats;

extern Bats bat;

void check_bat_move(int);
void bat_display();
void move_Bat(int);
void move_and_only_bat_display(int);
#endif

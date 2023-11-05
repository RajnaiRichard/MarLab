#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H
#include "Map.h"
#include "Ball.h"
#include "Bat.h"
#include "Brick.h"
enum objects {empty_space,bat_space,ball_space,brick_space};

extern char LCD_DISPLAY[PIXELS_X][PIXELS_Y];
extern char OUTPUT[800];
extern int OUTPUT_SIZE;
void reset_lcd_display();
void fill_lcd_display_array();
void GO_OUTPUT();
void FIRST_OUTPUT();
void ONLY_BAT_OUTPUT();
void game_over();
#endif

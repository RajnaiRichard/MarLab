#pragma once
#ifndef BALL_H
#define BALL_H

#include "Bat.h"
#include "Brick.h"
#include "Map.h"
#include "Display.h"
#define default_ball_locationX 10
#define default_ball_locationY 50
#define default_ball_moveX -1
#define default_ball_moveY -1
#define default_ball_radius 1
//   A labda 1es sug�rral
//           *
//         * * *
//           *
typedef struct {
	int locationX;
	int locationY;
	int moveX;
	int moveY;
	int radius;
}Balls;

extern Balls ball;
extern int ball_display_en;
void ball_init();
void move_Ball();
int brick_collision(int,int);
void ball_display();
#endif

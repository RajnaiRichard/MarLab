/*
 * mainloop.h
 *
 *  Created on: 2021. ápr. 27.
 *      Author: User
 */

#ifndef SRC_MAINLOOP_H_
#define SRC_MAINLOOP_H_
#include "Ball.h"
#include "Map.h"
#include "Display.h"
#include "Bat.h"
#include "Brick.h"
#include "bsp_uart.h"
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"


void mainloop_init();
void mainloop_go();
void mainloop_init_PCB();
void mainloop_go_PCB();

#endif /* SRC_MAINLOOP_H_ */

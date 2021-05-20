#ifndef GAME_H
#define GAME_H

#include "queue.h"
#include "random.h"
#include "utils.h"
#include "clcd.h"
#include "mytype.h"
#include "keypad.h"
#include "dot.h"
#include "save.h"
#include "led.h"
#define OBSTACLE_NUMBERS_OF_CASE 3

int make_obstacle(void);	// create obstacle function
void create_obstacles(Queue* q, int stage);
void write_obstacles(Queue* q);
error_t gameProgress();
error_t mainGame();
#endif
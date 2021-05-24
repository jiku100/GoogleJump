#ifndef GAME_H
#define GAME_H

#include <math.h>

#include "queue.h"
#include "random.h"
#include "utils.h"
#include "clcd.h"
#include "mytype.h"
#include "keypad.h"
#include "dot.h"
#include "save.h"
#include "led.h"
#include "fnd.h"

#define OBSTACLE_NUMBERS_OF_CASE 3

int make_obstacle(void);	// create obstacle function
void create_obstacles(Queue* q, int stage);
void write_obstacles(Queue* q);
int getSpeed(int stage);
void printGameStart();
void printStage(int stage);
void printStageClear();
void printGameEnd();
void printCompleteSave();
state_t gameProgress(Queue* obstacles, Player* p, int stage, int speed, int* score, int* life);
error_t mainGame();

#endif
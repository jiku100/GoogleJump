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

int make_obstacle(void);	// create obstacle
void create_obstacles(Queue* q, int stage); // create obstacle queue
void write_obstacles(Queue* q); // write obstacles in clcd
int getSpeed(int stage);    // get Speed accoring stage
void printGameStart();      // print Game start message in clcd
void printStage(int stage); // print Stage message in clcd
void printStageClear();     // print Stage clear message in clcd
void printGameEnd();        // print Game end message in clcd
void printCompleteSave();   // print Save complete message in clcd
state_t gameProgress(Queue* obstacles, Player* p, int stage, int speed, int* score, int* life); // Stage game process
error_t mainGame();     // Main game process

#endif
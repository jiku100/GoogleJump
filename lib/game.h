#ifndef GAME_H
#define GAME_H

#include "queue.h"
#include "random.h"
#include "utils.h"
#include "clcd.h"

#define OBSTACLE_NUMBERS_OF_CASE 3

int make_obstacle(void);	// create obstacle function
void create_obstacles(Queue* q, int stage);
void write_obstacles(Queue* q);

#endif
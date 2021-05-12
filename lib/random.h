#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <time.h>

#define OBSTACLE_NUMBERS_OF_CASE 3

void init_seed(void);	// initialize seed
int rand_range(int start, int finish); // rand range [start, finish)
int create_obstacle(void);	// create obstacle function

#endif

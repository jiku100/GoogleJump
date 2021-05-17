#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <time.h>

void init_seed(void);	// initialize seed
int rand_range(int start, int finish); // rand range [start, finish)

#endif

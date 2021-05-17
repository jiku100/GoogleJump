#include "random.h"

void init_seed(void){
	srand(time(NULL));
}

int rand_range(int start, int finish){
	int number_of_rand = finish - start;
	int num = (rand() % number_of_rand) + start;
	return num;
}
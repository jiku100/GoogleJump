#include "random.h"

void init_seed(void){
	srand(time(NULL));
}

int rand_range(int start, int finish){
	int number_of_rand = finish - start;
	int num = (rand() % number_of_rand) + start;
	return num;
}

int create_obstacle(void){
	static int remain_flat_obstacle = 0;

	if(remain_flat_obstacle > 0){
		remain_flat_obstacle--;
		return 0;
	}
	else{
		int obstacle = rand() % OBSTACLE_NUMBERS_OF_CASE;
		if(obstacle > 0){
			remain_flat_obstacle = rand_range(4, 7);
		}
		return obstacle;
	}
}

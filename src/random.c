#include "random.h"

void init_seed(void){
	srand(time(NULL));
}

/* 일정 범위 안의 숫자 랜덤 생성 함수 */
int rand_range(int start, int finish){
	int number_of_rand = finish - start;	// 랜덤 숫자 개수
	int num = (rand() % number_of_rand) + start;	
	return num;
}
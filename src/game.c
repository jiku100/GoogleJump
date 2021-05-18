#include "game.h"

int make_obstacle(void){
	return rand() % OBSTACLE_NUMBERS_OF_CASE;
}

void create_obstacles(Queue* q, int stage){
    int remain_zero = 4;
    int i = 0;
    int obstacle;
    int offset;

    for(i; i < 40; i++){
        if(remain_zero > 0){
            enqueue(q, 0);
            remain_zero--;
        }
        else{
            obstacle = make_obstacle();
            if(obstacle > 0){
                offset = max(7 - stage/2, 1);               
                remain_zero = rand_range(offset, offset+2);
            }
            enqueue(q, obstacle);
        }
    }
}

void write_obstacles(Queue* q){
    int cmd = 0;
    int obstacle = 0;
    int size = q->size;

    for(cmd; cmd < size; cmd){
        obstacle = dequeue(q);
        switch (obstacle)
        {
        case 0:
            clcd_set_DDRAM(0x40 + cmd);
            clcd_write_data('.');
            cmd++;
            break;
        case 1:
            clcd_set_DDRAM(0x40 + cmd);
            clcd_write_data('@');
            cmd++;
            break;
        case 2:
            clcd_set_DDRAM(0x00 + cmd);
            clcd_write_data('#');
            clcd_set_DDRAM(0x40 + cmd);
            clcd_write_data('.');
            cmd++;
        default:
            break;
        }
    }
}
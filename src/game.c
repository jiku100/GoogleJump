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

error_t gameProgress(Queue* obstacles, Player* p, int stage, int speed) {
	create_obstacles(obstacles, stage);
    int front = obstacles->front;
    int rear = obstacles->rear;
	write_obstacles(obstacles);
    led_set(p->life);
	usleep(1000000);
	int shift = 0;
    int key_count, key_value;
    int action = 0;
	for(shift; shift < 40; shift++){
        front = (front + 1) % MAX_SIZE;
        dot_clear();
        if(kbhit()){
            key_count = keyboard_read(&key_value);
            switch (key_value)
            {
            case 5:
                dot_write(2);
                break;
            case 9:
                dot_write(3);
                break;
            }
        }
        else{
            if(obstacles->data[front] == 1 || obstacles->data[front] == 2){
                dot_write(4);
                p->life--;
                led_set(p->life);
            }
            else{
                dot_write(action % 2);
                action++;
            }
        }
		clcd_shift(1, 0);	
		usleep(1000000);
	}
	return SUCCESS;
}

error_t mainGame(){
    Queue* obstacles = init_queue();
    Player* head = NULL;
    Player* p = search_player(head, "SeokGyeong");
    gameProgress(obstacles, p, 10, 1);
    usleep(1000000);
    clcd_clear_display();
    usleep(1000000);
    gameProgress(obstacles, p, 10, 2);

}
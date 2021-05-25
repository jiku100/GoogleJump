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

int getSpeed(int stage){
    int speed = 100000 * (powf(4, powf(0.85, stage)) + 2);
    return speed;
}

void printGameStart(){
    char* str = "  Game Start!! ";
    clcd_set_DDRAM(0x00);
    clcd_write_string(str);
    usleep(0);
}

void printStage(int stage){
    static char str[15] = "    Stage 01  ";
    str[10] = stage/10 + '0';
    str[11] = stage%10 + '0';
    clcd_set_DDRAM(0x00);
    clcd_write_string(str);
    usleep(0);
}

void printStageClear(){
    char* str = "  Stage Clear!! ";
    clcd_set_DDRAM(0x00);
    clcd_write_string(str);
    usleep(0);
}

void printGameEnd(){
    char* str = "   Game End!! ";
    clcd_set_DDRAM(0x00);
    clcd_write_string(str);
    usleep(0);
}

void printCompleteSave(){
    char* str = " Save Complete!! ";
    clcd_set_DDRAM(0x00);
    clcd_write_string(str);
    usleep(0);
}

state_t gameProgress(Queue* obstacles, Player* p, int stage, int speed, int* score, int* life) {
	create_obstacles(obstacles, stage);
    int front = obstacles->front;
    int rear = obstacles->rear;
	write_obstacles(obstacles);
    fnd_dec_number(*score);
    led_set(*life);
	usleep(1000000);
	int shift = 0;
    int key_count, key_value;
    int action = 0;
	for(shift; shift < 40; shift++){
        front = (front + 1) % MAX_SIZE;
        dot_clear();
        if(kbhit()){
            key_count = keyboard_read(&key_value);
            switch (obstacles->data[front])
            {
            case 1:
                if(key_value == 5){
                    dot_write(5);
                    *score += (80 + 20 * stage);
                    fnd_dec_number(*score);
                }
                else{
                    dot_write(4);
                    (*life)--;
                    led_set(*life);
                    if(*life == 0){
                        return FAIL;
                    }
                }
                break;

            case 2:
                if(key_value == 9){
                    dot_write(9);
                    *score += (80 + 20 * stage);
                    fnd_dec_number(*score);
                }
                else{
                    dot_write(4);
                    (*life)--;
                    led_set(*life);
                    if(*life == 0){
                        return FAIL;
                    }
                }

            default:
                if(key_value == 5 || key_value == 9){
                    dot_write(key_value);
                }
                else{
                    dot_write(action % 2);
                    action++;
                }        
                break;
            }  
        }
        else{
            if(obstacles->data[front] == 1 || obstacles->data[front] == 2){
                dot_write(4);
                (*life)--;
                led_set(*life);
                if(*life == 0){
                        return FAIL;
                }
            }
            else{
                dot_write(action % 2);
                action++;
            }
        }
		clcd_shift(1, 0);	
		usleep(speed);
	}
	return CLEAR;
}

error_t mainGame(char* name){
    Queue* obstacles = init_queue();
    Player* head = NULL;
    head = read_savefile();
    Player* p = NULL;
    if (head == NULL){
        p = create_node(name, 0, 0);
        head = append(head, p);
    }
    else{
        p = search_player(head, name);
    }

    int stage = 1;
    int score = 0;
    int life = 4;
    printGameStart();
    usleep(2000000);
    for(stage;;stage++){
        clcd_clear_display();
        printStage(stage);
        usleep(1500000);
        clcd_clear_display();
        if(gameProgress(obstacles, p, stage, getSpeed(stage), &score, &life) == FAIL){
            break;
        }
        clcd_clear_display();
        printStageClear();
        usleep(1000000);
    }
    usleep(1000000);
    clcd_clear_display();
    printGameEnd();
    if(p->stage < stage){
        setStage(p, stage);
    }
    if(p->score < score){
        setScore(p, score);
    }
    write_savefile(head);
    usleep(1000000);
    printCompleteSave();
    usleep(1000000);
}

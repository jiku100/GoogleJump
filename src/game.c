#include "game.h"

/* 장애물 생성 함수 */
int make_obstacle(void){
	return rand() % OBSTACLE_NUMBERS_OF_CASE;   // 0, 1, 2에 해당하는 장애물 생성
}

/* 장애물을 Queue에 저장하는 함수 */
void create_obstacles(Queue* q, int stage){
    int remain_zero = 4;    // 기본적으로 4개의 평지는 저장
    int i = 0;
    int obstacle;
    int offset;

    for(i; i < 40; i++){    // 총 40개의 위치에 저장
        if(remain_zero > 0){    // 저장할 평지의 개수가 남아있으면
            enqueue(q, 0);      // 평지를 저장
            remain_zero--;
        }
        else{   // 저장할 평지가 없는 경우
            obstacle = make_obstacle(); // 장애물을 생성하고
            if(obstacle > 0){   // 장애물이 평지가 아니면
                offset = max(7 - stage/2, 1);  // 스테이지별 기본적으로 장애물 사이의 평지 개수 설정
                remain_zero = rand_range(offset, offset+2); // 설정된 평지 개수를 기반으로 앞으로 생성할 평지 개수 설정
            }
            enqueue(q, obstacle);
        }
    }
}

/* clcd에 장애물을 그리는 함수 */
void write_obstacles(Queue* q){
    int cmd = 0;
    int obstacle = 0;
    int size = q->size;

    for(cmd; cmd < size; cmd){  // Queue에 저장된 개수만큼
        obstacle = dequeue(q);  // 하나를 빼고
        switch (obstacle)
        {
        case 0: // 평지인 경우는 
            clcd_set_DDRAM(0x40 + cmd); // 아랫 줄에 해당하는 위치에 . 그리기
            clcd_write_data('.');
            cmd++;
            break;
        case 1: // 점프 장애물인 경우
            clcd_set_DDRAM(0x40 + cmd); // 아랫 줄에 해당하는 위치에 @ 그리기
            clcd_write_data('@');
            cmd++;
            break;
        case 2: // 숙이기 장애물인 경우
            clcd_set_DDRAM(0x00 + cmd); // 윗 줄에 해당하는 위치에 # 그리기
            clcd_write_data('#');
            clcd_set_DDRAM(0x40 + cmd); // 아랫 줄에는 . 그리기
            clcd_write_data('.');
            cmd++;
        default:
            break;
        }
    }
}

/* 스테이지 별 속도를 계산하는 함수 */
int getSpeed(int stage){  
    int speed = 100000 * (powf(4, powf(0.85, stage)) + 2);  // Speed = 100000 * (4^(0.85^x) + 2) 자세한 것은 PPT 참고
    return speed;
}

/* 게임 시작 출력 함수 */
void printGameStart(){
    char* str = "  Game Start!! ";
    clcd_set_DDRAM(0x00);
    clcd_write_string(str);
    usleep(0);
}

/* 스테이지 출력 함수 */
void printStage(int stage){
    static char str[15] = "    Stage 01  ";
    str[10] = stage/10 + '0';
    str[11] = stage%10 + '0';
    clcd_set_DDRAM(0x00);
    clcd_write_string(str);
    usleep(0);
}

/* 스테이지 클리어 출력 함수 */
void printStageClear(){
    char* str = "  Stage Clear!! ";
    clcd_set_DDRAM(0x00);
    clcd_write_string(str);
    usleep(0);
}

/* 게임 끝 출력 함수 */
void printGameEnd(){
    char* str = "   Game End!! ";
    clcd_set_DDRAM(0x00);
    clcd_write_string(str);
    usleep(0);
}

/* 저장 성공 출력 함수 */
void printCompleteSave(){
    char* str = " Save Complete!! ";
    clcd_set_DDRAM(0x00);
    clcd_write_string(str);
    usleep(0);
}

/* 하나의 스테이지 진행 과정 함수 */
state_t gameProgress(Queue* obstacles, Player* p, int stage, int speed, int* score, int* life) {
	create_obstacles(obstacles, stage); // 스테이지 난이도에 따른 장애물 생성
    int front = obstacles->front;
    int rear = obstacles->rear;
	write_obstacles(obstacles); // clcd에 미리 장애물을 write
    fnd_dec_number(*score); // 현재 스코어 fnd 출력
    led_set(*life);         // 현재 목숨 led에 출력
	usleep(1000000);
	int shift = 0;
    int key_count, key_value;
    int action = 0;
	for(shift; shift < 40; shift++){    // 총 40번의 shift를 통해 스테이지 진행
        front = (front + 1) % MAX_SIZE;
        dot_clear(); 
        if(kbhit()){    // 키가 입력이 되었으면
            key_count = keyboard_read(&key_value);  // 해당 키의 값과 개수를 알아옴
            switch (obstacles->data[front])
            {
            case 1: // 장애물이 점프 장애물일 때
                if(key_value == 5){ // 키의 입력이 w인 경우
                    dot_write(5);   // 점프하는 모습 dot에 출력
                    *score += (80 + 20 * stage);    // 점수 증가
                    fnd_dec_number(*score); // fnd에 점수 출력
                }
                else{   // 만약 다른 키라면
                    dot_write(4);   // 목숨이 깍이는 모습 dot에 출력
                    (*life)--;  // 목숨 감소
                    led_set(*life); // led에 목숨 출력
                    if(*life == 0){ // 목숨이 0이 되면 게임 종료
                        return FAIL;
                    }
                }
                break;

            case 2: // 장애물이 숙이기 장애물인 경우
                if(key_value == 9){ // 키의 입력이 s인 경우, 이하의 경우는 위와 동일
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

            default:    // 장애물이 없는 경우
                if(key_value == 5 || key_value == 9){
                    dot_write(key_value);   // dot에 모습 출력
                }
                else{
                    dot_write(action % 2);  // 달리는 모습 출력
                    action++;
                }        
                break;
            }  
        }
        else{   // 키의 입력이 없는 경우
            if(obstacles->data[front] == 1 || obstacles->data[front] == 2){ // 장애물이 존재하는 경우
                dot_write(4);   // 목숨 깍이는 모습 출력
                (*life)--;      // 목숨 감소
                led_set(*life); 
                if(*life == 0){ // 목숨 0인 경우 게임 종료
                        return FAIL;
                }
            }
            else{   // 장애물이 없으면 달리는 모습 출력
                dot_write(action % 2);
                action++;
            }
        }
		clcd_shift(1, 0);   // 다음 장애물로 이동
		usleep(speed);  // speed 만큼 대기
	}
	return CLEAR;   // 스테이지 클리어 한 경우 CLEAR 반환
}

/* 전체 게임 진행 함수 */
error_t mainGame(char* name){   
    Queue* obstacles = init_queue();    // 장애물을 저장할 Queue 생성
    Player* head = NULL;
    head = read_savefile(); // head에 Savefile로부터 불러온 player info 저장
    Player* p = NULL;
    if (head == NULL){  // 만약 savefile이 비었다면
        p = create_node(name, 0, 0);    // name을 가지는 새로운 node 생성
        head = append(head, p); // head에 추가
    }
    else{   // savefile이 비지 않았으면
        p = search_player(head, name);  // head로부터 name을 가지느 node 찾아서 해당 위치 p에 저장
    }

    int stage = 1;  // 처음 스테이지 init
    int score = 0;  // 처음 점수 init
    int life = 4;   // 처음 목숨 init
    printGameStart();
    usleep(2000000);
    for(stage;;stage++){    // 무한으로 stage는 증가함
        clcd_clear_display();
        printStage(stage);
        usleep(1500000);
        clcd_clear_display();
        if(gameProgress(obstacles, p, stage, getSpeed(stage), &score, &life) == FAIL){  // stage가 만약 클리어 되지 않았으면
            break;  // 무한 루프를 종료함
        }
        clcd_clear_display();
        printStageClear();
        usleep(1000000);
    }
    // 게임이 끝나면 p node에 stage와 score를 setting
    usleep(1000000);
    clcd_clear_display();
    printGameEnd();
    if(p->stage < stage){
        setStage(p, stage);
    }
    if(p->score < score){
        setScore(p, score);
    }
    // 새로운 savefile를 생성
    write_savefile(head);
    usleep(1000000);
    printCompleteSave();
    usleep(1000000);
    // 게임 종료
}

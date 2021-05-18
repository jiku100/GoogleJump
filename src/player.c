#include "player.h"

/****************** initiation *******************/
Player* init_player(){
    Player* p = (Player*)malloc(sizeof(Player));
    strcpy(p->name, "None");
    p->stage = 0;
    p->score = 0;
    p->life = 0;
    return p;
}

/******************  Setter **********************/
void setName(Player* p, char name[]){
    strcpy(p->name, name);
}
void setStage(Player* p, int stage){
    p->stage = stage;
}
void setScore(Player* p, int score){
    p->score = score;
}
void setLift(Player* p, int life){
    p->life = life;
}
void setAll(Player* p, char name[], int stage, int score, int life){
    setName(p, name);
    setStage(p, stage);
    setScore(p, score);
    setLift(p, life);
}

/******************  Getter **********************/
char* getName(Player* p){
    char *str = malloc(sizeof(char) * 20);
    strcpy(str, p->name);
    return str;
}
int getStage(Player* p){
    return p->stage;
}
int getScore(Player* p){
    return p->score;
}
int getLift(Player* p){
    return p->life;
}

/****************** Actions **********************/
void liftDown(Player* p){
    p->life--;
}
void addScore(Player* p, int score){
    p->score += score;
}
void nextScore(Player* p){
    p->stage++;
}
void printPlayerInfo(Player* p){
    printf("\nName: %s\n", p->name);
    printf("Stage: %d\n", p->stage);
    printf("Score: %d\n", p->score);
    printf("Life: %d\n", p->life);    
}
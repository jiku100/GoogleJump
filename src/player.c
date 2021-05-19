#include "player.h"

/****************** initiation *******************/
Player* init_player(){
    Player* p = (Player*)malloc(sizeof(Player));
    strcpy(p->name, "None");
    p->stage = 0;
    p->score = 0;
    p->life = 0;
    p->next = NULL;
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
void setLife(Player* p, int life){
    p->life = life;
}
void setAll(Player* p, char name[], int stage, int score, int life){
    setName(p, name);
    setStage(p, stage);
    setScore(p, score);
    setLife(p, life);
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
int getLife(Player* p){
    return p->life;
}

/****************** Actions **********************/
void lifeDown(Player* p){
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

/**************** Linked List ********************/
Player* create_node(char name[], int stage, int score, int life){
    Player* node = (Player*)malloc(sizeof(Player));
	setName(node, name);
    setStage(node, stage);
    setScore(node, score);
    setLife(node, life);
    node->next = NULL;
	return node;
}

Player* append(Player* head, Player* node){
    Player* nextNode = head;

	if (head == NULL) {
		head = node;
		return head;
	}

	while (nextNode->next != NULL) {
		nextNode = nextNode->next;
	}

	nextNode->next = node;

	return head;
}

void printPlayerList(Player* head){
    if (head == NULL) {
		printf("There is no node!!\n");
	}
	else {
		while(head != NULL)
		{
			printf("%s\t%d\t%d\t%d\n", head->name, head->stage, head->score, head->life);
			head = head->next;
		}
	}
}
#include "player.h"

/****************** initiation *******************/
Player* init_player(){
    Player* p = (Player*)malloc(sizeof(Player));    // Player 구조체만큼 동적 할당
    strcpy(p->name, "None");
    p->stage = 0;
    p->score = 0;
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
void setAll(Player* p, char name[], int stage, int score, int life){
    setName(p, name);
    setStage(p, stage);
    setScore(p, score);
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

/****************** Actions **********************/
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
}

/**************** Linked List ********************/
Player* create_node(char name[], int stage, int score){
    Player* node = (Player*)malloc(sizeof(Player));
	setName(node, name);
    setStage(node, stage);
    setScore(node, score);
    node->next = NULL;
	return node;
}

/* Linked List에 node 추가 함수 */
Player* append(Player* head, Player* node){
    Player* nextNode = head;

	if (head == NULL) { // head에 Null이면
		head = node;    // head가 Node가 되고
		return head;    // head 반환
	}

	while (nextNode->next != NULL) {    // 만약 현재 노드의 Next가 NULL이 아니면
		nextNode = nextNode->next;  // 다음으로 이동
	}

	nextNode->next = node;  // 현재 node의 next에 새로운 node 추가

	return head;
}

void printPlayerList(Player* head, FILE* fp){   // 스트림을 입력 받아 해당 스트림에 출력
    if (head == NULL) {
		printf("There is no node!!\n");
	}
	else {
		while(head != NULL)
		{
			fprintf(fp, "%-17s%3d%13d\n", head->name, head->stage, head->score);
			head = head->next;
		}
	}
}
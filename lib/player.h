#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Player{
    char name[20];
    int stage;
    int score;
    struct Player* next;
} Player;

/****************** initiation *******************/
Player* init_player();  // Init Player class

/******************  Setter **********************/
void setName(Player* p, char name[]);   // Set player name
void setStage(Player* p, int stage);    // Set player stage
void setScore(Player* p, int score);    // Set player score
void setAll(Player* p, char name[], int stage, int score, int life);    // Set All 

/******************  Getter **********************/
char* getName(Player* p);   // Get player name
int getStage(Player* p);    // Get player stage
int getScore(Player* p);    // Get player score

/****************** Actions **********************/
void lifeDown(Player* p);   // Life down
void addScore(Player* p, int score);    // Add score
void nextScore(Player* p);  // Next stage
void printPlayerInfo(Player* p);    // Print Player info

/**************** Linked List ********************/
Player* create_node(char name[], int stage, int score);   // create Node
Player* append(Player* head, Player* node); // append Node
void printPlayerList(Player* head, FILE* fp); // print player list;
#endif
#ifndef SAVE_H_
#define SAVE_H_

#include <stdio.h>
#include "player.h"
#include <unistd.h>
#include "mytype.h"
#include <string.h>

Player* read_savefile();
error_t write_savefile(Player* head);
Player* search_player(Player* head, char* name);
void makeSaveDir();



#endif
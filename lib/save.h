#ifndef SAVE_H_
#define SAVE_H_

#include <stdio.h>
#include "player.h"
#include <unistd.h>
#include "mytype.h"
#include <string.h>

Player* read_savefile();        // Read players info from savefile
error_t write_savefile(Player* head);   // Write players info in savefile
Player* search_player(Player* head, char* name);    // Find certain player info from Linked List
void makeSaveDir(); // Make Save directory



#endif
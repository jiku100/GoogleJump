#include "save.h"

Player* read_savefile(){
    char* originalSaveFilePath = "./savefile/savefile.txt";
    FILE* in;
    if((in = fopen(originalSaveFilePath, "r")) == NULL){
        return NULL;
    }
    Player* head = NULL;
    char line[60];
    char name[20];
    int stage, score;

    fgets(line, 60, in);
    fgets(line, 60, in);
    while (!feof(in)) {
		sscanf(line, "%17s%3d%13d", name, &stage, &score);
		head = append(head, create_node(name, stage, score));
        fgets(line, 60, in);
	}
    return head;
}

error_t write_savefile(Player* head){
    char* tempSaveFilePath = "./savefile/tmp.txt";
    FILE* out;

    if((out = fopen(tempSaveFilePath, "w")) == NULL){
        printf("Can't open %s file\n", tempSaveFilePath);
        exit(1);
    }
	fprintf(out, "%7s%15s%14s\n", "Name", "Stage", "Score");
    printPlayerList(head, out);
    fclose(out);
    system("mv ./savefile/tmp.txt ./savefile/savefile.txt");
}

void makeSaveDir(){
    int r = 0;
    r = access("./savefile", F_OK);
    if(r<0){
        system("mkdir savefile");
    }
}

Player* search_player(Player* head, char name[]){
    if (head == NULL) {
	    head = append(head, create_node(name, 0, 0));
        return head;
	}
	else {
        do
        {
            if(strcmp(head->name, name) == 0){
                return head;
            }
            if(head->next == NULL){
                head = append(head, create_node(name, 0, 0));
                head = head->next;
                return head;
            }
            else{
                head = head->next;
            }
        } while (head != NULL);
	}
}
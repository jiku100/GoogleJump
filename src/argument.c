#include "argument.h"

error_t setPlayer(Player** p, int argc, char* argv[]){
    if(argc == 1){
        return ERROR;
    }
    else if(argc == 2){
        *p = init_player();
        setName(*p, argv[1]);
        return SUCCESS;
    }
}
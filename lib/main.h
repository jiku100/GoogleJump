#ifndef	MAIN_H
#define	MAIN_H 

#include <stdio.h>		// printf(), scanf(), fprintf()
#include <fcntl.h>		// open()
#include <unistd.h>		// close(), off_t
#include <sys/mman.h>	// mmap(), munmap()
#include <stdlib.h> 	// exit()
#include <string.h>		// strlen()

#include "random.h"
#include "queue.h"
#include "ieb.h"
#include "clcd.h"
#include "utils.h"
#include "game.h"
#include "dot.h"
#include "led.h"
#include "keypad.h"
#include "player.h"
#include "mytype.h"
#include "argument.h"

int main(int argc, char* argv[]);
short * mapper(off_t offset, int prot);
void unmapper();
void emergency_closer();

error_t gameProgress();
int show_obstacle();
void error();
truth_t inputter();

#endif

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit(void);    // get Keyboard input
int _getch(void);   // implemnet getch() function in Ubuntu
int max(int a, int b);  // max function
int min(int a, int b);  // min function

#endif
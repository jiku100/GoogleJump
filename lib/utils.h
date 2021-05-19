#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit(void);
int _getch(void);
int max(int a, int b);
int min(int a, int b);


#endif
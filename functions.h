#pragma once
#ifndef _FUNCTIONS_
#define _FUNCTIONS_
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

static struct termios old, newer;

//TERMINAL SCREEN FUNCTIONS
void gotoxy(int x, int y);
void initTermios(int echo);
void resetTermios(void);
bool kbhit();

//GETTING KEYBOARD INPUTS
char getch_(int echo);
char GETCH(void);
char getche(void);

//TERMINAL SCREEAN CO-ORDINATES
int getmax_x();
int getmax_y();

#endif
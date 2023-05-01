#pragma once
#ifndef _MIDDLE_
#define _MIDDLE_
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <cmath>
#include <sstream>
#include "functions.h"

using namespace std;

//PRINTING EVERYTHING IN THE MIDDLE
int distheplay(string s, int pp);
int preprocess(string filename); 
int directdistheplay(string my_string);
void processHighscore(string highscore_title, string highscores);
void processAnimation();
#endif
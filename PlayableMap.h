//HEADER GUARDS
#pragma once
#ifndef _PLAYABLEMAP_
#define _PLAYABLEMAP_

//INCLUDES
//libs
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <thread>
#include <chrono>

//other classes
#include "GameObject.h"
#include "Pill.h"


//CONSTANTS
//map
const int MAP_WIDTH = 28;
const int MAP_HEIGHT = 31;
//points
const int LARGE_PILL = 1;
const int SMALL_PILL = 0;
const int LARGE_PILL_PTS = 100;
const int SMALL_PILL_PTS = 50;
//terminal string values
const std::string LAYOUT_SPRITE_SHEET = "PlayableMap.txt";
const std::string DEFAULT_WALL_CHAR = "▩ ";
const std::string DEFAULT_EMPTY_CHAR = "  ";
const std::string DEFAULT_HORIZ_DOOR = "══";
const std::string DEFAULT_UNKNOWN = "??";


class PlayableMap
{
    public:
        //CONSTRUCTORS
        PlayableMap();
        PlayableMap(std::vector<GameObject*> &handle);


        //DECONSTRUCTORS
        ~PlayableMap();


        //EXTERNAL MEMBER FUNCTIONS
        std::string getCharAtPos(int x, int y);
        bool IsMoveable(int x, int y, int object_type);
        std::string mapToString();
        void initPill(std::vector<GameObject*>& handle);
    private:
        //INTERNAL MEMBERS
        std::string map_layout[MAP_HEIGHT][MAP_WIDTH];
};
#endif // _PLAYABLEMAP_
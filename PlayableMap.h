//HEADER GUARDS
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
//map size
const int MAP_WIDTH = 28;
const int MAP_HEIGHT = 31;
//points point values
const int LARGE_PILL = 1;
const int SMALL_PILL = 0;
const int LARGE_PILL_PTS = 100;
const int SMALL_PILL_PTS = 50;
//terminal string values
const std::string LAYOUT_SPRITE_SHEET = "PlayableMapSprites.txt";
const std::string PILL_SPRITE_SHEET = "PillSprites.txt";
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
        //returns the map character at a particular x,y coordinate on map
        std::string getCharAtPos(int x, int y);
        //checks if the x,y coordinate on map is a wall/door
        bool IsMoveable(int x, int y, int object_type);
        //loads the textfile into the array of strings and dynamically allocated Pills and stores the pointer in handle
        void initPill(std::vector<GameObject*>& handle);
    private:
        //INTERNAL MEMBERS
        //the 2D array containing the characters at each index. -> use string array to support unicode.
        std::string map_layout[MAP_HEIGHT][MAP_WIDTH];
};
#endif // _PLAYABLEMAP_
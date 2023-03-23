#pragma once
#ifndef _PLAYABLEMAP_
#define _PLAYABLEMAP_

#include <string>
#include <fstream>
#include <iostream>

const int MAP_WIDTH = 28;
const int MAP_HEIGHT = 31;

const std::string LAYOUT_SPRITE_SHEET = "PlayableMap.txt";
const std::string DEFAULT_WALL_CHAR = "▩ ";
const std::string DEFAULT_EMPTY_CHAR = "  ";
const std::string DEFAULT_HORIZ_DOOR = "══";
const std::string DEFAULT_UNKNOWN = "??";


class PlayableMap
{
    public:
        PlayableMap();
        ~PlayableMap();
        std::string getCharAtPos(int x, int y);
        bool IsMoveable(int x, int y);
        std::string mapToString();
    private:
        std::string map_layout[MAP_HEIGHT][MAP_WIDTH];
};

#endif // _PLAYABLEMAP_
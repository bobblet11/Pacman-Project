#pragma once
#ifndef _SCREEN_
#define _SCREEN_

#include <string>
#include <iostream>
#include <vector>
#include "ncurses.h"
#include "Character.h"
#include "PlayableMap.h"
#include <unistd.h>
#include <thread>
#include <chrono>
const std::string  BORDER_VERT = "║║";
const std::string  BORDER_HORIZ = "══";
const std::string  BORDER_CORNER_TL = "##";
const std::string  BORDER_CORNER_TR = "##";
const std::string  BORDER_CORNER_BL = "##";
const std::string  BORDER_CORNER_BR = "##";
const std::string  BORDER_EMPTY = "  ";

class Screen
{
    public:
        //constructors and deconstructors
        Screen (int width, int height, PlayableMap & map);
        ~Screen();

        //getters
        int getHeight();
        int getWidth();

        //render functions
        void render(std::vector<GameObject*> &handle);

    private:
        //member variables
        int width,height;
        std::string** frame;
        PlayableMap map_ptr;

        //render functions
        void resetFrame();
        void printCurrentFrame(std::vector<GameObject*> &handle);
};
#endif // _SCREEN_
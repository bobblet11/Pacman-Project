#ifndef _SCREEN_
#define _SCREEN_

//includes
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <thread>
#include <chrono>
#include "ncurses.h"
#include "PlayableMap.h"


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
        Screen();
        ~Screen();

        //getters
        int getHeight();
        int getWidth();

        //render functions
        void render(std::vector<GameObject*> &handle);

    private:
        //member variables
        int width,height; //height and width of the rendered screen
        std::string** frame; //pointer to a pointer for a 2D dynamic array of strings containing each rendered char at a x.y coordinate 
        PlayableMap map_ptr; //pointer to the map object

        //render functions
        void resetFrame(); //resets the frame array to default values
        void printCurrentFrame(std::vector<GameObject*> &handle); //prints the frame, and all gameObjects
};
#endif // _SCREEN_
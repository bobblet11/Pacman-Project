#pragma once
#ifndef _GHOSTS_Y_
#define _GHOSTS_Y_

#include "Ghosts.h"

class YellowGhost: public Ghosts
{
    public:
        YellowGhost(std::string,int,int,int obj_type, PlayableMap & map);
        ~YellowGhost();
        void handleState();
        void Chase(); //red chase
        void Scatter() ; //red scatter
        void Freightened(); //red freightened     
    private:
        int move_counter = 0;
        int scatter_counter = 0;
};

#endif
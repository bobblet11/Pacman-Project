#pragma once
#ifndef _GHOSTS_R_
#define _GHOSTS_R_

#include "Ghosts.h"

class RedGhost: public Ghosts
{
    public:
        RedGhost(std::string,int,int,int obj_type, PlayableMap &map);
        ~RedGhost();
        void handleState();
    private:
        int move_counter = 0;
        int scatter_counter = 0;
        void RandomMove();
        void Chase(); //red chase
        void Scatter() ; //red scatter
        void Freightened(); //red freightened     
};
#endif
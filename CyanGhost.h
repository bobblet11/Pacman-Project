#pragma once
#ifndef _GHOSTS_C_
#define _GHOSTS_C_

#include "Ghosts.h"

class CyanGhost: public Ghosts
{
    public:
        CyanGhost(std::string,int,int,int obj_type, PlayableMap &map);
        ~CyanGhost();
        void handleState();
        void Chase(); //red chase
        void Scatter() ; //red scatter
        void Freightened(); //red freightened     
    private:
        int move_counter = 0;
        int scatter_counter = 0;
};

#endif
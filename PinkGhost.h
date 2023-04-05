#pragma once
#ifndef _GHOSTS_P_
#define _GHOSTS_P_

#include "Ghosts.h"

class PinkGhost: public Ghosts
{
    public:
        PinkGhost(std::string,int,int,int obj_type);
        ~PinkGhost();
        void handleState();
        void Chase(); //red chase
        void Scatter() ; //red scatter
        void Freightened(); //red freightened     
    private:
        int move_counter = 0;
        int scatter_counter = 0;
};

#endif
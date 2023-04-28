//HEADER GUARD
#pragma once
#ifndef _PILL_
#define _PILL_

//INCLUDES
#include "GameObject.h"

class Pill: public GameObject
{
    private:
        //PILL MEMBERS
        int points;
    public:
        //EXTERNAL FUNCTIONS
        int getPoints();

        //CONSTRUCTOR
        Pill(std::string sprite_sheet, int posX, int posY, int obj_type, int pill_type, int pill_point);
        //DECONSTRUCTORS
        ~Pill();

};

#endif /*_PILL_*/

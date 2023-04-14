
#pragma once
#ifndef _PILL_
#define _PILL_

#include "GameObject.h"
#include "PlayableMap.h"
#include <string>

class Pill: public GameObject
{
private:
    int pill_point;
public:
    int getPoints();
    Pill(std::string sprite_sheet, int posX, int posY, int obj_type, int pill_type, int pill_point);
    ~Pill();

};

#endif /*_PILL_*/

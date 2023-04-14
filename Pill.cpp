#include "Pill.h"

Pill:: Pill(std::string sprite_sheet, int posX, int posY, int obj_type,int pill_type, int pill_point)
:GameObject(sprite_sheet, posX, posY, obj_type)
{
    this->pill_point = pill_point;
    setState(pill_type);
}

Pill:: ~Pill()
{

}

int Pill:: getPoints()
{
    return pill_point;
}

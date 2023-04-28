#include "Pill.h"
//CONSTRUCTOR
Pill:: Pill(std::string sprite_sheet, int posX, int posY, int obj_type,int pill_type, int pill_point)
:GameObject(sprite_sheet, posX, posY, obj_type)
{
    this->points = pill_point;
    setState(pill_type);
}


//DECONSTRUCTOR
Pill:: ~Pill()
{

}


//EXTERNAL MEMBER FUNCTIONS
int Pill:: getPoints()
{
    return points;
}

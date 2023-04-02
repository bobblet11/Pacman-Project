#include "Pill.h"

Pill:: Pill(std::string sprite_sheet, int posX, int posY, int colour_f, int colour_b, int obj_type,int pill_type, int pill_point)
:GameObject(sprite_sheet, posX, posY, colour_f,colour_b, obj_type)
{
    this->pill_point = pill_point;
    setState(pill_type);
}

Pill:: ~Pill()
{

}

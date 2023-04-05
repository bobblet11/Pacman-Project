#include "Ghosts.h"
Ghosts::Ghosts(std::string sprite_sheet,int posX,int posY,int obj_type)
:GameObject(sprite_sheet, posX, posY, obj_type)
{

}

Ghosts::~Ghosts()
{

}

void Ghosts::move(int delta_x, int delta_y)
{
    x += delta_x;
    y += delta_y;
}

void Ghosts:: handleState()
{
}

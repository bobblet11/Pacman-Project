#include "YellowGhost.h"

YellowGhost::YellowGhost(std::string sprite_sheet,int posX, int posY, int obj_type)
:Ghosts(sprite_sheet, posX, posY, obj_type)
{

}

YellowGhost::~YellowGhost()
{

}

void YellowGhost:: Chase()
{

}
void YellowGhost::Scatter()
{
    //if in position for scatter movement, ie in one of the SCATTER POSITIONS
        //SCATTER
    //else try pathfind to a scatter position
    if (move_counter == 0)
    {
        int new_X = SCATTER_PATTERN_Y[scatter_counter][0], new_Y = SCATTER_PATTERN_Y[scatter_counter][1];
        x = new_X + 1;
        y = new_Y + 1;
        scatter_counter++;
        scatter_counter%=34;
    }
    move_counter ++;
    move_counter%=FRAMES_PER_MOVE;
}
void YellowGhost::Freightened()
{

}

void YellowGhost:: handleState()
{
    Scatter();
}
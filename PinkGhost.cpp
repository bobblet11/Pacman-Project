#include "PinkGhost.h"

PinkGhost::PinkGhost(std::string sprite_sheet,int posX, int posY, int obj_type, PlayableMap& map)
:Ghosts(sprite_sheet, posX, posY, obj_type, map)
{

}

PinkGhost::~PinkGhost()
{

}

void PinkGhost:: Chase()
{

}
void PinkGhost::Scatter()
{
    //if in position for scatter movement, ie in one of the SCATTER POSITIONS
        //SCATTER
    //else try pathfind to a scatter position
    if (move_counter == 0)
    {
        int new_X = SCATTER_PATTERN_P[scatter_counter][0], new_Y = SCATTER_PATTERN_P[scatter_counter][1];
        x = new_X + 1;
        y = new_Y + 1;
        scatter_counter++;
        scatter_counter%=18;
    }
    move_counter ++;
    move_counter%=FRAMES_PER_MOVE;
}
void PinkGhost::Freightened()
{

}

void PinkGhost:: handleState()
{
    Scatter();
}
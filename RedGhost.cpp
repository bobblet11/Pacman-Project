#include "RedGhost.h"

RedGhost::RedGhost(std::string sprite_sheet,int posX, int posY, int obj_type,PlayableMap &map)
:Ghosts(sprite_sheet, posX, posY, obj_type, map)
{

}

RedGhost::~RedGhost()
{

}

void RedGhost:: Chase() //there is the issue of corners and also not true randomenss.
{
    srand((int) time(0));
    int move_Directions[4][3] = {0,0,0};
    int Directions[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}; 
    int counter = 0, reverse_direc = (current_direction == LEFT_G) ? RIGHT_G : (current_direction == RIGHT_G) ? LEFT_G : (current_direction == UP_G) ? DOWN_G : UP_G;

    if (move_counter == 0)
    {
        for (int i=0; i<4;i++)
        { 
            //check which direcion is moveable
            if(map.IsMoveable((Directions[i][0])+(this->x)-1 , (Directions[i][1])+(this->y)-1) && i != reverse_direc)
            {
                move_Directions[counter][0] = (Directions[i][0])+(this->x);
                move_Directions[counter][1] = (Directions[i][1])+(this->y);
                move_Directions[counter][2] = i; // direction
                counter++;
            }
        }
 
        int random_choice = rand()%((counter -1) + 1);
        this->x = move_Directions[random_choice][0];
        this->y = move_Directions[random_choice][1];
        this->current_direction = move_Directions[random_choice][2];
        move_counter ++;
        move_counter%=FRAMES_PER_MOVE;
    }
    else
    {
        move_counter ++;
        move_counter%=FRAMES_PER_MOVE;
    }
 

}
void RedGhost::Scatter()
{
    //if in position for scatter movement, ie in one of the SCATTER POSITIONS
        //SCATTER
    //else try pathfind to a scatter position
    if (move_counter == 0)
    {
        int new_X = SCATTER_PATTERN_R[scatter_counter][0], new_Y = SCATTER_PATTERN_R[scatter_counter][1];
        x = new_X + 1;
        y = new_Y + 1;
        scatter_counter++;
        scatter_counter%=18;
    }
    move_counter ++;
    move_counter%=FRAMES_PER_MOVE;
}
void RedGhost::Freightened()
{

}

void RedGhost:: handleState()
{
    Chase();
}
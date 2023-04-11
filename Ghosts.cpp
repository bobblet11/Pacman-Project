#include "Ghosts.h"
Ghosts::Ghosts(std::string sprite_sheet,int posX,int posY,int obj_type, PlayableMap map)
:GameObject(sprite_sheet, posX, posY, obj_type)
{
    this->map = map;
}

Ghosts::~Ghosts()
{

}

void Ghosts::move(int delta_x, int delta_y)
{
    x += delta_x;
    y += delta_y;
}

void Ghosts:: handleState(GameObject* charac_obj_ptr)
{
    Chase(charac_obj_ptr);
}

void Ghosts::Chase(GameObject* player)
{ if (object_type == 4)
    {
        //red
        
    }
    else if(object_type == 5)
    {
        //yellow
    }
    else if(object_type == 6)
    {
        //pink
    }
    else
    {
        //cyan
    }
    srand((int) time(0));
    int pos, length = 1000;
    int chase_prob = (object_type == 4) ? ghost_chase_prob_R : (object_type == 5) ? ghost_chase_prob_Y : (object_type == 6) ? ghost_chase_prob_P : ghost_chase_prob_C;
    int move_Directions[4][3] = {-1,-1,-1};
    int Directions[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}; 
    int counter = 0, reverse_direc = (current_direction == LEFT_G) ? RIGHT_G : (current_direction == RIGHT_G) ? LEFT_G : (current_direction == UP_G) ? DOWN_G : UP_G;
    if (move_counter == 0)
    {
        //calculate the shortest direction to move
        for (int i =0; i<4;i++)
        {
            if (map.IsMoveable(Directions[i][0] + x - 1, Directions[i][1] + y - 1) && i != reverse_direc)
            {
                move_Directions[counter][0] = Directions[i][0] + x;
                move_Directions[counter][1] = Directions[i][1] + y;
                move_Directions[counter][2] = i;

                if (abs(Directions[i][0] + x - player->getX()) + abs(Directions[i][1] + y - player->getY()) < length)
                {
                    length = abs(Directions[i][0] + x - player->getX()) + abs(Directions[i][1] + y - player->getY());
                    pos = counter;
                }
                counter++;
            }
            
        }

        //do a probability check
        bool choose_shortest_path = rand()%100<=chase_prob;
        //move towards which ever selected path
        if (choose_shortest_path)
        {
            x = move_Directions[pos][0];
            y = move_Directions[pos][1];
            current_direction = move_Directions[pos][2];
        }
        else
        {
            int random_choice = rand()%(counter);
            x = move_Directions[random_choice][0];
            y = move_Directions[random_choice][1];
            current_direction = move_Directions[random_choice][2];
        }
    }
    move_counter ++;
    move_counter%=FRAMES_PER_MOVE;
}

void Ghosts::Scatter()
{
    if (move_counter == 0)
    {
        //chase to the 0th scatter position
        //if the ghost is in scatter and has not visted scatter 0th yet, move to it
        //otherwise, if it has been at scatter 0, iterate through scatter pattern.
        
        int new_X, new_Y;
        if (object_type == 4)
        {
            //red
            new_X = SCATTER_PATTERN_R[scatter_counter][0];
            new_Y = SCATTER_PATTERN_R[scatter_counter][1];
            scatter_counter++;
            scatter_counter%=18;
        }
        else if(object_type == 5)
        {
            //yellow
            new_X = SCATTER_PATTERN_Y[scatter_counter][0];
            new_Y = SCATTER_PATTERN_Y[scatter_counter][1];
            scatter_counter++;
            scatter_counter%=34;
        }
        else if(object_type == 6)
        {
            //pink
            new_X = SCATTER_PATTERN_P[scatter_counter][0];
            new_Y = SCATTER_PATTERN_P[scatter_counter][1];
            scatter_counter++;
            scatter_counter%=18;
        }
        else
        {
            //cyan
            new_X = SCATTER_PATTERN_C[scatter_counter][0];
            new_Y = SCATTER_PATTERN_C[scatter_counter][1];
            scatter_counter++;
            scatter_counter%=34;
        }
        x = new_X + 1;
        y = new_Y + 1;
        
    }
    move_counter ++;
    move_counter%=FRAMES_PER_MOVE;
}
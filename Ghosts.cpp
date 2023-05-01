#include "Ghosts.h"
//CONSTRUCTOR
//sprite_sheet is the file name for the txt where ghost sprites are stored.
// posX,posY are the starting coordinates
// object type is the type this object represents, ie which colour ghost
// map is a reference to the map.
Ghosts::Ghosts(std::string sprite_sheet,int posX,int posY,int obj_type, PlayableMap & map)
:GameObject(sprite_sheet, posX, posY, obj_type)
{
    this->map = map;
}
//DECONSTRUCTOR
Ghosts::~Ghosts()
{

}

//EXTERNAL FUNCTIONS
void Ghosts:: handleState(GameObject* charac_obj_ptr, int & gameState,bool & freigtened, int & freightened_timer)
{
    //Scatter for 7 seconds, then Chase for 20 seconds.
    //Scatter for 7 seconds, then Chase for 20 seconds.
    //Scatter for 5 seconds, then Chase for 20 seconds.
    //Scatter for 5 seconds, then switch to Chase mode permanently.

    if (this->x == charac_obj_ptr->getX() && this->y == charac_obj_ptr->getY())
    {
        if (freigtened == false)
        {
            gameState = 3;
        }else
        {
            charac_obj_ptr->setPoints(charac_obj_ptr->getPoints() + 500);
            reached_scatter_start = false;
            Resting();
        }
    }

    if (freigtened == true)
    {
        Freightened(freigtened, charac_obj_ptr, freightened_timer);
        timer =0;
        colour = 3;
        return;
    }else
    {
        colour = object_type;
    }

    timer++;
    if (charac_obj_ptr->getPoints() < 3000) //easy difficulty
    {
        if (object_type == 5 || object_type == 6)
        {
            Resting();
            reached_scatter_start = false;
        }
        else
        {
            //scatter chase loop
            if (chaseCounter>3) //permanent chase
            {

                ghost_chase_prob_Y = 80;
                ghost_chase_prob_P = 45;
                ghost_chase_prob_C = 30;
                ghost_chase_prob_R = 100;
                Chase(charac_obj_ptr);
            }
            else if(timer /60 <=7) //if timer < 7
            {
                Scatter();
            }
            else if (timer/60 > 7 && timer/60 <= 27) //if timer < 27 ie 20 seconds after 
            {
                Chase(charac_obj_ptr);
            }
            else //reset timer
            {
                timer =0;
                chaseCounter++;
                reached_scatter_start = false;
            }
        }
        current_speed = FRAMES_PER_MOVE;
    }
    else if (charac_obj_ptr->getPoints() < 5000 && charac_obj_ptr->getPoints() > 3000) //medium diff
    {
        if (switchState == 0)
        {
            chaseCounter =0;
            timer=0;
            switchState = 1;
            ghost_chase_prob_Y = 55;
            ghost_chase_prob_P = 75;
            ghost_chase_prob_C = 55;
            ghost_chase_prob_R = 100;
            reached_scatter_start = false;
        }


        //scatter loop 
        if (chaseCounter>3)
        {//PERMANENT CHASE
            ghost_chase_prob_Y = 60;
            ghost_chase_prob_P = 100;
            ghost_chase_prob_C = 60;
            ghost_chase_prob_R = 100;
            Chase(charac_obj_ptr);
        }//SCATTER PERIOD
        else if(timer /60 <=7)
        {
            Scatter();
        }//CHASE PERIOD
        else if (timer/60 > 7 && timer/60 <= 27)
        {
            Chase(charac_obj_ptr);
        }//RESET CYCLE UP TO 3 times
        else
        {
            timer =0;
            chaseCounter++;
            reached_scatter_start = false;
        }
        current_speed = FRAMES_PER_MOVE-2;
    }
    else if (charac_obj_ptr->getPoints() > 5000 && charac_obj_ptr->getPoints() < 8000) //harder
    {
        ghost_chase_prob_Y = 55;
        ghost_chase_prob_P = 100;
        ghost_chase_prob_C = 55;
        ghost_chase_prob_R = 100;
        //permanent chase
        Chase(charac_obj_ptr); 
        current_speed = FRAMES_PER_MOVE-4;
        reached_scatter_start = false;
    }
    else // hardest
    {
        ghost_chase_prob_Y = 65;
        ghost_chase_prob_P = 100;
        ghost_chase_prob_C = 65;
        ghost_chase_prob_R = 100;
        //permanent chase
        Chase(charac_obj_ptr); 
        current_speed = FRAMES_PER_MOVE-7; 
        reached_scatter_start = false;
    }
}


//GHOST BEHAVIOURS
//player is a pointer towards the player object
void Ghosts::Chase(GameObject* player) // will move towards the player position
{ 
    //determines whihc probability to use corresponding to ghost colour
    int chase_prob = (object_type == 4) ? ghost_chase_prob_R : (object_type == 5) ? ghost_chase_prob_Y : (object_type == 6) ? ghost_chase_prob_P : ghost_chase_prob_C;
    //if timing to move is correct move
    if (move_counter == 0)
    {   
        //if the ghost is still in the box, move towards the exit
        if (checkIfInBox())
        {
            Pathfind(LEAVE_BOX_X, LEAVE_BOX_Y,75);
        }
        else //otherwise, move towards the player.
        {
            Pathfind(player->getX(), player->getY(), chase_prob);
        }
       
    }
    //increments the move counter every frame.
    move_counter ++;
    move_counter%=(current_speed);
}
//freightened is a bool for whether the ghosts are in freightened state
//player is pointer to player gameobject
//freightened_timer is the duration for ghosts to be in freightened state
//handles ghosts behaviour when freightened
void Ghosts::Freightened(bool & freigtened, GameObject* player, int & freightened_timer)
{
    //if the ghost is currently in freightened state and timer has hit 0
    if (freightened_timer <= 0)
    {   
        //reset probabilities of ghosts
        ghost_chase_prob_R = 100;
        ghost_chase_prob_Y = 55;
        ghost_chase_prob_P = 20;
        ghost_chase_prob_C = 20;
        //set freightened to false so that chase is used instead
        freigtened = false;
        return;
    }
    else
    {
        //set chase probabilities so that ghosts always move away from player
        ghost_chase_prob_Y = 0;
        ghost_chase_prob_P = 0;
        ghost_chase_prob_C = 0;
        ghost_chase_prob_R = 0;
        //chase player -> but will actually run away from player
        Chase(player);
        //increase speed
        current_speed=FRAMES_PER_MOVE+2;
        //decrement the timer so that freightended only lasts the amount of time in the freightened_timer variable
        freightened_timer -= 1;
    }
}
//handles the scatter behaviour
void Ghosts::Scatter()
{
    //first sees which scatter position to use coresponding to ghost colour
    int scatter_start_x = (object_type == 4) ? ghost_scatter_start_Rx : (object_type == 5) ? ghost_scatter_start_Yx : (object_type == 6) ? ghost_scatter_start_Px : ghost_scatter_start_Cx;
    int scatter_start_y = (object_type == 4) ? ghost_scatter_start_Ry : (object_type == 5) ? ghost_scatter_start_Yy : (object_type == 6) ? ghost_scatter_start_Py : ghost_scatter_start_Cy;
    //if the ghost is currently at the scatter position, or has reached it, then set to true
    if (this->x == scatter_start_x + 1 && this->y == scatter_start_y + 1)
    {
        reached_scatter_start = true;
    }

    //if the ghost has not yet reached the scatter start position
    if (reached_scatter_start == false)
    {
        //move towards starting position using Pathfind
        if (move_counter == 0)
        {
            if (checkIfInBox())
            {
                Pathfind(LEAVE_BOX_X, LEAVE_BOX_Y,75);
            }
            else
            {
                Pathfind(scatter_start_x + 1, scatter_start_y + 1,75);
            }
        }
    }
    else //otherwise if the ghost has already reached the starting scatter position before
    {
        //choose the next position the scatter path corresponding to ghost colour
        int divisor=0, new_X = 0, new_Y = 0;
        if (object_type == 4)
        {
            //red
            new_X = SCATTER_PATTERN_R[scatter_counter][0];
            new_Y = SCATTER_PATTERN_R[scatter_counter][1];
            divisor = 18;
        }
        else if(object_type == 5)
        {
            //yellow
            new_X = SCATTER_PATTERN_Y[scatter_counter][0];
            new_Y = SCATTER_PATTERN_Y[scatter_counter][1];
            divisor = 34;
        }
        else if(object_type == 6)
        {
            //pink
            new_X = SCATTER_PATTERN_P[scatter_counter][0];
            new_Y = SCATTER_PATTERN_P[scatter_counter][1];
            divisor = 18;
        }
        else
        {
            //cyan
            new_X = SCATTER_PATTERN_C[scatter_counter][0];
            new_Y = SCATTER_PATTERN_C[scatter_counter][1];
            divisor = 34;
        }

        //if timed to move, move to next scatter position
        if (move_counter == 0)
        {
            moveToNewPos(new_X + 1,new_Y + 1);
            scatter_counter++;
            scatter_counter%=divisor;
        }
    }
    move_counter++;
    move_counter%=current_speed;

}
//sets the position of ghosts to the spawn area box
void Ghosts::Resting()
{
    x = 14;
    y = 15;
}


//AUXILLARY FUNCTIONS
//target_x,target_y is the coordinates that the Ghost is chasing
//chase_prob is the probability that the ghost will move towards the targert
//chase_prob of 0 means it will never move towards
//chase_prob of 100 means it will always move towards
//Pathfind calculates direction to move towards target
void Ghosts::Pathfind(int target_x,int target_y, int chase_prob)
{
    //sets random seed to the current time
    srand((int) time(0));
    //initialises ints to a abritary large value
    int pos, length = 1000;

    //array of ints containing all possible coordinates to move in
    int move_Directions[4][3] = {};
    //array containing the possible directions to move in
    int Directions[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}; 
    int counter = 0, reverse_direc = (current_direction == LEFT_G) ? RIGHT_G : (current_direction == RIGHT_G) ? LEFT_G : (current_direction == UP_G) ? DOWN_G : UP_G;
    
    //calculate the shortest direction to move
    for (int i =0; i<4;i++)
    {
        //if the direction is a valid one ie not in reverse direction and is not a wall.
        if (map.IsMoveable(Directions[i][0] + x - 1, Directions[i][1] + y - 1, object_type) && i != reverse_direc)
        {
            //add the coordinate to list of possible directions
            move_Directions[counter][0] = Directions[i][0] + x;
            move_Directions[counter][1] = Directions[i][1] + y;
            move_Directions[counter][2] = i;
            
            //if the new coordinate brings the ghost closer to target, save the position of this direction
            if (abs(Directions[i][0] + x - target_x) + abs(Directions[i][1] + y - target_y) < length)
            {
                length = abs(Directions[i][0] + x - target_x) + abs(Directions[i][1] + y - target_y);
                pos = counter;
            }
            counter++;
        }
        
    }

    //if there is only one direction, ie not at a junction, move towards it.
    if (counter == 1)
    {
        moveToNewPos(move_Directions[0][0],move_Directions[0][1]);
        current_direction = move_Directions[0][2];
        return;
    }

    //otherwise, if there is list of directions to move in,

    //make a array of directions that arent the shortest path towards target
    int other_directions[4][3] = {-1,-1,-1}, count = 0;
    for (int i=0;i<counter;i++)
    {
        if (i!=pos)
        {
            other_directions[count][0] = move_Directions[i][0];
            other_directions[count][1] = move_Directions[i][1];
            other_directions[count][2] = move_Directions[i][2];
            count++;
        }
        
    }

    //if the probability check passes, then the ghost will move towards the target
    bool choose_shortest_path = rand()%100<=chase_prob;
    //move towards which ever selected path
    if (choose_shortest_path)
    {
        moveToNewPos(move_Directions[pos][0],move_Directions[pos][1]);
        current_direction = move_Directions[pos][2];
    }
    else //otherwise choose one of the other coordinates in other_directions randomly to move in
    {
        int random_choice = rand()%(count);
        moveToNewPos(other_directions[random_choice][0],other_directions[random_choice][1]);
        current_direction = other_directions[random_choice][2];
    }
}

//checks if the ghost is in the bounds of the spawn box
bool Ghosts::checkIfInBox()
{
    if (x > 11 && x < 18 && y > 13 && y < 17)
    {
        return true;
    }
    return false;
}

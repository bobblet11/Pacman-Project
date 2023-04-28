#include "Character.h"

//CONSTRUCTOR
Character::Character(std::string sprite_sheet, int screen_width, int screen_height, PlayableMap& map, int posX, int posY, int obj_type)
:GameObject(sprite_sheet, posX, posY, obj_type), screen_height(screen_height), screen_width(screen_width), map(map)
{
    if(!map.IsMoveable(posX-1,posY-1, object_type))
    {
        std::cout << "Invalid haracter starting coordinates" << std::endl;
        exit(-1);
    }
    setState(DEFAULT);
}

//DECONSTRUCTOR
Character::~Character()
{
}

//EXTERNAL MEMBER FUNCTIONS
void Character::handleCharacterMove(std::vector<GameObject*> & handle , int & character_index, bool & freightened)
{
    if (selectGetch()) //CHECK IF THERE IS A KEY IN QUEUE
    {
        char input = getch();
        if (input != last_input) //CHECK IF THE DIRECTION OF CHARACTER HAS CHANGED
        {
            last_input = input;
            move_count=0;
        }
    }
    moveCharacter(handle,character_index, freightened);
    move_count++;
    move_count%=MOVE_SPEED;
}
void Character :: updateAnimationState()
{
    // std::cout << "UPDATE ANIM CHARACTER " << std::endl;
    if (anim_counter < ANIMATION_DURATION)
        {
            setState(DEFAULT); //default state
        }
    else
        {
            setState(current_direction);
        }
    anim_counter++;
    anim_counter%=(ANIMATION_DURATION*2);

}

//INTERNAL MEMBER FUNCTIONS
int Character :: selectGetch()
{
    int input = getch();
    if (input != ERR) //CHECKS IF VALID KEY HAS BEEN PRESSED
    {
        ungetch(input); //PLACES THE INPUT BACK INTO THE QUEUE
        return 1;
    }
    else
    {
        return 0;
    }
}
void Character::moveCharacter(std::vector<GameObject*> & handle, int & character_index, bool & freightened) //actually moves the character 
{
    int moveY = (last_input == 'w') ? -1 : (last_input == 's') ? 1 : 0;
    int moveX = (last_input == 'd') ? 1 : (last_input == 'a') ? -1 : 0;

    int new_pos_X = moveX + x; 
    int new_pos_Y = moveY + y; 

    current_direction = (moveX==1) ? RIGHT : (moveX==-1) ? LEFT : (moveY==-1) ? UP : (moveY==1) ? DOWN : current_direction;

    if (map.IsMoveable(new_pos_X-1,new_pos_Y-1, object_type))
    {
        if (move_count == 0)
        {
            moveToNewPos(new_pos_X,new_pos_Y);
        }

        //BINARY SEARCH FOR PILL
        int length = handle.size()-1,pivot=0,start=0;
        while (true)
        {
            pivot = ((length-start)+1/2);
            for (int i = start; i < pivot;i++)
            {
                //CHECK IF PLAYER AND PILL COLLIDE
                if (handle.at(i)->object_type == 3 && handle.at(i)->getX() == x  && handle.at(i)->getY() == y)
                {
                    //SET PLAYER POINTS TO CURRENT VALUE + PILL VALUE
                    setPoints(getPoints() + handle.at(i)->getPoints());

                    //IF THE PILL WAS A SUPER PILL, SET GHOST STATE TO FREIGHTENED
                    if (handle.at(i)->getPoints() == 100)
                    {
                        freightened = true;
                    }

                    //DEALLOCATE THE PILL OBJECT MEMORY
                    delete handle.at(i);
                    //REMOVE POINTER
                    handle.erase(handle.begin()+i);
                    character_index-=1;
                    break;
                }
            }
            length -= pivot;
            start = pivot;

            if (length <=0)
            {
                break;
            }
        }
    }
}
int Character:: getPoints()
{
    return points;
}
void Character :: setPoints(int x)
{
    this->points = x;
}



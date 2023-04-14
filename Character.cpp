#include "Character.h"


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


Character::~Character()
{
}


void Character::handleCharacterMove(std::vector<GameObject*> & handle ,int & character_index)
{
    // std::cout << "CHARACTER MOVE" << std::endl;
    if (selectGetch()) //there is an actual key available in getch() queue
    {
        char input = getch();
        if (input != last_input) // new direction
        {
            last_input = input;
            move_count=0;
        }
    }
    moveCharacter(handle,character_index);
    move_count++;
    move_count%=MOVE_SPEED;
}


void Character::moveCharacter(std::vector<GameObject*> & handle, int & character_index) //actually moves the character 
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
                if (handle.at(i)->object_type == 3 && handle.at(i)->getX() == x  && handle.at(i)->getY() == y)
                {
                    points += handle.at(i)->getPoints();
                    //player has hit a pill
                    delete handle.at(i);
                    //removes the pointer
                    handle.erase(handle.begin()+i);
                    // std::cout << handle.size()<<std::endl;
                    // std::cout << character_index<<std::endl;
                    character_index-=1;
                    // std::cout << character_index<<std::endl;
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

int Character :: selectGetch()
{
    int input = getch();
    if (input != ERR)
    {
        ungetch(input); // places the char back into the input queue for next getch call.
        return 1;
    }
    else
    {
        return 0;
    }
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

int Character:: getPoints()
{
    return points;
}



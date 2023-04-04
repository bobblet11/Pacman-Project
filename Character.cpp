#include "Character.h"


Character::Character(std::string sprite_sheet, int screen_width, int screen_height, PlayableMap& map, int posX, int posY, int obj_type)
:GameObject(sprite_sheet, posX, posY, obj_type), screen_height(screen_height), screen_width(screen_width), map(map)
{
    if(!map.IsMoveable(posX-1,posY-1))
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
        input = getch();
        if (input == last_input) // moving in one direction
        {
            if (ERR_count > BUTTON_MASH_CONSTANT) //singular press, case where the time between each button press is large enough to not be considered holding down
            {
                move_count=0;
                moveCharacter(handle,character_index);
            }
            else //if holding down
            {
                if (move_count == 0)
                {
                    moveCharacter(handle,character_index);
                }
                move_count++;
                move_count%=MOVEDELAY;
            }
        }
        else //changing direction
        { 
            moveCharacter(handle,character_index);
        }
        ERR_count = 0;
        last_input = input;
    }
    else //if the getch is an ERR
    {
        ERR_count++;
    }
}


void Character::moveCharacter(std::vector<GameObject*> & handle, int & character_index) //actually moves the character 
{
    int moveY = (input == 'w') ? -1 : (input == 's') ? 1 : 0;
    int moveX = (input == 'd') ? 1 : (input == 'a') ? -1 : 0;
    int new_pos_X = moveX + getX(); 
    int new_pos_Y = moveY + getY(); 

    current_direction = (moveX==1) ? RIGHT : (moveX==-1) ? LEFT : (moveY==-1) ? UP : (moveY==1) ? DOWN : current_direction;

    if (map.IsMoveable(new_pos_X-1,new_pos_Y-1) && (new_pos_X < screen_width-1 &&  new_pos_X > 0 && new_pos_Y < screen_height-1 &&  new_pos_Y > 0 ))
    {
        setX(new_pos_X);
        setY(new_pos_Y);


        //BINARY SEARCH FOR PILL
        int length = handle.size()-1,pivot=0,start=0;
        while (true)
        {
            pivot = ((length-start)+1/2);
            for (int i = start; i < pivot;i++)
            {
                if (handle.at(i)->object_type == 3 && handle.at(i)->getX() == x  && handle.at(i)->getY() == y)
                {
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


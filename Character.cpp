#include "Character.h"

Character::Character(std::string sprite_sheet, int screen_width, int screen_height, PlayableMap& map, int posX, int posY, int colour_f, int colour_b)
:GameObject(sprite_sheet, posX, posY, colour_f,colour_b), screen_height(screen_height), screen_width(screen_width), map(map)
{
    std::cout << "Character constructor invoked" << std::endl;
    std::cout << "Current state index :"<< current_state_index << std::endl;
    std::cout << animation_sprites.at(current_state_index) << std::endl;
    if(!map.IsMoveable(posX-1,posY-1))
    {
        std::cout << "Invalid haracter starting coordinates" << std::endl;
        exit(-1);
    }

    setState(DEFAULT);
}


Character::~Character()
{
    std::cout << "Character deconstructor invoked" << std::endl;
    std::cout << "Current state index :"<< current_state_index << std::endl;
    std::cout << animation_sprites.at(current_state_index) << std::endl;
}

void Character::handleCharacterMove()
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
                moveCharacter();
            }
            else //if holding down
            {
                if (move_count == 0)
                {
                    moveCharacter();
                }
                move_count++;
                move_count%=MOVEDELAY;
            }
        }
        else //changing direction
        { 
            moveCharacter();
        }
        ERR_count = 0;
        last_input = input;
    }
    else //if the getch is an ERR
    {
        ERR_count++;
    }
}


void Character::moveCharacter() //actually moves the character 
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

void Character :: printCharacterAtPosition()
{
	// wattron(stdscr,COLOR_PAIR(10));
    mvprintw(y,x*2, "%s", getCurrentSprite().c_str());
    // wattroff(stdscr,COLOR_PAIR(10));
}
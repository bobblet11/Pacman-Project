#pragma once
#ifndef _CHARACTER_
#define _CHARACTER_

#include "GameObject.h"
#include "PlayableMap.h"
#include "ncurses.h"

const int DEFAULT =0, RIGHT = 1, DOWN = 2, LEFT = 3, UP = 4; // animation indexes
const int ANIMATION_DURATION = 30; //number of frames for each idle state animation
const int MOVEDELAY = 3;//the number of frames that equals to 1 mvoement when holding down, ie speed of character when holding down
const int BUTTON_MASH_CONSTANT = 6; //number of frames between key presses to count as holding down


class Character : public GameObject
{
    public:
        Character(std::string sprite_sheet, int screen_width, int screen_height, PlayableMap& map, int posX, int posY, int colour_f, int colour_b, int obj_type);
        ~Character();

        virtual void updateAnimationState();
        virtual void handleCharacterMove(std::vector<GameObject*> & handle,int & character_index);
        virtual void printCharacterAtPosition();

    private:
        int anim_counter=0;
        int move_count=0;
        int current_direction=0;
        int screen_width, screen_height;
        PlayableMap map;
        void moveCharacter(std::vector<GameObject*> & handle,int & character_index);

        int ERR_count;
        char input,last_input;

        int selectGetch();

        int CHARACTER_FORE_COLOUR;
        int CHARACTER_BACK_COLOUR; 
        

};


#endif // _CHARACTER_
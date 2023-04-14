#pragma once
#ifndef _CHARACTER_
#define _CHARACTER_

#include "GameObject.h"
#include "PlayableMap.h"
#include "ncurses.h"

const int DEFAULT =0, RIGHT = 1, DOWN = 2, LEFT = 3, UP = 4; // animation indexes
const int ANIMATION_DURATION = 9; //number of frames for each idle state animation
const int MOVE_SPEED = 9;//the number of frames that equals to 1 mvoement when holding down, ie speed of character when holding down
#define PACMAN_COLOUR 1

class Character : public GameObject
{
    public:
        Character(std::string sprite_sheet, int screen_width, int screen_height, PlayableMap& map, int posX, int posY, int obj_type);
        ~Character();
        virtual void updateAnimationState();
        virtual void handleCharacterMove(std::vector<GameObject*> & handle,int & character_index);
        int getPoints();
    private:
        int anim_counter=0;
        int move_count=0;
        int current_direction=0;
        int screen_width, screen_height;
        PlayableMap map;
        void moveCharacter(std::vector<GameObject*> & handle,int & character_index);

        char last_input;

        int points= 0;

        int selectGetch();
};


#endif // _CHARACTER_
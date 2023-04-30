//HEADER GUARD
#pragma once
#ifndef _CHARACTER_
#define _CHARACTER_

//INCLUDES
#include "GameObject.h"
#include "PlayableMap.h"
#include "ncurses.h"

//CONSTANTS
const int DEFAULT =0, RIGHT = 1, DOWN = 2, LEFT = 3, UP = 4;   //animation index
const int ANIMATION_DURATION = 9;                              //number of frames for each idle state animation
const int MOVE_SPEED = 9;                                      //the number of frames that equals to 1 mvoement when holding down, ie speed of character when holding down
const int PACMAN_COLOUR = 1;                                   //colour pair for pacman

class Character : public GameObject
{
    public:
        //CONSTRUCTORS
        Character(std::string sprite_sheet, int screen_width, int screen_height, PlayableMap& map, int posX, int posY, int obj_type);
        //DECONSTRUCTORS
        ~Character();
        
        //EXTERNAL MEMBER FUNCTIONS
        virtual void updateAnimationState();
        virtual void handleCharacterMove(std::vector<GameObject*> & handle,int & character_index,bool & freightened);
    
        virtual int getPoints();
        virtual void setPoints(int x);

    private:
        //CHARACTER MEMBERS
        int points= 0;

        int anim_counter=0;
        int move_count=0;
        int current_direction=0;

        int screen_width, screen_height;
        PlayableMap map;

        int last_input;
        int selectGetch();

        //CHARACTER MEMBER FUNCTIONS
        void moveCharacter(std::vector<GameObject*> & handle,int & character_index,bool & freightened);

      
};


#endif // _CHARACTER_
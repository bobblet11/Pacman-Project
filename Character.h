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
        void updateAnimationState(); //sets the current sprite to the current index
        //calls all interal functions to move the character
        void handleCharacterMove(std::vector<GameObject*> & handle,int & character_index,bool & freightened, int & freightened_timer);
    
        int getPoints(); //retreives the points of this Character
        void setPoints(int new_points); //sets the points value of this Character

    private:
        //CHARACTER MEMBERS
        int points= 0; //stores all points aqquired by character

        int anim_counter=0; //count of frames used to determine animation cycle of character
        int move_count=0; //count of frames used to determine speed of character
        int current_direction=0; //direction the character is facing.

        int screen_width, screen_height; //width and height of screen.
        PlayableMap map; //the map for checking if position is passable

        int last_input; //the last valid input 
        int selectGetch(); //function that will only allow keypresses to add to the getch buffer

        //CHARACTER MEMBER FUNCTIONS
        //will move the character and check for any GameObjects encountered.
        void moveCharacter(std::vector<GameObject*> & handle,int & character_index,bool & freightened,int & freightened_timer);

      
};


#endif // _CHARACTER_
//HEADER GUARDS
#pragma once
#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_


//INCLUDES
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ncurses.h>


class GameObject
{


    public:
        //CONSTRUCTORS
        GameObject(std::string,int,int, int obj_type);
        GameObject(const GameObject &t);
        virtual ~GameObject();


        //GETTERS
        std::vector<std::string> getAnimationSprites();
        int getX();
        int getY();
        int getWidth();
        int getHeight();
        int getCurrentStateIndex();
        std::string& getCurrentSprite();


        //VARIABLES
        int object_type = 0;
       
        //SETTERS
        void setState(const int state);
        void setX(const int x);
        void setY(const int y);


        //PUBLIC FUNCITONS
        void printCharacterAtPosition();


        //VIRTUALS
        virtual void updateAnimationState();
        virtual void handleCharacterMove(std::vector<GameObject*> & handle,int & character_index,bool & freightened);
        virtual void handleState(GameObject* charac_obj_ptr, int & gameState, bool&freightened);
        virtual int getPoints();
        virtual void setPoints(int x);
        
        
    protected:
        //GAMEOBJECT MEMBERS
        int x,y;
        int width, height;
        int num_of_sprite_states, current_state_index;
        std::vector<std::string> animation_sprites;
        int colour;


        //INTERNAL FUNCTIONS
        void moveToNewPos(int x,int y);
        void readSpriteSheet(std::string sprite_sheet);


};

#endif // _GAMEOBJECT_
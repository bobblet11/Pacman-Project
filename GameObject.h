#pragma once
#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_


#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ncurses.h>

class GameObject
{
    //inhertied classes will ahve built it animation states and indexes
    public:
        GameObject(std::string,int,int,int colour_f, int colour_b);    //copy constructor
        GameObject(const GameObject &t);
        virtual ~GameObject();

        //getters
        std::vector<std::string> getAnimationSprites();
        int getX();
        int getY();
        int getWidth();
        int getHeight();
        int getCurrentStateIndex();
        std::string& getCurrentSprite();

        //have a vector of game objects in the screen or main, constantly update.

        void setState(const int state);
        void setX(const int x);
        void setY(const int y);

        //virtuals
        virtual void printCharacterAtPosition();
        virtual void updateAnimationState();
        virtual void handleCharacterMove();

    protected:
        int x,y;
        int width, height;
        int CHARACTER_FORE_COLOUR;
        int CHARACTER_BACK_COLOUR; 


        int num_of_sprite_states, current_state_index;
        std::vector<std::string> animation_sprites;

        void readSpriteSheet(std::string sprite_sheet);
};

#endif // _GAMEOBJECT_
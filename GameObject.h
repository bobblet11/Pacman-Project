#pragma once
#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_


#include <string>
#include <fstream>
#include <iostream>

class GameObject
{
    //inhertied classes will ahve built it animation states and indexes
    public:
        GameObject(std::string,int,int);
        virtual ~GameObject();

        //getters
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

    protected:
        int x,y;
        int width, height;

        int num_of_sprite_states, current_state_index;
        std::string* animation_sprites;

        void readSpriteSheet(std::string sprite_sheet);
};

#endif // _GAMEOBJECT_
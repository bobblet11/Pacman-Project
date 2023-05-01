//HEADER GUARDS
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
        GameObject(std::string,int,int, int obj_type); //normal constructor
        GameObject(const GameObject &t); // copy constructor for the vector.push_back()
        virtual ~GameObject(); //deconstructor


        //GETTERS
        std::vector<std::string> getAnimationSprites(); //returns the vector containing animation sprites
        int getX(); //returns x coordinate
        int getY(); //returns y coordinate
        int getCurrentStateIndex(); //returns the index of the current animation state
        std::string& getCurrentSprite(); //returns the string that is being displayed for this GameObject


        //VARIABLES
        int object_type = 0; //object type determines what object the GameObject represents ie Character, Red Ghost, a pill
       
        //SETTERS
        void setState(const int state); //sets animation state to change the sprite displayed
        void setX(const int x); //sets the x coordinate
        void setY(const int y); //sets the y coordinate


        //PUBLIC FUNCITONS
        void printCharacterAtPosition(); //prints the current sprite at its current x,y position


        //VIRTUALS -functions defined in children class. these functions are only called by children objects
        virtual void updateAnimationState();
        virtual void handleCharacterMove(std::vector<GameObject*> & handle,int & character_index,bool & freightened, int & freightened_timer);
        virtual void handleState(GameObject* charac_obj_ptr, int & gameState, bool&freightened, int & freightened_timer);
        virtual int getPoints();
        virtual void setPoints(int x);
        
        
    protected:
        //GAMEOBJECT MEMBERS
        int x,y; //coordinates of the gameobject

        //variables to handle the sprite states and animations
        int num_of_sprite_states, current_state_index; 
        std::vector<std::string> animation_sprites; 
        
        //represents colour pair the sprite renders in
        int colour;


        //INTERNAL FUNCTIONS
        void moveToNewPos(int x,int y); //moves from current x,y to the x,y provided in arguments
        void readSpriteSheet(std::string sprite_sheet); //reads txt file and extracts sprites


};

#endif // _GAMEOBJECT_
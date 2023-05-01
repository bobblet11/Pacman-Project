#pragma once
#ifndef _GHOSTS_
#define _GHOSTS_

#include "GameObject.h"
#include "PlayableMap.h"

//the directions of the ghosts movement
const int UP_G = 0, RIGHT_G = 1, DOWN_G  = 2, LEFT_G = 3;
//the speed of the ghosts ie how many frames is required to pass before moving one space
const int FRAMES_PER_MOVE = 16; 
//the X and Y coordinates of the ghost spawn box
const int LEAVE_BOX_X = 15, LEAVE_BOX_Y = 12;

//THE FOLLOWING ARE THE PRE DETERMINED PATHS FOR GHOST SCATTER BEHAVIOUR. 
//EACH COLOUR HAS ITS OWN SCATTER PATTERN
    const int SCATTER_PATTERN_Y[34][2] = {
    {1,29},{2,29},{3,29},{4,29},{5,29},{6,29},{7,29},{8,29},{9,29},{10,29},{11,29},{12,29},    //left to right
    {12,28},{12,27},{12,26},
    {11,26},{10,26},{9,26},   
    {9,25},{9,24},{9,23}, 
    {8,23},{7,23},{6,23},
    {6,24},{6,25},{6,26},   
    {5,26},{4,26},{3,26},{2,26},{1,26},        
    {1,27},{1,28}};             

    const int SCATTER_PATTERN_R[18][2] = {
    {21,1},{22,1},{23,1},{24,1},{25,1},{26,1}, 
    {26,2},{26,3},{26,4},{26,5},                
    {25,5},{24,5},{23,5},{22,5},{21,5},          
    {21,4},{21,3},{21,2}};                        

    const int SCATTER_PATTERN_P[18][2] = {
    {1,1},{2,1},{3,1},{4,1},{5,1},{6,1},    
    {6,2},{6,3},{6,4},{6,5},                  
    {5,5},{4,5},{3,5},{2,5},{1,5},        
    {1,4},{1,3},{1,2}};                        

    const int SCATTER_PATTERN_C[34][2] = {
    {15,29},{16,29},{17,29},{18,29},{19,29},{20,29},{21,29},{22,29},{23,29},{24,29},{25,29},{26,29},    //left to right
    {26,28},{26,27},{26,26},
    {25,26},{24,26},{23,26},{22,26},{21,26},  
    {21,25},{21,24},{21,23},  
    {20,23},{19,23},{18,23},
    {18,24},{18,25},{18,26},
    {17,26},{16,26},{15,26},      
    {15,27},{15,28}};  

    
class Ghosts: public GameObject
{
    public:
        //CONSTRUCTORS
        Ghosts(std::string,int,int,int obj_type, PlayableMap & map);
        ~Ghosts();
        //CONTROLS WHICH STATE THE GHOST IS CURRENTLY IN AND THE DIFFICULTY OF GHOST AI
        void handleState(GameObject* charac_obj_ptr, int & gameState, bool & freightened, int & freightened_timer);
    
    private:
        //GHOST BEHAVIOUR: CHASES THE PLAYER
        void Chase(GameObject* charac_obj_ptr);


        //GHOST BEHAVIOUR: MOVES TO SCATTER POSITION, THEN FOLLOWS SCATTER PATTERN
        void Scatter() ;
        //the coordinates each ghost much reach before starting to follow scatter pattern
        int ghost_scatter_start_Rx = 21, ghost_scatter_start_Ry  = 1;
        int ghost_scatter_start_Px = 1, ghost_scatter_start_Py  = 1;
        int ghost_scatter_start_Cx = 16, ghost_scatter_start_Cy  = 29;
        int ghost_scatter_start_Yx = 1, ghost_scatter_start_Yy  = 29;
        int scatter_counter = 0;                   //counts frames to determine when ghost can move to next position in scatter path
        bool reached_scatter_start = false;        //determines whether the ghost has reached the starting scatter position 

        //GHOST BEHAVIOUR: MOVES AWAY FROM PLAYER
        void Freightened(bool & freigtened, GameObject* player, int&freightened_timer);
        //GHOST BEHAVIOUR: SETS POSITION TO GHOST SPAWN AREA
        void Resting();

        PlayableMap map;     //map object for checking if the position is moveable
        int current_speed=FRAMES_PER_MOVE;  //THE CURRENT SPEED OF THE GHOST
        int current_direction = -1;        //direction used to prevent ghost from moving backwards
        int move_counter = 0;        //counts frames to determine when ghost can move


        void Pathfind(int target_x,int target_y, int chase_prob); //decides the direction the ghost will move in order to move towards the target coordinates
        
        //the probabiliies that a ghost will choose a direction that follows the player
        int ghost_chase_prob_R = 100, ghost_chase_prob_Y = 55, ghost_chase_prob_P = 20, ghost_chase_prob_C = 20;
        
        int chaseCounter = 0;        //counts how many chase cycles the ghosts have been through

        bool checkIfInBox(); //checks if the ghost is within the bounds of the spawn box

        int timer=0; //timer for counting how long a ghost cycle has gone for
        int switchState=0; //used to change ghost cycles
};


#endif 

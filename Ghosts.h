#pragma once
#ifndef _GHOSTS_
#define _GHOSTS_

#include "GameObject.h"
#include "PlayableMap.h"

    //ghost system works as such
    //start - only red
    //500 points - red and blue
    //1000 points - red,blue, pink
    //1500 points - all ghosts 1.5 speed
    //2000 points - all ghosts 2 speed
    const int UP_G = 0, RIGHT_G = 1, DOWN_G  = 2, LEFT_G = 3;
    const int FRAMES_PER_MOVE = 16; //ghanges this to a global variable to allow for speed changes, ie value will decrease to diff values
    
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
        {21,1},{22,1},{23,1},{24,1},{25,1},{26,1},    //left to right
        {26,2},{26,3},{26,4},{26,5},                  //top to bot
        {25,5},{24,5},{23,5},{22,5},{21,5},           //right to left
        {21,4},{21,3},{21,2}};                        //bot to top

    const int SCATTER_PATTERN_P[18][2] = {
        {1,1},{2,1},{3,1},{4,1},{5,1},{6,1},    //left to right
        {6,2},{6,3},{6,4},{6,5},                  //top to bot
        {5,5},{4,5},{3,5},{2,5},{1,5},           //right to left
        {1,4},{1,3},{1,2}};                        //bot to top
    
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
        Ghosts(std::string,int,int,int obj_type, PlayableMap map);
        ~Ghosts();
        void handleState(GameObject* charac_obj_ptr);
    private:
        void Chase(GameObject* charac_obj_ptr);
        void Scatter() ;
        void Freightened();

        int current_speed=FRAMES_PER_MOVE;

        void move(int delta_x, int delta_y);
        int current_state = 0;
        PlayableMap map;
        int current_direction = -1;
        int move_counter = 0;
        int scatter_counter = 0;
        
        void Resting();
        bool reached_scatter_start = false;
        void Pathfind(int target_x,int target_y, int chase_prob);
        
        int ghost_chase_prob_R = 100, ghost_chase_prob_Y = 55, ghost_chase_prob_P = 20, ghost_chase_prob_C = 20;
        int ghost_scatter_start_Rx = 21, ghost_scatter_start_Ry  = 1;
        int ghost_scatter_start_Px = 1, ghost_scatter_start_Py  = 1;
        int ghost_scatter_start_Cx = 16, ghost_scatter_start_Cy  = 29;
        int ghost_scatter_start_Yx = 1, ghost_scatter_start_Yy  = 29;
};

#endif 

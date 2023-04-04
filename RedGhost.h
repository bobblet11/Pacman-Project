#include "Ghosts.h"

const int FRAMES_PER_MOVE = 10;

const int SCATTER_PATTERN[18][2] = {
{21,1},{22,1},{23,1},{24,1},{25,1},{26,1},    //left to right
{26,2},{26,3},{26,4},{26,5},                  //top to bot
{25,5},{24,5},{23,5},{22,5},{21,5},           //right to left
{21,4},{21,3},{21,2}};                        //bot to top

class RedGhost: public Ghosts
{
    public:
        RedGhost(std::string,int,int,int obj_type);
        ~RedGhost();
        void handleState();
        void Chase(); //red chase
        void Scatter() ; //red scatter
        void Freightened(); //red freightened     
    private:
        int move_counter = 0;
        int scatter_counter = 0;
};
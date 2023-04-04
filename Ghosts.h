#include "GameObject.h"
//0 = scatter
class Ghosts: public GameObject
{
    public:
        Ghosts(std::string,int,int,int obj_type);
        ~Ghosts();
        virtual void handleState();
    private:
        virtual void Chase() = 0;
        virtual void Scatter() =0;
        virtual void Freightened()=0;

        void move(int delta_x, int delta_y);
        int current_state = 0;
};
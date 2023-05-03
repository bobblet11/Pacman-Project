#include "Pill.h"
//CONSTRUCTOR
//sprite sheet is the filename for txt with sprites
//screen width,height is width,height of the box where everything is rendered.
//map is the Playable map object
//posX,posY is the starting coordinate of the Character
//obj_type is the type of Gameobject the character is -> should be set to character.
//pill_type is used to distinguish between super pills and normal pills
//pill point the points added to player when the pill is eaten.
Pill:: Pill(std::string sprite_sheet, int posX, int posY, int obj_type,int pill_type, int pill_point)
:GameObject(sprite_sheet, posX, posY, obj_type)
{
    this->points = pill_point;
    setState(pill_type);
}


//DECONSTRUCTOR
Pill:: ~Pill()
{

}


//EXTERNAL MEMBER FUNCTIONS
//returns the points this pill is worth
int Pill:: getPoints()
{
    return points; //returns the point value of the pill
}

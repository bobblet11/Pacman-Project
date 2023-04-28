#include "GameObject.h"


//CONSTRUCTORS
GameObject::GameObject(std::string sprite_sheet, int posX,  int posY, int obj_type)
:x(posX), y(posY)
{   
    object_type = obj_type;
    readSpriteSheet(sprite_sheet);
    current_state_index = 0;
}


//COPY CONSTRUCTORS
GameObject :: GameObject(const GameObject &t)
:x(t.x), y(t.y)
{
    animation_sprites =  t.animation_sprites;
    current_state_index = 0;
}


//DECONSTRUCTORS
GameObject::~GameObject()
{
}


//GETTERS
std::vector<std::string> GameObject :: getAnimationSprites()
{
    return animation_sprites;
}
int GameObject :: getX()
{
    return x;
}
int GameObject :: getY()
{
    return y;
}
int GameObject :: getWidth()
{
    return width;
}
int GameObject :: getHeight()
{
    return height;
}
std::string& GameObject :: getCurrentSprite()
{
    return animation_sprites.at(current_state_index);
}
int GameObject :: getCurrentStateIndex()
{
    return current_state_index;
}


//INTERNAL FUNCTIONS
void GameObject :: readSpriteSheet(std::string sprite_sheet)
{
    std::string line;
    std::fstream file;
    file.open(sprite_sheet);
    if (!file)
    {
        std::cout << "[ERROR] Failed to open sprite sheet." << std::endl;
        exit(1);
    }
    while(getline(file,line))
    {
        animation_sprites.push_back(line);
    }
    file.close();
}
void GameObject :: moveToNewPos(int x,int y)
{
    if (x == 29 && y == 15 )
    {
        this-> x = 1;
        this -> y = 15;
    }
    else if (x == 0 && y == 15)
    {
        this-> x = 28;
        this -> y = 15;
    }
    else
    {
        this->x = x;
        this->y = y;
    }
}

//SETTERS
void GameObject::setState(const int state)
{
    current_state_index = state;
}
void GameObject::setX(const int x)
{
    this->x = x;
}
void GameObject::setY(const int y)
{
    this->y = y;
}

//EXTERNAL FUNCTIONS
void GameObject :: printCharacterAtPosition()
{
	attron(COLOR_PAIR(object_type));
    mvprintw(y+1,x*2, "%s", getCurrentSprite().c_str());
    attroff(COLOR_PAIR(object_type));
}


//VIRTUALS (FOR CHILD CLASSES)
void GameObject :: updateAnimationState()
{
}
void GameObject :: handleCharacterMove(std::vector<GameObject*> & handle,int & character_index,bool & freightened)
{
}
void GameObject ::  handleState(GameObject* charac_obj_ptr, bool & running, bool&freightened)
{
}
void GameObject :: setPoints(int x)
{

}
int GameObject :: getPoints()
{
    return  0;
}